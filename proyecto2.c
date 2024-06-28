#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
    * Proyecto 2
    * Autores: Antony Medina y Arley Grijalba
    * Fecha: 27/06/2024
    * Objetivo: Graficar dos funciones cuadráticas y encontrar los subdominios donde la diferencia entre las funciones sea menor a un porcentaje de error ingresado.
    
    */

// Función para calcular el valor de una función cuadrática
double cuadratica(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

// Función para encontrar los subdominios
void encontrar_subdominios(double a1, double b1, double c1, double a2, double b2, double c2, double error, FILE *archivo_sub) {
    double x;
    double f1, f2, diferencia, diferencia_porcentual;
    int en_subdominio = 0;
    double inicio, fin;
    int subdominio_encontrado = 0;

    for (x = -100000; x <= 100000; x += 0.1) {
        f1 = cuadratica(a1, b1, c1, x);
        f2 = cuadratica(a2, b2, c2, x);
        diferencia = fabs(f1 - f2);
        diferencia_porcentual = (diferencia / fabs(f1)) * 100;

        if (diferencia_porcentual <= error) {
            if (!en_subdominio) {
                inicio = x;
                en_subdominio = 1;
            }
            fin = x;
        } else {
            if (en_subdominio) {
                fprintf(archivo_sub, "%lf %lf\n", inicio, fin);
                en_subdominio = 0;
                subdominio_encontrado = 1;
            }
        }
    }
    if (en_subdominio) {
        fprintf(archivo_sub, "%lf %lf\n", inicio, fin);
        subdominio_encontrado = 1;
    }

    if (!subdominio_encontrado) {
        printf("No se encontraron subdominios donde la diferencia entre las funciones sea menor al porcentaje de error especificado.\n");
    }
}

// Función para generar el archivo de datos para gnuplot
void generar_archivo_datos(double a1, double b1, double c1, double a2, double b2, double c2) {
    FILE *fp = fopen("datos.dat", "w");
    double x;
    for (x = -100; x <= 100; x += 0.1) {
        fprintf(fp, "%lf %lf %lf\n", x, cuadratica(a1, b1, c1, x), cuadratica(a2, b2, c2, x));
    }
    fclose(fp);
}

// Función para generar el script de gnuplot
void generar_imagen() {
    FILE *gp = fopen("graficar.gnuplot", "w");
    fprintf(gp, "set terminal png size 1200,800\n");
    fprintf(gp, "set output 'grafica.png'\n");
    fprintf(gp, "set style rect fc lt -1 fillstyle solid 0.15\n");

    FILE *archivo_sub = fopen("subdominio.dat", "r");
    double inicio, fin;
    int id_rect = 1;
    while (fscanf(archivo_sub, "%lf %lf", &inicio, &fin) == 2) {
        fprintf(gp, "set object %d rect from %lf, graph 0 to %lf, graph 1\n", id_rect++, inicio, fin);
    }
    fclose(archivo_sub);

    fprintf(gp, "plot 'datos.dat' using 1:2 with lines title 'Función 1', \\\n");
    fprintf(gp, "     'datos.dat' using 1:3 with lines title 'Función 2'\n");
    fclose(gp);
}

int main() {
    double a1, b1, c1, a2, b2, c2, error;

    // Entrada de coeficientes para la primera función cuadrática
    printf("Ingrese los coeficientes de la primera función cuadrática (a b c) con un tab de espacio:\n");
    scanf("%lf %lf %lf", &a1, &b1, &c1);

    // Entrada de coeficientes para la segunda función cuadrática
    printf("Ingrese los coeficientes de la segunda función cuadrática (d e f) con un tab de espacio:\n");
    scanf("%lf %lf %lf", &a2, &b2, &c2);

    // Entrada del porcentaje de error
    printf("Ingrese el porcentaje de error (0-100): ");
    scanf("%lf", &error);

    // Generar los archivos de datos y el script de gnuplot
    generar_archivo_datos(a1, b1, c1, a2, b2, c2);

    FILE *archivo_sub = fopen("subdominio.dat", "w");
    encontrar_subdominios(a1, b1, c1, a2, b2, c2, error, archivo_sub);
    fclose(archivo_sub);

    generar_imagen();

    // Ejecutar gnuplot para generar la gráfica
    system("gnuplot graficar.gnuplot");

    printf("Gráfica generada en 'grafica.png'. Utiliza un visor de imágenes para abrir 'grafica.png'.\n");

    return 0;
}