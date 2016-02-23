/*
 * http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
 */

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <pthread.h>

/* Compiling with: -Wall -pedantic -lpthread
 *  optionally add -lrt or -On with 0<n<9 */
/* #define NT 16 */
#define DIM 500*1000*1000	/*50M */
#define NChild 2
#define deb 1

void *baby( void *ptr );

/*Global Vars*/

/*Locking vars*/

void threads(int NChildren);
void * baby (void * ptr);

int main(int argc, char * argv[])
{	
	int NChildren;
	clockid_t clk;
	struct timespec tpi,tpf;
	long nseci,nsecf;
	
	if (deb>=1) printf("Argc= %d \n",argc);

	if (argc>=2)
	{
		if (deb>1) printf("args ::  %s %s \n",argv[0],argv[1]);
		NChildren=atoi(argv[1]);
		if (deb>1) printf("in arg evaluation: NChildren= %d \n ",NChildren);
		if (NChildren<1)
		{
			printf("\nError retriving NC from arg. Set it at %d default value.\n",NChild);
			NChildren=NChild;
		}
		/* else if(NChildren>NChild)	NChildren=NChild; */
	
	}
	else 
	{
		NChildren=NChild;
	}

	clock_gettime(clk,&tpi);	
	nseci=tpi.tv_nsec;
	
	threads(NChildren);
	
	clock_gettime(clk,&tpf);	
	nsecf=tpf.tv_nsec;
	nsecf=nsecf-nseci+1000000000*(tpf.tv_sec-tpi.tv_sec);
	printf("nsec passati %li usec %li msec %li \n",nsecf,nsecf/1000,nsecf/1000000);
		

	exit(0);
}


void threads(int NChildren)
{
	int i,irets;
	pthread_t threads[NChildren];
	/* if (deb==1)	*/
		printf("  threads()  ::  NChildren = %i.\n",NChildren);
	/* Create independent threads each of which will execute function */
	for (i=0;i<NChildren;i++)
		irets = pthread_create( &threads[i], NULL, baby, (void*) &i);

	printf("  threads :: Waiting for babies. \n");
	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	for (i=0;i<NChildren;i++)
		pthread_join( threads[i], NULL);
}

void * baby (void * ptr)
{
	int cn,i;	/*Child's Number*/
	if (ptr==NULL)
		printf("Error!!! ptr ==NULL!!!!\n");
	else 
		cn= *  (int *) ptr; 
	
	if (deb==1) printf("Baby %i: i=%i \n",cn,i);
	
	i=0;
	while (i<DIM)
	{
		i++;	
	}
	if (deb==1) printf("Baby %i: Ended\n",cn);
	return 0;
}

