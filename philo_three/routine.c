/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:28:34 by ejawe             #+#    #+#             */
/*   Updated: 2021/02/23 22:25:52 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_print_status(t_philo *philo, char *status)
{
	if (philo->info->must_eat_time > 0 &&
			philo->must_eat_count == philo->info->must_eat_time)
		return ;
	sem_wait(philo->info->sem_status);
	if (!philo->info->is_dead)
	{
		ft_putnbr((ft_gettime() - philo->info->start));
		write(1, " ", 1);
		ft_putnbr(philo->index + 1);
		write(1, " ", 1);
		write(1, status, ft_strlen(status));
		if (ft_strlen(status) != 4)
			write(1, "\n", 1);
	}
	sem_post(philo->info->sem_status);
}

void	ft_print_death(t_philo *philo, char *status)
{
	if (philo->info->must_eat_time > 0 &&
			philo->must_eat_count == philo->info->must_eat_time)
		return ;
	if (philo->info->is_dead)
	{
		ft_putnbr((ft_gettime() - philo->info->start));
		write(1, " ", 1);
		ft_putnbr(philo->index + 1);
		write(1, " ", 1);
		write(1, status, ft_strlen(status));
		if (ft_strlen(status) != 4)
			write(1, "\n", 1);
	}
}

void	*ft_death(void *rphilo)
{
	t_philo *philo;

	philo = rphilo;
	while (!philo->info->is_dead)
	{
		if (!philo->info->is_dead &&
				(ft_gettime() - philo->start_meal) > philo->info->die_time)
		{
			sem_wait(philo->info->sem_eat);
			if (!philo->info->is_dead)
			{
				philo->info->is_dead = 1;
				sem_wait(philo->info->sem_status);
				usleep(100);
				ft_print_death(philo, "died");
				kill(0, SIGINT);
			}
		}
		usleep(100);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	if (philo->info->must_eat_time > 0 &&
			philo->must_eat_count == philo->info->must_eat_time)
		return ;
	sem_wait(philo->info->sem_fork);
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	philo->start_meal = ft_gettime();
	philo->must_eat_count = philo->must_eat_count + 1;
	usleep(philo->info->eat_time * 1000);
	if (philo->info->must_eat_time > 0 &&
			philo->must_eat_count == philo->info->must_eat_time)
		sem_post(philo->info->sem_must_eat);
	sem_post(philo->info->sem_fork);
}

int		ft_routine(t_philo *philo)
{
	pthread_t thread;

	philo->start_meal = ft_gettime();
	if (pthread_create(&thread, NULL, &ft_death, (void*)philo))
		return (1);
	pthread_detach(thread);
	while (1)
	{
		ft_eat(philo);
		if (!philo->info->is_dead)
			ft_print_status(philo, "is sleeping");
		usleep(philo->info->sleep_time * 1000);
		if (!philo->info->is_dead)
			ft_print_status(philo, "is thinking");
	}
	return (0);
}
