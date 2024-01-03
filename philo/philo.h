/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:46:08 by nrossa            #+#    #+#             */
/*   Updated: 2023/11/23 10:12:01 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum	e_result
{
	KO,
	OK
};

enum	e_time
{
	DEATH,
	EAT,
	SLEEP,
	THINKING,
	FORK
};

enum	e_fork
{
	LEFT,
	RIGHT
};

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				meal_nb;
	int				start_time;
	int				time[3];
	int				*death;
	pthread_mutex_t	*print;
	pthread_mutex_t	*fork[2];
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*last_mutex;
	pthread_mutex_t	*death_mutex;
}	t_philo;

typedef struct s_data
{
	int				time[3];
	int				start_time;
	int				philo_nb;
	int				meal_nb;
	int				death;
	t_philo			*philo_data;
	pthread_t		*philo;
	pthread_t		reaper;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	last_mutex;
	pthread_mutex_t	death_mutex;
}	t_data;

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		ft_get_time(void);
int		ft_init_data(t_data *data, int argc, char **argv);
void	ft_start_simulation(t_data *data);
void	*ft_print_state(t_philo *philo, int state);
void	ft_msleep(int mls);

#endif
