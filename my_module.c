#include <stdio.h>
#include <json/json.h>
#include <list_processor/list_processor.h>

int my_module_a (list_processor *p_list_processor, array *p_in, json_value **p_out);
int my_module_b (list_processor *p_list_processor, array *p_in, json_value **p_out);
int my_module_c (list_processor *p_list_processor, array *p_in, json_value **p_out);

// Data
symbolic_expression_property _manifest[] =
{
    { .pfn_lp_eval = my_module_a, ._name = "alice" },
    { .pfn_lp_eval = my_module_b, ._name = "bob" },
    { .pfn_lp_eval = my_module_c, ._name = "charlie" }
};
size_t manifest_size = (sizeof(_manifest)/sizeof(symbolic_expression_property));

void my_module_init ( void ) __attribute__((constructor));

void my_module_init ( void ) 
{
    
    // My Module
    for (size_t i = 0; i < manifest_size; i++)
        lp_register(_manifest[i]._name, _manifest[i].pfn_lp_eval);

    // Done
    return;
}

int my_module_a (list_processor *p_list_processor, array *p_in, json_value **p_out)
{
    json_value *p_value = realloc(0, sizeof(json_value));
    *p_value = (json_value) {.type = JSON_VALUE_STRING, .string = "Alice"}, *p_out = p_value;
    return 1;
}

int my_module_b (list_processor *p_list_processor, array *p_in, json_value **p_out)
{
    json_value *p_value = realloc(0, sizeof(json_value));
    *p_value = (json_value) {.type = JSON_VALUE_STRING, .string = "Bob"}, *p_out = p_value;
    return 1;
}

int my_module_c (list_processor *p_list_processor, array *p_in, json_value **p_out)
{
    json_value *p_value = realloc(0, sizeof(json_value));
    *p_value = (json_value) {.type = JSON_VALUE_STRING, .string = "Charlie"}, *p_out = p_value;
    return 1;
}
