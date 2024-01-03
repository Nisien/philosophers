/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:46:08 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/03 21:42:43 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <semaphore.h>

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
}	t_philo;

typedef struct s_data
{
	int				time[3];
	int				start_time;
	int				philo_nb;
	int				meal_nb;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*print;
	sem_t			*meal;
	sem_t			*check_death;
	pid_t			*philo_pid;
	t_philo			philo_data;
	pthread_t		reaper;
	pthread_t		waiter;
}	t_data;

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		ft_get_time(void);
int		ft_init_data(t_data *data, int argc, char **argv);
void	ft_start_simulation(t_data *data);
void	ft_get_philo_data(t_data *data);
void	*ft_reaper(void *arg);
void	*ft_waiter(void *arg);
void	ft_init_waiter(t_data *data);
void	*ft_print_state(t_data *data, t_philo *philo, int state);
void	ft_msleep(int mls);

#endif
