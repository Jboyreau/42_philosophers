/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:17 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/02 13:25:13 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "philo.h"
#define KILO 1000
#define MODE_DESTROY 0
#define MODE_JOIN 1
#define SIX 6
#define NB_EAT 4
#define ZERO 0
#define TEN 10
#define LOOP_START -1
#define ONE 1
#define TWO 2

static void	starting_block(t_alloc_vars *vars)
{
	while (ONE)
	{
		pthread_mutex_lock(&((*vars).death_mutex));
		if ((*vars).launch == ONE)
		{
			pthread_mutex_unlock(&((*vars).death_mutex));
			break ;
		}
		pthread_mutex_unlock(&((*vars).death_mutex));
		usleep(ONE);
	}
}

static char	rep(t_alloc_vars *vars, t_philo *philo, size_t *timestamp, char m)
{
	if (take_fork(vars, philo, timestamp) == ZERO)
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

void	*start(void *arg)
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

static char	rep_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp, char m)
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
	usleep(KILO);
	print_think((*philo).num, vars, philo, &timestamp);
	if ((*vars).argc == SIX)
	{
		(*philo).eat_count = ZERO;
		while (ONE)
			if (rep_(vars, philo, &timestamp, ONE) == ZERO)
				return (inc_end(vars), NULL);
		return (inc_end(vars), NULL);
	}
	while (ONE)
		if (rep_(vars, philo, &timestamp, ZERO) == ZERO)
			return (inc_end(vars), NULL);
	return (inc_end(vars), NULL);
}
