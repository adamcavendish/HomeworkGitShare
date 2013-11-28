// C-lib
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// POSIX
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char * argv[])
{
	ssize_t buffer_len = 1024;
	char buffer[buffer_len];
	int pipefd[2];
	pid_t child_pid1 = -1;
	pid_t child_pid2 = -1;

	fprintf(stdout, "Parent: %d\n", getpid());

	if(pipe2(pipefd, 0) == -1) {
		perror("Pipe Error!");
		exit(1);
	}//if

	if((child_pid1 = fork()) == -1) {
		perror("Fork Error!");
		exit(1);
	}//if
	if(child_pid1 > 0) {
		if((child_pid2 = fork()) == -1) {
			perror("Fork Error!");
			exit(1);
		}//if
	}//if
	
	if(child_pid1 == 0 || child_pid2 == 0) {
		sprintf(buffer, "Child: %d\n", getpid());
		ssize_t ret = write(pipefd[1], buffer, strlen(buffer));
		if(ret < 0) {
			perror("Write Error!");
			exit(1);
		}//if
		exit(0);
	} else {
		sleep(1);
		ssize_t ret = read(pipefd[0], buffer, buffer_len);
		buffer[ret] = '\0';
		fprintf(stdout, "Reading from child: \n");
		fprintf(stdout, "%s", buffer);
	}//if-else
	
	return 0;
}//main

