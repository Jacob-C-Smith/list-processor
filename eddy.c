// Header
#include <eddy/eddy.h>

dict *p_eddy_bindings = (void *) 0;

static bool initialized = false;

void eddy_init ( void )
{

    // State check
    if ( initialized == true ) return;

    // Initialize the log library
    log_init();

    // Initialize the sync library
    sync_init();

    // Initialize the hash cache library
    hash_cache_init();

    // Initialize the stream processor
    {

        // Construct a lookup for tasks
        dict_construct(&p_eddy_bindings, 1024, 0);
    }

    // Set the initialized flag
    initialized = true;

    // Done
    return;
}

int eddy_register(const char *p_name, json_value *(*pfn_symbol)(array *p_array))
{

    dict_add(p_eddy_bindings, p_name, pfn_symbol);

    // Success
    return 1;
}


json_value *process_symbol ( json_value *p_value )
{
    static int z = 0;
    json_value *p_result = (void *) 0;

    for (size_t i = 0; i < z; i++) fprintf(stdout, "  ");
    //json_value_print(p_value);putchar('\n');fflush(stdout);
    
    try_again:
    switch (p_value->type)
    {
        case JSON_VALUE_ARRAY:
            size_t size = array_size(p_value->list);
            
            {
                json_value *p_first_value = (void *) 0;
                array_index(p_value->list, 0, (void **)&p_first_value);

                if ( p_first_value->type == JSON_VALUE_ARRAY )
                {
                    p_first_value = process_symbol(p_first_value);
                    goto try_again;
                }
                
                json_value *(*pfn_func)(array *p_array) = dict_get(p_eddy_bindings, p_first_value->string);
                p_result = pfn_func(p_value->list);

                break;
            }
            
            break;
        case JSON_VALUE_STRING:
            p_result = p_value;
            break;
        case JSON_VALUE_INTEGER:
            p_result = p_value;
            break;
        default:
            break;
    }

    // Success
    return p_result;
}


void eddy_exit ( void )
{
    
    // State check
    if ( initialized == false ) return;

    // Clean up the log library
    log_exit();

    // Clean up the sync library
    sync_exit();

    // Clean up the hash cache library
    hash_cache_exit();

    // Clear the initialized flag
    initialized = false;

    // Done
    return;
}
