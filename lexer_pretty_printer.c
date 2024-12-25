/** !
 * eddy lexer pretty printer
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
                    printf("{\033[01;91m\"separator\"\033[0m:\"%c\"}", c);
                    putchar('\n');
                    
                    break;
                case '\n':
                case ' ':

                    break;
                case '\"':
                    printf("{\033[01;91m\"separator\"\033[00;0m:\"%c\"}", c);
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
                    printf("{\033[01;34m\"identifier\"\033[00;0m:\"\033[03;3m");
                    
                    do  { putchar(c); c = getchar(); } 
                    while
                    (
                        c != ' ' &&
                        c != '(' &&
                        c != ')' 
                    );
                    ungetc(c, stdin);
                    printf("\033[00;0m\"}\n");
                    break;
            }
            
            // 
            c = getchar();

        }
    }
    

    // Success
    return EXIT_SUCCESS;
}
