/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:20 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/02 12:33:48 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "philo.h"
#define NB_PARAM 6
#define NB_PARAM_ 5
#define INDEX_LAST_DURATION 4
#define MIN_PHILO 2
#define SIZE_PARAMS 5
#define ZERO 0
#define LOOP_START -1
#define LIM1 47
#define LIM2 58
#define ONE 1
#define MICROS_SIZE 4
#define KILO 1000
#define CHAR_ZERO 48

static char	check_overflow(char *s)
{
	static char	*max_int = "4294967295";
	int			s_len;
	int			max_len;

	s_len = ZERO;
	max_len = ZERO;
	while (*(s + s_len))
		++s_len;
	while (*(max_int + max_len))
		++max_len;
	if (s_len < max_len)
		return (ONE);
	if (s_len > max_len)
		return (printf("The value %s overflows\n", s), ZERO);
	s_len = LOOP_START;
	while (*(s + (++s_len)))
	{
		if (*(max_int + s_len) > *(s + s_len))
			return (ONE);
		if (*(max_int + s_len) < *(s + s_len))
			return (printf("The value %s overflows\n", s), ZERO);
	}
	return (ONE);
}

static size_t	ft_atolu(char *s)
{
	int			i;
	size_t		sum;

	i = LOOP_START;
	sum = 0;
	while (*(s + (++i)) > LIM1 && *(s + i) < LIM2)
		sum = (sum << 3) + (sum << 1) + *(s + i) - CHAR_ZERO;
	return (sum);
}

static void	the_single_one_must_die(t_alloc_vars *vars)
{
	printf("0ms 1 has taken a fork\n");
	usleep(*((*vars).micros + TIME_DEATH));
	printf("%ldms 1 died\n", *((*vars).micros + TIME_DEATH) / KILO);
}

static char	alloc(t_alloc_vars *vars, size_t nb_philos, int argc)
{
	if (nb_philos == ZERO)
		return (ZERO);
	(*vars).params = malloc((argc) * sizeof(size_t));
	if ((*vars).params == NULL)
		return (ZERO);
	*((*vars).params) = nb_philos;
	(*vars).micros = malloc(MICROS_SIZE * sizeof(size_t));
	if ((*vars).micros == NULL)
		return (ZERO);
	(*vars).philos = malloc(nb_philos * sizeof(t_philo));
	if ((*vars).philos == NULL)
		return (ZERO);
	return (ONE);
}

char	parsing(char **argv, t_alloc_vars *vars, int argc)
{
	static int	j = LOOP_START;

	if (argc != NB_PARAM && argc != NB_PARAM_)
		return (ZERO);
	if (alloc(vars, ft_atolu(*(argv + ONE)), --argc) == ZERO)
		return (ZERO);
	while (++j < argc)
	{
		if (check_overflow(*(argv + j + ONE)) == ZERO)
			return (ZERO);
		*((*vars).params + j) = ft_atolu(*(argv + j + ONE));
		if (*((*vars).params + j) == ZERO)
			return (ZERO);
	}
	j = ZERO;
	while (++j < INDEX_LAST_DURATION)
		*((*vars).micros + j - ONE) = KILO * (*((*vars).params + j));
	*((*vars).micros + TIME_THINK) = ZERO;
	if (*((*vars).params) < MIN_PHILO)
		return (the_single_one_must_die(vars), ZERO);
	return (ONE);
}
