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
    extern void lp_base_io_register ( void );
    
    // Initialize eddy
    lp_init();

    // Arithmetic
    //lp_base_arithmetic_register();

    // Logic
    //lp_base_logic_register();

    // Relational
    //lp_base_relational_register();

    // Control
    //lp_base_control_register();

    // String
    //lp_base_string_register();

    // IO
    lp_base_io_register();

    // Done
    return;
}
