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

/*
** Print_command
** ---------------------------------------------------------------------------
** Esta funcion hace varios pasos:
** 1.- Hace la union de diversos strings para crear un path.
** 2.- Verifica si el path tiene un acceso correcto.
** 3.- Si el acceso es correcto creara un fork el cual se convertira en el
** ejecutable que se introdujo. Ejemplos(ls, open, vim, etc.).
*/

int				print_command(t_var *x, char *path, char *command, char **var)
{
	char		*tmp;
	char		*tmp2;
	char		**matrix;
	pid_t		pid;

	matrix = matrix_list(x);
	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp, command);
	if (access(tmp2, X_OK) == 0)
	{
		x->z = 1;
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

/*
** command_cmp
** ---------------------------------------------------------------------------
** Esta funcion hace el recorte de las matrices para poder dar paso a la
** creacion de los paths(funcion print_command).
** 1.- Se obtendran el env, dando paso a buscar el env $PATH.
** 2.- Encontrado el $PATH se convertira en una matriz doble con el
**     ft_strplit separando el path por sus ':' asi obteniendo todos los path
**     del ordenador.
** 3.- enviara la siguiente informacion a la funcion print_command.
** --- 1.- x (estructura donde se almacena la t_list donde esta env).
** --- 2.- var[0] (este es el ejecutable a comprobar y a ejecutar en la
**         siguiente en caso de que exista).
** --- 3.- var (matriz que contiene el nombre del ejecutable con las flags en
**         caso de que contenga).
*/

int				command_cmp(t_var *x, char **var)
{
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
			path_mat = ft_strsplit(ft_strchr(matrix[i], '=') + 1, ':');
			while (path_mat[++j])
			{
				if (print_command(x, path_mat[j],  var[0], var) == 1)
				{
					x->z = 1;
					ft_memdel((void**)&matrix);
					ft_memdel((void**)&path_mat);
					return (1);
				}
			}
		}
	}
	if (x->z == 1)
		return (1);
	return (0);
}
