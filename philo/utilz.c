/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:26 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/02 13:03:36 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "philo.h"
#define ONE 1
#define ZERO 0
#define TEN 10
#define THIRTEEN 13
#define NINE 9
#define EIGHT 8
#define FOUR 4
#define NB_EAT 4
#define SIX 6
#define FIVE_H 2000
#define LOOP_START -1
#define KILO 1000
#define TWO 2
#define TEN_KILO 10000

char	take_fork_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	if (can_i_wait(vars, philo, timestamp) == ZERO)
		return (ZERO);
	pthread_mutex_lock(((*philo).next_fork));
	pthread_mutex_lock(&((*philo).fork));
	if (check_death(vars, philo, *timestamp) == ZERO)
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

char	wait_n_watch(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	size_t		i;
	size_t		end;

	end = (*((*vars).micros + TIME_EAT) - *((*vars).micros + TIME_SLEEP))
		/ TEN_KILO;
	i = LOOP_START;
	while (++i < end)
	{
		if (check_death(vars, philo, *timestamp) == ZERO)
			return (ZERO);
		usleep(TEN_KILO);
		if (check_death(vars, philo, *timestamp) == ZERO)
			return (ZERO);
	}
	usleep(*((*vars).micros + TIME_SLEEP) - ((end << THIRTEEN)
			+ (end << TEN) + (end << NINE) + (end << EIGHT) + (end << FOUR)));
	usleep(FIVE_H);
	return (ZERO);
}

static char	rep(t_alloc_vars *vars, t_philo *philo, size_t *timestamp, char m)
{
	if (take_fork_(vars, philo, timestamp) == ZERO)
		return (ZERO);
	if (m == ONE)
		if ((*philo).eat_count >= *((*vars).params + NB_EAT))
			return (ZERO);
	if (sleep_(vars, philo, timestamp) == ZERO)
		return (ZERO);
	if (print_think((*philo).num, vars, philo, timestamp) == ZERO)
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
	starting_block(vars);
	gettimeofday(&t, NULL);
	timestamp = (KILO * t.tv_sec) + (t.tv_usec / (size_t)KILO);
	(*philo).ts = timestamp;
	if ((*philo).num % TWO)
		(usleep(KILO), print_think((*philo).num, vars, philo, &timestamp));
	if ((*vars).argc == SIX)
	{
		(*philo).eat_count = ZERO;
		while (ONE)
			if (rep(vars, philo, &timestamp, ONE) == ZERO)
				return (inc_end(vars), NULL);
		return (inc_end(vars), NULL);
	}
	while (ONE)
		if (rep(vars, philo, &timestamp, ZERO) == ZERO)
			return (inc_end(vars), NULL);
	return (inc_end(vars), NULL);
}
