/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:49:29 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/26 15:58:59 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//FIXME: make check_limits and atoi, only one function.
int	check_limits(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' && (str[i + 1] >= 48 && str[i + 1] <= 57))
		i++;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	if (res > INT_MAX || res < INT_MIN)
	{
		printf("Invalid Argument\n");
		return (false);
	}
	return (true);
}

int	check_digit(char *str)
{
	while (*str)
	{
		if (*str == '+')
			str++;
		if (*str < 48 || *str > 57)
		{
			printf("Wrong Digit Detected\n");
			return (false);
		}
		str++;
	}
	return (true);
}

int	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Wrong Nº of Arguments\n");
		printf("./philo [philo_nbr] [t_to_die] [t_to_eat] \
		[t_to_sleep] [total_nbr_ to_eat]\n");
		return (false);
	}
	while (av[--ac] && ac > 0)
	{
		if (!av[ac][0])
		{
			printf("Invalid Argument\n");
			return (false);
		}
	}
	ac++;
	while (av[ac])
	{
		if (!check_digit(av[ac]) || !check_limits(av[ac]))
			return (false);
		ac++;
	}
	return (true);
}
