// Este archivo define la cola de Procesos Listos, donde los procesos entran y 
// la CPU los toma para ejecutarlos 

#ifndef QUEUE_H
#define QUEUE_H

#include "pcb.h"	// Se incluye este archivo, ya que la cola va a almacenar estructuras de tipo pcb_t
#include <pthread.h>	// Se incluye esta libreria para los hilos y herramientas de sincronizacion 

#define MAX_QUEUE_SIZE 10 // Capacidad maxima de la cola 

/* En un sistema operativo no se sabe cuantos procesos exactamente se van a tener,
 * es por eso que se usa una lista enlazada, la cual se compone de nodos. Entonces, 
 * cada nodo guarda un puntero a un proceso y la direccion del siguiente nodo en la fila */

typedef struct node {
	
	pcb_t *process;
	struct node *next;
} node_t;

/* Estructura de la Cola de Procesos Listos con Sincronizacion (Como es compartida, 
 * entonces se debe usar mutex para evitar las condiciones de carrera, asegurando 
 * que solo un hilo a la vez toque la cola. Ademas, se usa una variable condicional
 * para que la CPU no siga usando recursos si la cola esta vacia, y se despierte solo 
 * cuando ingrese un nuevo proceso, practicamente para que espere) */

typedef struct {

	node_t *frente;			// Es un puntero al inicio de la cola
	node_t *fin;			// Es un puntero al final de la cola
	int count;			// Contador actual de procesos

	// Mutex para la cola, ya sea para insertar o extrar un PCB 
	pthread_mutex_t lock;		// Se usa Mutex para exclusion mutua (evitar condiciones de carrera)

	// Variables condicionales 
	pthread_cond_t cond_empty;	// Para que las CPUs esperen si no hay procesos
	pthread_cond_t cond_full;	// Para que el Generador espere si la cola esta llena
} queue_t;

/* Funciones para manejar la cola*/

void init_queue(queue_t *q);		// Inicializa punteros de cola en null, prepara el mutex y variable condicional
void enqueue(queue_t *q, pcb_t *p);	// Inserta un proceso al final de la cola 
pcb_t* dequeue(queue_t *q);		// Extrae un proceso del inicio

#endif

