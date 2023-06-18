/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:23 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/02 12:33:51 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"
#define LOOP_START -1
#define KILO 1000
#define THREE 3
#define TEN 10
#define EIGHTEEN 18
#define ELEVEN 11
#define THIRTEEN 13
#define ONE 1
#define ZERO 0
#define TWO 2
#define THREE 3
#define FOURTY_EIGHT 48
#define SIZE_DIGITS 22
#define M_ONE -1
#define TEN_KILO 10000
#define FIVE 5
#define NINE 9
#define EIGHT 8
#define FOUR 4

void	pn(size_t n, char *tab, unsigned char *i)
{
	size_t	power;
	size_t	save_n;
	size_t	result;

	save_n = n / (size_t)TEN;
	power = ONE;
	while (save_n)
	{
		save_n /= (size_t)TEN;
		power = (power << THREE) + (power << ONE);
	}
	while (power)
	{
		result = n / power;
		*(tab + (++(*i))) = FOURTY_EIGHT + result;
		n = n - (result * power);
		power /= (size_t)TEN;
	}
}

char	print_fork(unsigned int id, t_alloc_vars *vars, t_philo *philo)
{
	t_timeval	t;
	size_t		new_timestamp;

	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (ZERO);
	}
	pthread_mutex_unlock(&((*vars).death_mutex));
	(pthread_mutex_lock(&((*vars).mutex_stdout)), gettimeofday(&t, NULL));
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	display(new_timestamp - (*philo).ts, id, " has taken a fork\n");
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (ONE);
}

char	print_eat(unsigned int id, t_alloc_vars *vars, size_t *timestamp,
t_philo *philo)
{
	t_timeval	t;
	size_t		new_timestamp;

	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (ZERO);
	}
	pthread_mutex_unlock(&((*vars).death_mutex));
	(pthread_mutex_lock(&((*vars).mutex_stdout)), gettimeofday(&t, NULL));
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	display(new_timestamp - (*philo).ts, id, " is eating\n");
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (*timestamp = new_timestamp, ONE);
}

char	print_sleep(unsigned int id, t_alloc_vars *vars, t_philo *philo)
{
	t_timeval	t;
	size_t		new_timestamp;

	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
	{
		pthread_mutex_unlock(&((*vars).death_mutex));
		return (ZERO);
	}
	pthread_mutex_unlock(&((*vars).death_mutex));
	(pthread_mutex_lock(&((*vars).mutex_stdout)), gettimeofday(&t, NULL));
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	display(new_timestamp - (*philo).ts, id, " is sleeping\n");
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	return (ONE);
}

char	print_think(unsigned int id, t_alloc_vars *vars, t_philo *philo,
size_t *timestamp)
{
	t_timeval	t;
	size_t		new_timestamp;

	(pthread_mutex_lock(&((*vars).mutex_stdout)), gettimeofday(&t, NULL));
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	display(new_timestamp - (*philo).ts, id, " is thinking\n");
	pthread_mutex_unlock(&((*vars).mutex_stdout));
	if (wait_n_watch(vars, philo, timestamp) == ZERO)
		return (ZERO);
	return (ONE);
}
