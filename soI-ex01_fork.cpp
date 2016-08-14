#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
// nome do acadêmico: lucas joao martins

using namespace std;
int main () {
    pid_t pid_value;
    int count = 0;

    for (int i = 0; i < 5; i++) {
        cout << "Parent process " << getpid()
             << ": Creating child" << endl;

        pid_value = fork();

        /* If there was an error on duplication then */
        if (pid_value == -1) {
            cout << "Error on fork()" << endl;
            return -1;
        }

        /* If child-process is running then */
        if (pid_value == 0) {
            cout << "Child process " << getpid() << ": Running" << endl;
            count++;
            sleep(1);
            cout << "Child process " << getpid()
                 << ": Exiting with status " << count << endl;
            return count;
        }
    }

    /* if this is the parent-process then */
    cout << "Parent process " << getpid()
         << ": Waiting children to exit" << endl;
    int errno, status, sum = 0;

    for (int j = 0; j < 5; j++) {
        /* Parent-process waits for all children to exit, adding each status to the sum variable */
        waitpid(-1, &status, 0);

        if (WIFEXITED(status))
            sum += WEXITSTATUS(status);

        if (errno == ECHILD) {
            cout << "Error on waitpid" << endl;
            return -1;
        }

    }

    cout << "Parent process " << getpid()
         << ": Exiting with sum " << sum << endl;

    return count;

    /* Respostas do "Para pensar e responder junto ao código:"
    ...

    */
}
