#include <stdio.h>
#include <json/json.h>
#include <eddy/eddy.h>

json_value *my_module_a ( array *p_array );
json_value *my_module_b ( array *p_array );
json_value *my_module_c ( array *p_array );

void my_module_init ( void ) __attribute__((constructor));

void my_module_init ( void ) 
{

    // Initialize eddy
    eddy_init();

    // My Module
    eddy_register("my_module_alice"  , my_module_a);
    eddy_register("my_module_bob"    , my_module_b);
    eddy_register("my_module_charlie", my_module_c);

    log_info("[my module] Registered\033[0m"); printf("\n");

    // Done
    return;
}

json_value *my_module_a ( array *p_array )
{
    json_value *p_value = realloc(0, sizeof(json_value));
    *p_value = (json_value) {.type = JSON_VALUE_STRING, .string = "Alice"};
    return p_value;
}

json_value *my_module_b ( array *p_array )
{
    json_value *p_value = realloc(0, sizeof(json_value));
    *p_value = (json_value) {.type = JSON_VALUE_STRING, .string = "Bob"};
    return p_value;
}

json_value *my_module_c ( array *p_array )
{
    json_value *p_value = realloc(0, sizeof(json_value));
    *p_value = (json_value) {.type = JSON_VALUE_STRING, .string = "Charlie"};
    return p_value;
}
