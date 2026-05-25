# Variables del compilador
CC = gcc	
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lpthread

# Archivos y directorios
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/queue.c $(SRC_DIR)/cpu.c $(SRC_DIR)/metrics.c
OBJS = $(SRCS:.c=.o)
TARGET = minikernel

# Regla por defecto: compilar el ejecutable
all: $(TARGET)
	
# Enlace del ejecutable final
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilación de archivos objeto (.o) desde el código fuente (.c)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos temporales y el ejecutable
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

# Regla para ejecutar el programa una vez compilado
run: all
	./$(TARGET)
# Regla para compilar y correr pruebas
test: src/queue.o tests/test_queue.c
	$(CC) $(CFLAGS) src/queue.o tests/test_queue.c -o tests/test_queue $(LDFLAGS)
	./tests/test_queue
