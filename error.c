/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:09:42 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/31 16:15:15 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(const char *msg, const char *mode)
{
	(void) mode;
	/* if (mode == "All")
		;//clean()
	else if (mode == "Philos")
		;//clean()
	else if (mode == "Forks")
		;//clean() */
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}