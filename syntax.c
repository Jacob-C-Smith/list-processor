/** !
 * list processor syntax
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

// list processor
#include <list_processor/list_processor.h>

int print_list ( void )
{

    char  _in[1024]   = { 0 };
    char *p_in        = _in;
    bool first = 1;
    static int d = 0;
    
    while ( !feof(stdin) )
    {

        // Initialized data
        json_value *p_value = (void *) 0;

        // Read line from standard in
        int rc = scanf(" %[^\n]", p_in);

        if ( rc == -1 ) break;
        else if ( rc == 0 ) log_warning("[lp] [syntax] Error!\n");

        // Parse the json value
        json_value_parse(p_in, 0, &p_value);

        // Error check
        if ( p_value->type != JSON_VALUE_OBJECT ) return 0;
        if ( dict_get(p_value->object, "identifier" ) )
        {
            
            // Print the token
            json_value *p_id_value = dict_get(p_value->object, "identifier");

            if ( first == 0 )
                putchar(','), putchar(' ');
            else first = 0;

            switch (p_id_value->type)
            {
            case JSON_VALUE_STRING:
                printf("\"%s\"", p_id_value->string);
                break;
            case JSON_VALUE_BOOLEAN:
                printf("%s", p_id_value->boolean ? "true" : "false");
                break;
            case JSON_VALUE_INTEGER:
                printf("%d", p_id_value->integer);
                break;
            case JSON_VALUE_NUMBER:
                printf("%g", p_id_value->number);
                break;
            
            default:
                break;
            }

        }
        else if ( dict_get(p_value->object, "separator" ) )
        {

            // Initialized data
            char  _in[1024] = { 0 };
            char *p_in      = _in;
            if (strcmp(((json_value *)dict_get(p_value->object, "separator" ))->string, "(") == 0 ) 
            {

                if ( first == 0 )
                {
                    if ( d != 0 )
                        putchar(','), putchar(' ');
                }
                else first = 0;

                d++;
                putchar('[');
                putchar(' ');
                print_list();
            }
            else
            {
                putchar(' ');
                putchar(']');

                d--;
                if ( d == 0 )
                {
                    fflush(stdout);
                    putchar('\n');
                }
            }
        }

        if ( d == 0 ) fflush(stdout);

        // Free the value
        json_value_free(p_value);

        fflush(stdout);
    }

    return 1;
}

int main ( int argc, const char *argv[] )
{    

    // read-eval-write loop
    print_list();
    
    fprintf(stderr, "\033[44m%s \033[0m", argv[0]);

    // EOF?
    if ( feof(stdin) ) fprintf(stderr, "\033[44m>>> \033[0m");

    // Success
    return EXIT_SUCCESS;
}
