/*******************[LIBRERIAS]*********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************[ESTRUCTURAS]*********************/
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

/*******************[CONSTANTES]*********************/
char PATH_RECIPES[100];

/*******************[DEFINICION FUNCIONES]*********************/
void init_files();
void load_paths();
void main_menu();
void menu_recipes();
bool check_update_field( int );

/*******************[MAIN]*********************/
int main()
{
    init_files();
    main_menu();
    return 0;
}

/*******************[INIT_FILES]*********************/
void init_files()
{
    load_paths();

    // RECIPES
    Recipes recipes_data[5] =
    {
        {1, 1, "Pasta Carbonara", 30, 2, 4, "Cocinar la pasta y mezclar con una salsa de huevo, queso parmesano y panceta.", "./images/53241bc1ba.jpg", 5, "", "2023-11-18 03:35:00", 1},
        {2, 1, "Ensalada César", 15, 1, 2, "Preparar lechuga, crutones, pollo a la parrilla y aderezo de anchoas.", "./images/bb9f156d17.jpg", 1, "", "2023-11-18 03:35:00", 1},
        {3, 2, "Tacos de Carnitas", 60, 3, 6, "Cocinar la carne de cerdo lentamente con especias y servir en tortillas de maíz con cebolla y cilantro.", "./images/19fa9895e3.jpg", 2, "", "2023-11-18 03:35:00", 1},
        {4, 2, "Risotto de Champiñones", 45, 2, 3, "Cocinar arroz con caldo de champiñones, agregar champiñones salteados y queso parmesano.", "./images/d7d699bbc4.jpg", 4, "", "2023-11-18 03:35:00", 1},
        {5, 1, "Pastel de Chocolate", 60, 3, 8, "Hornear un pastel de chocolate con glaseado de vainilla y decorar con fresas.", "./images/ce1e490d3e.jpg", 1, "", "2023-11-18 03:35:00", 1}
    };

    FILE* stream_recipes = fopen( PATH_RECIPES, "rb" );

    if( stream_recipes == NULL )
    {
        stream_recipes = fopen( PATH_RECIPES, "wb" );
        fwrite( recipes_data, sizeof( Recipes ), sizeof( recipes_data ) / sizeof( Recipes ), stream_recipes );
    }

    fclose( stream_recipes );

    return;
}

/*******************[LOAD_PATHS]*********************/
void load_paths()
{
    char* file_paths =  "./files/file_paths.txt";
    FILE* file_stream = fopen( file_paths, "r" );

    fscanf( file_stream, "PATH_RECIPES=%99s", PATH_RECIPES );

    fclose( file_stream );
    return;
}

/*******************[MAIN_MENU]*********************/
void main_menu()
{
    bool flag_main_cicle =          true;
    short int option_main_cicle =   0;

    while( flag_main_cicle )
    {
        printf( "Ingrese la opcion del menu al que quiere ingresar:\n" );
        printf( "[1] Recetas.\n" );
        printf( "[0] Salir del programa.\n" );

        scanf( " %hd", &option_main_cicle );
        fflush( stdin );

        switch( option_main_cicle )
        {
            // MENU_RECIPES
            case 1:
                menu_recipes();
            break;

            // EXIT
            default:
                flag_main_cicle = false;
            break;
        }
    }

    return;
}

