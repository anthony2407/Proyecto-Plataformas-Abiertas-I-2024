# Proyecto C - IE-0117 Programación Bajo Plataformas Abiertas

## Universidad de Costa Rica | Escuela de Ingeniería Eléctrica

### Integrantes del grupo:
- Antony Medina Garcia
- Arley Grijalba Gutierrez


## Descripción General

Este proyecto consta de dos partes:

1. **Juego de Tik Tak Toe (Gato)**
2. **Graficado de Funciones Cuadráticas con Error Esperado**

Ambos programas se deben desarrollar en Ubuntu 18.04 LTS, 20.04 LTS, o 22.04 LTS y deben ser compilados utilizando un Makefile.

## Requisitos

- GTK-3
- Glade
- Gnuplot u otra biblioteca de graficación

## Instrucciones de Compilación y Ejecución

### Parte 1: Tik Tak Toe (Gato)

1. **Descripción:**
   - Juego de Gato con interfaz gráfica utilizando GTK-3 y diseñado con Glade.
   - 9 botones en una plantilla 3x3 que cambian su imagen a X o O al ser presionados.
   - El juego termina cuando hay tres figuras consecutivas del mismo tipo y muestra un mensaje de victoria o empate.

2. **Compilación:**
   ```bash
   make p1

### Parte 2: Graficado de Funciones Cuadráticas con Error Esperado

1. **Descripción:**
   - Programa que recibe dos funciones cuadráticas y un porcentaje de error.
   - Encuentra el subdominio donde la diferencia entre ambas funciones no supere el porcentaje de error.
   -   Grafica ambas curvas y el rango donde la diferencia es menor al error proporcionado.


2. **Compilación:**
   ```bash
   make p2


# Ejecucion
./exe dependiendo de cual proyecto se compilo

# Para eliminar los ejecutables generados use:
```bash
   make clean