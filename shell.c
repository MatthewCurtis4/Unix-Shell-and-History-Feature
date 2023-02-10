

// create an interafce that accepts user command
//gives a prompt to which user enters another command
// fork everytime a new command is entered and run it on the child



//Components:
/*
Components:
- learn design of shell interface as parent process
- Reading input
- writing prompt
- create new processes for each command with fork() 
and execute using one of the sytstem calls in the exec() family

Part A:
1. case where parents waits for child
2. Case where parent executes in background or concurrently while child process executes.

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80 /* The maximum length command */

int main(){
    //char cmd[MAX_LINE];
    int length = MAX_LINE/2 + 1;
    char *cmd[length]; /* command line argument*/
    char *args[length];
    int should_run = 1; /*flag to determine when to exit program*/

    while (should_run){
        pid_t pid;
        //string input;
        //read in command line
        printf("osh>");
        fflush(stdout); //clears output buffer
        fgets(cmd, length, stdin);

        char *endfix = strchr(cmd, '\n');//find new line character and remove it
        if (endfix){
            *endfix = '\0';
        }

        //check if last entry is \n which it likely will be and replace it
        if (cmd[strlen(cmd)-1] == '\n'){cmd[strlen(cmd)-1] = '\0';}

        int i = 0;
        char *token = strtok(cmd, " ");//split input string into a series of strings split on spaces
        while (token){ //parse into seperate inputs
            args[i++] = token; 
            token = strtok(NULL, " ");
        }
        args[i] = NULL; //add null to end to signify end of list for exec
        //printf("i value = %d 1st3rd entry = %s 4th is = %s\n", i, args[2], args[3]);
        execlp(args[0], args[0], args[1], args[2]);
        printf("top");
        int j=0;
        while (args[j]){
            printf("first%s\n",args[j++]);
        }
        //exit case
        if (args == "exit"){ should_run = 0;}

        pid = fork(); //create child

        if (pid < 0){ //if failure
            printf("FAILLLLED");
            //fprintf(stderr, "Fork Failed");
            return 1;
        }
        else if (pid == 0){ //Child process;
            //printf("child PID Root: %d\n",getpid());
            //execvp(*args, NULL) #allows us to load another process
            //printf("Running Child");
            execvp(args[0], args);//file name, arugments *name*, null makes end of list of args
            printf("child");
            //execlp("cat", "cat", "prog.c", NULL); //example
            //execlp("/bin/ls", "ls", NULL);
        }
        else { //Parent process
            wait(NULL);
            //printf("Parent PID Root: %d\n", getpid());
            printf("Task Complete");
        }

    /*
    After reading input:
    1. ford a child process using fork()
    2. child process will invoke execvp()
    3. parent will invoke wait() unless command included &
    */

    }
    return 0;
}
