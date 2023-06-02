#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"
#define KILO 1000
#define THREE 3
#define TEN 10
#define EIGHTEEN 18
#define ELEVEN 11
#define THIRTEEN 13
#define ONE 1
#define ZERO 0
#define TWO 2
#define FOURTY_EIGHT 48
#define SIZE_DIGITS 22
#define M_ONE -1

void	pn(size_t n)
{
	int		i;
	size_t	power;
	size_t	save_n;
	size_t	result;
	char	digits[SIZE_DIGITS];

	save_n = n / (size_t)TEN;
	power = ONE;
	while (save_n)
	{
		save_n /= (size_t)TEN;
		power = (power << THREE) + (power << ONE);
	}
	i = M_ONE;
	while (power)
	{
		result = n / power;
		*(digits + (++i)) = FOURTY_EIGHT + result;
		n = n - (result * power);
		power /= (size_t)TEN;
	}
	*(digits + (++i)) = ZERO;
	write(ONE, digits, i);
}

char	print_fork(unsigned int id, t_alloc_vars *vars)
{
	t_timeval	t;
	size_t		new_timestamp;

	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (ZERO);
	}
	(pthread_mutex_unlock(&((*vars).death_mutex)), gettimeofday(&t, NULL));
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	pthread_mutex_lock(&((*vars).mutex_stdout));
	(pn(new_timestamp - (*vars).ts), write(ONE, "ms ", THREE), pn(id));
	write(ONE, " has taken a fork\n", EIGHTEEN);
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (ONE);
}

char	print_eat(unsigned int id, t_alloc_vars *vars, size_t *timestamp)
{
	t_timeval	t;
	size_t		new_timestamp;

	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (ZERO);
	}
	(pthread_mutex_unlock(&((*vars).death_mutex)), gettimeofday(&t, NULL));
	pthread_mutex_lock(&((*vars).mutex_stdout));
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	(pn(new_timestamp - (*vars).ts), write(ONE, "ms ", THREE), pn(id));
	write(ONE, " is eating\n", ELEVEN);
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (*timestamp = new_timestamp, ONE);
}

char	print_sleep(unsigned int id, t_alloc_vars *vars)
{
	t_timeval	t;
	size_t		new_timestamp;

	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
	}
	(pthread_mutex_unlock(&((*vars).death_mutex)), gettimeofday(&t, NULL));
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	pthread_mutex_lock(&((*vars).mutex_stdout));
	(pn(new_timestamp - (*vars).ts), write(ONE, "ms ", THREE), pn(id));
	write(ONE, " is sleeping\n", THIRTEEN);
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (ONE);
}

char	print_think(unsigned int id, t_alloc_vars *vars)
{
	t_timeval	t;
	size_t		new_timestamp;

	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
		return (pthread_mutex_unlock(&((*vars).death_mutex)), ZERO);
	(pthread_mutex_unlock(&((*vars).death_mutex)), gettimeofday(&t, NULL));
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	pthread_mutex_lock(&((*vars).mutex_stdout));
	(pn(new_timestamp - (*vars).ts), write(ONE, "ms ", THREE), pn(id));
	write(ONE, " is thinking\n", THIRTEEN);
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (ONE);
}
