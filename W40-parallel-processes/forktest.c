#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>

int main()
{
	pid_t k, child;
	int p, status, q;

	child = fork();
	if (child != 0) {
		for (p = 0; p < 20; p++) {
			printf("\t\t\tParent, iteration %d, child PID=%d\n", p, child);
			usleep(500000);
		}
		waitpid(child, &status, 0);
		printf("\t\t\tChild died, PID was, %d\n", child);

		/* wait for interrupt ^C */
		poll(NULL, 0, -1);
	} else {
		pid_t pid = getpid();
		printf("Child PID= %d \n", pid);
		for (p = 0; p < 10; p++) {
			printf ("Child PID %d, iteration %d\n", pid, p);
			usleep(500000);
		}
		exit(1);
	}
}
