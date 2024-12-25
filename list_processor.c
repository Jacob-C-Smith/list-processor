// Header
#include <list_processor/list_processor.h>

// External declarations
extern fn_lp_eval lp_read;
extern fn_lp_eval lp_write;

static bool initialized = false;
static dict *p_global = (void *) 0;

int lp_help ( list_processor *p_list_processor, array *p_array, json_value **pp_value );

struct 
{
    char _name[64];
    struct
    {
        char _name[32];
        fn_lp_eval *pfn_lp_eval;
    } _pfn_lp_eval[32];
} _p_pfn_lp_symbols[] = {
    [LP_INTRINSIC_ARITHMETIC] = 
    {
        ._name = "arithmetic",
        ._pfn_lp_eval = 
        {
            [0] = { 0 }
        }
    },
    [LP_INTRINSIC_IO] = 
    {
        ._name = "io",
        ._pfn_lp_eval = 
        {
            [0] = 
            {
                ._name = "read",
                .pfn_lp_eval = lp_read
            },
            [1] = 
            {
                ._name = "write",
                .pfn_lp_eval = lp_write
            }
        }
    }
};

void lp_init ( void )
{

    // State check
    if ( initialized == true ) return;

    // Initialize the log library
    log_init();

    // Initialize the sync library
    sync_init();

    // Initialize the hash cache library
    hash_cache_init();

    // Construct a global lookup
    dict_construct(&p_global, 1024, 0);

    // Set the initialized flag
    initialized = true;

    // Done
    return;
}

int lp_constructor ( list_processor **pp_list_processor, size_t bump_size )
{

    // Argument check
    if ( pp_list_processor == (void *) 0 ) goto no_list_processor;
    if ( bump_size         ==          0 ) bump_size = 4096;

    // External declarations
    extern fn_lp_eval lp_read;
    extern fn_lp_eval lp_write;
    extern fn_lp_eval lp_help;
    extern fn_lp_eval lp_import;
    extern fn_lp_eval lp_add;
    extern fn_lp_eval lp_sub;
    extern fn_lp_eval lp_mul;
    extern fn_lp_eval lp_div;
    extern fn_lp_eval lp_while;
    extern fn_lp_eval lp_if;
    extern fn_lp_eval lp_and;
    extern fn_lp_eval lp_or;
    extern fn_lp_eval lp_eq;
    extern fn_lp_eval lp_neq;
    extern fn_lp_eval lp_get;
    extern fn_lp_eval lp_set;
    extern fn_lp_eval lp_env;

    // Initialized data
    list_processor *p_list_processor = realloc(0, sizeof(list_processor) + bump_size);

    // Error check
    if ( p_list_processor == (void *) 0 ) goto no_mem;

    // Construct an environment
    dict_construct(&p_list_processor->p_env, 2048, 0);
    dict_construct(&p_list_processor->p_scope, 2048, 0);

    // Set the read and write symbols
    lp_env_set(p_list_processor, "read", lp_read);
    lp_env_set(p_list_processor, "write", lp_write);
    lp_env_set(p_list_processor, "help", lp_help);
    lp_env_set(p_list_processor, "import", lp_import);
    lp_env_set(p_list_processor, "+", lp_add);
    lp_env_set(p_list_processor, "-", lp_sub);
    lp_env_set(p_list_processor, "*", lp_mul);
    lp_env_set(p_list_processor, "/", lp_div);
    lp_env_set(p_list_processor, "if", lp_if);
    lp_env_set(p_list_processor, "while", lp_while);
    lp_env_set(p_list_processor, "&", lp_and);
    lp_env_set(p_list_processor, "|", lp_or);
    lp_env_set(p_list_processor, "==", lp_eq);
    lp_env_set(p_list_processor, "!=", lp_neq);
    lp_env_set(p_list_processor, "get", lp_get);
    lp_env_set(p_list_processor, "set", lp_set);
    lp_env_set(p_list_processor, "env", lp_env);
    
    // Set the max size
    p_list_processor->size = bump_size;
    
    // Return a pointer to the caller
    *pp_list_processor = p_list_processor;

    // Success
    return 1;

    // TODO
    no_list_processor:
        return 0;
    
    // Error handling
    {
        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    log_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
        }
    }
}

