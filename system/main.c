/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5 // number of philosophers and forks

// TODO - locks must be declared and initialized here
mutex_t forks[N];
mutex_t mutex;
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
    uint32 right = forks[(phil_id + 1) % N]; // TODO - right fork
    uint32 left = forks[phil_id];            // TODO - left fork

    while (TRUE)
    {
        srand(phil_id);
        int r = rand() % 10;
        mutex_t left_fork = forks[left];
        mutex_t right_fork = forks[right];
        if (r > 3)
        { // think
            // mutex_lock(&mutex);
            kprintf("Philosopher %d thinking: zzzZZZzzz\n", phil_id);
            think();
            // mutex_unlock(&mutex);
        }
        else if (r < 3)
        {
            if (right_fork == FALSE && left_fork == FALSE)
            {
                // mutex_lock(&mutex);
                mutex_lock(&right_fork);
                mutex_lock(&left_fork);
                kprintf("Philosopher %d eating: nom nom nom\n", phil_id);
                eat();
                mutex_unlock(&right_fork);
                mutex_unlock(&left_fork);
                // mutex_unlock(&mutex);
            }
            else
            {
                break;
            }
        }
        // mutex_unlock(&mutex);
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
