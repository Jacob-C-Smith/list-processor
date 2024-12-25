#include <stdio.h>
#include <json/json.h>
#include <list_processor/list_processor.h>

int lp_if ( list_processor *p_list_processor, array *p_array, json_value **pp_value );
int lp_while ( list_processor *p_list_processor, array *p_array, json_value **pp_value );
int lp_fun ( list_processor *p_list_processor, array *p_array, json_value **pp_value );
int lp_fun_fun ( list_processor *p_list_processor, array *p_array, json_value **pp_value );

void lp_control_register ( void )
{
    lp_register("if", "Conditional evaluation; (if (bool-expr) (true-block) <(false-block)>)", lp_if);
    lp_register("while", "Repeat while continuation condition evaluates true", lp_while);
    lp_register("fun", "Define a function", lp_fun);
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

int lp_fun ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    // Initialized data
    json_value *p_function_identifier  = (void *) 0,
               *p_param_list           = (void *) 0,
               *p_body                 = (void *) 0,
               *p_body_result          = (void *) 0,
               *p_value                = (void *) 0;

    // Store identifier
    array_index(p_array, 1, (void **)&p_function_identifier);

    // Store parameter list
    array_index(p_array, 2, (void **)&p_param_list);

    // Store function body
    array_index(p_array, 3, (void **)&p_body);

    // Parse the parameter list
    if (p_param_list->type != JSON_VALUE_ARRAY) return 0;
    
    //
    for (size_t i = 0; i < array_size(p_param_list->list); i++)
    {

        json_value *p_param_i_value = (void *) 0;

        array_index(p_param_list->list, i, (void **) &p_param_i_value);

        // 
        {
            json_value *p_param_i_identifier = (void *) 0;
            json_value *p_param_i_identifier_2 = (void *) 0;

            array_index(p_param_i_value->list, 1, (void **) &p_param_i_identifier);
            array_index(p_param_i_value->list, 2, (void **) &p_param_i_identifier_2);
        }
    }
    
    lp_env_set(p_list_processor, p_function_identifier->string, lp_fun_fun);
    
    // Allocate a block
    p_value = realloc(0, sizeof(json_value));

    // Populate the block
    *p_value = (json_value) { .type = JSON_VALUE_INTEGER, .integer = 1 };
    *pp_value = p_value;

    // Done
    return 1; 
}

int lp_fun_fun ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    // Initialized data
    json_value *p_function_identifier  = (void *) 0,
               *p_param_list           = (void *) 0,
               *p_body                 = (void *) 0,
               *p_body_result          = (void *) 0,
               *p_value                = (void *) 0;

    // Allocate a block
    p_value = realloc(0, sizeof(json_value));

    // Populate the block
    *p_value = (json_value) { .type = JSON_VALUE_INTEGER, .integer = 1 };
    *pp_value = p_value;

    // Done
    return 1; 
}

/*
int lp_for ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
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
*/