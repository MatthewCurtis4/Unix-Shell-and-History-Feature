#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LEN 100

int main(void) {
  char input[MAX_LEN];
  int should_run = 1;

  while (should_run) {
    printf("osh> ");
    fgets(input, MAX_LEN, stdin);

    // Remove newline character from input
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "exit") == 0) {
      should_run = 0;
      continue;
    }

    char *args[MAX_LEN];
    int i = 0;
    char *p = strtok(input, " ");
    while (p != NULL) {
      args[i++] = p;
      p = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid == -1) {
      perror("fork");
      exit(1);
    }

    if (pid == 0) {
      // Child process
      execvp(args[0], args);
      perror("execvp");
      exit(1);
    } else {
      // Parent process
      wait(NULL);
    }
  }

  return 0;
}