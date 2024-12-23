
#include <stdio.h>
#include <json/json.h>
#include <eddy/eddy.h>

json_value *eddy_eq  ( array *p_array );
json_value *eddy_neq ( array *p_array );

void eddy_base_relational_register ( void )
{

    // Equals
    eddy_register("==", eddy_eq);

    // Not equals
    eddy_register("!=", eddy_neq);


    fprintf(stderr, "[eddy] [base] [relational] Registered\n");    
}


json_value *eddy_eq ( array *p_array )
{

    size_t max = array_size(p_array);
    bool result = false;
    json_value *p_a = (void *) 0,
               *p_b = (void *) 0;

    array_index(p_array, 1, (void **) &p_a);
    array_index(p_array, 2, (void **) &p_b);
    
    p_a = process_symbol(p_a);
    p_b = process_symbol(p_b);

    if ( p_a->type != p_b->type ) goto done;

    try_again:
    switch (p_a->type)
    {
        case JSON_VALUE_STRING:
            result = ( 0 == strcmp(p_a->string, p_b->string) );
            break;

        case JSON_VALUE_INTEGER:
            result = ( p_a->integer == p_b->integer );
            break;

        case JSON_VALUE_ARRAY:
            p_a = process_symbol(p_a);
            p_b = process_symbol(p_b);
            goto try_again;
        
        default:
            break;
    }
    
    done:
    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_BOOLEAN,
    p_value->boolean = result;

    return p_value;
}

json_value *eddy_neq ( array *p_array )
{

    size_t max = array_size(p_array);
    bool result = false;
    json_value *p_a = (void *) 0,
               *p_b = (void *) 0;

    array_index(p_array, 1, (void **) &p_a);
    array_index(p_array, 2, (void **) &p_b);
    
    if ( p_a->type != p_b->type ) goto done;

    try_again:
    switch (p_a->type)
    {
        case JSON_VALUE_STRING:
            result = ( 0 != strcmp(p_a->string, p_b->string) );
            break;

        case JSON_VALUE_INTEGER:
            result = ( p_a->integer != p_b->integer );
            break;

        case JSON_VALUE_ARRAY:
            p_a = process_symbol(p_a);
            p_b = process_symbol(p_b);
            goto try_again;
        
        default:
            break;
    }
    
    done:
    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_BOOLEAN,
    p_value->boolean = result;

    return p_value;
}
