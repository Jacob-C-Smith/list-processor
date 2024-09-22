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
int stream_processor_node_constructor         ( stream_processor_node **pp_node, const char *p_name, json_value *p_value );
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
        .pfn_constructor = (fn_stream_processor_node_constructor* ) stream_processor_node_input_stream_constructor,
    },
    [1] =
    {
        ._name = "output stream",
        .pfn_constructor = (fn_stream_processor_node_constructor* ) stream_processor_node_output_stream_constructor,
    },
    [2] = 
    {
        ._name = "program",
        .pfn_constructor = (fn_stream_processor_node_constructor* ) stream_processor_node_program_constructor
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
        char *p_name = &p_stream_processor->p_node_graph->_p_nodes[i]->_name;

        stream_processor_node_constructor(&p_stream_processor->_p_nodes[i], p_name, p_stream_processor->p_node_graph->_p_nodes[i]->value);

        dict_add(p_stream_processor->p_nodes, &p_stream_processor->_p_nodes[i]->_name, p_stream_processor->_p_nodes[i]);
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

void *stream_processor_input_stream_thread ( stream_processor_node *p_stream_processor_node )
{

    static int d = 0;

    while (!feof(p_stream_processor_node->input_stream.p_f))
    {

        monitor_wait(&p_stream_processor_node->_read_monitor);

        printf("read %d\n", d);
        d++;
        
        fread(p_stream_processor_node->_buffer, sizeof(p_stream_processor_node->_buffer), 1, p_stream_processor_node->input_stream.p_f);

        monitor_notify(p_stream_processor_node->p_write_monitor);
    };

    p_stream_processor_node->input_stream.eof = true;

    // Success
    return (void *) 1;
}

void *stream_processor_output_stream_thread ( stream_processor_node *p_stream_processor_node )
{


    static int d = 0;

    while (1)
    {

        monitor_wait(&p_stream_processor_node->_read_monitor);

        printf("write %d\n", d);
        d++;

        fwrite(p_stream_processor_node->output_stream.p_source->_buffer, sizeof(p_stream_processor_node->output_stream.p_source->_buffer), 1, p_stream_processor_node->output_stream.p_f);
        
        monitor_notify(p_stream_processor_node->p_write_monitor);
    };

    // Success
    return (void *) 1;
}

int stream_processor_start ( stream_processor *p_stream_processor )
{

    monitor_create(&p_stream_processor->_monitor);

    p_stream_processor->_p_sources[0]->p_write_monitor = &p_stream_processor->_p_drains[0]->_read_monitor;
    p_stream_processor->_p_drains[0]->p_write_monitor = &p_stream_processor->_p_sources[0]->_read_monitor;
    p_stream_processor->_p_drains[0]->output_stream.p_source = p_stream_processor->_p_sources[0];

    for (size_t i = 0; i < p_stream_processor->source_quantity; i++)
    {
        stream_processor_node *p_node = p_stream_processor->_p_sources[i];
        parallel_thread *p_parallel_thread = (void *) 0;

        switch(p_node->_type)
        {
            case STERAM_PROCESSOR_NODE_TYPE_INPUT_STREAM:
                
                parallel_thread_start(&p_parallel_thread, (fn_parallel_task *)stream_processor_input_stream_thread, (void *) p_node);

                break;
        }
    }

    for (size_t i = 0; i < p_stream_processor->drain_quantity; i++)
    {
        stream_processor_node *p_node = p_stream_processor->_p_drains[i];
        parallel_thread *p_parallel_thread = (void *) 0;

        switch(p_node->_type)
        {
            case STERAM_PROCESSOR_NODE_TYPE_OUTPUT_STREAM:
                
                parallel_thread_start(&p_parallel_thread, (fn_parallel_task *)stream_processor_output_stream_thread, (void *) p_node);

                break;
        }
    }

    //while(p_stream_processor->_p_sources[0]->input_stream.eof == false)
    {
        monitor_notify_all(&p_stream_processor->_p_sources[0]->_read_monitor);
    }
    while(p_stream_processor->_p_sources[0]->input_stream.eof == false);

    // Success
    return 1;
}

int stream_processor_task_add ( const char *p_name, fn_stream_processor_task *pfn_stream_processor_task )
{
    dict_add(p_stream_processor_tasks, p_name, pfn_stream_processor_task);
    return 1;
}

int stream_processor_node_constructor ( stream_processor_node **pp_node, const char *p_name, json_value *p_value )
{

    // Initialized data
    stream_processor_node *p_node = (void *) 0;
    dict *p_dict = p_value->object;
    json_value *p_type_value = dict_get(p_dict, "type");
    fn_stream_processor_node_constructor *pfn_node_constructor = dict_get(p_stream_processor_node_constructors, p_type_value->string);
    
    // Strategy
    pfn_node_constructor(&p_node, p_value);

    strncpy(p_node->_name, p_name, strlen(p_name));

    // Return a pointer to the caller
    *pp_node = p_node;

    // Success
    return 1;
}

int stream_processor_node_input_stream_constructor ( stream_processor_node **pp_node, json_value *p_value )
{

    // Initialized data
    stream_processor_node *p_node = realloc(0, sizeof(stream_processor_node));
    dict *p_dict = p_value->object;
    json_value *p_path_value = dict_get(p_dict, "path");
    const char *const p_path = p_path_value->string;

    // Open the input stream
    p_node->input_stream.p_f = fopen(p_path, "r");
    monitor_create(&p_node->_read_monitor);

    // Copy the input stream path
    strncpy(&p_node->input_stream._path, p_path, strlen(p_path));

    // Store the node type
    p_node->_type = STERAM_PROCESSOR_NODE_TYPE_INPUT_STREAM;

    // Return a pointer to the caller
    *pp_node = p_node;

    // Success
    return 1;
}

int stream_processor_node_output_stream_constructor ( stream_processor_node **pp_node, json_value *p_value )
{

    // Initialized data
    stream_processor_node *p_node = realloc(0, sizeof(stream_processor_node));
    dict *p_dict = p_value->object;
    json_value *p_path_value = dict_get(p_dict, "path");
    const char *const p_path = p_path_value->string;

    // Open the output stream
    p_node->output_stream.p_f = fopen(p_path, "w+");
    monitor_create(&p_node->_read_monitor);

    // Copy the output stream path
    strncpy(&p_node->output_stream._path, p_path, strlen(p_path));

    // Store the node type
    p_node->_type = STERAM_PROCESSOR_NODE_TYPE_OUTPUT_STREAM;

    // Return a pointer to the caller
    *pp_node = p_node;

    // Success
    return 1;
}

int stream_processor_node_program_constructor ( stream_processor_node **pp_node, json_value *p_value )
{
    
    // Initialized data
    stream_processor_node *p_node = realloc(0, sizeof(stream_processor_node));
    dict *p_dict = p_value->object;
    json_value *p_task_value = dict_get(p_dict, "task");
    const char *const p_task = p_task_value->string;

    monitor_create(&p_node->_read_monitor);

    // Store the node type
    p_node->_type = STERAM_PROCESSOR_NODE_TYPE_PROGRAM;
    
    // Return a pointer to the caller
    *pp_node = p_node;

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
