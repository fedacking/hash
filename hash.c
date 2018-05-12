#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "hash.h"

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
struct hash {
	lista_t** tabla;
	size_t cantidad;
	size_t capacidad;
	void destruir_dato(void*);
};

struct hash_campos{
	char* clave;
	void* dato;
};

struct hash_iter {
	size_t pos;
	const hash_t* hash;
	lista_iter_t* iter_actual;
};


/* ******************************************************************
 *                			HASH FUNCTION
 * *****************************************************************/
//One-at-a-time hash

unsigned long funcion_hash(const char* clave, size_t capacidad) {
  unsigned char *p = clave;
  unsigned h = 0;

  for (int i=0; i<capacidad; i++) {
	  h += p[i];
	  h += (h << 10);
	  h ^= (h >> 6);
  }

  h += (h << 3);
  h ^= (h >> 11);
  h += (h << 15);

  return h%capacidad;
}




/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/