int lp_help_print ( char *p_key, size_t i )
{

    // Print 
    printf("%s:%i\n", p_key, i);

    // Success
    return 1;
}

int lp_help ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{
    
    // Initialized data
    json_value *p_result = 0;
    void (*function)(const void *const p_key, size_t i );
    char *_p_binding[1024] = { 0 };
    size_t len = dict_keys(p_list_processor->p_env, 0);
    
    dict_keys(p_list_processor->p_env, (const char **const) _p_binding);

    // Print each binding
    for (size_t i = 0; i < len; i++) printf("\n - %s",_p_binding[i]);
    printf("\n\n");
    
    *pp_value = p_result;

    // Success
    return 1;
}

int lp_register ( const char *const p_name, fn_lp_eval *pfn_lp_eval )
{

    // Argument check
    if ( p_name      == (void *) 0 ) goto no_name;
    if ( pfn_lp_eval == (void *) 0 ) goto no_fn_lp_eval;

    // Add the symbolic expression
    dict_add(p_global, p_name, pfn_lp_eval);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            
            // TODO
            no_name:
            no_fn_lp_eval:
            
                // Error
                return 0;
        }
    }
}

int lp_env_set ( list_processor *p_list_processor, const char *p_name, fn_lp_eval *pfn_lp_eval )
{

    // Argument check
    if ( p_list_processor == (void *) 0 ) goto no_list_processor;
    if ( p_name           == (void *) 0 ) goto no_name;
    if ( pfn_lp_eval      == (void *) 0 ) goto no_fn_lp_eval;
    
    // Add the symbol to the environment
    dict_add(p_list_processor->p_env, p_name, pfn_lp_eval);

    // Log
    fprintf(stderr, "\033[01;94m[lp]\033[00;0m %p -> \033[01;94m\'%s\'\033[00;0m\n", pfn_lp_eval, p_name);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_list_processor:
                #ifndef NDEBUG
                    log_error("[list processor] [environmnet] Null pointer provided for parameter \"p_list_processor\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_name:
                #ifndef NDEBUG
                    log_error("[list processor] [environmnet] Null pointer provided for parameter \"p_name\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_fn_lp_eval:
                #ifndef NDEBUG
                    log_error("[list processor] [environmnet] Null pointer provided for parameter \"pfn_lp_eval\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

// 
int lp_eval ( list_processor *p_list_processor, json_value *p_value, json_value **pp_value )
{

    
    static int z = 0;

    // Initialized data
    json_value *p_result = (void *) 0;

    for (size_t i = 0; i < z; i++) fprintf(stdout, "  ");
    //json_value_print(p_value);putchar('\n');fflush(stdout);
    
    try_again:
    switch (p_value->type)
    {
        case JSON_VALUE_ARRAY:

            // Initialized data
            {
                size_t      size          = array_size(p_value->list);
                json_value *p_first_value = (void *) 0;
                fn_lp_eval *pfn_lp_eval   = (void *) 0;
                // 
                array_index(p_value->list, 0, (void **)&p_first_value);

                if ( p_first_value->type == JSON_VALUE_ARRAY )
                {
                    lp_eval(p_list_processor, p_first_value, &p_first_value);
                    goto try_again;
                }
                
                pfn_lp_eval = dict_get(p_list_processor->p_env, p_first_value->string);
                
                if ( pfn_lp_eval == (void *) 0 ){
                    log_error("[list processor] No binding for \"%s\"\n", p_first_value->string);
                    getchar();
                    goto no_bind;
                } 
                
                p_result = (void *)pfn_lp_eval(p_list_processor, p_value->list, &p_value);

                break;
            }
            
            break;
            
        case JSON_VALUE_STRING:
        case JSON_VALUE_INTEGER:
        case JSON_VALUE_BOOLEAN:
        case JSON_VALUE_NUMBER:
        case JSON_VALUE_OBJECT:
            p_result = p_value;
            break;

        default:
            break;
    }

    *pp_value = p_value;

    // Success
    return 1;
    no_bind:
        return 0;

}

void lp_exit ( void )
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
