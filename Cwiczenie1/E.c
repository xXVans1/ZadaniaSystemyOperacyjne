#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main () {


    int i;

    int UID = getuid();
    int GID = getgid();
    int PID = getpid();
    int PPID = getppid();
    int PGID = getpgid(PID);

    printf ("Macierzysty: UID %d | GID %d | PID %d | PPID %d | PGID %d\n", UID, GID, PID, PPID, PGID);

    for (i = 1; i < 4; i++) {

        switch (fork ()) {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                // akcja dla procesu potomnego
                UID = getuid();
                GID = getgid();
                PID = getpid();
                PPID = getppid();

                setpgid (0, 0);

                PGID = getpgid(PID);

                printf ("(%d) | UID %d | GID %d | PID %d | PPID %d | PGID %d\n", i, UID, GID, PID, PPID, PGID);
                break;
            default:
                // akcja dla procesu macierzystego
                wait(NULL);
        }
    }
    return 0;
}