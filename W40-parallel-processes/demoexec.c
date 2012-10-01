#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main ()
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) {
		printf("Child %d, executing \"/bin/date\"\n", getpid());
		execl("/bin/date", "date", NULL);

		printf("This should not happen!\n");
		exit(1);
	}

	printf("Parent waiting for child's dead\n");
	waitpid(pid, &status, 0);
	printf("Parent, PID: %d: Child with PID %d just died with status %d.\n",
		getpid(), pid, WEXITSTATUS(status));

	exit(0);
}
