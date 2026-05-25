// Este archivo representa los mecanismos y funciones que usa el el hilo de 
// Metricas para medir y reportar el rendimiento del Scheduler (RR)

#ifndef METRICS_H
#define METRICS_H

#include <time.h>

/* Esta estructura junta todos los parametros que el hilo de Metricas debe 
 * calcular y reportar */
typedef struct {

	int total_procesos_completos;	// Contador de cuantos procesos terminaron de ejecutarse 
	double total_tiempo_respuesta;	// Es una suma total de todos los tiempos de respuesta de cada proceso
	double prom_tiempo_respuesta;	// Es el promedio del tiempo de respuesta 
	double throughput;		// Representa la cantidad de procesos que han sido completados en cierto tiempo
} metrics_t;


// Funciones
 
void init_metrics();				// Inicializa los contadores y acumuladores en cero
void update_metrics(int tiempo_respuesta);	// Toma los datos del PCB y actualiza totales globales 
void report_metrics();				// Funcion principal que ejecuta el hilo de Metricas 

#endif
