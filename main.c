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
#define LOOP_START -1
#define ONE 1

static char	rep(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	if (take_fork(vars, philo, timestamp) == ZERO)
		return (ZERO);
	if (think(vars, philo, timestamp) == ZERO)
		return (ZERO);
	if (sleep_(vars, philo, timestamp) == ZERO)
		return (ZERO);
	return (ONE);
}

static void	*start(void *arg)
{
	t_philo			*philo;
	t_alloc_vars	*vars;
	t_timeval		t;
	unsigned int	i;
	size_t			timestamp;

	philo = (t_philo *)arg;
	vars = (*philo).vars;
	i = LOOP_START;
	gettimeofday(&t, NULL);
	timestamp = (KILO * t.tv_sec) + (t.tv_usec / (size_t)KILO);
	if ((*vars).argc == SIX)
	{
		while (++i < *((*vars).params + NB_EAT))
			if (rep(vars, philo, &timestamp) == ZERO)
				return (NULL);
	}
	else
		while (1)
			if (rep(vars, philo, &timestamp) == ZERO)
				return (NULL);
	return (NULL);
}

static void	destroy(t_alloc_vars *vars, char mode, char m1, char m2)
{
	static size_t	index = LOOP_START;

	if (mode == MODE_JOIN)
	{
		while (++index < (*vars).nb_threads)
		{
			pthread_join((*((*vars).philos + index)).id, NULL);
			pthread_mutex_lock(&((*vars).death_mutex));
			(*vars).death = ONE;
			pthread_mutex_unlock(&((*vars).death_mutex));
		}
	}
	if ((*vars).params)
		free((*vars).params);
	if ((*vars).micros)
		free((*vars).micros);
	if (m1 == ONE)
		pthread_mutex_destroy(&((*vars).death_mutex));
	if (m2 == ONE)
		pthread_mutex_destroy(&((*vars).mutex_stdout));
	index = LOOP_START;
	while (++index < (*vars).nb_fork)
		pthread_mutex_destroy(&((*(((*vars).philos) + index)).fork));
	if ((*vars).philos)
		free((*vars).philos);
}

static void	fork_point(t_alloc_vars *vars, void *start(void *param))
{
	static unsigned int	i = LOOP_START;
	unsigned int		index_last_fork;

	index_last_fork = *((*vars).params) - ONE;
	while (++i < *((*vars).params))
		if (pthread_mutex_init(&((*((*vars).philos + i)).fork), NULL))
			return ((*vars).nb_fork = ++i, (void)ZERO);
	(*vars).nb_fork = i;
	i = LOOP_START;
	(*((*vars).philos + index_last_fork)).num = index_last_fork + ONE;
	(*((*vars).philos + index_last_fork)).next_fork = (*((*vars).philos)).fork;
	(*(((*vars).philos) + index_last_fork)).vars = vars;
	while (++i < index_last_fork)
	{
		(*((*vars).philos + i)).num = i + ONE;
		(*((*vars).philos + i)).next_fork = (*(((*vars).philos) + i + 1)).fork;
		(*(((*vars).philos) + i)).vars = vars;
		if (pthread_create(&((*(((*vars).philos) + i)).id), NULL, start,
				&(*((*vars).philos + i))))
			(*vars).nb_threads = ++i;
		usleep(10);
	}
	pthread_create(&((*(((*vars).philos) + i)).id), NULL, start,
		&(*((*vars).philos + i)));
		(*vars).nb_threads = ++i;
}

int	main(int argc, char **argv)
{
	static t_alloc_vars		vars;

	if (parsing(argv, &vars, argc) == ZERO)
		return (destroy(&vars, MODE_DESTROY, ZERO, ZERO), EXIT_FAILURE);
	vars.argc = argc;
	if (pthread_mutex_init(&(vars.mutex_stdout), NULL))
		return (destroy(&vars, MODE_DESTROY, ZERO, ZERO), EXIT_FAILURE);
	if (pthread_mutex_init(&(vars.death_mutex), NULL))
		return (destroy(&vars, MODE_DESTROY, ZERO, ONE), EXIT_FAILURE);
	fork_point(&vars, &start);
	return (destroy(&vars, MODE_JOIN, ONE, ONE), EXIT_SUCCESS);
}
