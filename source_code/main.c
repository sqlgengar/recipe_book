/*******************[LIBRERIAS]*********************/
#include <time.h>
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
    int score;
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
bool check_update_string( char[] );
bool check_update_int( int );
void update_date_register( char[] );
bool is_repeat( int[], int, int );
int find_autoincrement( int[], int );

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
                // select id
                int temp_int =              0;
                bool is_update =            false;
                char* temp_string =         NULL;
                size_t id_register_update = 0;
                
                printf( "Ingrese el número de la receta que desea modificar:\n" );
                scanf( " %zu", &id_register_update );
                fflush( stdin );

                // update name
                printf( "Nuevo nombre: [0 para no editar]\n" );
                scanf( " %s", temp_string );
                fflush( stdin );

                if( check_update_string )
                {
                    strcpy( memory_recipes[id_register_update - 1].name, temp_string );
                    is_update = true;
                }

                // update duration
                printf( "Nuevo tiempo de preparacion: [0 para no editar]\n" );
                scanf( " %d", &temp_int );
                fflush( stdin );

                if( check_update_int )
                {
                    memory_recipes[id_register_update - 1].duration = temp_int;
                    is_update = true;
                }

                // update level
                printf( "Nuevo tiempo de preparacion: [0 para no editar]\n" );
                scanf( " %d", &temp_int );
                fflush( stdin );

                if( check_update_int )
                {
                    memory_recipes[id_register_update - 1].level = temp_int;
                    is_update = true;
                }

                // update parts
                printf( "Nueva cantidad de partes: [0 para no editar]\n" );
                scanf( " %d", &temp_int );
                fflush( stdin );

                if( check_update_int )
                {
                    memory_recipes[id_register_update - 1].parts = temp_int;
                    is_update = true;
                }

                // update preparation
                printf( "Nuevo script de preparacion: [0 para no editar]\n" );
                scanf( " %s", temp_string );
                fflush( stdin );

                if( check_update_int )
                {
                    strcpy( memory_recipes[id_register_update - 1].preparation, temp_string );
                    is_update = true;
                }

                // update date register
                if( is_update ) update_date_register( memory_recipes[id_register_update - 1].date_update );
            break;

            // DELETE RECIPE
            case 3:
                size_t id_register_delete = 0;

                printf( "Ingrese el número de la receta que desea eliminar:\n" );
                scanf( " %zu", &id_register_delete );
                fflush( stdin );

                memory_recipes[id_register_delete - 1].status = 0;
                
                // update date register
                update_date_register( memory_recipes[id_register_delete - 1].date_update );
            break;

            // ADD RECIPE
            case 4:
                int temp_id = 0;
                int ids[100];

                // resolucion del id de la tabla
                printf( "Ingrese el id: [0 para valor automatico]\n" );
                scanf( " %d", &temp_id );
                fflush( stdin );

                for( size_t k = 0; k < amount_recipes; k++ )
                {
                    ids[k] = memory_recipes[k].id;
                }

                if( is_repeat( ids, temp_id, amount_recipes ) )
                {
                    printf( "Id repedito, operacion no permitida.\n" );
                }
                else
                {
                    autoincrement_recipes = temp_id;
                }

                if( temp_id == 0 ) autoincrement_recipes = find_autoincrement( ids, amount_recipes );

                // Aumentar un espacio de memoria.
                memory_recipes = realloc( memory_recipes, amount_recipes * sizeof( Recipes ) );

                // Registrar id.
                memory_recipes[amount_recipes - 1].id = autoincrement_recipes;

                // Registrar id_user.
                memory_recipes[amount_recipes - 1].id_user = 1;

                // Registrar name.
                printf( "Ingrese nombre de la receta:\n" );
                getchar();
                fgets( memory_recipes[amount_recipes - 1].name, sizeof( memory_recipes[amount_recipes - 1].name ), stdin );
                memory_recipes[amount_recipes - 1].name[strcspn( memory_recipes[amount_recipes - 1].name, "\n" )] = '\0';
                fflush( stdin );
                
                // Registrar dutarion.
                do
                {
                    printf( "Ingrese duracion de receta:\n" );
                    scanf( " %d", &memory_recipes[amount_recipes - 1].duration );
                    fflush( stdin );
                } while( memory_recipes[amount_recipes - 1].duration <= 0 );

                // Registrar level.
                printf( "Ingrese el nivel de la receta:\n" );
                scanf( " %d", &memory_recipes[amount_recipes - 1].level );
                fflush( stdin );

                // Registrar parts.
                do
                {
                    printf( "Ingrese cuantas prociones rinde la receta:\n" );
                    scanf( " %d", &memory_recipes[amount_recipes - 1].parts );
                    fflush( stdin );
                } while( memory_recipes[amount_recipes - 1].parts <= 0 );
                
                // Registrar preparation.
                printf( "Ingrese la preparion de la receta:\n" );
                fgets( memory_recipes[amount_recipes - 1].preparation, sizeof( memory_recipes[amount_recipes - 1].preparation ), stdin );

                // Registrar image.
                strcpy( memory_recipes[amount_recipes -1].image, "./images/default.jpg" );

                // Registrar score.
                memory_recipes[amount_recipes - 1].score = 0;

                // Registrar date_update.
                strcpy( memory_recipes[amount_recipes - 1].date_update, '\0' );
                
                // Registrar date.
                time_t current;
                struct tm* info_time;
                time( &current );
                info_time = localtime( &current );

                strftime( memory_recipes[amount_recipes - 1].date, sizeof( memory_recipes[amount_recipes - 1].date ), "%Y-%m-%d %H:%M:%S", info_time );
                
                // Registrar status.
                memory_recipes[amount_recipes - 1].status = true;

                // Incrementar cantidad de recetas.
                amount_recipes++;
            break;

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

void update_date_register( char register_date[11] )
{
    time_t current_time;
    struct tm *time_info;
    time(&current_time);
    time_info = localtime(&current_time);
    strftime( register_date, sizeof( register_date[11] ), "%Y-%m-%d", time_info );
}

bool is_repeat( int ids[], int find_id, int amount_registers )
{
    bool repeated = false;

    for( int i = 0; i < amount_registers; i++ )
    {
        if( ids[i] == find_id )
        {
            repeated = true;
            break;
        }
    }

    return repeated;
}

int find_autoincrement( int ids[], int amount_registers )
{
    int autoincrement = 1;

    for( int i = 0; i < amount_registers; i++ )
    {
        autoincrement++;
    }

    return autoincrement;
}