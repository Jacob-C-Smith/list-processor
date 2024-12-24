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

// Initializer
/** !
 * This gets called at runtime before main. 
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void eddy_init ( void ) __attribute__((constructor));

/** !
 * Register a symbolic expression
 * 
 * @param p_name     the name of the symbolic expression
 * @param pfn_symbol the symbolic expression
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int eddy_register ( const char *p_name, json_value *(*pfn_symbol) (array *p_array) );

/** !
 * Recursively evaluate a symbolic expression
 * 
 * @param p_value the symbolic expression
 * 
 * @return the result of evaluating the symbolic expression
 */
DLLEXPORT json_value *process_symbol ( json_value *p_value );

// Cleanup
/** !
 * This gets called at runtime after main
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void stream_processor_exit ( void ) __attribute__((destructor));
