#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "utilities.h"

/*
    Read in a line of text from the console

    Params: buf: pointer to an allocated buffer
            len: allocated size of buffer
    Returns: length of string read or -1 for error
*/
int getLineInput(char buf[], size_t len)
{
    memset(buf, 0, len);
    fpurge(stdin); //clears any junk in stdin
    char *bufp;
    bufp = buf;
    while(1) {
        vTaskDelay(100/portTICK_PERIOD_MS);
        *bufp = getchar();
        if(*bufp != '\0' && *bufp != 0xFF && *bufp != '\r') { //ignores null input, 0xFF, CR in CRLF
            if(*bufp == '\n') {
                //'enter' (EOL) handler 
                *bufp = '\0';
                break;
            } 
            else if (*bufp == '\b') {
                //backspace handler
                if(bufp-buf >= 1) { 
                    putchar('\b');
                    bufp--; 
                }
            }
            else { 
                putchar(*bufp);
                bufp++; 
            } //pointer to next character
        }
        
        // Only accept len-1 characters, (len) character being null terminator.
        if(bufp-buf > (len)-2) {
            bufp = buf + (len -1);
            *bufp = '\0';
            break;
        }
    } 
    return (int)(bufp - buf);
}