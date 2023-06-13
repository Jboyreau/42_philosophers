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
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define KILO 1000
#define TEN_KILO 10000
#define LOOP_START -1
#define FOUR 4
#define TEN 10
#define EIGHT 8
#define NINE 9
#define THIRTEEN 13
#define SIXTY 60

char	can_i_wait_sixty(t_alloc_vars *vars, t_philo *philo,
size_t timestamp, size_t new_timestamp)
{
	size_t	past_time;

	past_time = (new_timestamp - timestamp);
	if (past_time + SIXTY > *((*vars).params + ONE))
	{
		usleep(*((*vars).micros + TIME_DEATH) - (past_time * KILO));
		new_timestamp += *((*vars).params + ONE) - past_time;
		pthread_mutex_lock(&((*vars).mutex_report));
		(*vars).report = ONE;
		pthread_mutex_unlock(&((*vars).mutex_report));
		pthread_mutex_lock(&((*vars).mutex_stdout));
		printf("%ldms %d died\n", new_timestamp - (*philo).ts, (*philo).num);
		pthread_mutex_unlock(&((*vars).mutex_stdout));
		return (ZERO);
	}
	return (ONE);
}

char	take_fork_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	if (can_i_wait(vars, philo, timestamp) == ZERO)
		return (ZERO);
	pthread_mutex_lock(((*philo).next_fork));
	pthread_mutex_lock(&((*philo).fork));
	if (check_death(vars, philo, *timestamp, ZERO) == ZERO)
	{
		pthread_mutex_unlock(&((*philo).fork));
		return (pthread_mutex_unlock(((*philo).next_fork)), ZERO);
	}
	if (print_fork((*philo).num, vars, philo) == ZERO
		|| print_fork((*philo).num, vars, philo) == ZERO)
	{
		pthread_mutex_unlock(&((*philo).fork));
		return (pthread_mutex_unlock(((*philo).next_fork)), ZERO);
	}
	if (eat(vars, philo, timestamp) == ZERO)
	{
		pthread_mutex_unlock(&((*philo).fork));
		return (pthread_mutex_unlock(((*philo).next_fork)), ZERO);
	}
	pthread_mutex_unlock(&((*philo).fork));
	return (pthread_mutex_unlock(((*philo).next_fork)), ONE);
}

char	equal_or_not(unsigned int *params, unsigned int nt)
{
	if (*(params + TWO) > *(params + THREE))
		if (*(params + ONE) - nt < *(params + TWO) - *(params + THREE))
			return (ONE);
	if (*(params + ONE) - nt < *(params + TWO))
		return (ONE);
	return (ZERO);
}
