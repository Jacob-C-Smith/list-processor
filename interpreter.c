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

// list processor
#include <list_processor/list_processor.h>

/** !
 * Parse command line arguments
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point

 * 
 * @return void on success, program abort on failure
 */
void parse_command_line_arguments ( int argc, const char *argv[] );

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Initialized data
    list_processor *p_list_processor = (void *) 0;
    json_value *p_value = (void *) 0;
    bool running = true;
    char _program[1024] = { 0 };

    // Parse command line arguments
    parse_command_line_arguments(argc, argv);

    // Construct a list constructor
    lp_constructor(&p_list_processor, 4096);

    // Read Eval Write loop
    while ( running )
    {

        // Clear input buffer
        memset(_program, 0, sizeof(_program));
        static int y = 0;
        
        fprintf(stderr, " >>> ", y++);

        // Read line from standard in
        if ( -1 == scanf(" %[^\n]", &_program) )
        {

            // EOF
            running = false; 

            // Done
            continue;
        }

        // Parse the input
        json_value_parse(_program, 0, &p_value);

        // Evaluate the input
        lp_eval(p_list_processor, p_value, &p_value);
    
        // Release the input
        //json_value_free(p_value);
        
        switch (p_value->type)
        {
            case JSON_VALUE_STRING: 
                fprintf(stderr, "\033[96m\033[1m\033[4mstr\033[0m \033[03m\"%.15s\"\033[0m", p_value->string);
                fprintf(stderr, "%s", p_value->string);

                break;
            case JSON_VALUE_BOOLEAN: 
                fprintf(stderr, "\033[96m\033[1m\033[4mbool\033[0m \033[03m%s\033[0m", p_value->boolean ? "true" : "false");
                break;
            case JSON_VALUE_INTEGER: 
                fprintf(stderr, "\033[96m\033[1m\033[4mint\033[0m \033[03m%d\033[0m", p_value->integer);

                break;
            case JSON_VALUE_NUMBER: 
                fprintf(stderr, "\033[96m\033[1m\033[4mnum\033[0m \033[03m%g\033[0m", p_value->number);

                break;
            case JSON_VALUE_OBJECT: 
                json_value_fprint(p_value, stderr);

                break;
            case JSON_VALUE_ARRAY:
            {
                
                for (size_t i = 0; i < array_size(p_value->list) - 1; i++)
                {
                    json_value *p_xvalue = (void *) 0;
                    array_index(p_xvalue->list, i, (void **) &p_xvalue);
                    fprintf(stderr, "arr @%d : ", i);
                    json_value_fprint(p_xvalue, stderr);
                }
            }
                break;
            default:
                break;
        }
    };

    // End
    fprintf(stderr, "\033[44m%s \033[0m", argv[0]);

    // EOF?
    if ( feof(stdin) ) fprintf(stderr, "\033[44m\033[0m\n");
    
    // Success
    return EXIT_SUCCESS;
}

void parse_command_line_arguments ( int argc, const char *argv[] )
{

    // If no command line arguments are supplied, run all the examples
    if ( argc == 1 ) return;
    size_t mem = 0;
    size_t scale = 1; 
    char unit = 0;
    
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
