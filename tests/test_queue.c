#include <stdio.h>
#include <assert.h>
#include "queue.h"

int main() {
	   
       	queue_t q;
	init_queue(&q);
	
	pcb_t p1 = {.pid = 1, .burst_time = 10};
	pcb_t p2 = {.pid = 2, .burst_time = 5};

	printf("Ejecutando pruebas de la cola...\n");

	enqueue(&q, &p1);
	enqueue(&q, &p2);
	assert(q.count == 2);
	printf("- Inserción correcta (count=2)\n");

	pcb_t *out = dequeue(&q);
	assert(out->pid == 1);
	printf("- Extracción correcta (PID 1 primero)\n");

	assert(q.count == 1);
	printf("Todas las pruebas de la cola pasaron exitosamente.\n");
	
	return 0;
}
