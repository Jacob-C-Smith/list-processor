/** !
 * Stream processor example program
 * 
 * 
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Stream processor
#include <stream_processor/stream_processor.h>

// Function declarations
/**!
 * Return the size of a file IF buffer == 0 ELSE read a file into buffer
 * 
 * @param path path to the file
 * @param buffer buffer
 * @param binary_mode "wb" IF true ELSE "w"
 * 
 * @return 1 on success, 0 on error
 */
size_t load_file ( const char *path, void *buffer, bool binary_mode );

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Initialized data
    stream_processor *p_stream_processor = (void *) 0;
    char _file_buffer[4096] = { 0 };
    json_value *p_value = (void *) 0;
    
    // Load a stream processor file
    load_file("resources/simple.json", &_file_buffer, false);

    // Parse the file
    json_value_parse(&_file_buffer, 0, &p_value);

    // Construct the stream processor
    stream_processor_construct(&p_stream_processor, p_value);

    // Get stream processor info
    stream_processor_info(p_stream_processor);

    // Start the stream processor
    stream_processor_start(p_stream_processor);

    // Wait for the stream processor to stop
    //stream_processor_wait_idle(p_stream_processor);

    // Success
    return EXIT_SUCCESS;
}

size_t load_file ( const char *path, void *buffer, bool binary_mode )
{

    // Argument checking 
    if ( path == 0 ) goto no_path;

    // Initialized data
    size_t  ret = 0;
    FILE   *f   = fopen(path, (binary_mode) ? "rb" : "r");
    
    // Check if file is valid
    if ( f == NULL ) goto invalid_file;

    // Find file size and prep for read
    fseek(f, 0, SEEK_END);
    ret = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);
    
    // Read to data
    if ( buffer ) 
        ret = fread(buffer, 1, ret, f);

    // The file is no longer needed
    fclose(f);
    
    // Success
    return ret;

    // Error handling
    {

        // Argument errors
        {
            no_path:
                #ifndef NDEBUG
                    log_error("[json] Null path provided to function \"%s\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // File errors
        {
            invalid_file:
                #ifndef NDEBUG
                    printf("[Standard library] Failed to load file \"%s\". %s\n",path, strerror(errno));
                #endif

                // Error
                return 0;
        }
    }
}
