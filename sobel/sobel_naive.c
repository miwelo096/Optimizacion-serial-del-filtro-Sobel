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

void free_image(int** image, int rows) {
    for (int i = 0; i < rows; i++) {
        free(image[i]);
    }
    free(image);
}

int main() {
    const char* filename = "txt/prueba.txt";
    int rows = 2;
    int cols = 5;

    int** image = read_image(filename, rows, cols);
    if (image == NULL) {
        return 1;
    }

    // Imprime la imagen leida
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }

    free_image(image, rows);
    return 0;
}