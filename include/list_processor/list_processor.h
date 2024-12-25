/** !
 * 
 * 
 * 
 */

// Include guard
#pragma once

// json module
#include <json/json.h>

// sync module
#include <sync/sync.h>

// node module
#include <node/node.h>

// parallel module
#include <parallel/parallel.h>
#include <parallel/thread.h>

enum list_processor_intrinsics_e
{
    LP_INTRINSIC_ARITHMETIC = 1,
    LP_INTRINSIC_CONTROL    = 2,
    LP_INTRINSIC_IO         = 3,
    LP_INTRINSIC_LOGIC      = 4,
    LP_INTRINSIC_RELATIONAL = 5,
    LP_INTRINSIC_STIRNG     = 6
};

struct list_processor_s;
struct symbolic_expression_property_s;

typedef struct list_processor_s list_processor;
typedef struct symbolic_expression_property_s symbolic_expression_property;
typedef int (fn_lp_eval)(list_processor *p_list_processor, array *p_in, json_value **p_out);

struct list_processor_s
{
    dict *p_env;
    dict *p_scope;
    size_t size;
    unsigned char _bump[];
};

struct symbolic_expression_property_s
{
    const char  _name[64];
    fn_lp_eval *pfn_lp_eval;
};

// Initializer
/** !
 * This gets called at runtime before main. 
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void lp_init ( void ) __attribute__((constructor));

DLLEXPORT int lp_constructor ( list_processor **pp_list_processor, size_t bump_size );

// Environment
DLLEXPORT int lp_env_set ( list_processor *p_list_processor, const char *p_name, fn_lp_eval *pfn_lp_eval );
DLLEXPORT int lp_env_get ( list_processor *p_list_processor, const char *p_name, void *a );

/** !
 * Register a symbolic expression
 * 
 * @param p_name     the name of the symbolic expression
 * @param pfn_symbol the symbolic expression
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int lp_register ( const char *const p_name, fn_lp_eval *pfn_lp_eval );

// Evaluate
/** !
 * Recursively evaluate a symbolic expression
 * 
 * @param p_list_processor the list processor
 * @param p_value          the symbolic expression
 * 
 * @return the result of evaluating the symbolic expression
 */
DLLEXPORT int lp_eval ( list_processor *p_list_processor, json_value *p_value, json_value **pp_value );

// Cleanup
/** !
 * This gets called at runtime after main
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void lp_exit ( void ) __attribute__((destructor));
