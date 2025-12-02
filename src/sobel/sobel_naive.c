#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int** read_image(const char* filename, int rows, int cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error al abrir el archivo %s\n", filename);
        return NULL;
    }
    // Interpretacion naive, crea una matriz para almacenar la imagen y reserva memoria
    int **matriz;

    // Reserva memoria
    matriz = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matriz[i] = (int*)malloc(cols * sizeof(int));
    }
    // Lee los valores de la imagen desde el archivo
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &matriz[i][j]);
        }
    }
    fclose(file);
    return matriz;
}

void write_image(const char* filename, int** matriz, int rows, int cols) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error al crear el archivo %s\n", filename);
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matriz[i][j]);
            if (j < cols - 1) fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Función para liberar la memoria de la matriz
void free_matrix(int** matriz, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int** sobel_filter(int** matriz, int rows, int cols) {
    // Kernel gx del filtro Sobel
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    // Kernel gy del filtro Sobel
    int gy[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    for (int i = 1; i < rows - 1; i++) {
        // Bucle que recorre los píxeles de la imagen, excluyendo los bordes
        for (int j = 1; j < cols - 1; j++) {
            int sobelX = 0;
            int sobelY = 0;
            // Bucle que aplica convolución al área 3x3 alrededor del píxel actual para cada uno de los kernels. Por eso u y v toman valores de -1 a 1
            for (int u = -1; u <= 1; u++) {
                for (int v = -1; v <= 1; v++) {
                    int pixel = matriz[i + u][j + v];
                    sobelX = sobelX+ pixel * gx[u + 1][v + 1];
                    sobelY = sobelY+ pixel * gy[u + 1][v + 1];
                }
            }

            // Magnitud del gradiente después de aplicar los filtros Sobel
            int magnitude = (int)sqrt((sobelX * sobelX) + (sobelY * sobelY));
            // Limita el valor a 0-255
            if (magnitude < 0) magnitude = 0;
            if (magnitude > 255) magnitude = 255;
            matriz[i][j] = magnitude;
        }
    }

    return matriz;
}

int main() {
    const char* input_file = "txt/Torre_1080.txt";
    const char* output_file = "txt/Torre_1080_sobel_naive.txt";

    // Introzuzco las dimensiones de la imagen directamente en el programa para evitar entrada/salida o tener que leerlas del archivo
    int rows = 512;
    int cols = 512;

    // Almaceno la imagen en una matriz
    int** imagen = read_image(input_file, rows, cols);
    if (!imagen) {
        return 1;
    }

    // Aplico el filtro Sobel
    int** imagen_sobel = sobel_filter(imagen, rows, cols);
    if (!imagen_sobel) {
        free_matrix(imagen, rows);
        return 1;
    }

    // Escribo la imagen procesada
    write_image(output_file, imagen_sobel, rows, cols);

    // Libero la memoria
    free_matrix(imagen, rows);

    printf("Filtro Sobel aplicado y guardado en %s\n", output_file);
    return 0;
}