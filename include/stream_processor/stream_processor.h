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
DLLEXPORT void stream_processor_init ( void ) __attribute__((constructor));

/** !
 * Construct a stream processor from a json value
 * 
 * @param pp_stream_processor result
 * @param p_value             the json value
 * 
 * @return 1 on success, 0 on error
 */
int stream_processor_construct ( stream_processor **const pp_stream_processor, const json_value *const p_value );

int stream_processor_info ( stream_processor *p_stream_processor );

int stream_processor_start ( stream_processor *p_stream_processor );

/** !
 * Add a stream processor task property
 * 
 * @param p_name                    the name 
 * @param pfn_stream_processor_task the stream processor task
 * 
 * @return 1 on success, 0 on error
 */
int stream_processor_task_add ( const char *p_name, fn_stream_processor_task *pfn_stream_processor_task );

// Cleanup
/** !
 * This gets called at runtime after main
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void stream_processor_exit ( void ) __attribute__((destructor));
