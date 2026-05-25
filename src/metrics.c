// Este archivo es necesario para el desarrollo de como medir el rendimiento del scheduler

#include "metrics.h"
#include "sync.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>


metrics_t stats;
time_t start_time;


void init_metrics(){

	stats.total_procesos_completos = 0;
	stats.total_tiempo_respuesta = 0.0;
	stats.prom_tiempo_respuesta = 0.0;
	stats.throughput = 0.0;
	start_time = time(NULL); 		// Registra el inicio de la simulacion
}


void update_metrics(int arrival_time){

	// El tiempo actual menos el de inicio da como resultado el tiempo relativo de la simulacion
	int current_sim_time = (int)time(NULL);
	int response_time = current_sim_time - arrival_time;

	if(response_time < 0) response_time = 0;  // Validacion para evitar tiempos negativos

	stats.total_procesos_completos++;
	stats.total_tiempo_respuesta += response_time;

	if(stats.total_procesos_completos > 0){
		stats.prom_tiempo_respuesta = stats.total_tiempo_respuesta / stats.total_procesos_completos;
	}
}


void* metrics_thread(void* arg){
	
	while(1){
		
		sleep(5);

		pthread_mutex_lock(&metrics_lock);

		time_t now = time(NULL);
		double elapsed = difftime(now, start_time);

		if(elapsed > 0){
			stats.throughput = (double)stats.total_procesos_completos / elapsed;
		}

		printf("\n---------Estadisticas del MiniKernel---------\n");
		printf("Procesos completados:       %d\n", stats.total_procesos_completos);
		printf("Tiempo de Respuesta Promedio:  %.2f seg\n", stats.prom_tiempo_respuesta);
		printf("Throughput (Rendimiento):    %.2f proc\n", stats.throughput);
		printf("------------------------------------------------");
		
		pthread_mutex_unlock(&metrics_lock);
	}
	return NULL;
}
