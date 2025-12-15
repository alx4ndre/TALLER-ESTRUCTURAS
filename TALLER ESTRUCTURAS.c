#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LIBROS 10
#define LONG_TITULO 100
#define LONG_AUTOR 50
#define LONG_ESTADO 15

typedef struct {
    int id;
    char titulo[LONG_TITULO];
    char autor[LONG_AUTOR];
    int anio;
    char estado[LONG_ESTADO];
} Libro;

Libro biblioteca[MAX_LIBROS];
int cantidadLibros = 0;

void limpiarBuffer();
int buscarIndicePorID(int id);
void registrarLibro();
void mostrarLibros();
void buscarLibro();
void actualizarEstado();
void eliminarLibro();
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int opcion;
    do {
        printf("\n--- GESTIÓN DE BIBLIOTECA ---\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar todos los libros\n");
        printf("3. Buscar libro (ID o Título)\n");
        printf("4. Actualizar estado (Prestado/Disponible)\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Error: Ingrese un número válido.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        switch (opcion) {
            case 1: registrarLibro(); break;
            case 2: mostrarLibros(); break;
            case 3: buscarLibro(); break;
            case 4: actualizarEstado(); break;
            case 5: eliminarLibro(); break;
            case 6: printf("Saliendo del sistema...\n"); break;
            default: printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int buscarIndicePorID(int id) {
    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i].id == id) {
            return i;
        }
    }
    return -1;
}

void registrarLibro() {
    if (cantidadLibros >= MAX_LIBROS) {
        printf("Error: La biblioteca está llena (Máximo %d libros).\n", MAX_LIBROS);
        return;
    }

    Libro nuevoLibro;
    int idTemp;

    printf("\n--- REGISTRO DE LIBRO ---\n");
    
    while (1) {
        printf("Ingrese ID del libro (número único): ");
        if (scanf("%d", &idTemp) != 1) {
            printf("Error: Debe ingresar un número entero.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        if (buscarIndicePorID(idTemp) != -1) {
            printf("Error: El ID %d ya existe. Intente con otro.\n", idTemp);
        } else {
            nuevoLibro.id = idTemp;
            break;
        }
    }

    printf("Ingrese Título: ");
    fgets(nuevoLibro.titulo, LONG_TITULO, stdin);
    nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = 0;

    printf("Ingrese Autor: ");
    fgets(nuevoLibro.autor, LONG_AUTOR, stdin);
    nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = 0;

    printf("Ingrese Año de publicación: ");
    while (scanf("%d", &nuevoLibro.anio) != 1) {
        printf("Error: Ingrese un año válido: ");
        limpiarBuffer();
    }
    limpiarBuffer();

    strcpy(nuevoLibro.estado, "Disponible");

    biblioteca[cantidadLibros] = nuevoLibro;
    cantidadLibros++;
    printf("¡Libro registrado con éxito!\n");
}

void mostrarLibros() {
    if (cantidadLibros == 0) {
        printf("\nNo hay libros registrados.\n");
        return;
    }

    printf("\n%-5s | %-30s | %-20s | %-6s | %-12s\n", "ID", "TÍTULO", "AUTOR", "AÑO", "ESTADO");
    printf("-------------------------------------------------------------------------------------\n");
    for (int i = 0; i < cantidadLibros; i++) {
        printf("%-5d | %-30s | %-20s | %-6d | %-12s\n", 
            biblioteca[i].id, 
            biblioteca[i].titulo, 
            biblioteca[i].autor, 
            biblioteca[i].anio, 
            biblioteca[i].estado);
    }
}

void buscarLibro() {
    int opcion, idBusqueda;
    char tituloBusqueda[LONG_TITULO];
    int encontrado = 0;

    printf("\nBuscar por: 1. ID | 2. Título: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    if (opcion == 1) {
        printf("Ingrese ID a buscar: ");
        scanf("%d", &idBusqueda);
        limpiarBuffer();
        
        int idx = buscarIndicePorID(idBusqueda);
        if (idx != -1) {
            printf("\nLibro Encontrado:\n");
            printf("ID: %d, Título: %s, Autor: %s, Estado: %s\n", 
                biblioteca[idx].id, biblioteca[idx].titulo, biblioteca[idx].autor, biblioteca[idx].estado);
        } else {
            printf("Libro con ID %d no encontrado.\n", idBusqueda);
        }

    } else if (opcion == 2) {
        printf("Ingrese el título (o parte del título): ");
        fgets(tituloBusqueda, LONG_TITULO, stdin);
        tituloBusqueda[strcspn(tituloBusqueda, "\n")] = 0;

        printf("\nResultados de búsqueda:\n");
        for (int i = 0; i < cantidadLibros; i++) {
            if (strstr(biblioteca[i].titulo, tituloBusqueda) != NULL) {
                printf("- [%d] %s (%s)\n", biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].estado);
                encontrado = 1;
            }
        }
        if (!encontrado) printf("No se encontraron coincidencias.\n");
    } else {
        printf("Opción inválida.\n");
    }
}

void actualizarEstado() {
    int id, idx;
    printf("\n--- ACTUALIZAR ESTADO ---\n");
    printf("Ingrese ID del libro: ");
    scanf("%d", &id);
    limpiarBuffer();

    idx = buscarIndicePorID(id);
    if (idx == -1) {
        printf("Libro no encontrado.\n");
        return;
    }

    if (strcmp(biblioteca[idx].estado, "Disponible") == 0) {
        strcpy(biblioteca[idx].estado, "Prestado");
        printf("El estado del libro '%s' cambió a PRESTADO.\n", biblioteca[idx].titulo);
    } else {
        strcpy(biblioteca[idx].estado, "Disponible");
        printf("El estado del libro '%s' cambió a DISPONIBLE.\n", biblioteca[idx].titulo);
    }
}

void eliminarLibro() {
    int id, idx;
    printf("\n--- ELIMINAR LIBRO ---\n");
    printf("Ingrese ID del libro a eliminar: ");
    scanf("%d", &id);
    limpiarBuffer();

    idx = buscarIndicePorID(id);
    if (idx == -1) {
        printf("Libro no encontrado.\n");
        return;
    }

    for (int i = idx; i < cantidadLibros - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
    }
    
    cantidadLibros--;
    printf("Libro eliminado correctamente.\n");
}