// Este archivo cumple la funcion de integrar todas las funciones y 
// componentes anteriormente creados 


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "queue.h"
#include "sync.h"
#include "metrics.h"

#define N_CPUS 3    // Numero de CPUs simuladas


pthread_mutex_t metrics_lock;


extern void* cpu_worker(void* arg);
extern void* metrics_thread(void* arg);


void* process_generator(void* arg){
	
	queue_t *ready_queue = (queue_t*)arg;
	int next_pid = 1; 
	srand(time(NULL));

	while(1){

		// Como primer paso, duerme un tiempo aleatorio entre 1 y 3 segundos
		sleep((rand() % 3) + 1);

		// Como segundo paso, se crea un nuevo proceso (PCB)
		pcb_t *new_pcb = (pcb_t*)malloc(sizeof(pcb_t));
		if(new_pcb == NULL) continue;

		// Como tercer paso, se asigna atributos aleatorios
		new_pcb->pid = next_pid++;
		new_pcb->burst_time = (rand() % 10) + 1;
		new_pcb->remaining_time = new_pcb->burst_time;
		new_pcb->arrival_time = (int)time(NULL);
		new_pcb->state = 0;  // Estado del proceso como Listo
	
		printf("[Generador] Nuevo Proceso PID %d creado (Burst: %d)\n", new_pcb->pid, new_pcb->burst_time);

		// Como cuarto paso, se inserta el proceso en la cola de listos
		enqueue(ready_queue, new_pcb);
	}
	return NULL;
}

int main(){
	
	pthread_t generator_tid, metrics_tid;
	pthread_t cpu_threads[N_CPUS];		 // Hilos para representar las CPUs
	queue_t ready_queue;

	printf("Iniciando MiniKernel con %d CPUs (Algoritmo Round Robin)...\n", N_CPUS);

	// Se inicializan los recursos y la sincronizacion
	init_queue(&ready_queue);
	init_metrics();
	pthread_mutex_init(&metrics_lock, NULL);

	// Se lanza el hilo Generador de Procesos
	pthread_create(&generator_tid, NULL, process_generator, &ready_queue);

	// Se lanzan los hilos de CPUs simuladas
	for (int i = 0; i < N_CPUS; i++){
		pthread_create(&cpu_threads[i], NULL, cpu_worker, &ready_queue);
	}

	// Se lanza el hilo de Metricas
	pthread_create(&metrics_tid, NULL, metrics_thread, NULL);

	// Se espera a que los hilos terminen (en esta simulacion corren indefinidamente)
	pthread_join(generator_tid, NULL);
	for(int i = 0; i <N_CPUS; i++){
		pthread_join(cpu_threads[i], NULL);
	}
	pthread_join(metrics_tid, NULL);

	return 0;

}


