/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

static char	rep(t_alloc_vars *vars, t_philo *philo, size_t *timestamp, char m)
{
	if (take_fork(vars, philo, timestamp) == ZERO)
		return (ZERO);
	if (m == ONE)
		if ((*philo).eat_count >= *((*vars).params + NB_EAT))
			return (ZERO);
	if (sleep_(vars, philo, timestamp) == ZERO)
		return (ZERO);
	if (print_think((*philo).num, vars, philo) == ZERO)
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
	if ((*philo).num % TWO)
		(usleep(KILO), print_think((*philo).num, vars, philo));
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

static void	destroy(t_alloc_vars *vars, char mode)
{
	static size_t	index = LOOP_START;

	if (mode == MODE_JOIN)
	{
		while (++index < (*vars).nb_threads)
			pthread_join((*((*vars).philos + index)).id, NULL);
		index = LOOP_START;
		while (++index < (*vars).nb_fork)
			pthread_mutex_destroy(&(*((*vars).philos + index)).fork);
	}
	if ((*vars).params)
		free((*vars).params);
	if ((*vars).micros)
		free((*vars).micros);
	if ((*vars).philos)
		free((*vars).philos);
}

static void	fork_point(t_alloc_vars *vars)
{
	static unsigned int	i = LOOP_START;
	unsigned int		index_last_fork;

	mutex_init(vars);
	index_last_fork = (*((*vars).params)) - ONE;
	while (++i < *((*vars).params))
		if (pthread_mutex_init(&((*((*vars).philos + i)).fork), NULL))
			return ((*vars).nb_fork = ++i, (void)ZERO);
	(*vars).nb_fork = i;
	i = LOOP_START;
	(*((*vars).philos + index_last_fork)).num = index_last_fork + ONE;
	(*((*vars).philos + index_last_fork)).next_fork = &(*((*vars).philos)).fork;
	(*(((*vars).philos) + index_last_fork)).vars = vars;
	while (++i < index_last_fork)
	{
		(*((*vars).philos + i)).num = i + ONE;
		(*((*vars).philos + i)).next_fork = &(*(((*vars).philos) + i + 1)).fork;
		(*(((*vars).philos) + i)).vars = vars;
		thread_creation(vars, i);
	}
	thread_creation(vars, i);
	pthread_mutex_lock(&((*vars).death_mutex));
	(*vars).launch = ONE;
	pthread_mutex_unlock(&((*vars).death_mutex));
}

int	main(int argc, char **argv)
{
	static t_alloc_vars		vars;

	if (parsing(argv, &vars, argc) == ZERO)
		return (destroy(&vars, MODE_DESTROY), EXIT_FAILURE);
	vars.argc = argc;
	fork_point(&vars);
	check_end(&vars);
	destroy(&vars, MODE_JOIN);
	return (EXIT_SUCCESS);
}
