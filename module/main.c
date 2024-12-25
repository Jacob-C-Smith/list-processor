/** !
 * Eddy Arithmetic operations
 * 
 * @file arithmetic.c
 * 
 * @author Jacob Smith
 */

// standard library
#include <stdio.h>

// json module
#include <json/json.h>

// list processor module
#include <list_processor/list_processor.h>

// Forward declarations
void lp_base_init ( void ) __attribute__((constructor));


void lp_base_init ( void ) 
{
    // External functions
    extern void lp_init ( void );
    
    extern void lp_arithmetic_register ( void );
    extern void lp_env_register ( void );
    extern void lp_logic_register ( void );
    extern void lp_module_register ( void );
    extern void lp_relational_register ( void );
    extern void lp_control_register ( void );
    extern void lp_string_register ( void );
    extern void lp_io_register ( void );

    // Initialize eddy
    lp_init();

    // Arithmetic
    lp_arithmetic_register();

    // Env
    lp_env_register();

    // Logic
    lp_logic_register();

    // Module
    lp_module_register();

    // Relational
    lp_relational_register();

    // Control
    lp_control_register();

    // String
    //lp_string_register();

    // IO
    lp_io_register();

    // Done
    return;
}
