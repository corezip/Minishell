/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:14:19 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/21 21:14:23 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				pre_cd(t_var *x, char **var)
{
	int				i;
	char			*tmp;
	char			*final;
	char			**matrix;

	i = 0;
	while (var[i])
		i++;
	matrix = (char**)malloc(sizeof(char*) * 3);
	matrix[0] = ft_strdup("cd");
	if (i > 2)
	{
		i = 0;
		while (var[++i] && var[i + 1])
		{
			if (i > 1)
			{
				ft_memdel((void**)&tmp);
				tmp = ft_strjoin(final, " ");
			} 
			else
				tmp = ft_strjoin(var[i], " ");
			if (i > 1)
				ft_memdel((void**)&final);
			final = ft_strjoin(tmp, var[i + 1]);
		}
		matrix[1] = ft_strdup(final);
		matrix[2] = NULL;
		cd_access(x, matrix);
	}
	else
		cd_access(x, var);
}

/*
** Cd_mod
** ---------------------------------------------------------------------------
** Se encarga de hacer los cambios en los path(nuevo y viejo).
*/

void				cd_mod(t_var *x)
{
	char			*tmp;

	if (chdir(x->path) == 0)
	{
		del_env(x, "PWD");
		tmp = ft_strjoin("PWD=", x->path);
		x->tmp = ft_lstnew(tmp, ft_strlen(tmp) + 1);
		ft_lstaddback(&x->head, x->tmp);
		ft_memdel((void**)&tmp);
		del_env(x, "OLDPWD");
		tmp = ft_strjoin("OLDPWD=", x->oldpath);
		x->tmp = ft_lstnew(tmp, ft_strlen(tmp) + 1);
		ft_lstaddback(&x->head, x->tmp);
		ft_memdel((void**)&tmp);
	}
	else
		ft_printfcolor("Error chdir\n");
}

/*
** New_paths
** ---------------------------------------------------------------------------
** Tipo ft_swap pero con matrices.
*/

void			new_paths(t_var *x, char *var)
{
	char		*tmp;

	tmp = ft_strdup(x->path);
	ft_memdel((void**)&x->path);
	x->path = ft_strdup(var);
	ft_memdel((void**)&x->oldpath);
	x->oldpath = ft_strdup(tmp);
	x->tmp_path = ft_strdup(x->path);
	ft_memdel((void**)&tmp);
}

/*
** Matrix_list
** ---------------------------------------------------------------------------
** Esta funcion se encarga de crear una matriz doble con todos los datos que
** contiene t_list head(contiene los env), y regresando la.
*/

char				**matrix_list(t_var *x)
{
	t_list			*tmp;
	t_list			*tmp2;
	char			**mat;
	int				i;
	int				j;

	j = -1;
	i = 0;
	tmp = x->head;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	free(tmp);
	tmp2 = x->head;
	mat = (char**)malloc(sizeof(char*) * i + 1);
	while (tmp2)
	{
		mat[++j] = (char*)malloc(sizeof(char) * ft_strlen(tmp2->content) + 1);
		mat[j] = ft_strdup(tmp2->content);
		tmp2 = tmp2->next;
	}
	mat[j] = "\0";
	return (mat);
}
