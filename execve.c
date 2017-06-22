/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 20:18:04 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/21 20:18:08 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				command_ls(t_var *x, char **var)
{
	pid_t				pid;
	char			**matrix;
	int i;

	i = -1;
	matrix = matrix_list(x);
	if ((pid = fork())  == 0)
	{
		execve("/bin/ls", var, matrix);
		return ;
	}
	else if (pid > 0)
		pid = wait(0);
	else
		ft_printf("Error!\n");
}
