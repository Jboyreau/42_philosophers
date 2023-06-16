/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:12 by jboyreau          #+#    #+#             */
/*   Updated: 2023/06/14 03:52:19 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

enum e_params
{
	TIME_DEATH,
	TIME_EAT,
	TIME_SLEEP,
	TIME_THINK,
};

enum e_bits
{
	A = 3,
	B = 5,
	C,
	D,
	E,
	F,
};

typedef struct timevalue
{
	size_t	s;
	size_t	u;
}	t_tv;

typedef struct timeval	t_timeval;

typedef struct philosopher
{
	unsigned int	num;
	unsigned int	eat_count;
	size_t			last_eat;
	size_t			ts;
	size_t			time_to_wait;
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	void			*vars;
}	t_philo;

typedef struct allocated_vars
{
	char					death;
	char					report;
	char					launch;
	unsigned int			argc;
	unsigned int			nb_fork;
	unsigned int			nb_threads;
	unsigned int			end;
	pthread_mutex_t			mutex_stdout;
	pthread_mutex_t			death_mutex;
	pthread_mutex_t			mutex_report;
	pthread_mutex_t			mutex_end;
	unsigned int			*params;
	size_t					*micros;
	t_philo					*philos;
}	t_alloc_vars;

char	print_fork(unsigned int id, t_alloc_vars *vars, t_philo *philo);
char	print_sleep(unsigned int id, t_alloc_vars *vars, t_philo *philo);
char	print_eat(unsigned int id, t_alloc_vars *vars, size_t *timestamp,
			t_philo *philo);
char	print_think(unsigned int id, t_alloc_vars *vars, t_philo *philo,
			size_t *timestamp);
char	wait_n_watch(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);
char	parsing(char **argv, t_alloc_vars *vars, int argc);
char	check_death2(t_alloc_vars *vars, t_philo *philo, size_t timestamp);
char	check_death(t_alloc_vars *vars, t_philo *philo, size_t timestamp,
			char mode);
char	can_i_wait_sixty(t_alloc_vars *vars, t_philo *philo,
			size_t timestamp, size_t new_timestamp);
char	equal_or_not(unsigned int *params, unsigned int nt);
char	can_i_wait(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);
char	take_fork(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);
char	take_fork_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);
char	eat(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);
char	sleep_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);
void	inc_end(t_alloc_vars *vars);
void	*start(void *arg);
void	*start_(void *arg);
void	check_end(t_alloc_vars *vars);

#endif
