/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:17 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/02 13:25:13 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "philo.h"
#define ZERO 0
#define ONE 1

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
