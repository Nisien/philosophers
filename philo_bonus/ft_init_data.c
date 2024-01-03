/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 05:25:47 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/03 21:42:26 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_waiter(t_data *data)
{
	pthread_create(&data->waiter, NULL, &ft_waiter, data);
	pthread_detach(data->waiter);
}

static void	ft_init_semaphore(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("meal");
	sem_unlink("check_death");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, data->philo_nb);
	data->death = sem_open("death", O_CREAT | O_EXCL, S_IRWXU, 0);
	data->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
	data->meal = sem_open("meal", O_CREAT | O_EXCL, S_IRWXU, 0);
	data->check_death = sem_open("check_death", O_CREAT | O_EXCL, S_IRWXU, 1);
}

static int	ft_get_data(t_data *data, int argc, char **argv)
{
	data->time[DEATH] = ft_atoi(argv[2]);
	data->time[EAT] = ft_atoi(argv[3]);
	data->time[SLEEP] = ft_atoi(argv[4]);
	data->philo_nb = ft_atoi(argv[1]);
	if (argc == 5)
		data->meal_nb = -1;
	else if (argc == 6)
		data->meal_nb = ft_atoi(argv[5]);
	return (OK);
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	ft_get_data(data, argc, argv);
	if (data->time[DEATH] == 0 || data->philo_nb == 1)
		return (KO);
	data->philo_pid = malloc(sizeof(pid_t) * data->philo_nb);
	if (!data->philo_pid)
		return (KO);
	memset(data->philo_pid, '\0', sizeof(pid_t) * data->philo_nb);
	ft_init_semaphore(data);
	return (OK);
}
