


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80 /* The maximum length command */

int main(){

    int length = MAX_LINE/2 + 1;
    char *cmd[length]; /* command line argument*/
    char *args[length];
    int should_run = 1; /*flag to determine when to exit program*/
    
    char history[5][MAX_LINE+ 5] = {} //unspecified length
    int hcounter = 0;

    while (should_run){
        int waiter = 1;
        pid_t pid;
        //read in command line
        printf("osh>");
        fflush(stdout); //clears output buffer
        fgets(cmd, length, stdin);



        char *endfix = strchr(cmd, '\n');//find new line character and remove it
        if (endfix){
            *endfix = '\0';
        }

        //replace last entry if it is new line character
        if (cmd[strlen(cmd)-1] == '\n'){cmd[strlen(cmd)-1] = '\0';}

        //handle exit command
        if (strcmp(cmd, "exit") == 0) {            
            should_run = 0;
            continue;
        }

        if (strcmp(cmd, "history") == 0){
            //store most recent 5
            //check if more than 5 are stored
            if (count < 5):
                strcpy(history[count % 5], cmd);
            count++;
            int w = 0;
            while (history[w]){
                printf("%d. %s\n", count, history[w++]);

            }

        }

        if (strcmp(cmd, "!!") == 0){
            if (history[0] == NULL){
                //return error message saying no history to be ran
            }
        }

        int i = 0;
        //split input string into a series of strings split on spaces and popular args
        char *token = strtok(cmd, " ");
        while (token){
            args[i++] = token; 
            token = strtok(NULL, " ");
        }

        //detect the & case
        if (strcmp(args[i-1], "&") == 0){
            waiter = 0;
            args[i-1] = NULL;
        }

        args[i] = NULL; //add null to end to signify end of list for exec

    }
}