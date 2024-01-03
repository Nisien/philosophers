/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:45:54 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/04 00:14:54 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (KO);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (KO);
			j++;
		}
		i++;
	}
	return (OK);
}

static void	ft_special_case(t_data *data)
{
	if (data->time[DEATH] == 0)
		printf("0 1 died\n");
	else if (data->philo_nb == 1)
	{
		printf("0 1 has taken a fork\n");
		printf("%d 1 died\n", data->time[DEATH]);
	}
}

void	*ft_waiter(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->philo_nb)
	{
		sem_wait(data->meal);
		i++;
	}
	sem_post(data->death);
	return (NULL);
}

static void	ft_end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		kill(data->philo_pid[i], SIGKILL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!ft_check_arg(argc, argv))
		return (printf("Bad argument(s)\n"), 0);
	memset(&data, '\0', sizeof(t_data));
	if (!ft_init_data(&data, argc, argv))
		return (ft_special_case(&data), 0);
	ft_start_simulation(&data);
	ft_end_simulation(&data);
	free(data.philo_pid);
	sem_close(data.forks);
	sem_close(data.death);
	sem_close(data.print);
	sem_close(data.meal);
	sem_close(data.check_death);
	return (0);
}
