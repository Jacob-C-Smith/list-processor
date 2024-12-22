/** !
 * Stream processor example program
 * 
 * 
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// json 
#include <json/json.h>

// Stream processor
#include <stream_processor/stream_processor.h>

struct list_processor_symbol_s;
typedef struct list_processor_symbol_s list_processor_symbol;

struct list_processor_cell_s;
typedef struct list_processor_cell_s list_processor_cell;

struct list_processor_s;
typedef struct list_processor_s list_processor;

struct list_processor_cell_s
{

    int _symbol;

    union
    {
        list_processor_cell   *p_cons;
        list_processor_symbol *p_symbol;
    };

    list_processor_cell *p_cdr;
};

struct list_processor_s
{
    size_t node_quantity;
};

/** !
 * Parse command line arguments
 * 
 * @param argc               the argc parameter of the entry point
 * @param argv               the argv parameter of the entry point

 * 
 * @return void on success, program abort on failure
 */
void parse_command_line_arguments ( int argc, const char *argv[], size_t *p_memory_size );

// Data
struct
{
    size_t used;
    size_t memory_size;
    char *p_memory;
} cell_bump;

list_processor_cell *cell_alloc ( void );

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Initialized data
    size_t memory_pool_size = 65536;

    // Parse command line arguments
    parse_command_line_arguments(argc, argv, &memory_pool_size);

    if ( memory_pool_size == -1 ) return EXIT_FAILURE;

    //log_info("[eddy] [bump] Allocated %d bytes\n", memory_pool_size);

    cell_bump.used = 0;
    cell_bump.memory_size = memory_pool_size;
    cell_bump.p_memory = realloc(0, memory_pool_size);

    while ( !feof(stdin) )
    {

        // Initialized data
        char _text[256] = { 0 };
        int t = 0;
        size_t parsed = 0;
        size_t token_len = 0;
        char _token[256] = { 0 };
        char *p_token = _text;
        char c = 0;

        // Prompt
        fprintf(stderr, "🐶 ");

        // Read
        c = getchar();
        
        // 
        while ( !feof(stdin) )
        {
            
            // Initialized data
            int l_t = t;
            

            //
            switch (c)
            {
                case '(':
                case ')':
                    printf("{\"separator\":\"%c\"}", c);
                    putchar('\n');
                    
                    break;
                case '\n':
                case ' ':

                    break;
                    
                default:            
                    printf("{\"identifier\":\"");
                    
                    do  { putchar(c); c = getchar(); } 
                    while
                    (
                        c != ' ' &&
                        c != '(' &&
                        c != ')' 
                    );
                    ungetc(c, stdin);
                    printf("\"}\n");
                    break;
            }
            
            // 
            c = getchar();

        }
    }
    
    cell_bump.p_memory = realloc(cell_bump.p_memory, 0);

    // Success
    return EXIT_SUCCESS;
}

list_processor_cell *cell_alloc ( void )
{

    if ( cell_bump.used > cell_bump.memory_size + sizeof(list_processor_cell) ) cell_bump.used = 0;
 

    list_processor_cell *p_cell = (list_processor_cell *) cell_bump.p_memory[cell_bump.used];


    
    return p_cell;
}

void parse_command_line_arguments ( int argc, const char *argv[], size_t *p_memory_size )
{

    // If no command line arguments are supplied, run all the examples
    if ( argc == 1 ) return;
    size_t mem = 0;
    size_t scale = 1; 
    char unit = 0;
    
    if ( strcmp(argv[1], "memory") == 0 )
        switch (sscanf(argv[2], "%d%c", &mem, &unit)) {case 2:
            switch ( unit )
            {
                case 'b':
                case 'B':
                    scale = 1;
                    break;
                case 'k':
                case 'K':
                    scale = 1024;
                    break;
                case 'm':
                case 'M':
                    scale = 1024*1024;
                    break;
                case 'g':
                case 'G':
                    scale = 1024*1024*1024;
                    break;
                default:
                    break;
            }
            break;default:break;}

    // Default
    else goto invalid_arguments;
    
    *p_memory_size = mem * scale;

    // Success
    return;
    
    // Error handling
    {

        // Argument errors
        {
            invalid_arguments:
                
                // Print a usage message to standard out
                //print_usage(argv[0]);

                // Abort
                exit(EXIT_FAILURE);
        }
    }
}

// size_t load_file ( const char *path, void *buffer, bool binary_mode )
// {

//     // Argument checking 
//     i
// // Function declarations
// /**!
//  * Return the size of a file IF buffer == 0 ELSE read a file into buffer
//  * 
//  * @param path path to the file
//  * @param buffer buffer
//  * @param binary_mode "wb" IF true ELSE "w"
//  * 
//  * @return 1 on success, 0 on error
//  */
// size_t load_file ( const char *path, void *buffer, bool binary_mode );

// // Entry point
// int main ( int argc, const char *argv[] )
// {
    
//     // Initialized data
//     stream_processor *p_stream_processor = (void *) 0;
//     char _file_buffer[4096] = { 0 };
//     json_value *p_value = (void *) 0;
    
//     // Load a stream processor file
//     load_file("resources/simple.json", &_file_buffer, false);

//     // Parse the file
//     json_value_parse(_file_buffer, 0, &p_value);

//     // Construct the stream processor
//     //stream_processor_construct(&p_stream_processor, p_value);

//     // Get stream processor info
//     //stream_processor_info(p_stream_processor);

//     // Start the stream processor
//     //stream_processor_start(p_stream_processor);

//     // Wait for the stream processor to stop
//     //stream_processor_wait_idle(p_stream_processor);

//     // Success
//     return EXIT_SUCCESS;
// }

// size_t load_file ( const char *path, void *buffer, bool binary_mode )
// {

//     // Argument checking 
//     if ( path == 0 ) goto no_path;

//     // Initialized data
//     size_t  ret = 0;
//     FILE   *f   = fopen(path, (binary_mode) ? "rb" : "r");
    
//     // Check if file is valid
//     if ( f == NULL ) goto invalid_file;

//     // Find file size and prep for read
//     fseek(f, 0, SEEK_END);
//     ret = (size_t) ftell(f);
//     fseek(f, 0, SEEK_SET);
    
//     // Read to data
//     if ( buffer ) 
//         ret = fread(buffer, 1, ret, f);

//     // The file is no longer needed
//     fclose(f);
    
//     // Success
//     return ret;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_path:
//                 #ifndef NDEBUG
//                     log_error("[json] Null path provided to function \"%s\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // File errors
//         {
//             invalid_file:
//                 #ifndef NDEBUG
//                     printf("[Standard library] Failed to load file \"%s\". %s\n",path, strerror(errno));
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }
