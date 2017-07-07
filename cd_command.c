/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 20:55:25 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/18 20:55:27 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ---------------------------------------------------------------------------
*/

int					back_cd(t_var *x)
{
	char			*tmp;

	tmp = ft_strsub(x->path, 0, ft_strlen(x->path) -
	ft_strlen(ft_strrchr(x->path, '/')));
	if (ft_strlen(tmp) <= 0)
		tmp = ft_strdup("/");
	if (access(tmp, F_OK) == 0)
	{
		new_old_path(x, tmp);
		ft_memdel((void**)&tmp);
		return (1);
	}
	ft_memdel((void**)&tmp);
	return (0);
}

/*
** ---------------------------------------------------------------------------
*/

int					cd_dash(t_var *x)
{
	char			*tmp;
	t_list			*new;

	new = x->head;
	while (new)
	{
		if (!ft_strncmp("OLDPWD=", new->content, 7))
			tmp = ft_strsub(new->content, 7, ft_strlen(
				ft_strchr(new->content, '=')));
		new = new->next;
	}
	new_old_path(x, tmp);
	ft_memdel((void**)&tmp);
	free(new);
	return (1);
}

/*
** ---------------------------------------------------------------------------
*/

int				home_cd(t_var *x)
{
	t_list		*new;
	char		*tmp;

	new = x->head;
	while (new)
	{
		if (!ft_strncmp("HOME=", new->content, 5))
			tmp = ft_strsub(new->content, 5, ft_strlen(
				ft_strchr(new->content, '=')));
		new = new->next;
	}
	new_old_path(x, tmp);
	ft_memdel((void**)&tmp);
	free(new);
	return (1);
}

/*
** ---------------------------------------------------------------------------
*/

int				slash_cd_2(t_var *x, char **var)
{
	if (ft_strlen(var[1]) == 1)
		new_old_path(x, "/");
	else if (access(var[1], F_OK) == 0)
	{
		new_old_path(x, var[1]);
		return (1);
	}
	return (0);
}

/*
** ---------------------------------------------------------------------------
*/

void			access_cd_2(t_var *x, char **var, int i)
{
	char		**matrix;

	matrix = ft_strsplit(var[1], '/');
	x->original_path = ft_strdup(x->path);
	if (var[1][0] == '/')
			slash_cd_2(x, var);
	while (matrix[++i] && x->flag == 1)
	{
		if (!ft_strcmp(".", matrix[i]))
			return ;
		else if (!ft_strcmp("..", matrix[i]))
			x->flag = back_cd(x); 
		else if (!ft_strcmp("~", matrix[i]))
			x->flag = home_cd(x);
		else if (!ft_strcmp("-", var[1]))
			x->flag = cd_dash(x); 
		else
			x->flag = front_cd(x, matrix[i], 0);
		if (cd_error(x, matrix[i]) == 1)
			break ;
	}
	memdelmat(matrix);
	ft_memdel((void**)&matrix);
	cd_mod(x);
	ft_memdel((void**)&x->original_path);
}
