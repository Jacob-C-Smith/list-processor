/** !
 * Eddy Arithmetic operations
 * 
 * @file arithmetic.c
 * 
 * @author Jacob Smith
 */

// standard library
#include <stdio.h>

// json module
#include <json/json.h>

// eddy module
#include <eddy/eddy.h>

// Forward declarations


/** !
 * add operation
 *
 * @param p_array values for add operation.
 * 
 * @return p_array[1] + p_array[2] + ... + p_array[N] 
 */
json_value *eddy_add ( array *p_array );

/** !
 * sub operation
 *
 * @param p_array values for sub operation.
 * 
 * @return p_array[1] - p_array[2] - ... - p_array[N] 
 */
json_value *eddy_sub ( array *p_array );

/** !
 * mul operation
 *
 * @param p_array values for mul operation.
 * 
 * @return p_array[1] * p_array[2] * ... * p_array[N] 
 */
json_value *eddy_mul ( array *p_array );

/** !
 * div operation
 *
 * @param p_array values for div operation.
 * 
 * @return p_array[1] / p_array[2] / ... / p_array[N] 
 */
json_value *eddy_div ( array *p_array );

// Function declarations
void eddy_base_arithmetic_register ( void )
{

    // Register arithmetic functions
    eddy_register("+", eddy_add);
    eddy_register("-", eddy_sub);
    eddy_register("*", eddy_mul);
    eddy_register("/", eddy_div);

    // Done
    return;
}

json_value *eddy_add ( array *p_array )
{

    // Initialized data
    size_t max = array_size(p_array);
    size_t acc = 0;
    
    // Walk the list
    for (size_t i = 1; i < max; i++)
    {
        
        // Initialized data
        json_value *p_value = (void *) 0;
        size_t addend = 0;

        // Access the i'th element of the array
        array_index(p_array, i, (void **) &p_value);

        // Strategy
        try_again:
        switch (p_value->type)
        {

            // Number from string
            case JSON_VALUE_STRING:

                // TODO: Error check
                // Scan the number from ascii text
                sscanf(p_value->string, " %d", &addend);
                
                // Accumulate
                acc += addend;
                
                // Done
                break;

            case JSON_VALUE_INTEGER:

                // Accumulate
                acc += p_value->integer;

                // Done
                break;

            case JSON_VALUE_ARRAY:

                // eval
                p_value = process_symbol(p_value);

                // Done
                goto try_again;

            // TODO: Error handling
            default: break;
        }
    }

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_INTEGER,
    p_value->integer = acc;

    return p_value;
}

json_value *eddy_sub ( array *p_array )
{

    size_t max = array_size(p_array);
    json_value *p_init = (void *) 0;
    size_t accumulator = 0;

    array_index(p_array, 1, (void **) &p_init);

    try_again:
    switch (p_init->type)
    {
        case JSON_VALUE_STRING:
            sscanf(p_init->string, " %d", &accumulator);
            break;

        case JSON_VALUE_INTEGER:
            accumulator -= p_init->integer;
            break;

        case JSON_VALUE_ARRAY:
            p_init = process_symbol(p_init);
            goto try_again;
        
        default:
            break;
    }

    for (size_t i = 2; i < max; i++)
    {
        
        json_value *p_value = (void *) 0;
        size_t addend = 0;

        array_index(p_array, i, (void **) &p_value);

        try_again_i:
        switch (p_value->type)
        {
            case JSON_VALUE_STRING:
                sscanf(p_value->string, " %d", &addend);
                accumulator -= addend;
                break;

            case JSON_VALUE_INTEGER:
                accumulator -= p_value->integer;
                break;

            case JSON_VALUE_ARRAY:
                p_value = process_symbol(p_value);
                goto try_again_i;
                continue;
            
            default:
                break;
        }

    }

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_INTEGER,
    p_value->integer = accumulator;

    return p_value;
}

json_value *eddy_mul ( array *p_array )
{

    size_t max = array_size(p_array);
    size_t accumulator = 1;
    
    for (size_t i = 1; i < max; i++)
    {
        
        json_value *p_i_value = (void *) 0;
        size_t addend = 1;

        array_index(p_array, i, (void **) &p_i_value);

        try_again:
        switch (p_i_value->type)
        {
            case JSON_VALUE_STRING:
                sscanf(p_i_value->string, " %d", &addend);
                accumulator *= addend;
                break;

            case JSON_VALUE_INTEGER:
                accumulator *= p_i_value->integer;
                break;

            case JSON_VALUE_ARRAY:
                p_i_value = process_symbol(p_i_value);
                goto try_again;
                continue;
                
            default:
                break;
        }

    }

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_INTEGER,
    p_value->integer = accumulator;

    return p_value;
}

json_value *eddy_div ( array *p_array )
{

    size_t max = array_size(p_array);
    json_value *p_init = (void *) 0;
    size_t accumulator = 0;

    array_index(p_array, 1, (void **) &p_init);

    try_again:
    switch (p_init->type)
    {
        case JSON_VALUE_STRING:
            sscanf(p_init->string, " %d", &accumulator);
            break;

        case JSON_VALUE_INTEGER:
            accumulator = p_init->integer;
            break;

        case JSON_VALUE_ARRAY:
            p_init = process_symbol(p_init);
            goto try_again;
        
        default:
            break;
    }

    for (size_t i = 2; i < max; i++)
    {
        
        json_value *p_value = (void *) 0;
        size_t addend = 0;

        array_index(p_array, i, (void **) &p_value);

        try_again_i:
        switch (p_value->type)
        {
            case JSON_VALUE_STRING:
                sscanf(p_value->string, " %d", &addend);
                accumulator /= addend;
                break;

            case JSON_VALUE_INTEGER:
                accumulator /= p_value->integer;
                break;

            case JSON_VALUE_ARRAY:
                p_value = process_symbol(p_value);
                goto try_again_i;
                continue;
            
            default:
                break;
        }

    }

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_INTEGER,
    p_value->integer = accumulator;

    return p_value;
}
