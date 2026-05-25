// Este archivo contiene todos los parametros que representan la estructura 
// de un proceso en el MiniKernel, representa al Bloque de Control de Proceso

#ifndef PCB_H
#define PCB_H

typedef struct {

	int pid;		// Identificador del proceso
	int burst_time;		// Es el tiempo total en el que el proceso necesita CPU	
	int remaining_time;	// Es el tiempo que le falta por ejecutar al proceso 
	int priority;		// Representa el valor de la prioridad del proceso 
	int arrival_time;	// Es el tiempo en el que el proceso entra a la cola de listos
	int state;		// Representa el estado actual del proceso
} pcb_t;

#endif
