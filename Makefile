# Variables
CC = gcc  # Define el compilador a usar, en este caso gcc para C.
CFLAGS = `pkg-config --cflags gtk+-3.0`  # Opciones de compilación para incluir las cabeceras de GTK+ 3.0.
LDFLAGS = `pkg-config --libs gtk+-3.0`  # Opciones de enlace para incluir las bibliotecas de GTK+ 3.0.
LMFLAGS= -lm  # Opciones de enlace para incluir la biblioteca matemática estándar de C.
TARGET = exe  # Nombre del archivo ejecutable que se generará.
SOURCE = proyecto1.c  # Nombre del archivo fuente para el primer proyecto.
SOURCE_= proyecto2.c  # Nombre del archivo fuente para el segundo proyecto.
GLADE = tic_tac_toe.glade  # Archivo de interfaz de usuario de Glade para GTK+.


all: p1 p2  # Objetivo predeterminado que compila ambos proyectos.


p1: $(TARGET)  # Compila el primer proyecto generando el ejecutable definido en TARGET.

# Reglas para ejecutar proyecto1.c
$(TARGET): $(SOURCE) 
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)  # Compila el archivo fuente $(SOURCE) con las opciones de compilación y enlace definidas.

# Reglas para ejecutar proyecto2.c
p2: 
	$(CC) -o $(TARGET) $(SOURCE_) $(LMFLAGS)  # Compila el segundo proyecto, sobrescribiendo el ejecutable $(TARGET) con las opciones de enlace $(LMFLAGS).

# Borra los archivos generados por la compilación.
clean:
	rm -f $(TARGET) *.o *.dat *.png *.gnuplot # Elimina el ejecutable, archivos objeto, y archivos generados.


.PHONY: all p1 clean  # Declara all, p1, y clean como objetivos ficticios.