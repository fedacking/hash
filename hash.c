#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "hash.h"

#define CAPACIDAD_INICIAL 10

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
struct hash {
	lista_t** tabla;
	size_t cantidad;
	size_t capacidad;
	hash_destruir_dato_t destruir_dato;
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
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {

	hash_t* tabla_hash = malloc(sizeof(hash_t));

	if (!tabla_hash) {
		return NULL;
	}

	tabla_hash->tabla = malloc(CAPACIDAD_INICIAL * sizeof(lista_t*));

	if (!tabla_hash->tabla){
		free(tabla_hash);
		return NULL;
	}

	for (int i = 0; i < CAPACIDAD_INICIAL; i++) {
		tabla_hash->tabla[i] = lista_crear();
	}
	
	tabla_hash->cantidad = 0;
	tabla_hash->capacidad = CAPACIDAD_INICIAL;
	tabla_hash->destruir_dato = destruir_dato;
	
	return tabla_hash;

}

size_t hash_cantidad(const hash_t *hash) {
	return hash->cantidad;
}


/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/
