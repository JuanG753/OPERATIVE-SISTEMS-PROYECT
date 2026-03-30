CC = gcc
CFLAGS = -Wall -Wextra -pthread -I./variables -I./procesos
TARGET = main
SOURCES = main.c variables/globales.c procesos/agentes.c procesos/brazo.c procesos/drones.c

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run:
	./$(TARGET)

refrigerados:
	./$(TARGET) -refrigerados

ultradelicados:
	./$(TARGET) -ultradelicados