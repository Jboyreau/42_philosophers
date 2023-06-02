#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"
#define ZERO 0
#define ONE 1
#define NB_EAT 4
#define KILO 1000
#define SIX 6

void	check_end(t_alloc_vars *vars)
{
	int i = 0;

	while ((*vars).death == ZERO)
	{
		pthread_mutex_lock(&((*vars).mutex_end));
		if ((*vars).end >= (*vars).nb_threads)
			return (pthread_mutex_unlock(&((*vars).mutex_end)), (void)0);
		pthread_mutex_unlock(&((*vars).mutex_end));
		pthread_mutex_lock(&((*vars).mutex_report));
		if ((*vars).report == ONE)
		{
			pthread_mutex_unlock(&((*vars).mutex_report));
			pthread_mutex_lock(&((*vars).death_mutex));
			(*vars).death = ONE;
			pthread_mutex_unlock(&((*vars).death_mutex));
		}
		else
			pthread_mutex_unlock(&((*vars).mutex_report));
		usleep(ONE);
	}
}

void	inc_end(t_alloc_vars *vars)
{
	pthread_mutex_lock(&((*vars).mutex_end));
	++(*vars).end;
	pthread_mutex_unlock(&((*vars).mutex_end));
}

static char	rep_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp, char m)
{
	if (take_fork_(vars, philo, timestamp) == ZERO)
		return (ZERO);
	if ((*philo).eat_count >= *((*vars).params + NB_EAT) && m == ONE)
		return (ZERO);
	if (sleep_(vars, philo, timestamp) == ZERO)
		return (ZERO);
	if (print_think((*philo).num, vars) == ZERO)
		return (ZERO);
	return (ONE);
}

void	*start_(void *arg)
{
	t_philo			*philo;
	t_alloc_vars	*vars;
	t_timeval		t;
	size_t			timestamp;

	philo = (t_philo *)arg;
	vars = (*philo).vars;
	gettimeofday(&t, NULL);
	timestamp = (KILO * t.tv_sec) + (t.tv_usec / (size_t)KILO);
	if ((*philo).num == ONE)
		(*vars).ts = timestamp;
	else
		usleep(ONE * (*philo).num);
	if ((*vars).argc == SIX)
	{
		(*philo).eat_count = ZERO;
		while (1)
			if (rep_(vars, philo, &timestamp, ONE) == ZERO)
				return (inc_end(vars), NULL);
		return (inc_end(vars), NULL);
	}
	while (1)
		if (rep_(vars, philo, &timestamp, ZERO) == ZERO)
			return (inc_end(vars), NULL);
	return (inc_end(vars), NULL);
}

void	thread_creation(t_alloc_vars *vars, unsigned int i)
{
	if ((*((*vars).philos + i)).num == (*vars).nb_fork)
	{
		if (pthread_create(&((*(((*vars).philos) + i)).id), NULL, start_,
			&(*((*vars).philos + i))) == ZERO)
			(*vars).nb_threads = i;
		return ;
	}
	if (pthread_create(&((*(((*vars).philos) + i)).id), NULL, start,
		&(*((*vars).philos + i))) == ZERO)
		(*vars).nb_threads = ++i;
}
