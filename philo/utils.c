#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "philo.h"
#define ZERO 0
#define ONE 1

void	check_end(t_alloc_vars *vars)
{
	while ((*vars).death == ZERO)
	{
		pthread_mutex_lock(&((*vars).mutex_end));
		if ((*vars).end >= (*vars).nb_threads)
			return(pthread_mutex_unlock(&((*vars).mutex_end)), (void)0);
		pthread_mutex_unlock(&((*vars).mutex_end));
		pthread_mutex_lock(&((*vars).mutex_report));
		if ((*vars).report == ONE)
		{
			pthread_mutex_unlock(&((*vars).mutex_report));
			pthread_mutex_lock(&((*vars).death_mutex));
			(*vars).death = ONE;
			pthread_mutex_unlock(&((*vars).death_mutex));
		}
		pthread_mutex_unlock(&((*vars).mutex_report));
	}
}

void	inc_end(t_alloc_vars *vars)
{
	pthread_mutex_lock(&((*vars).mutex_end));
	++(*vars).end;
	pthread_mutex_unlock(&((*vars).mutex_end));
}
