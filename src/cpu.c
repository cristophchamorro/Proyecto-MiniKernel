// Este archivo es usado para implementar la logica de las CPUs simuladas. 
// Estas CPUs deben tomar procesos de la cola de listos, ejecutar un quantum, actualizar
// los estados del proceso y realizar el context switch, con la politica Round Robin

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "sync.h"
#include "metrics.h"


void* cpu_worker(void* arg){
	
	queue_t *ready_queue = (queue_t*)arg;

	while(1){
	
		// Como primero paso, se toma un proceso de la cola de listos 
		pcb_t *p = dequeue(ready_queue);
		
		printf("[CPU] ejecutando Proceso con PID: %d (Tiempo restante: %d)\n", p->pid, p->remaining_time);

		// Como segundo paso, se ejecuta por un Quantum o el tiempo restante (lo que sea menor) 
		int run_time = (p->remaining_time < QUANTUM) ? p->remaining_time : QUANTUM;

		// Se simula la ejecucion 
		sleep(run_time);

		p->remaining_time -= run_time;

		// Como tercer paso, se verifica si el proceso ha terminado o necesita volver a la cola (Round Robin)
		if(p->remaining_time > 0){
			printf("[CPU] Context Switch: Proceso %d vuelve a la cola\n", p->pid);
			enqueue(ready_queue, p);	// Se vuelva a insertar al final de la cola  
		} else{
			printf("[CPU] Proceso %d finalizado\n", p->pid);

			// Como cuarto paso, se actualizan metricas globalmente de forma segura 
			pthread_mutex_lock(&metrics_lock);
			update_metrics(p->arrival_time);
			pthread_mutex_unlock(&metrics_lock);

			// Como ultimo paso, se libera la memoria del PCB ya que ha terminado 
			free(p);
		}
	}
	return NULL;
}
