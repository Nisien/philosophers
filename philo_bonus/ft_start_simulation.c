/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 01:37:32 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/03 21:44:24 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_reaper(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (OK)
	{
		sem_wait(data->check_death);
		if (ft_get_time() > (data->philo_data.last_meal
				+ data->time[DEATH]))
		{
			sem_post(data->check_death);
			ft_print_state(data, &data->philo_data, DEATH);
			sem_post(data->death);
			exit (OK);
		}
		sem_post(data->check_death);
	}
	return (NULL);
}

static void	ft_eating(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	ft_print_state(data, philo, FORK);
	sem_wait(data->forks);
	ft_print_state(data, philo, FORK);
	ft_print_state(data, philo, EAT);
	sem_wait(data->check_death);
	philo->last_meal = ft_get_time();
	sem_post(data->check_death);
	if (philo->meal_nb != -1)
		philo->meal_nb--;
	if (!philo->meal_nb)
		sem_post(data->meal);
	ft_msleep(data->time[EAT]);
	sem_post(data->forks);
	sem_post(data->forks);
}

static void	ft_philo_loop(t_data *data, t_philo *philo)
{
	while (philo->meal_nb)
	{
		ft_eating(data, philo);
		ft_print_state(data, philo, SLEEP);
		ft_msleep(data->time[SLEEP]);
		ft_print_state(data, philo, THINKING);
	}
	exit (OK);
}

static void	ft_philo_routine(t_data *data)
{
	t_philo	*philo;

	philo = &data->philo_data;
	data->start_time = ft_get_time();
	sem_wait(data->check_death);
	philo->last_meal = ft_get_time();
	sem_post(data->check_death);
	philo->meal_nb = data->meal_nb;
	if (philo->id % 2)
	{
		ft_print_state(data, philo, THINKING);
		ft_msleep(data->time[EAT] / 2);
	}
	ft_philo_loop(data, philo);
}

void	ft_start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philo_data.id = i + 1;
		data->philo_pid[i] = fork();
		if (data->philo_pid[i] == -1)
		{
			while (--i >= 0)
				kill(data->philo_pid[i], SIGKILL);
			return ;
		}
		else if (data->philo_pid[i] == 0)
		{
			pthread_create(&data->reaper, NULL, &ft_reaper, data);
			pthread_detach(data->reaper);
			ft_philo_routine(data);
		}
		i++;
	}
	if (data->meal_nb > 0)
		ft_init_waiter(data);
	sem_wait(data->death);
}
