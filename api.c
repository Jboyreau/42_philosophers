#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"
#define ZERO 0
#define ONE 1
#define KILO 1000
#define TEN_KILO 10000

static char	check_death(t_alloc_vars *vars, t_philo *philo,
size_t new_timestamp, size_t timestamp)
{
	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
		return (pthread_mutex_unlock(&((*vars).death_mutex)), ZERO);
	pthread_mutex_unlock(&((*vars).death_mutex));
	if (new_timestamp - timestamp >= *((*vars).params + ONE))
	{
		pthread_mutex_lock(&((*vars).mutex_stdout));
		printf("%ldms %d died\n", new_timestamp, (*philo).num);
		pthread_mutex_unlock(&((*vars).mutex_stdout));
		return (ZERO);
	}
	return (ONE);
}

char	sleep_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	size_t		i;
	size_t		new_timestamp;
	t_timeval	t;

	if (print_sleep((*philo).num, vars, timestamp) == ZERO)
		return (ZERO);
	i = 0;
	while (i <= *((*vars).micros + TIME_SLEEP))
	{
		pthread_mutex_lock(&((*vars).death_mutex));
		if ((*vars).death)
			return (pthread_mutex_unlock(&((*vars).death_mutex)), ZERO);
		pthread_mutex_unlock(&((*vars).death_mutex));
		usleep(TEN_KILO);
		gettimeofday(&t, NULL);
		new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
		if (check_death(vars, philo, new_timestamp, *timestamp) == ZERO)
			return (ZERO);
		i += TEN_KILO;
	}
	return (ONE);
}

char	eat(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	size_t		i;
	size_t		new_timestamp;
	t_timeval	t;

	if (print_eat((*philo).num, vars, timestamp) == ZERO)
		return (ZERO);
	i = 0;
	while (i <= *((*vars).micros + TIME_EAT))
	{
		pthread_mutex_lock(&((*vars).death_mutex));
		if ((*vars).death)
			return (pthread_mutex_unlock(&((*vars).death_mutex)), ZERO);
		pthread_mutex_unlock(&((*vars).death_mutex));
		usleep(TEN_KILO);
		gettimeofday(&t, NULL);
		new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
		if (check_death(vars, philo, new_timestamp, *timestamp) == ZERO)
			return (ZERO);
		i += TEN_KILO;
	}
	++((*philo).eat_count);
	return (ONE);
}

char	take_fork(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	pthread_mutex_lock(&((*philo).fork));
	if (print_fork((*philo).num, vars, timestamp) == ZERO)
		return (pthread_mutex_unlock(&((*philo).fork)), ZERO);
	pthread_mutex_lock(&((*philo).next_fork));
	if (print_fork((*philo).num, vars, timestamp) == ZERO)
	{
		pthread_mutex_unlock(&((*philo).next_fork));
		return (pthread_mutex_unlock(&((*philo).fork)), ZERO);
	}
	if (eat(vars, philo, timestamp) == ZERO)
	{
		pthread_mutex_unlock(&((*philo).next_fork));
		return (pthread_mutex_unlock(&((*philo).fork)), ZERO);
	}
	pthread_mutex_unlock(&((*philo).next_fork));
	return (pthread_mutex_unlock(&((*philo).fork)), ONE);
}
