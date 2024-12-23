#include <stdio.h>
#include <json/json.h>
#include <eddy/eddy.h>

void eddy_base_init ( void ) __attribute__((constructor));

void eddy_base_init ( void ) 
{
    // External functions
    extern void eddy_base_arithmetic_register ( void );
    extern void eddy_base_logic_register ( void );
    extern void eddy_base_relational_register ( void );
    extern void eddy_base_control_register ( void );
    extern void eddy_base_string_register ( void );
    extern void eddy_base_io_register ( void );
    
    // Initialize eddy
    eddy_init();

    // Arithmetic
    eddy_base_arithmetic_register();

    // Logic
    eddy_base_logic_register();

    // Relational
    eddy_base_relational_register();

    // Control
    eddy_base_control_register();

    // String
    eddy_base_string_register();

    // IO
    eddy_base_io_register();
    
    fprintf(stderr, "[eddy] Registered\n");

    // Done
    return;
}
