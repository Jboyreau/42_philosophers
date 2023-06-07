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
#define LOOP_START -1
#define KILO 1000
#define FIVE_H 5
#define THREE 3
#define TEN 10
#define EIGHTEEN 18
#define ELEVEN 11
#define THIRTEEN 13
#define ONE 1
#define ZERO 0
#define TWO 2
#define THREE 3
#define FOURTY_EIGHT 48
#define SIZE_DIGITS 22
#define M_ONE -1
#define TEN_KILO 10000
#define TWO_TH 2000
#define NINE 9
#define EIGHT 8
#define FOUR 4

char	wait_n_watch(t_alloc_vars *vars, t_philo *philo, size_t *timestamp)
{
	size_t		i;
	size_t		end;

	if (*((*vars).params + TWO) >= *((*vars).params + THREE))
	{
		usleep(FIVE_H);
		return (ONE);
	}
	end = (*((*vars).params + TWO) - *((*vars).params + THREE)) / TEN;
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
	usleep(TWO_TH);
	return (ONE);
}
