/** !
 * Eddy interpreter
 * 
 * @file interpreter.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// array
#include <array/array.h>

// dict
#include <dict/dict.h>

// json 
#include <json/json.h>

// eddy
#include <eddy/eddy.h>

/** !
 * Parse command line arguments
 * 
 * @param argc          the argc parameter of the entry point
 * @param argv          the argv parameter of the entry point
 * @param p_memory_size result
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
} value_bump;

json_value *value_alloc ( void )
{
    json_value *p_value = (json_value *) &value_bump.p_memory[value_bump.used];

    value_bump.used += sizeof(json_value);

    return p_value;
}


const char *string_alloc ( size_t len )
{
    char *p_value = (char *) &value_bump.p_memory[value_bump.used];

    value_bump.used += len + 1;

    return p_value;
}

json_value *eddy_print ( array *p_array )
{

    size_t max = array_size(p_array);
    
    for (size_t i = 1; i < max; i++)
    {

        json_value *p_value = (void *) 0;

        array_index(p_array, i, (void **) &p_value);

        try_again:
        switch (p_value->type)
        {
            case JSON_VALUE_STRING:
                printf("%s\n", p_value->string);
                break;
                
            case JSON_VALUE_INTEGER:
                printf("%d\n", p_value->integer);
                break;
            
            case JSON_VALUE_BOOLEAN:
                printf("%s\n", p_value->boolean ? "true" : "false");
                break;

            case JSON_VALUE_ARRAY:
                p_value = process_symbol(p_value);
                goto try_again;
            default:
                break;
        }

    }
    

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_INTEGER,
    p_value->integer = 1;

    return p_value;
}

json_value *eddy_scan_int ( array *p_array )
{    
    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type = JSON_VALUE_INTEGER;
    scanf(" %d", &p_value->integer);
    getchar();
    
    return p_value;
}

json_value *eddy_scan_str ( array *p_array )
{    
    json_value *p_value = realloc(0, sizeof(json_value));
    char *p_string = string_alloc(63+1);
    p_value->type = JSON_VALUE_INTEGER;
    scanf(" %s", p_string);
    getchar();
    *p_value = (json_value) { .type = JSON_VALUE_STRING, .string = p_string };

    return p_value;
}

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Initialized data
    size_t memory_pool_size = 65536;
    json_value *p_value = (void *) 0;
    char _program[1024] = { 0 };

    // Construct environment
    {

        // IO
        eddy_register("print", eddy_print);
        eddy_register("read_int", eddy_scan_int);
        eddy_register("read_str", eddy_scan_str);
    }

    // Parse command line arguments
    parse_command_line_arguments(argc, argv, &memory_pool_size);

    if ( memory_pool_size == -1 ) return EXIT_FAILURE;

    value_bump.used = 0;
    value_bump.memory_size = memory_pool_size;
    value_bump.p_memory = realloc(0, memory_pool_size);
    bool running = true;

    while(running)
    {

        fprintf(stderr, ">>> ");
        memset(_program, 0, sizeof(_program));
        if ( -1 == scanf(" %[^\n]", &_program) )
        {
            running = false;
            continue;
        }

        json_value_parse(_program, 0, &p_value);

        process_symbol(p_value);
    };

    value_bump.p_memory = realloc(value_bump.p_memory, 0);
    json_value_free(p_value);

    // Success
    return EXIT_SUCCESS;
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
