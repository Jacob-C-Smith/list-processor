#include <stdio.h>
#include <json/json.h>
#include <eddy/eddy.h>

json_value *eddy_if ( array *p_array );

void eddy_base_control_register ( void )
{

    // If
    eddy_register("if", eddy_if);

    fprintf(stderr, "[eddy] [base] [control] Registered\n");

}

json_value *eddy_if ( array *p_array )
{

    size_t max = array_size(p_array);
    bool result = false;
    json_value *p_condition = (void *) 0,
               *p_if_true   = (void *) 0,
               *p_if_false  = (void *) 0;
    json_value *p_value = realloc(0, sizeof(json_value));

    array_index(p_array, 1, (void **)&p_condition);
    array_index(p_array, 2, (void **)&p_if_true);
    array_index(p_array, 3, (void **)&p_if_false);

    p_condition = process_symbol(p_condition);

      if ( p_condition->boolean )
        p_if_true = process_symbol(p_if_true);
    else if ( p_condition->boolean == false )
        p_if_false = process_symbol(p_if_false);
    
    *p_value = (json_value) { .type = JSON_VALUE_BOOLEAN, .boolean = p_condition->boolean };

    return p_value;
}
