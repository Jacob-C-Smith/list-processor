/** !
 * Eddy module operations
 * 
 * @file module.c
 * 
 * @author Jacob Smith
 */

// standard library
#include <stdio.h>

// posix
#include <dlfcn.h>

// json module
#include <json/json.h>

// list processor module
#include <list_processor/list_processor.h>

// Forward declarations
int lp_import ( list_processor *p_list_processor, array *p_array, json_value **pp_value );

void lp_module_register ( void )
{

    lp_register("import", "Open a shared object and add symbols to this scope.", lp_import);

    // Done
    return;
}

int lp_import ( list_processor *p_list_processor, array *p_array, json_value **pp_value )
{

    // Initialized data
    int result = 1;
    json_value *p_value = realloc(0, sizeof(json_value)),
               *p_a = (void *) 0;
    char _path[FILENAME_MAX] = { 0 };
    void *p_dlsym_handle = (void *) 0;

    // Library to import
    array_index(p_array, 1, (void **) &p_a);
    
    try_again:
    switch (p_a->type)
    {

        // Any type
        case JSON_VALUE_STRING:
            
            // Done
            break;
            
        case JSON_VALUE_ARRAY:
            
            // Evaluate the list
            lp_eval(p_list_processor, p_a, &p_a);

            // Print the list
            goto try_again;

        // Default
        case JSON_VALUE_INVALID:
        case JSON_VALUE_OBJECT:
        case JSON_VALUE_BOOLEAN:
        case JSON_VALUE_INTEGER:
        case JSON_VALUE_NUMBER:

        default:

            // Error
            result = 0;

            // Done
            goto done;
    }

    // Construct the library path
    sprintf(_path, "lib%s.so", p_a->string);

    // Open the shared object
    p_dlsym_handle = dlopen(_path, RTLD_LAZY);

    // 
    size_t manifest_size = *(size_t *)dlsym(p_dlsym_handle, "manifest_size");
    symbolic_expression_property *p_manifest = dlsym(p_dlsym_handle, "_manifest");

    for (size_t i = 0; i < manifest_size; i++)
        lp_env_set(p_list_processor, p_manifest[i]._name, p_manifest[i].pfn_lp_eval);

    done:

    log_info("[%s] Loaded %d symbols from \"%s\"\n", p_a->string, manifest_size, _path);

    // Populate the value
    *p_value = (json_value) { .type = JSON_VALUE_INTEGER, .integer = result };

    // Return a pointer to the caller
    *pp_value = p_value;

    // Success
    return 1;
}

