// Este archivo se centra en las herramientas de sincronizacion que 
// permiten al MiniKernel evitar condiciones de carrera


#ifndef SYNC_H
#define SYNC_H

#include <pthread.h>

/* Estas herramientas dan seguridad al momento de acceder a los recursos
 * compartidos, como la cola de procesos y las metricas*/

// Mutex se usa para proteger el acceso a las variables globales de las metricas

extern pthread_mutex_t metrics_lock;	// extern indica que metrics_lock existe, y reserva memoria en otro archivo 

// Se define una constante para el quantum (que es el tiempo maximo de CPU por cada proceso)

#define QUANTUM 2

#endif

