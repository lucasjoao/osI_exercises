#include <iostream>
#include <pthread.h>
// nome do acadêmico: lucas joao martins

/**
*@brief   linux system calls and api based on unit "processes and threads".
*@details atividade 2 da disciplina ine5412. Duas threads são criadas. Uma
          incrementa 100 vezes a variável x enquanto a outra decrementa 100
          vezes a mesma variável. Valor inicial e final da variável é printado
          na tela. Incremento e decremento são protegidos através de um mutex.
*@return  status do fim da execucao do programa
**/

using namespace std;

pthread_mutex_t mymutex;

void *inc_(void *void_ptr)
{
	/* increment x to 100 */
	int *ptr = (int *)void_ptr;
	int i=0;
	for (; i<100; i++)
	{
		/* enter critical region */
    /**
    *@brief   pthread_mutex_lock - lock a mutex
    *@details lock the mutex referenced. If the mutex is already locked, the
              calling thread shall block until the mutex becomes available.
              This operation shall return with the mutex object referenced by mutex in the locked state with the calling thread as its owner.
              Behavior change according mutex type.
    *@param   pthread_mutex_t *mutex - mutex that will be locked
    *@return  on success returns 0; on error, it returns an error number
    *@sa      pthread_mutex_unlock, pthread_mutex_destroy
    **/
    pthread_mutex_lock(&mymutex);
		++(*ptr);
		/* leave critical region */
    /**
    *@brief   pthread_mutex_unlock - unlock a mutex
    *@details release the mutex referenced. The manner in which a mutex is
              released is dependent upon the mutex's type attribute. If there
              are threads blocked on the mutex object referenced by mutex when is called, then mutex becoming available
    *@param   pthread_mutex_t *mutex - mutex that will be unlocked
    *@return  on success returns 0; on error, it returns an error number
    *@sa      pthread_mutex_lock, pthread_mutex_destroy
    **/
    pthread_mutex_unlock(&mymutex);
	}
	cout << "increment finished" << endl;
	return NULL;
}

void *dec_(void *void_ptr)
{
  /* decrement x to 100 */
  int *ptr = (int *)void_ptr;
	int i=0;
	for (; i<100; i++)
	{
    /* enter critical region */
    pthread_mutex_lock(&mymutex);
    --(*ptr);
    /* leave critical region */
    pthread_mutex_unlock(&mymutex);
	}
    cout << "decrement finished" << endl;
    return NULL;
}

int main()
{
	long int x = 0;
	cout << "x: " << x << endl;

	/* declare threads */
  pthread_t inc_thread, dec_thread;
	/* init mutex */
  /**
  *@brief   pthread_mutex_init - initialize a mutex
  *@details initialize the mutex referenced with attributes specified. Upon
            successful initialization, the state of the mutex becomes
            initialized and unlocked
  *@param   pthread_mutex_t *restrict mutex - mutex that will be initialized
  *@param   const pthread_mutexattr_t *restrict attr - attributes that will be
            used in the mutex
  *@return  on success returns 0; on error, it returns an error number
  *@sa      pthread_mutex_lock, pthread_mutex_destroy
  **/
  pthread_mutex_init(&mymutex, NULL);

  /* create a first thread which executes inc_(&x) */
  /**
  *@brief   pthread_create - create a new thread
  *@details starts a new thread in the calling process
  *@param   pthread_t *thread - thread that will be created
  *@param   const pthread_attr_t *attr - determine attributes for the new
            thread
  *@param   void *(*start_routine) (void *) - routine that new thread invoke
            when starts execution
  *@param   void *arg - argument passed to start_routine
  *@return  on success returns 0; on error, it returns an error number and the
            contents of thread are undefined
  *@sa      pthread_join
  **/
  pthread_create(&inc_thread, NULL, inc_, &x);

	/* create a second thread which executes dec_(&x) */
  pthread_create(&dec_thread, NULL, dec_, &x);

  /* wait for the first thread to finish */
  /**
  *@brief   pthread_join - join with a terminated thread
  *@details waits for the thread specified to terminate. If that thread has
            already terminated, then returns immediately. The thread specified
            must be joinable
  *@param   pthread_t thread - thread that will be waited to terminate
  *@param   void **retval - location that receive the exit status of the target
            thread
  *@return  on success returns 0; on error, it returns an error number
  *@sa      pthread_create
  **/
  pthread_join(inc_thread, NULL);

	/* wait for the second thread to finish */
  pthread_join(dec_thread, NULL);

	/* destroy mutex */
  /**
  *@brief   pthread_mutex_destroy - destroy a mutex
  *@details destroy the mutex referenced
  *@param   pthread_mutex_t *mutex - mutex that will be destroyed
  *@return  on success returns 0; on error, it returns an error number
  *@sa      pthread_mutex_lock, pthread_mutex_init
  **/
  pthread_mutex_destroy(&mymutex);

	cout << "x: " << x << endl;
	return 0;
}

/* Respostas do "Para pensar e responder junto ao código:"

   1. Com processos a variável count possuirá um valor próprio para cada processo, porque a memória não é compartilhada entre processos.

   2. Com threads o mesmo não acontece, porque o valor da variável count é o mesmo para todas as threads, já que a memória é compartilhada.

   3. Após o fim do aplicativo o valor esperado de x é 0.

   4. Sem mutex o valor de x pode variar de -100 a 100, já que a atomicidade do decremento/incremento não será garantida.
*/
