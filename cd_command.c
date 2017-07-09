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
** Back_cd
** ---------------------------------------------------------------------------
** Funcion que retrocede en carpetas con el comando cd.
*/

int				back_cd(t_var *x)
{
	char		*tmp;
	char		*tmp2;

	tmp2 = ft_strrchr(x->path, '/');
	tmp = ft_strsub(x->path, 0, ft_strlen(x->path) - ft_strlen(tmp2));
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
** Cd_dash
** ---------------------------------------------------------------------------
** Funcion que cambia el viejo path por el path para hacer el comando "cd ~".
*/

int				cd_dash(t_var *x)
{
	char		*tmp;
	t_list		*new;

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
** Home_cd
** ---------------------------------------------------------------------------
** Esta funcion nos creara el path del Home de la computadora.
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
** Slash_cd_2
** ---------------------------------------------------------------------------
** Funcion con el que se logra entrar si el comando introducido es "cd /"
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
** Access_cd_2
** ---------------------------------------------------------------------------
** Version 2 de la funcion Access_cd, la cual escoge la opcion del comando cd.
*/

void			access_cd_2(t_var *x, char **var, int i)
{
	x->matrix = ft_strsplit(var[1], '/');
	x->original_path = ft_strdup(x->path);
	if (!var[1])
		home_cd(x);
	else if (var[1][0] == '/')
		slash_cd_2(x, var);
	while (x->matrix[++i] && x->flag == 1)
	{
		if (!ft_strcmp(".", x->matrix[i]))
			return ;
		else if (!ft_strcmp("..", x->matrix[i]))
			x->flag = back_cd(x);
		else if (!ft_strcmp("~", x->matrix[i]))
			x->flag = home_cd(x);
		else if (!ft_strcmp("-", var[1]))
			x->flag = cd_dash(x);
		else
			x->flag = front_cd(x, x->matrix[i], 0);
		if (cd_error(x, x->matrix[i]) == 1)
			break ;
	}
	memdelmat(x->matrix);
	ft_memdel((void**)&x->matrix);
	cd_mod(x);
	ft_memdel((void**)&x->original_path);
}
