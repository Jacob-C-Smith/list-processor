/** !
 * Eddy syntax
 * 
 * @file main.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>

// json module
#include <json/json.h>

int print_list ( void )
{

    char  _in[1024]   = { 0 };
    char *p_in        = _in;
    bool first = 1;
    
    while( fgets(p_in, 1024, stdin) )
    {

        // Initialized data
        json_value *p_value = (void *) 0;

        // Parse the json value
        json_value_parse(p_in, 0, &p_value);

        // Error check
        if ( p_value->type != JSON_VALUE_OBJECT ) return 0;
        if ( dict_get(p_value->object, "identifier" ) )
        {
            
            // Print the token
            char *p_lexeme = ((json_value *) dict_get(p_value->object, "identifier"))->string;
            if ( first == 0 )
                putchar(','), putchar(' ');
            else first = 0;

            printf("\"%s\"", p_lexeme);                

        }
        else if ( dict_get(p_value->object, "separator" ) )
        {

            // Initialized data
            char  _in[1024] = { 0 };
            char *p_in      = _in;
            if (strcmp(((json_value *)dict_get(p_value->object, "separator" ))->string, "(") == 0 ) 
            {

                if ( first == 0 )
                    putchar(','), putchar(' ');
                else first = 0;

                putchar('[');
                putchar(' ');
                print_list();
                

            }
            else
            {
                putchar(' ');
                putchar(']');
            }
        }

        // Free the value
        json_value_free(p_value);
    }

    return 1;
}

int main ( int argc, const char *argv[] )
{

    // Initialized data


    // read-eval-write loop
    print_list();

    fprintf(stderr, "\033[44m%s \033[0m", argv[0]);

    // EOF?
    if ( feof(stdin) )
        fprintf(stderr, "\033[44m>>> \033[0m");

    putchar('\n');

    // Success
    return EXIT_SUCCESS;
}
