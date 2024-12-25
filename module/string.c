// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>

// #include <array/array.h>
// #include <json/json.h>
// #include <list_processor/list_processor.h>

// json_value *lp_len ( array *p_array );

// void lp_base_string_register ( void )
// {

//     // Length
//     lp_register("len", lp_len);

//     fprintf(stderr, "[list processor] [string] Registered\n");

// }

// json_value *lp_len ( array *p_array )
// {

//     json_value *p_value = (void *) 0;
//     signed length = -1;
    
//     array_index(p_array, 1, (void **) &p_value);

//     try_again:
//     switch (p_value->type)
//     {
//         case JSON_VALUE_STRING:
//             length = strlen(p_value->string);
//             break;

//         case JSON_VALUE_ARRAY:
//             p_value = lp_eval(p_value);
//             goto try_again;
            
//         case JSON_VALUE_INTEGER:
//             length = p_value->integer;
//         default:
//             break;
//     }

//     p_value = realloc(0, sizeof(json_value));
//     *p_value = (json_value) { .type = JSON_VALUE_INTEGER, .integer = length };

//     return p_value;
// }
