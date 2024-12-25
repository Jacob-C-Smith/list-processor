
#include <stdio.h>
#include <json/json.h>
#include <list_processor/list_processor.h>

fn_lp_eval lp_eq;
fn_lp_eval lp_neq;

void lp_base_relational_register ( void )
{

    lp_register("==", lp_eq);
    lp_register("!=", lp_neq);


    fprintf(stderr, "[eddy] [relational] Registered\n");    
}


int lp_eq ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    size_t max = array_size(p_array);
    bool result = false;
    json_value *p_a = (void *) 0,
               *p_b = (void *) 0;

    array_index(p_array, 1, (void **) &p_a);
    array_index(p_array, 2, (void **) &p_b);
    
    lp_eval(p_list_processor, p_a, &p_a);
    lp_eval(p_list_processor, p_b, &p_b);

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
            lp_eval(p_list_processor, p_a, &p_a);
            lp_eval(p_list_processor, p_b, &p_b);
            goto try_again;
        
        default:
            break;
    }
    
    done:
    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_BOOLEAN,
    p_value->boolean = result;
    *pp_value = p_value;
    return 1;
}

int lp_neq ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    size_t max = array_size(p_array);
    bool result = false;
    json_value *p_a = (void *) 0,
               *p_b = (void *) 0;

    array_index(p_array, 1, (void **) &p_a);
    array_index(p_array, 2, (void **) &p_b);
    
    lp_eval(p_list_processor, p_a, &p_a);
    lp_eval(p_list_processor, p_b, &p_b);

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
            lp_eval(p_list_processor, p_a, &p_a);
            lp_eval(p_list_processor, p_b, &p_b);
            goto try_again;
        
        default:
            break;
    }
    
    done:
    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_BOOLEAN,
    p_value->boolean = result;
    *pp_value = p_value;
    return 1;
}