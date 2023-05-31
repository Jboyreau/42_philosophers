#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "philo.h"
#define KILO 1000
#define ONE 1
#define ZERO 0

char	print_fork(unsigned int id, t_alloc_vars *vars, size_t *timestamp)
{
	t_timeval		t;
	size_t	new_timestamp;

	pthread_mutex_lock(&((*vars).mutex_stdout));
	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	(pthread_mutex_unlock(&((*vars).death_mutex)), gettimeofday(&t, NULL));//TODO: write + ft_putnbr
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
	+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
	+ (t.tv_usec / (size_t)KILO);
	if (new_timestamp - *timestamp >= *((*vars).params + ONE))
	{
		printf("%ldms %d died\n", new_timestamp, id);
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	printf("%ldms %d has taken a fork\n", new_timestamp, id);
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (*timestamp = new_timestamp, ONE);
}

char	print_eat(unsigned int id, t_alloc_vars *vars, size_t *timestamp)
{
	t_timeval		t;
	size_t	new_timestamp;

	pthread_mutex_lock(&((*vars).mutex_stdout));
	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	(pthread_mutex_unlock(&((*vars).death_mutex)), gettimeofday(&t, NULL));//TODO: write + ft_putnbr
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
	+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
	+ (t.tv_usec / (size_t)KILO);
	if (new_timestamp - *timestamp >= *((*vars).params + ONE))
	{
		printf("%ldms %d died\n", new_timestamp, id);
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	printf("%ldms %d is eating\n", new_timestamp, id);
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (*timestamp = new_timestamp, ONE);
}

char	print_sleep(unsigned int id, t_alloc_vars *vars, size_t *timestamp)
{
	t_timeval		t;
	size_t	new_timestamp;

	pthread_mutex_lock(&((*vars).mutex_stdout));
	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	(pthread_mutex_unlock(&((*vars).death_mutex)), gettimeofday(&t, NULL));//TODO: write + ft_putnbr
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
	+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
	+ (t.tv_usec / (size_t)KILO);
	if (new_timestamp - *timestamp >= *((*vars).params + ONE))
	{
		printf("%ldms %d died\n", new_timestamp, id);
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	printf("%ldms %d is sleeping\n", new_timestamp, id);
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (*timestamp = new_timestamp, ONE);
}

char	print_think(unsigned int id, t_alloc_vars *vars, size_t *timestamp)
{
	t_timeval		t;
	size_t	new_timestamp;

	pthread_mutex_lock(&((*vars).mutex_stdout));
	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	(pthread_mutex_unlock(&((*vars).death_mutex)), gettimeofday(&t, NULL));//TODO: write + ft_putnbr
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
	+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
	+ (t.tv_usec / (size_t)KILO);
	if (new_timestamp - *timestamp >= *((*vars).params + ONE))
	{
		printf("%ldms %d died\n", new_timestamp, id);
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	printf("%ldms %d is thinking\n", new_timestamp, id);
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (*timestamp = new_timestamp, ONE);
}
