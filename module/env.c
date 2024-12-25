
#include <stdio.h>
#include <json/json.h>
#include <list_processor/list_processor.h>

fn_lp_eval lp_get;
fn_lp_eval lp_set;
fn_lp_eval lp_env;

void eddy_base_env_register ( void )
{
    lp_register("get", lp_get);
    lp_register("set", lp_set);
    lp_register("env", lp_env);
}

int lp_get ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{
    
    json_value *p_identifier = (void *) 0,
               *p_get_value  = (void *) 0;
               
    array_index(p_array, 1, (void **)&p_identifier);
    p_get_value = dict_get(p_list_processor->p_scope, p_identifier->string);

    *pp_value = p_get_value;

    return 1;
}

int lp_set ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{


    json_value *p_identifier = (void *) 0,
               *p_set_val    = (void *) 0,
               *p_value      = realloc(0, sizeof(json_value));

    array_index(p_array, 1, (void **)&p_identifier);
    array_index(p_array, 2, (void **)&p_set_val);

    lp_eval(p_list_processor, p_set_val, &p_value);

    dict_add(p_list_processor->p_scope, p_identifier->string, p_value);
    
    *pp_value = p_value;

    return 1;
}

int lp_env ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{
    
    json_value *p_value = realloc(0, sizeof(json_value));
    const char *_p_env[1024] = { 0 };
    size_t key_count = dict_keys(p_list_processor->p_scope, 0);
    dict_keys(p_list_processor->p_scope, _p_env);

    for (size_t i = 0; i < key_count; i++)
    {
        printf("%-8s ", _p_env[i]);
        json_value_print(dict_get(p_list_processor->p_scope, _p_env[i]));
        putchar('\n');
    }

    *p_value = (json_value) { 
        .type = JSON_VALUE_INTEGER,
        .integer = key_count
    };

    *pp_value = p_value;

    return 1;
}