#include <stdio.h>
#include <json/json.h>
#include <list_processor/list_processor.h>

int lp_if ( list_processor *p_list_processor, array *p_array, json_value **pp_value );
int lp_while ( list_processor *p_list_processor, array *p_array, json_value **pp_value );

void lp_control_register ( void )
{

    lp_register("if", lp_if);
    lp_register("while", lp_while);
}

int lp_if ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    // Initialized data
    json_value *p_condition = (void *) 0,
               *p_if_true   = (void *) 0,
               *p_if_false  = (void *) 0,
               *p_value     = (void *) 0;

    // Store condition
    array_index(p_array, 1, (void **)&p_condition);

    // Store if true block
    array_index(p_array, 2, (void **)&p_if_true);

    // Store if false block
    array_index(p_array, 3, (void **)&p_if_false);

    // Evaluate condition
    lp_eval(p_list_processor, p_condition, &p_condition);

    // Evaluate block
    if      ( p_condition->boolean ) lp_eval(p_list_processor, p_if_true, &p_if_true);
    else if ( p_condition->boolean == false ) 
        if ( p_if_false ) 
            lp_eval(p_list_processor, p_if_false, &p_if_false);

    // Allocate a block
    p_value = realloc(0, sizeof(json_value));

    // Populate the block
    *pp_value = p_condition->boolean ? p_if_true : p_if_false;

    // Done
    return 1; 
}


int lp_while ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    // Initialized data
    json_value *p_test_condition = (void *) 0,
               *p_condition      = (void *) 0,
               *p_body           = (void *) 0,
               *p_body_result    = (void *) 0,
               *p_value          = (void *) 0;

    // Store condition
    array_index(p_array, 1, (void **)&p_test_condition);

    // Store if true block
    array_index(p_array, 2, (void **)&p_body);

    // Store if false block
    array_index(p_array, 3, (void **)&p_body_result);

    // Evaluate condition
    lp_eval(p_list_processor, p_test_condition, &p_condition);

    // Evaluate block
    while ( p_condition->boolean )
    {
        
        lp_eval(p_list_processor, p_body, &p_body_result);

        // Evaluate condition
        lp_eval(p_list_processor, p_test_condition, &p_condition);
    }
    
    // Allocate a block
    p_value = realloc(0, sizeof(json_value));

    // Populate the block
    *p_value = (json_value) { .type = JSON_VALUE_BOOLEAN, .boolean = p_condition->boolean };
    *pp_value = p_value;

    // Done
    return 1; 
}

