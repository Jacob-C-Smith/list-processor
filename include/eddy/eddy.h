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

enum stream_processor_node_type_e 
{
    STERAM_PROCESSOR_NODE_TYPE_INPUT_STREAM  = 0,
    STERAM_PROCESSOR_NODE_TYPE_OUTPUT_STREAM = 1,
    STERAM_PROCESSOR_NODE_TYPE_PROGRAM       = 2,
    STERAM_PROCESSOR_NODE_TYPE_QUANTITY      = 3
};

struct stream_processor_s;
struct stream_processor_node_s;

typedef struct stream_processor_s      stream_processor;
typedef struct stream_processor_node_s stream_processor_node;

typedef int(fn_stream_processor_node_constructor)(stream_processor_node **pp_node, const json_value *const p_value);
typedef int(fn_stream_processor_task)(stream_processor_node *p_node);

// Initializer
/** !
 * This gets called at runtime before main. 
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void eddy_init ( void ) __attribute__((constructor));
DLLEXPORT int eddy_register(const char *p_name, json_value *(*pfn_symbol)(array *p_array));
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
