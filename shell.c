// my approach has it so when history is called, the "table" is printed first
// and then history is added to the "table"







// when doing *wrong command* & it completely throws off the indexing


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 80 /* The maximum length command */
#define HISTORY_MAX 5

int main(){

    int length = MAX_LINE/2 + 1;
    char *cmd[length]; /* command line argument*/
    char *args[length];
    int should_run = 1; /*flag to determine when to exit program*/
    
    char *history[HISTORY_MAX][MAX_LINE+ 5] = {}; //unspecified length
    int cmdcount = 0;

    while (should_run){
        int waiter = 1;
        bool byepass = false; //check if it is a command where you dont need to run execvp()
        pid_t pid;
        printf("osh>");
        fflush(stdout); //clears output buffer
        fgets(cmd, length, stdin); //read in command line

        char *endfix = strchr(cmd, '\n');//find new line character and remove it
        if (endfix){
            *endfix = '\0';
        }

        //replace last entry if it is new line character
        if (cmd[strlen(cmd)-1] == '\n'){cmd[strlen(cmd)-1] = '\0';}

        //handle exit command
        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "exit &") == 0) {            
            should_run = 0;
            continue;
        }

        //run the last command if prompt entered is !!
        if (strcmp(cmd, "!!") == 0){
            //ensure there is a previous command to run
            if (cmdcount >= 1){
                //replace the command that will be ran by the previous command
                //vital to do this after strcpy above so !! will still show up in history log properly
                strcpy(cmd, history[(cmdcount-1) % HISTORY_MAX]);
            }
            else {printf("No commands in the history\n");}
        }

        if (strcmp(cmd, "history") == 0){
            //store most recent 5
            //check if more than 5 are stored
            byepass = true;
            int entries = HISTORY_MAX;
            int start = cmdcount - HISTORY_MAX; //start at 5th most recent item
            if (cmdcount <= HISTORY_MAX){ //num
                if(cmdcount < 1){
                    printf("There is no command history to display\n");
                }
                start = 0; //start at first index if num of cmds is under 5
                entries = cmdcount;
            }
            for (int i = 0; i < entries; i++){
                //we use % below so it finds the relative position it is compared to the other 5
                printf("%d %s\n", start + i + 1, history[(start+i) % HISTORY_MAX]);
            }
        }
    
        strcpy(history[cmdcount % HISTORY_MAX], cmd);
        cmdcount++; //make sure to increment cmdcount after !! test. Ensure indexing is correct
        
        
        
        int i = 0;
        //split input string into a series of strings split on spaces and popular args
        char *token = strtok(cmd, " ");

        // if (token != NULL) {//if entry is not just new line character/empty
        //       strcpy(history[cmdcount % HISTORY_MAX], cmd);
        //       cmdcount++; //make sure to increment cmdcount after !! test. Ensure indexing is correct
        // }
        // else{ byepass = true;}

        while (token){
            args[i++] = token; 
            token = strtok(NULL, " ");
        }

        //char* starttoken = strtok(args, " \t\n");

        //detect the & case
        if (strcmp(args[i-1], "&") == 0){
            waiter = 0;
            args[i-1] = NULL;
        }


        //ADD IN CASE IF THERE IS A STR IN ARGUMENTS THAT IS AN & STILL
        // IF SO BYEPASS AND PRINT WRONG


        args[i] = NULL; //add null to end to signify end of list for exec
        
        pid = fork(); //create child

        if (pid < 0){ //if failure
            printf("Failed PID");
            return 1;
        }
        if (pid == 0){ //Child process;
            //execvp(args[0], args);//file name, arugments *name*, null makes end of list of args
            execvp(args[0], args);
            // if (byepass == false){
            //     int status = execvp(args[0], args);//file name, arugments *name*, null makes end of list of args
            //     if (status == -1){
            //          printf("error: invalid command - try again\n");
            //     }
            // }
        }
        else { //Parent process

            //determine if parent process will wait or not.
            if (waiter == 1){
                wait(NULL);
            }
            waiter = 1;
        }

    }
    return 0;
}

