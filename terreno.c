#include "funcionesTP01.c"
#include "config.h"

float ** crear_terreno ( size_t * n ) {
* n = 0;

const float terreno_estatico [][2]={
{0 , 100} ,
{ -1 , VENTANA_ALTO * 2.0 / 3} ,
{ VENTANA_ANCHO , 100}
};


size_t nt = 3;
float ** terreno = matriz_a_vector ( terreno_estatico , nt ) ;
if ( terreno == NULL ) return NULL ;

terreno [1][0] = rand () % VENTANA_ANCHO ;


for ( size_t i = 1; i < 30; i ++) {
float ** aux = densificar_vector ( terreno , nt , 2 * ( i + 5) , 100 / i ) ;
destruir_vector ( terreno , nt , 2) ;
if ( aux == NULL ) return NULL ;
terreno = aux ;
nt = 2 * ( i + 5) ;
}
* n = nt ;
return terreno ;
}
