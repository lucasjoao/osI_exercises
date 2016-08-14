#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
// nome do acadêmico: lucas joao martins

/**
*@brief   linux system calls and api based on unit "Foundamentals of Operating
          Systems"
*@details atividade 1 da disciplina ine5412. Um processo cria cinco processos
          filhos, quando todos os filhos acabam o pai retorna a soma dos
          status que cada filho retornou.
*@return  status do fim da execucao do programa
**/

using namespace std;
int main () {
    pid_t pid_value;
    int count = 0;

    for (int i = 0; i < 5; i++) {
        /**
        *@brief   getpid - get process identification
        *@details returns the process ID of the calling process
        *@return  process ID that is a pid_t types
        *@sa      fork()
        **/
        cout << "Parent process " << getpid()
             << ": Creating child" << endl;

        /**
        *@brief   fork - create a child process
        *@details creates a new process by duplicating the calling process.
                  The new process is referred to as the child process. The
                  calling process is referred to as the parent process. The
                  child process and the parent process run in separate memory
                  spaces. At the time of fork() both memory spaces have the
                  same content.
        *@return  on success, the PID of the child process is returned in the
                  parent, and 0 is returned in the child. On failure, -1 is
                  returned in the parent, no child process is created, and
                  errno is set appropriately.
        **/
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
            /**
            *@brief   sleep - sleep for the specified number of seconds
            *@details makes the calling thread sleep until seconds have
                      elapsed or a signal arrives which is not ignored.
            *@param   unsigned int seconds - seconds that the thread will sleep
            *@return  zero if the requested time has elapsed, or the number of
                      seconds left to sleep, if the call was interrupted by a
                      signal handler.
            **/
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
        /* Parent-process waits for all children to exit, adding each status
           to the sum variable */
        /**
        *@brief   waitpid - wait for process to change state
        *@details suspends execution of the calling process until a child
                  specified by pid argument has changed state. By default,
                  waitpid() waits only for terminated children.
        *@param   pid_t pid - pid that will be waited by calling process. -1
                  meaning wait for any child process.
        *@param   int *status - if is not NULL, store status information in
                  the int to which it points. This integer can be inspected with macros (which take the integer itself as an argument,
                  not a pointer to it)
        *@param   int options - some constants or zero that change behaviour of
                  the function
        *@return  on success, returns the process ID of the child whose state
                  has changed. On error, -1 is returned.
        *@sa      fork(), ECHILD, WIFEXITED(), WEXITSTATUS
        **/
        waitpid(-1, &status, 0);

        /**
        *@brief   ECHILD - error constant of waitpid procedure
        *@details (for  waitpid()) the process specified by pid (waitpid())
                  or idtype does not exist or is not a child of the calling
                  process
        **/
        if (errno == ECHILD) {
            cout << "Error on waitpid" << endl;
            return -1;
        }

        /**
        *@brief   WIFEXITED - macro of waitpid procedure
        *@details returns true if the child terminated normally, that is, by
                  calling exit(3) or _exit(2), or by returning from main().
        *@param   int status - status of process
        *@return  boolean type
        **/
        if (WIFEXITED(status))
            /**
            *@brief   WEXITSTATUS - macro of waitpid procedure
            *@details returns the exit status of the child. This consists of
                      the least significant 8 bits of the status argument that
                      the child specified in a call to exit(3) or _exit(2) or
                      as the argument for a return statement in main(). This
                      macro should be employed only if WIFEXITED returned true.
            *@param   int status - status of process
            *@return  int type that is the status
            **/
            sum += WEXITSTATUS(status);
    }

    cout << "Parent process " << getpid()
         << ": Exiting with sum " << sum << endl;

    return count;

    /* Respostas do "Para pensar e responder junto ao código:"
       1) 5.

       2) Não, porque o programa só trabalha com processos, e, não há
          compartilhamento de memória entre processos. Condição de corrida só
          pode acontecer nessa situação.

       3) Espero ver endereços diferentes ao comparar o ponteiro count do
          processo pai com o ponteiro count do processo filho, isso porque
          cada processo possui a sua própria região da memória para trabalhar,
          ou seja, não compartilham memória.
    */
}
