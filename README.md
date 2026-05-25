* Descripcion breve del Proyecto del MiniKernel

Este miniKernel es un mini sistema operativo que simula la ejecucion de procesos 
concurrentes y la planificacion de CPU. El sistema ha sido desarrollado en C y POSIX, 
el cual utiliza hilos para generar procesos, simular el funcionamiento de las 
CPUs y reportar estadisticas del rendimiento del algoritmo de scheduling

* Componentes Principales del proyecto
   
El sistema esta compuesto de los siguientes componentes:
    1. Generador de procesos: Este hilo se encarga de crear procesos basados en la estructura PCB asignando 
    ciertos intervalos de tiempo (burst_time) y tiempos de llegada (arrival_time) que son aleatorios
    2. Cola de Procesos: Estructura de datos compartida y protegida mediante mutex y variables condicionales
    para garantizar la integridad de los datos entre hilos.
    3. CPUs simuladas: Es un conjunto de hilos (cpu_threads) que extraen procesos de la cola de listos, ejecutan 
    un quantum, actualizan el estado del proceso y realizan el context switch.
    4. Metricas: Es un hilo independiente que genera reportes de rendimiento, calculando el tiempo de respuesta y 
    throughput. 

* Estructura del Repositorio

El repositorio creado sigue la misma logica o disposicion expuesta en el documento del proyecto:
Dentro de la carpeta principal Minikernel se incluye:
    1. inlude/ : Contiene las cabeceras (pcb.h, queue.h, metrics.h, sync.h)
    2. src/ : Contiene la implementacion logica (main.c, queue.c, cpu.c, metrics.c)
    3. tests/ : Carpeta que sera usada para la creacion de las pruebas 
    4. Makefile : Archivo especifico para automatizar la compilacion y ejecucion del proyecto
    5. README.md : Explicacion y descripcion del proyecto

* Instrucciones de uso

Para compilar y ejecutar el sistema en Ubuntu de WSL, se deben usar los siguiente comandos en la terminal:
    1. Para compilar: escribir 'make'
    2. Para ejecutar la simulacion: escribir './minikernel' o 'make run'
    3. Para ejecutar las pruebas: escribir 'make test'
    4. Para terminar con la ejecucion del proyecto: ejecutar 'Ctrl + C'
    5. Para limpiar archivos: escribir 'make clean'


