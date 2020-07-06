#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include "config.h"
#include "naves.h"
#include "funcionesTP01.h"
#include "caracteres.h"


#define DT 1.0/JUEGO_FPS


		
int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Lunar Lander");

	int dormir = 0;

	// BEGIN código del alumno
	srand(time(NULL));

	size_t terreno_tam = 0;
	float** terreno = crear_terreno(&terreno_tam);
		if(terreno == NULL){
			return EXIT_FAILURE;
		}
	
	size_t nave_tam = sizeof(nave_grande) / sizeof(nave_grande[0]);
	float **nave = matriz_a_vector(nave_grande,nave_tam);
		if(nave == NULL){
			destruir_vector(terreno, terreno_tam, 2);
			return EXIT_FAILURE;
		}
	
	const float chorro_grande[3][2] = {
		{-NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y},
		{0, NAVE_GRANDE_TOBERA_Y},
		{NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y}
	};

	float** chorro = matriz_a_vector(chorro_grande, 3);
		if(chorro == NULL){
			destruir_vector(terreno, terreno_tam, 2);
			destruir_vector(nave, nave_tam, 2);
			return EXIT_FAILURE;
		}

	double x = 0, y = 0, 
	vx = NAVE_VX_INICIAL, vy = NAVE_VY_INICIAL, 
	angulo = NAVE_ANGULO_INICIAL, 
	fuel = JUEGO_COMBUSTIBLE_INICIAL,
	altitude = NAVE_Y_INICIAL,
	time = 0;

	int potencia = NAVE_POTENCIA_INICIAL,
	score = 0;
	
	// END código del alumno

	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						
						if(potencia == NAVE_MAX_POTENCIA)
							potencia = NAVE_MAX_POTENCIA;
						else potencia += 1;

						if(chorro[1][1] == 4 * NAVE_GRANDE_TOBERA_Y)
							chorro[1][1] = 4 * NAVE_GRANDE_TOBERA_Y;
						else chorro[1][1] -= 1;

						break;

					case SDLK_DOWN:

						if(potencia == 0)
							potencia = 0;
						else potencia -= 1;

						if(chorro[1][1] == NAVE_GRANDE_TOBERA_Y)
							chorro[1][1] = NAVE_GRANDE_TOBERA_Y;
						else chorro[1][1] += 1;

						break;

					case SDLK_RIGHT:

						if(angulo > -NAVE_ANGULO_INICIAL + NAVE_ROTACION_PASO){
							angulo -= NAVE_ROTACION_PASO;
							fuel -= JUEGO_COMBUSTIBLE_RADIANES * NAVE_ROTACION_PASO;
						}

						break;

					case SDLK_LEFT:

						if(angulo < NAVE_ANGULO_INICIAL - NAVE_ROTACION_PASO){
							angulo += NAVE_ROTACION_PASO;
							fuel -= JUEGO_COMBUSTIBLE_RADIANES * NAVE_ROTACION_PASO;		
						}

						break;

				}
				// END código del alumno


			}
			continue;
		}
	
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


		// BEGIN código del alumno
		
		dibujar(renderer, terreno, 0,  0, terreno_tam);

		float** nave_aux = pedir_memoria(nave_tam, 2);
			if(nave_aux == NULL) 
				break;
			
		copiar_vector(nave, nave_aux, nave_tam);

		float** chorro_aux = pedir_memoria(3, 2);
			if(chorro_aux == NULL){
				destruir_vector(nave_aux, nave_tam, 2);
				break;
			}
	
		copiar_vector(chorro, chorro_aux, 3);

		double ax = -potencia * sin(angulo);

		double ay = potencia * cos(angulo) - G;
		
		vx = computar_velocidad(vx, ax, DT);
		
		vy = computar_velocidad(vy, ay, DT);
		
		x = computar_posicion(x, vx, DT);

		y = computar_posicion(y, vy, DT);
		

		rotar(nave_aux, nave_tam, angulo);
		rotar(chorro_aux, 3, angulo);

		trasladar(nave_aux, nave_tam, x, y);
		trasladar(chorro_aux, 3, x, y);

		dibujar(renderer, nave_aux, NAVE_X_INICIAL,  NAVE_Y_INICIAL, nave_tam);
		dibujar(renderer, chorro_aux, NAVE_X_INICIAL,  NAVE_Y_INICIAL, 3);

		destruir_vector(nave_aux, nave_tam, 2);
		destruir_vector(chorro_aux, 3, 2);
	
		altitude = 100 - y - y_correspondiente(terreno, NAVE_X_INICIAL + x, terreno_tam);
		fuel -= JUEGO_COMBUSTIBLE_POT_X_SEG * potencia * DT;

	
		dibujar_letras(renderer, "SCORE", 2, 200, 775);
		dibujar_letras(renderer, "TIME", 2, 200, 760);
		dibujar_letras(renderer, "FUEL", 2, 200, 745);
		dibujar_letras(renderer, "ALTITUDE", 2, 500, 775);
		dibujar_letras(renderer, "HORIZONTAL SPEED ", 2, 500, 760);
		dibujar_letras(renderer, "VERTICAL SPEED", 2, 500, 745);

		dibujar_numero(renderer, score, 2, 300, 775);
		dibujar_numero(renderer, abs(time), 2, 300, 760);
		dibujar_numero(renderer, abs(fuel), 2, 300, 745);
		dibujar_numero(renderer, abs(altitude), 2, 700, 775);
		dibujar_numero(renderer, abs(vx), 2, 700, 760);
		dibujar_numero(renderer, abs(vy), 2, 700, 745);


		if(vx >= 0) dibujar_letras(renderer, ">", 1, 750, 760);

		else dibujar_letras(renderer, "<", 1, 750, 760);

		if(vy >= 0)dibujar_letras(renderer,"^", 1, 750, 745);

		else dibujar_letras(renderer,"~", 1, 750, 745);


		if(!esta_arriba(terreno,terreno_tam,NAVE_X_INICIAL+x,NAVE_Y_INICIAL+y-13)){

			if(abs(vx) < 1 && abs(vy) < 10 && angulo < 0.01){

				score += 50;
				dibujar_letras(renderer,"YOU HAVE LANDED", 4, 400, 600);
			}

			else if(abs(vx) < 2 && abs(vy) < 20 && angulo < 0.01){

				score += 15;
				dibujar_letras(renderer,"YOU LANDED HARD", 4, 400, 600);
			}

			else{

				score += 5;
				fuel -= 250;
				dibujar_letras(renderer, "DESTROYED", 4, 400, 600);
			}

			x = 0;
			y = 0;
	   		vx = NAVE_VX_INICIAL;
			vy = NAVE_VY_INICIAL; 
			angulo = NAVE_ANGULO_INICIAL; 
			potencia = NAVE_POTENCIA_INICIAL;
			chorro[1][1] = NAVE_GRANDE_TOBERA_Y;

			destruir_vector(terreno, terreno_tam, 2);

			dormir = 2000;

			terreno = crear_terreno(&terreno_tam);
				if(terreno == NULL){

					break;
				}		
		}

		if(fuel < 0){

			printf("Your score is %04i!\n", score);

		break;

		}
		if(NAVE_X_INICIAL+x>VENTANA_ANCHO) x=0;

		else if(NAVE_X_INICIAL+x<0) x=750;

		time += DT;

		// END código del alumno


        	SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	// BEGIN código del alumno
	destruir_vector(nave, nave_tam, 2);

	destruir_vector(chorro, 3, 2);

	destruir_vector(terreno, terreno_tam, 2);

	// END código del alumno

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}


