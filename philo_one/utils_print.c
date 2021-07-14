/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:08:05 by ejawe             #+#    #+#             */
/*   Updated: 2021/01/22 19:08:09 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->info->status);
	if (!philo->info->is_dead && !(philo->info->must_eat_time > 0 &&
				philo->must_eat_count >= philo->info->must_eat_time))
	{
		ft_putnbr((ft_gettime() - philo->info->start));
		write(1, " ", 1);
		ft_putnbr(philo->index + 1);
		write(1, " ", 1);
		write(1, status, ft_strlen(status));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&philo->info->status);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putnbr(unsigned long n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + 48);
}
