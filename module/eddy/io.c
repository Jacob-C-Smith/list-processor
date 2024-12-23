#include <stdio.h>
#include <json/json.h>
#include <eddy/eddy.h>

json_value *eddy_read ( array *p_array );
json_value *eddy_write ( array *p_array );

void eddy_base_io_register ( void )
{

    // Read
    eddy_register("read", eddy_read);

    // Write
    eddy_register("write", eddy_write);

    fprintf(stderr, "[eddy] [io] Registered\n");

}

json_value *eddy_read ( array *p_array )
{


    json_value *p_value = realloc(0, sizeof(json_value));
    json_value *p_fd = (void *) 0;
    json_value *p_text = (void *) 0;
    
    extern json_value *value_alloc ( void );
    extern const char *string_alloc ( size_t len );

    p_value->type   = JSON_VALUE_STRING,
    p_value->string = string_alloc(256);
    
    scanf(" %[^\n]255s", p_value->string);
    getchar();

    return p_value;
}

json_value *eddy_write ( array *p_array )
{

    json_value *p_value = realloc(0, sizeof(json_value)),
               *p_a = (void *) 0;

    array_index(p_array, 1, (void **) &p_a);
    
    try_again:
    switch (p_a->type)
    {
        case JSON_VALUE_BOOLEAN:
        case JSON_VALUE_STRING:
        case JSON_VALUE_INTEGER:
        case JSON_VALUE_NUMBER:
            json_value_print(p_a);
            putchar('\n');
            break;
        case JSON_VALUE_ARRAY:
            p_a = process_symbol(p_a);
            goto try_again;
        default:
            break;
    }

    p_value->type    = JSON_VALUE_INTEGER,
    p_value->integer = 1;

    return p_value;
}

