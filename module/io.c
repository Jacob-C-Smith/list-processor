/** !
 * Eddy IO operations
 * 
 * @file io.c
 * 
 * @author Jacob Smith
 */

// standard library
#include <stdio.h>

// json module
#include <json/json.h>

// list processor module
#include <list_processor/list_processor.h>

// Forward declarations
int lp_read  ( list_processor *p_list_processor, array *p_array, json_value **pp_value );
int lp_write ( list_processor *p_list_processor, array *p_array, json_value **pp_value );

void lp_base_io_register ( void )
{

    // IO
    lp_register("read", lp_read);
    lp_register("write", lp_write);

    // Done
    return;
}

int lp_read ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{
    
    // Initialized data
    json_value *p_value = realloc(0, sizeof(json_value));
    char *p_text = realloc(0, 256);
    double d = 0;
    
    // Read
    scanf(" %[^\n]255s", p_text);
    getchar();

    json_value_parse(p_text, 0, &p_value);

    *pp_value = p_value;
    
    return 1;
}

int lp_write ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{
    
    // Initialized data
    int result = 1;
    json_value *p_value = realloc(0, sizeof(json_value)),
               *p_a = (void *) 0;

    // Write
    array_index(p_array, 1, (void **) &p_a);
    
    try_again:
    switch (p_a->type)
    {

        // Any type
        case JSON_VALUE_BOOLEAN:
        case JSON_VALUE_STRING:
        case JSON_VALUE_INTEGER:
        case JSON_VALUE_NUMBER:
        case JSON_VALUE_OBJECT:

            // Print as json
            json_value_print(p_a);

            // Newline
            putchar('\n');
            
            // Done
            break;
            
        case JSON_VALUE_ARRAY:
            
            // Evaluate the list
            if ( lp_eval(p_list_processor, p_a, &p_a) == 1 ) goto try_again;
            
            // Print the list
            break;

        // Default
        case JSON_VALUE_INVALID:
        default:

            // Error
            result = 0;

            // Done
            break;
    }

    // Populate the value
    *p_value = (json_value) { .type = JSON_VALUE_INTEGER, .integer = result };

    // Return a pointer to the caller
    *pp_value = p_value;

    // Success
    return 1;
}

