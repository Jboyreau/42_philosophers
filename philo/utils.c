/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:26 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/02 13:03:36 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"
#define ZERO 0
#define ONE 1
#define TWO 2
#define NB_EAT 4
#define KILO 1000
#define SIX 6

void	check_end(t_alloc_vars *vars)
{
	while ((*vars).death == ZERO)
	{
		pthread_mutex_lock(&((*vars).mutex_end));
		if ((*vars).end >= (*vars).nb_threads)
			return (pthread_mutex_unlock(&((*vars).mutex_end)), (void)0);
		pthread_mutex_unlock(&((*vars).mutex_end));
		pthread_mutex_lock(&((*vars).mutex_report));
		if ((*vars).report == ONE)
		{
			pthread_mutex_unlock(&((*vars).mutex_report));
			pthread_mutex_lock(&((*vars).death_mutex));
			(*vars).death = ONE;
			pthread_mutex_unlock(&((*vars).death_mutex));
		}
		else
			pthread_mutex_unlock(&((*vars).mutex_report));
		usleep(ONE);
	}
}

void	inc_end(t_alloc_vars *vars)
{
	pthread_mutex_lock(&((*vars).mutex_end));
	++(*vars).end;
	pthread_mutex_unlock(&((*vars).mutex_end));
}

void	thread_creation(t_alloc_vars *vars, unsigned int i)
{
	if (i % TWO)
	{
		if (pthread_create(&((*(((*vars).philos) + i)).id), NULL, start,
				&(*((*vars).philos + i))) == ZERO)
			(*vars).nb_threads = ++i;
		return ;
	}
	if (pthread_create(&((*(((*vars).philos) + i)).id), NULL, start_,
			&(*((*vars).philos + i))) == ZERO)
	(*vars).nb_threads = ++i;
}

void	starting_block(t_alloc_vars *vars)
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

void	mutex_init(t_alloc_vars *vars)
{
	if (pthread_mutex_init(&((*vars).mutex_stdout), NULL))
		return ;
	if (pthread_mutex_init(&((*vars).death_mutex), NULL))
		return ;
	if (pthread_mutex_init(&((*vars).mutex_report), NULL))
		return ;
	if (pthread_mutex_init(&((*vars).mutex_end), NULL))
		return ;
}
