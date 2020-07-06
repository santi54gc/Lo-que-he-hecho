#ifndef _LETRAS_H_
#define _LETRAS_H_

#define CARACTER_ANCHO 6
#define CARACTER_ALTO 6

extern const int caracter_a[7][2];
extern const int caracter_b[12][2];
extern const int caracter_c[4][2];
extern const int caracter_d[7][2];
extern const int caracter_e[7][2];
extern const int caracter_f[6][2];
extern const int caracter_g[7][2];
extern const int caracter_h[6][2];
extern const int caracter_i[6][2];
extern const int caracter_j[4][2];
extern const int caracter_k[6][2];
extern const int caracter_l[3][2];
extern const int caracter_m[5][2];
extern const int caracter_n[4][2];
extern const int caracter_o[5][2];
extern const int caracter_p[5][2];
extern const int caracter_q[9][2];
extern const int caracter_r[7][2];
extern const int caracter_s[6][2];
extern const int caracter_t[4][2];
extern const int caracter_u[4][2];
extern const int caracter_v[3][2];
extern const int caracter_w[5][2];
extern const int caracter_x[5][2];
extern const int caracter_y[5][2];
extern const int caracter_z[4][2];

extern const int caracter_0[5][2];
extern const int caracter_1[2][2];
extern const int caracter_2[6][2];
extern const int caracter_3[7][2];
extern const int caracter_4[5][2];
extern const int caracter_5[6][2];
extern const int caracter_6[5][2];
extern const int caracter_7[3][2];
extern const int caracter_8[7][2];
extern const int caracter_9[5][2];

extern const int caracter_derecha[5][2];
extern const int caracter_izquierda[5][2];
extern const int caracter_arriba[5][2];
extern const int caracter_abajo[5][2];

extern const int caracter_espacio[1][2];

/*Esta funcion recibe un caracter y un puntero a size_t. La funcion devuelve una variable del tipo const int** que corresponde al vector asociado al caracter dentro del diccionario definido. A su vez devuelve por interfaz la cantidad de coordenadas del vector.*/
const int** letra_a_vector(char letra, size_t* cc);	
	
/*Este procedimiento recibe una cadena de caracteres, un entero llamado factor y dos flotantes. Este procedimiento dibuja una palabra en la interfaz grafica de SDL2 multiplicada por el factor en una posicion (inicial_x,inicial_y)*/
void dibujar_letras(SDL_Renderer *renderer,char palabra[],int factor, float inicial_x, float inicial_y);

/*Este procedimiento recibe un numero, un entero llamado factor y dos flotantes. Este procedimiento dibuja un numero en la interfaz grafica de SDL2 multiplicado por el factor en una posicion (inicial_x,inicial_y). El numero dibujado consta de 4 cifras que en caso de no tenerlas se dibuja alineado a la derecha completando con ceros*/
void dibujar_numero(SDL_Renderer *renderer,int numero, size_t factor, float inicialx, float inicialy);
#endif // _LETRAS_H_
