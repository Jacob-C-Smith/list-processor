/** !
 * list processor lexer
 * 
 * @file lexer.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// json 
#include <json/json.h>

// list processor
#include <list_processor/list_processor.h>

/** !
 * Parse command line arguments
 * 
 * @param argc               the argc parameter of the entry point
 * @param argv               the argv parameter of the entry point

 * 
 * @return void on success, program abort on failure
 */
void parse_command_line_arguments ( int argc, const char *argv[], size_t *p_memory_size );

// Entry point
int main ( int argc, const char *argv[] )
{
    
    while ( !feof(stdin) )
    {

        // Initialized data
        char _text[256] = { 0 };
        int t = 0;
        size_t parsed = 0;
        size_t token_len = 0;
        char _token[256] = { 0 };
        char *p_token = _text;
        char c = 0;

        // Prompt
        //fprintf(stderr, "\r🐶 ");

        // Read
        c = getchar();
        
        // 
        while ( !feof(stdin) )
        {
            
            // Initialized data
            int l_t = t;
            

            //
            switch (c)
            {
                case '(':
                case ')':
                    printf("{\"separator\":\"%c\"}", c);
                    putchar('\n');
                    
                    break;
                case '\n':
                case ' ':

                    break;
                case '\"':
                    printf("{\"identifier\":");
                
                    do  { putchar(c); c = getchar(); } 
                    while
                    (
                        c != '\"'
                    );
                    c = getchar();
                    printf("\"}\n");

                    break;
                default:            
                    printf("{\"identifier\":\"");
                    
                    do  { putchar(c); c = getchar(); } 
                    while
                    (
                        c != ' ' &&
                        c != '(' &&
                        c != ')' 
                    );
                    ungetc(c, stdin);
                    printf("\"}\n");
                    break;
            }
            
            // 
            c = getchar();

        }
    }
        
    fprintf(stderr, "\033[44m%s \033[0m", argv[0]);

    // EOF?
    if ( feof(stdin) ) fprintf(stderr, "\033[44m>>> \033[0m");

    // Success
    return EXIT_SUCCESS;
}
