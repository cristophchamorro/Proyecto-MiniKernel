
#include "queue.h"
#include <stdlib.h> 
#include <stdio.h>


void init_queue(queue_t *q){
	
	q->frente = q->fin = NULL;
	q->count = 0;
	pthread_mutex_init(&q->lock, NULL);
	pthread_cond_init(&q->cond_empty, NULL);
	pthread_cond_init(&q->cond_full, NULL);
}

void enqueue(queue_t *q, pcb_t *p){
	
	pthread_mutex_lock(&q->lock);

	// 1. Se usa la segunda variable condicional: esperar si la cola esta llena 
	while(q->count >= MAX_QUEUE_SIZE){
		pthread_cond_wait(&q->cond_full, &q->lock);
	}

	// 2. Verificacion de malloc (Seguridad de la memoria)
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
       	if(new_node == NULL){
		fprintf(stderr, "Error: no se pudo asignar memoria para el nodo\n");
		pthread_mutex_unlock(&q->lock);
		return;
	}	

	new_node->process = p;
	new_node->next = NULL;

	if(q->fin == NULL){
		q->frente = q->fin = new_node;	
	} else{
		q->fin->next = new_node;
		q->fin = new_node;
	}

	q->count++;

	// Marcar que la cola ya no esta vacia 
	pthread_cond_signal(&q->cond_empty);
	pthread_mutex_unlock(&q->lock);
}

pcb_t* dequeue(queue_t *q){
	
	pthread_mutex_lock(&q->lock);

	// Se debe esperar si la cola esta vacia
	while(q->count == 0){
		pthread_cond_wait(&q->cond_empty, &q->lock);
	}

	node_t *temp = q->frente;
	pcb_t *p = temp->process;
	q->frente = q->frente->next;

	if(q->frente == NULL){
		q->fin = NULL;
	}

	q->count--;

	free(temp);  // Funcion usada para liberar memoria dinamica reservada con malloc, 
		     // ya extraido un proceso, no se necesita el nodo,  por ello se libera esa memoria

	// 3. Marcar al generador que ahora ya hay espacio (la cola no esta llena)
	pthread_cond_signal(&q->cond_full);
	pthread_mutex_unlock(&q->lock);

	return p;
}

