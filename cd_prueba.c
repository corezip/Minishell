/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_prueba.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 16:46:31 by gsolis            #+#    #+#             */
/*   Updated: 2017/07/05 16:46:32 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_memdel((void**)&x->oldpath);
		ft_memdel((void**)&tmp);
	}
	else
		ft_printfcolor("Error chdir\n");
}

void				new_old_path(t_var *x, char *tmp)
{
	x->tmp_path = ft_strdup(tmp);
	ft_memdel((void**)&x->oldpath);
	x->oldpath = ft_strdup(x->path);
	ft_memdel((void**)&x->path);
	x->path = ft_strdup(x->tmp_path);
	ft_memdel((void**)&x->tmp_path);
}

int					front_cd(t_var *x, char *var, int p)
{
	if (!ft_strcmp(var, "/"))
	{
		x->f_tmp = ft_strdup("/");
		x->f_tmp2 = ft_strdup("/");
	}
	else
	{
		if (!ft_strcmp(x->path, "/"))
			x->f_tmp = ft_strdup("/");
		else
			x->f_tmp = ft_strjoin(x->path, "/");
		x->f_tmp2 = ft_strjoin(x->f_tmp, var);
	}
	if (access(x->f_tmp2, F_OK) == 0)
	{
		new_old_path(x, x->f_tmp2);
		p = 1;
	}
	ft_memdel((void**)&x->f_tmp);
	ft_memdel((void**)&x->f_tmp2);
	return (p);
}

int			back_cd(t_var *x)
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

void			access_cd_2(t_var *x, char **var)
{
	char		**matrix;

	x->i = -1;
	// if (ft_strlen(var[1]) == 1 && var[1][0] == '/')
	// 	// 
	matrix = ft_strsplit(var[1], '/');
	x->original_path = ft_strdup(x->path);
	while (matrix[++x->i])
	{
		if (!ft_strcmp("..", matrix[x->i]))
			back_cd(x);
		// else if (var[1][0] == '/')
		// 	// 
		// else if (!ft_strcmp("~", var[1]))
		// 	// 
		// else if (!ft_strcmp("-", var[1]))
		// 	// 
		else
			front_cd(x, matrix[x->i], 0);
	}
	memdelmat(matrix);
	cd_mod(x);
}
