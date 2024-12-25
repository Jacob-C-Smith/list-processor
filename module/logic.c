
#include <stdio.h>
#include <json/json.h>
#include <list_processor/list_processor.h>

fn_lp_eval lp_and;
fn_lp_eval lp_or;

void lp_logic_register ( void )
{
    lp_register("and", "Logical and", lp_and);
    lp_register("or", "Logical or", lp_or);
}

int lp_and ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    size_t max = array_size(p_array);
    bool result = true;
    
    for (size_t i = 1; i < max; i++)
    {
        
        json_value *p_value = (void *) 0;
        size_t addend = 0;

        array_index(p_array, i, (void **) &p_value);

        try_again:
        switch (p_value->type)
        {
            case JSON_VALUE_STRING:
                sscanf(p_value->string, " %d", &addend);
                result &= addend;
                break;

            case JSON_VALUE_INTEGER:
                result &= (p_value->integer);
                break;

            case JSON_VALUE_ARRAY:
                lp_eval(p_list_processor, p_value, &p_value);
                goto try_again;
                continue;
            case JSON_VALUE_BOOLEAN:
                result &= p_value->boolean;
                break;
            default:
                break;
        }

    }

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_BOOLEAN,
    p_value->boolean = result;
    *pp_value = p_value;
    return 1;
}

int lp_or ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    size_t max = array_size(p_array);
    bool result = false;
    
    for (size_t i = 1; i < max; i++)
    {
        
        json_value *p_value = (void *) 0;
        size_t addend = 0;

        array_index(p_array, i, (void **) &p_value);

        try_again:
        switch (p_value->type)
        {
            case JSON_VALUE_STRING:
                sscanf(p_value->string, " %d", &addend);
                result |= addend;
                break;

            case JSON_VALUE_INTEGER:
                result |= (p_value->integer);
                break;

            case JSON_VALUE_ARRAY:
                lp_eval(p_list_processor, p_value, &p_value);
                goto try_again;
                continue;
            
            case JSON_VALUE_BOOLEAN:
                result |= p_value->boolean;
                break;
            default:
                break;
        }

    }

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_BOOLEAN,
    p_value->boolean = result;
    *pp_value = p_value;
    return 1;
}