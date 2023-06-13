/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:30 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/02 12:33:35 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"
#define LOOP_START -1
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define EIGHT 8
#define NINE 9
#define TEN 10
#define THIRTEEN 13
#define KILO 1000
#define TINY_SLEEP 60000

char	check_death(t_alloc_vars *vars, t_philo *philo, size_t timestamp,
char mode)
{
	t_timeval	t;
	size_t		new_timestamp;

	gettimeofday(&t, NULL);
	new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
		+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
		+ (t.tv_usec / (size_t)KILO);
	pthread_mutex_lock(&((*vars).death_mutex));
	if ((*vars).death)
		return (pthread_mutex_unlock(&((*vars).death_mutex)), ZERO);
	pthread_mutex_unlock(&((*vars).death_mutex));
	if (new_timestamp - timestamp > *((*vars).params + ONE))
	{
		pthread_mutex_lock(&((*vars).mutex_report));
		(*vars).report = ONE;
		pthread_mutex_unlock(&((*vars).mutex_report));
		pthread_mutex_lock(&((*vars).mutex_stdout));
		printf("%ldms %d died\n", new_timestamp - (*philo).ts, (*philo).num);
		pthread_mutex_unlock(&((*vars).mutex_stdout));
		return (ZERO);
	}
	if (mode == ONE)
		if (can_i_wait_sixty(vars, philo, timestamp, new_timestamp) == ZERO)
			return (ZERO);
	return (ONE);
}

char	sleep_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	size_t		i;
	size_t		end;

	if (print_sleep((*philo).num, vars, philo) == ZERO)
		return (ZERO);
	end = *((*vars).micros + TIME_SLEEP);
	i = TINY_SLEEP;
	while (i < end)
	{
		if (check_death(vars, philo, *timestamp, ONE) == ZERO)
			return (ZERO);
		usleep(TINY_SLEEP);
		i += TINY_SLEEP;
	}
	if (check_death(vars, philo, *timestamp, ZERO) == ZERO)
		return (ZERO);
	usleep(end - (i - TINY_SLEEP));
	return (ONE);
}

char	eat(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	size_t		i;
	size_t		end;

	if (print_eat((*philo).num, vars, timestamp, philo) == ZERO)
		return (ZERO);
	end = *((*vars).micros + TIME_EAT);
	i = TINY_SLEEP;
	while (i < end)
	{
		if (check_death(vars, philo, *timestamp, ONE) == ZERO)
			return (ZERO);
		usleep(TINY_SLEEP);
		i += TINY_SLEEP;
	}
	if (check_death(vars, philo, *timestamp, ZERO) == ZERO)
		return (ZERO);
	usleep(end - (i - TINY_SLEEP));
	++((*philo).eat_count);
	return (ONE);
}

char	can_i_wait(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	t_timeval		t;
	size_t			new_timestamp;
	unsigned int	nt;

	if (*((*vars).params + TWO) >= *((*vars).params + THREE)
		&& (*((*vars).params) % TWO))
	{
		gettimeofday(&t, NULL);
		new_timestamp = (t.tv_sec << F) + (t.tv_sec << E) + (t.tv_sec << D)
			+ (t.tv_sec << C) + (t.tv_sec << B) + (t.tv_sec << A)
			+ (t.tv_usec / (size_t)KILO);
		nt = new_timestamp - *timestamp;
		if (equal_or_not((*vars).params, nt))
		{
			(usleep(*((*vars).micros) - (nt * KILO)), gettimeofday(&t, NULL));
			new_timestamp = KILO * t.tv_sec + (t.tv_usec / (size_t)KILO);
			(pthread_mutex_lock(&((*vars).mutex_report)), (*vars).report = ONE);
			pthread_mutex_unlock(&((*vars).mutex_report));
			pthread_mutex_lock(&((*vars).mutex_stdout));
			printf("%ldms %d died\n", new_timestamp - (*philo).ts, (*philo).num);
			return (pthread_mutex_unlock(&((*vars).mutex_stdout)), ZERO);
		}
	}
	return (ONE);
}

char	take_fork(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	if (can_i_wait(vars, philo, timestamp) == ZERO)
		return (ZERO);
	pthread_mutex_lock(&((*philo).fork));
	pthread_mutex_lock(((*philo).next_fork));
	if (check_death(vars, philo, *timestamp, ZERO) == ZERO)
	{
		pthread_mutex_unlock(((*philo).next_fork));
		return (pthread_mutex_unlock(&((*philo).fork)), ZERO);
	}
	if (print_fork((*philo).num, vars, philo) == ZERO
		|| print_fork((*philo).num, vars, philo) == ZERO)
	{
		pthread_mutex_unlock(((*philo).next_fork));
		return (pthread_mutex_unlock(&((*philo).fork)), ZERO);
	}
	if (eat(vars, philo, timestamp) == ZERO)
	{
		pthread_mutex_unlock(((*philo).next_fork));
		return (pthread_mutex_unlock(&((*philo).fork)), ZERO);
	}
	pthread_mutex_unlock(((*philo).next_fork));
	return (pthread_mutex_unlock(&((*philo).fork)), ONE);
}
