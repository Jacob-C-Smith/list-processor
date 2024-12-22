// Header
#include <stream_processor/stream_processor.h>

// Preprocessor macros
#define STREAM_PROCESSOR_NAME_LENGTH_MAX 255
#define STREAM_PROCESSOR_NODE_NAME_LENGTH_MAX 63
#define STREAM_PROCESSOR_NODE_CONSTRUCTORS_QUANTITY 3

// Structure definitions
struct stream_processor_node_s
{
    char _name[STREAM_PROCESSOR_NODE_NAME_LENGTH_MAX + 1];
    enum stream_processor_node_type_e _type;
    monitor  _read_monitor;
    monitor *p_write_monitor;
    char _buffer[4096];
    union
    {
        struct 
        {
            FILE *p_f;
            char _path[FILENAME_MAX];
            bool eof;
        } input_stream;

        struct 
        {
            FILE *p_f;
            char _path[FILENAME_MAX];
            stream_processor_node *p_source;
        } output_stream;

        struct 
        {
            int i;
        } program;
    };
};

struct stream_processor_s
{
    char _name[STREAM_PROCESSOR_NAME_LENGTH_MAX + 1];
    monitor _monitor;
    node_graph *p_node_graph;
    dict *p_nodes;
    size_t node_quantity, source_quantity, drain_quantity;
    stream_processor_node *_p_sources[64];
    stream_processor_node *_p_drains[64];
    stream_processor_node *_p_nodes[];
};

// Function declarations
//int stream_processor_node_constructor         ( stream_processor_node **pp_node, const char *p_name, json_value *p_value );
int stream_processor_node_input_stream_constructor    ( stream_processor_node **pp_node, json_value *p_value );
int stream_processor_node_output_stream_constructor    ( stream_processor_node **pp_node, json_value *p_value );
int stream_processor_node_program_constructor ( stream_processor_node **pp_node, json_value *p_value );

// Data
struct 
{
    char _name[63 + 1];
    fn_stream_processor_node_constructor *pfn_constructor;
} _node_constructors[STREAM_PROCESSOR_NODE_CONSTRUCTORS_QUANTITY] = 
{
    [0] =
    {
        ._name = "input stream",
        //.pfn_constructor = (fn_stream_processor_node_constructor* ) stream_processor_node_input_stream_constructor,
    },
    [1] =
    {
        ._name = "output stream",
        //.pfn_constructor = (fn_stream_processor_node_constructor* ) stream_processor_node_output_stream_constructor,
    },
    [2] = 
    {
        ._name = "program",
        //.pfn_constructor = (fn_stream_processor_node_constructor* ) stream_processor_node_program_constructor
    }
};
dict *p_stream_processor_node_constructors = (void *) 0;
dict *p_stream_processor_tasks = (void *) 0;

static bool initialized = false;

void stream_processor_init ( void )
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
        dict_construct(&p_stream_processor_tasks, 64, 0);

        // Construct a lookup for node constructors
        dict_construct(&p_stream_processor_node_constructors, STREAM_PROCESSOR_NODE_CONSTRUCTORS_QUANTITY, 0);

        // Populate the node constructors
        for (size_t i = 0; i < STREAM_PROCESSOR_NODE_CONSTRUCTORS_QUANTITY; i++)
            dict_add(p_stream_processor_node_constructors, _node_constructors[i]._name, _node_constructors[i].pfn_constructor);
    }

    // Set the initialized flag
    initialized = true;

    // Done
    return;
}

int stream_processor_construct ( stream_processor **const pp_stream_processor, const json_value *const p_value )
{

    // Initialized data
    stream_processor *p_stream_processor = realloc(0, sizeof(stream_processor));

    // Initialize memory
    memset(p_stream_processor, '\0', sizeof(stream_processor));

    // Construct a node graph
    node_graph_construct(&p_stream_processor->p_node_graph, p_value); 

    // Store the quantity of nodes
    p_stream_processor->node_quantity = p_stream_processor->p_node_graph->node_quantity;

    // Grow the allocation
    p_stream_processor = realloc(p_stream_processor, sizeof(stream_processor) + ( sizeof(stream_processor_node*) * p_stream_processor->p_node_graph->node_quantity));

    dict_construct(&p_stream_processor->p_nodes, p_stream_processor->node_quantity, 0);

    // Construct each node
    for (size_t i = 0; i < p_stream_processor->p_node_graph->node_quantity; i++)
    {
        char *p_name = p_stream_processor->p_node_graph->_p_nodes[i]->_name;

        //stream_processor_node_constructor(&p_stream_processor->_p_nodes[i], p_name, p_stream_processor->p_node_graph->_p_nodes[i]->value);

        dict_add(p_stream_processor->p_nodes, p_stream_processor->_p_nodes[i]->_name, p_stream_processor->_p_nodes[i]);
    }

    // Construct each connection
    for (size_t i = 0; i < p_stream_processor->p_node_graph->node_quantity; i++)
    {

        node *p_node = p_stream_processor->p_node_graph->_p_nodes[i];
        stream_processor_node *p_stream_processor_node = p_stream_processor->_p_nodes[i];

        if ( p_node->in_quantity  == 0 ) p_stream_processor->_p_sources[p_stream_processor->source_quantity++] = p_stream_processor_node;
        if ( p_node->out_quantity == 0 ) p_stream_processor->_p_drains[p_stream_processor->drain_quantity++]   = p_stream_processor_node;
    }
    
    // Returna pointer to the caller
    *pp_stream_processor = p_stream_processor;

    // Success
    return 1;
}

int stream_processor_info ( stream_processor *p_stream_processor )
{

    // Print each node in the graph
    node_graph_print(p_stream_processor->p_node_graph);

    // Success
    return 1;
}

void stream_processor_exit ( void )
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