/*******************[MENU_RECIPES]*********************/
void menu_recipes()
{
    Recipes* memory_recipes;
    FILE* stream_recipes =              NULL;
    size_t amount_recipes =             0;
    bool flag_recipes_cicle =           true;
    short int option_recipes_cicle =    0;
    short int autoincrement_recipes =   1;

    // CARGAR MEMORIA
    stream_recipes = fopen( PATH_RECIPES, "rb" );

    fseek( stream_recipes, 0, SEEK_END );
    long size_file_recipes = ftell( stream_recipes );
    fclose( stream_recipes );

    amount_recipes = size_file_recipes / sizeof( Recipes );

    memory_recipes = malloc( amount_recipes * sizeof( Recipes ) );

    stream_recipes = fopen( PATH_RECIPES, "rb" );
    fread( memory_recipes, sizeof( Recipes ), amount_recipes, stream_recipes );
    fclose( stream_recipes );

    for( size_t j = 0; j < amount_recipes; j++ )
    {
        if( memory_recipes[j].id > autoincrement_recipes ) autoincrement_recipes = memory_recipes[j].id;
    }

    // CICLO DE FUNCIONES
    while( flag_recipes_cicle )
    {
        printf( "Ingrese alguna de la sisuiente opciones del menu:\n" );
        printf( "[1] Listar las recetas.\n" );
        printf( "[2] Modificar una receta.\n" );
        printf( "[3] Eliminar una receta.\n" );
        printf( "[4] Crear una receta.\n" );
        printf( "[0] Salir de recetas.\n" );

        scanf( " %hd", &option_recipes_cicle );
        fflush( stdin );

        switch( option_recipes_cicle )
        {
            // LIST RECIPE
            case 1:
                printf( "| %-4s | %-8s | %-30s | %-8s | %-6s | %-5s | %-45s | %-25s | %-6s | %-11s | %-20s | %-6s |\n",
                        "ID", "ID User", "Name", "Duration", "Level", "Parts", "Preparation", "Image", "Score", "Date Update", "Date", "Status" );
                printf( "|-------------------------------------------------------------------------------------------------------------------------|\n" );

                for( size_t i = 0; i < amount_recipes; i++ )
                {
                    if( memory_recipes[i].status == 1 )
                    {
                        printf( "| %-4d | %-8d | %-30s | %-8d | %-6d | %-5d | %-45s | %-25s | %-6d | %-11s | %-20s | %-6d |\n",
                            memory_recipes[i].id, memory_recipes[i].id_user, memory_recipes[i].name, memory_recipes[i].duration, memory_recipes[i].level, memory_recipes[i].parts, 
                            memory_recipes[i].preparation, memory_recipes[i].image, memory_recipes[i].score, memory_recipes[i].date_update, memory_recipes[i].date, memory_recipes[i].status );
                    }
                }
            break;

            // EDIT RECIPE
            case 2:
                printf( "Ingrese el número de la receta que desea modificar:\n" );
                size_t id_register_update = 0;
                scanf( " %zu", &id_register_update );
                fflush( stdin );

                printf( "Nuevo nombre: " );
                scanf( "%s", memory_recipes[id_register_update-1].name );
                fflush( stdin );
            break;

            // DELETE RECIPE
            case 3:
                printf( "Ingrese el número de la receta que desea eliminar:\n" );
                size_t id_register_delete = 0;
                scanf("%zu", &id_register_delete);
                fflush( stdin );

                memory_recipes[id_register_delete-1].status = 0;
            break;

            // ADD RECIPE
            case 4:
                int temp_id;
                printf( "Ingrese autoincrement: (0 para valor automatico)\n" );
                scanf( " %d", &temp_id );
                fflush( stdin );
                for( size_t k = 0; k < amount_recipes; k++ )
                {
                    if( memory_recipes[k].id == temp_id )
                    {
                        printf( "Id repetido\n" );
                        break;
                    }
                }
                if( autoincrement_recipes < temp_id ) autoincrement_recipes = temp_id;
                amount_recipes++;
                memory_recipes = realloc( memory_recipes, amount_recipes * sizeof( Recipes ) );
                memory_recipes[amount_recipes - 1].id = autoincrement_recipes;
                memory_recipes[amount_recipes - 1].id_user = 1;
                printf( "Ingrese nombre de la receta:\n" );
                getchar();
                fgets(memory_recipes[amount_recipes - 1].name, sizeof(memory_recipes[amount_recipes - 1].name), stdin);
                memory_recipes[amount_recipes - 1].name[strcspn(memory_recipes[amount_recipes - 1].name, "\n")] = '\0';
                fflush(stdin);
                memory_recipes[amount_recipes - 1].status = true;
                autoincrement_recipes++;
            break;

            // EXIT
            default:
                flag_recipes_cicle = false;
            break;
        }
    }

    // ESCRIBIR MEMORIA
    stream_recipes = fopen( PATH_RECIPES, "wb" );
    fwrite( memory_recipes, sizeof( Recipes ), amount_recipes, stream_recipes );
    fclose( stream_recipes );

    free( memory_recipes );
    return;
}