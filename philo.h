#ifndef PHILO_H
# define PHILO_H

enum params
{
	TIME_DEATH,//0
	TIME_EAT,//1
	TIME_SLEEP,//2
	TIME_THINK,//3
};

enum bits
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

typedef struct timeval t_timeval;

typedef struct philosopher
{
	unsigned int	num;
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	next_fork;
	void			*vars;
}	t_philo;

typedef struct allocated_vars
{
	char					death;
	unsigned int			argc;
	unsigned int			nb_fork;
	unsigned int			nb_threads;
	pthread_mutex_t			mutex_stdout;
	pthread_mutex_t			death_mutex;
	unsigned int			*params;
	size_t					*micros;
	t_philo					*philos;
}	t_alloc_vars;

char	print_fork(unsigned int id, t_alloc_vars *vars, size_t *timestamp);
char	print_sleep(unsigned int id, t_alloc_vars *vars, size_t *timestamp);
char	print_eat(unsigned int id, t_alloc_vars *vars, size_t *timestamp);
char	print_think(unsigned int id, t_alloc_vars *vars, size_t *timestamp);
char	parsing(char **argv, t_alloc_vars *vars, int argc);
char	take_fork(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);
char	eat(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);
char	sleep_(t_alloc_vars *vars, t_philo *philo, size_t *timestamp);

# endif
