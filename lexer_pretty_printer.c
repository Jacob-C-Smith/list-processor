/** !
 * eddy lexer pretty printer
 * 
 * @file lexer.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// json 
#include <json/json.h>

// eddy
#include <eddy/eddy.h>

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
        fprintf(stderr, "\r🐶 ");

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
                    printf("{\033[01;91m\"separator\"\033[0m:\"%c\"}", c);
                    putchar('\n');
                    
                    break;
                case '\n':
                case ' ':

                    break;
                case '\"':
                    printf("{\033[01;91m\"separator\"\033[00;0m:\"%c\"}", c);
                    printf("{\"identifier\":");
                
                    do  { putchar(c); c = getchar(); } 
                    while
                    (
                        c != '\"'
                    );
                    c = getchar();
                    printf("\"}\n");

                    break;
                default:            
                    printf("{\033[01;34m\"identifier\"\033[00;0m:\"\033[03;3m");
                    
                    do  { putchar(c); c = getchar(); } 
                    while
                    (
                        c != ' ' &&
                        c != '(' &&
                        c != ')' 
                    );
                    ungetc(c, stdin);
                    printf("\033[00;0m\"}\n");
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
