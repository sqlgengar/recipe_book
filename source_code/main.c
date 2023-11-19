#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int id;
    int id_user;
    char name[80];
    int duration;
    int level;
    int parts;
    char preparation[2000];
    char image[100];
    short int score;
    char date_update[5];
    char date[20];
    short int status;
} Recipes;


int main()
{
    char* path_recipes = "./files/recipes.dat";
    bool flag_main_cicle = true;
    short int option_main_cicle = 0;
    Recipes* memory_recipes;
    FILE* stream_recipes = NULL;

    Recipes recipes_data[5] =
    {
        {1, 1, "Pasta Carbonara", 30, 2, 4, "Cocinar la pasta y mezclar con una salsa de huevo, queso parmesano y panceta.", "./images/53241bc1ba.jpg", 5, "", "2023-11-18 03:35:00", 1},
        {2, 1, "Ensalada César", 15, 1, 2, "Preparar lechuga, crutones, pollo a la parrilla y aderezo de anchoas.", "./images/bb9f156d17.jpg", 1, "", "2023-11-18 03:35:00", 1},
        {3, 2, "Tacos de Carnitas", 60, 3, 6, "Cocinar la carne de cerdo lentamente con especias y servir en tortillas de maíz con cebolla y cilantro.", "./images/19fa9895e3.jpg", 2, "", "2023-11-18 03:35:00", 1},
        {4, 2, "Risotto de Champiñones", 45, 2, 3, "Cocinar arroz con caldo de champiñones, agregar champiñones salteados y queso parmesano.", "./images/d7d699bbc4.jpg", 4, "", "2023-11-18 03:35:00", 1},
        {5, 1, "Pastel de Chocolate", 60, 3, 8, "Hornear un pastel de chocolate con glaseado de vainilla y decorar con fresas.", "./images/ce1e490d3e.jpg", 1, "", "2023-11-18 03:35:00", 1}
    };

    stream_recipes = fopen( path_recipes, "rb" );
    if( stream_recipes == NULL )
    {
        stream_recipes = fopen( path_recipes, "wb" );
        fwrite( recipes_data, sizeof( Recipes ), sizeof( recipes_data ) / sizeof( Recipes ), stream_recipes );
    }
    fclose( stream_recipes );

    stream_recipes = fopen( path_recipes, "rb" );

    fseek( stream_recipes, 0, SEEK_END );
    long size_file_recipes = ftell( stream_recipes );
    fclose( stream_recipes );

    size_t amount_recipes = size_file_recipes / sizeof( Recipes );

    memory_recipes = malloc( amount_recipes * sizeof( Recipes ) );

    stream_recipes = fopen( path_recipes, "rb" );
    fread( memory_recipes, sizeof( Recipes ), amount_recipes, stream_recipes );
    fclose( stream_recipes );

    while( flag_main_cicle )
    {
        printf( "Ingrese alguna de la sisuiente opciones del menu: (0 para salir)\n" );
        printf( "[1] Listar las recetas\n" );
        printf( "[2] Modificar una receta\n" );
        printf( "[3] Eliminar una receta\n" );
        printf( "[4] Crear una receta\n" );

        scanf( " %hd", &option_main_cicle );
        fflush( stdin );

        switch( option_main_cicle )
        {
            case 1:
                while( memory_recipes != NULL )
                {
                    printf( "%d ", memory_recipes->id );
                    printf( "%s\n", memory_recipes->name );

                    memory_recipes++;
                }
            break;

            case 2:
                printf("Ingrese el número de la receta que desea modificar: ");
                size_t id_register;
                scanf("%zu", &id_register);

                printf("Nuevo nombre: ");
                scanf("%s", memory_recipes[id_register-1].name);
            break;

            case 3:
                //elimiar receta;
            break;

            case 4:
                //crear receta;
            break;
        
            default:
                flag_main_cicle = false;
                continue;
            break;
        }
    }

    stream_recipes = fopen( path_recipes, "wb" );
    fwrite( memory_recipes, sizeof( Recipes ), sizeof( memory_recipes ) / sizeof( Recipes ), stream_recipes );
    fclose( stream_recipes );

    free( memory_recipes );
    return 0;
}