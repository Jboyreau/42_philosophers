/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:23 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/02 12:33:51 by jboyreau         ###   ########.fr       */
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
	size_t		i;
	size_t		end;

	if (*((*vars).params + TWO) <= *((*vars).params + THREE))
	{
		if (check_death(vars, philo, *timestamp, ZERO) == ZERO)
			return (ZERO);
		return (usleep(FIVE_H), ONE);
	}
	end = (*((*vars).micros + TIME_EAT) - *((*vars).micros + TIME_SLEEP));
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
	usleep(FIVE_H);
	return (ONE);
}
