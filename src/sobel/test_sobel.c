#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Declaración de funciones externas de sobel_naive.c
int** read_image(const char* filename, int rows, int cols);
void free_matrix(int** matriz, int rows);
int** sobel_filter(int** matriz, int rows, int cols);

// Función para escribir la imagen procesada a un archivo
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
    printf("Imagen guardada en: %s\n", filename);
}

// Función para contar filas y columnas del archivo
void get_image_dimensions(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error al abrir el archivo %s\n", filename);
        *rows = 0;
        *cols = 0;
        return;
    }

    *rows = 0;
    *cols = 0;
    char buffer[10000];
    
    while (fgets(buffer, sizeof(buffer), file)) {
        (*rows)++;
        if (*cols == 0) {
            // Contar columnas en la primera fila
            int temp_cols = 0;
            char* token = strtok(buffer, " \t\n");
            while (token != NULL) {
                temp_cols++;
                token = strtok(NULL, " \t\n");
            }
            *cols = temp_cols;
        }
    }

    fclose(file);
}

int main() {
    const char* input_file = "txt/Eiffelturm.txt";
    const char* output_file = "txt/Eiffelturm_sobel.txt";
    
    printf("=== Test del Filtro Sobel ===\n\n");
    
    // 1. Obtener dimensiones de la imagen
    int rows, cols;
    get_image_dimensions(input_file, &rows, &cols);
    
    if (rows == 0 || cols == 0) {
        printf("Error: No se pudieron obtener las dimensiones de la imagen\n");
        return 1;
    }
    
    printf("Dimensiones de la imagen: %d x %d\n", rows, cols);
    
    // 2. Leer la imagen
    printf("Leyendo imagen desde: %s\n", input_file);
    int** imagen = read_image(input_file, rows, cols);
    
    if (!imagen) {
        printf("Error al leer la imagen\n");
        return 1;
    }
    
    printf("Imagen cargada exitosamente\n");
    
    // 3. Mostrar algunos valores de la imagen original (esquina superior izquierda)
    printf("\nPrimeros 5x5 pixeles de la imagen original:\n");
    for (int i = 0; i < 5 && i < rows; i++) {
        for (int j = 0; j < 5 && j < cols; j++) {
            printf("%3d ", imagen[i][j]);
        }
        printf("\n");
    }
    
    // 4. Aplicar el filtro Sobel
    printf("\nAplicando filtro Sobel...\n");
    int** imagen_sobel = sobel_filter(imagen, rows, cols);
    
    if (!imagen_sobel) {
        printf("Error al aplicar el filtro Sobel\n");
        free_matrix(imagen, rows);
        return 1;
    }
    
    printf("Filtro Sobel aplicado exitosamente\n");
    
    // 5. Mostrar algunos valores de la imagen procesada
    printf("\nPrimeros 5x5 pixeles después del filtro Sobel:\n");
    for (int i = 0; i < 5 && i < rows; i++) {
        for (int j = 0; j < 5 && j < cols; j++) {
            printf("%3d ", imagen_sobel[i][j]);
        }
        printf("\n");
    }
    
    // 6. Guardar la imagen procesada
    printf("\nGuardando imagen procesada...\n");
    write_image(output_file, imagen_sobel, rows, cols);
    
    // 7. Liberar memoria
    free_matrix(imagen_sobel, rows);
    
    printf("\n=== Test completado exitosamente ===\n");
    
    return 0;
}
