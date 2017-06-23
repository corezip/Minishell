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

int				print_command(t_var *x, char *path, char *command, char **var)
{
	char		*tmp;
	char		*tmp2;
	char		**matrix;
	pid_t		pid;

	matrix = matrix_list(x);
	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp, command);
	if (access(tmp, R_OK) == 0)
	{
		ft_memdel((void**)&tmp);
		if ((pid = fork()) == 0)
		{
			execve(tmp2, var, matrix);
			ft_memdel((void**)&tmp2);
			ft_memdel((void**)&matrix);
			return (1);
		}
		else if (pid > 0)
			pid = wait(0);
	}
	return (0);
}

int				command_cmp(t_var *x, char **var)
{
	char			*path;
	char			**matrix;
	char			**path_mat;
	int				i;
	int				j;

	j = -1;
	i = -1;
	matrix = matrix_list(x);
	while (matrix[++i])
	{
		if (!ft_strncmp("PATH=", matrix[i], 5))
		{
			path_mat = ft_strsplit(matrix[i], ':');
			while (path_mat[++j])
			{
				if (print_command(x, path_mat[j],  var[0], var) == 1)
					return (1);
			}
		}
	}
	return (0);
}

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
	ft_memdel((void**)&matrix);
}
