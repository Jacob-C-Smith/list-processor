
#include <stdio.h>
#include <json/json.h>
#include <eddy/eddy.h>

json_value *eddy_and ( array *p_array );
json_value *eddy_or ( array *p_array );

void eddy_base_logic_register ( void )
{

    // Logical AND
    eddy_register("&", eddy_and);

    // Logical OR
    eddy_register("|", eddy_or);
}


json_value *eddy_and ( array *p_array )
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
                p_value = process_symbol(p_value);
                goto try_again;
                continue;
            
            default:
                break;
        }

    }

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_BOOLEAN,
    p_value->boolean = result;

    return p_value;
}

json_value *eddy_or ( array *p_array )
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
                p_value = process_symbol(p_value);
                goto try_again;
                continue;
            
            default:
                break;
        }

    }

    json_value *p_value = realloc(0, sizeof(json_value));
    p_value->type    = JSON_VALUE_BOOLEAN,
    p_value->boolean = result;

    return p_value;
}