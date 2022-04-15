/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5 // number of philosophers and forks

// TODO - locks must be declared and initialized here
mutex_t forks[N];
mutex_t mutex = FALSE;
mutex_t left_fork;
mutex_t right_fork;

/**
 * Delay for a random amount of time
 * @param alpha delay factor
 */
void holdup(int32 alpha)
{
    long delay = rand() * alpha;
    while (delay-- > 0)
        ; // no op
}

/**
 * Eat for a random amount of time
 */
void eat()
{
    holdup(10000);
}

/**
 * Think for a random amount of time
 */
void think()
{
    holdup(1000);
}

/**
 * Philosopher's code
 * @param phil_id philosopher's id
 */
void philosopher(uint32 phil_id)
{
    // find the index for right and left forks
    uint32 right = (phil_id + 1) % N; // TODO - right fork
    uint32 left = phil_id;            // TODO - left fork
    // initiate a lock for both left and right fork
    left_fork = forks[left];
    right_fork = forks[right];
    // srand with the seed being the phil_id
    srand(phil_id);
    while (TRUE)
    {
        if ((rand() % 10) >= 3)
        {
            // think 70% chance
            // lock up the print statement
            mutex_lock(&mutex);
            kprintf("Philosopher %d thinking: zzzZZZzzz\n", phil_id);
            mutex_unlock(&mutex);
            // call think()
            think();
        }
        else
        {
            // eat when both the right fork and the left fork are available
            if (right_fork == FALSE && left_fork == FALSE)
            {
                // lock up both forks
                mutex_lock(&right_fork);
                mutex_lock(&left_fork);
                // lock up the print statement
                mutex_lock(&mutex);
                kprintf("Philosopher %d eating: nom nom nom\n", phil_id);
                mutex_unlock(&mutex);
                // call to eat()
                eat();
                // unlock the forks
                mutex_unlock(&left_fork);
                mutex_unlock(&right_fork);
            }
        }
    }
}

int main(uint32 argc, uint32 *argv)
{
    // do not change
    ready(create((void *)philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
    ready(create((void *)philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
    ready(create((void *)philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
    ready(create((void *)philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
    ready(create((void *)philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

    return 0;
}
