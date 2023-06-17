/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:23 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/14 03:54:02 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"
#define ONE 1
#define ZERO 0
#define TWO 2
#define THREE 3
#define FIVE_H 500
#define TINY_SLEEP 60000

char	wait_n_watch(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	if (*((*vars).params + TWO) <= *((*vars).params + THREE))
	{
		if (check_death(vars, philo, *timestamp) == ZERO)
			return (ZERO);
		return (usleep(FIVE_H), ONE);
	}
	(*philo).time_to_wait = ((*((*vars).micros + TIME_EAT)
				- *((*vars).micros + TIME_SLEEP)) + (size_t)FIVE_H);
	if (check_death2(vars, philo, *timestamp) == ZERO)
		return (ZERO);
	usleep((*philo).time_to_wait);
	if (check_death(vars, philo, *timestamp) == ZERO)
		return (ZERO);
	return (ONE);
}
