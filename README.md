# Ticket-Sale-using-Semaphore
Ps. I found this question online.
A very simple example of a critical section that is protected by a
semaphore lock. There is a global variable numTickets which tracks the
 number of tickets remaining to sell. We will create many threads that all
 will attempt to sell tickets until they are all gone. However, we must
control access to this global variable lest we sell more tickets than
 really exist. We have a semaphore lock that will only allow one seller
thread to access the numTickets variable at a time. Before attempting to
 sell a ticket, the thread must acquire the lock by waiting on the semaphore
 and then release the lock when through by signalling the semaphore.
