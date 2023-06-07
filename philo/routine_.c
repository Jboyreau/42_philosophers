/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_.c                                         :+:      :+:    :+:   */
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

void	inc_end(t_alloc_vars *vars)
{
	pthread_mutex_lock(&((*vars).mutex_end));
	++(*vars).end;
	pthread_mutex_unlock(&((*vars).mutex_end));
}
