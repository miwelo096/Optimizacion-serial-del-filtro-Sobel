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