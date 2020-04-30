/* 
 * A very simple example of a critical section that is protected by a
 * semaphore lock. There is a global variable numTickets which tracks the
 * number of tickets remaining to sell. We will create many threads that all
 * will attempt to sell tickets until they are all gone. However, we must
 * control access to this global variable lest we sell more tickets than
 * really exist. We have a semaphore lock that will only allow one seller
 * thread to access the numTickets variable at a time. Before attempting to
 * sell a ticket, the thread must acquire the lock by waiting on the semaphore
 * and then release the lock when through by signalling the semaphore.
 */
 //Compile gcc ticketSale.c -lpthread

#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<math.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <stdbool.h> 
#include <sys/mman.h>
#include <pthread.h> 
#include <semaphore.h>

#define NUM_TICKETS 35
#define NUM_SELLERS 4
#define NAMELEN 16

int numTickets = NUM_TICKETS;
int ticketSold=0;
sem_t ticketsLock; //Semaphore

/*
This is the function carried by each thread.
Each thread represents a seller.
*/
void sellTicket(int id)
{
	bool done =false;
	int numTicketsSoldByThread =0;
    
	
	 
	 while (!done)
	 {
		usleep(100);
		sem_wait(&ticketsLock); //wait for lock
		 if(numTickets==0){
			 done =true;
		 }
		 else 
		 {
			numTickets--;
            numTicketsSoldByThread++;	
            ticketSold++;	//ticket being sold
			
        printf("Ticket %d is sold by seller %d \n",ticketSold,id);			
		 }
		 sem_post(&ticketsLock); //release lock
	 }
	printf ("Seller #%d has sold %d tickets \n",id,numTicketsSoldByThread); //Do a final count for each thread
}

int main ()
{
	
	 sem_init( &ticketsLock, 0, 1);
	 pthread_t thread_id[NUM_SELLERS];
	 for (int i = 1; i < NUM_SELLERS+1; i++) 
   {
   // create sellers
	pthread_create(&thread_id[i], NULL,sellTicket,i);
 }
  
   for (int i = 0; i < NUM_SELLERS; i++)
   {
    pthread_join(thread_id[i], NULL);
	
   }
   printf("All done!\n");

}