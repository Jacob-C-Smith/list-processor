#include <stdio.h>



struct list_processor_symbol_s;
typedef struct list_processor_symbol_s list_processor_symbol;

struct list_processor_cons_cell_s;
typedef struct list_processor_cons_cell_s list_processor_cons_cell;

struct list_processor_s;
typedef struct list_processor_s list_processor;

struct list_processor_cons_cell_s
{

    int _symbol;

    union
    {
        list_processor_cons_cell *p_cons;
        list_processor_symbol    *p_symbol;
    };

    list_processor_cons_cell *p_cdr;
};

struct list_processor_s
{
    size_t node_quantity;
};

