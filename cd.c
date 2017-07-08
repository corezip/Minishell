/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 22:40:17 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/28 22:40:18 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ---------------------------------------------------------------------------
*/

int				cd_error(t_var *x, char *line)
{
	if (x->flag == 0 && x->no == 0)
	{
		ft_printfcolor("%s %s\n", x->error, 39, line, 97);
		return (1);
	}
	return (0);
}

/*
** ---------------------------------------------------------------------------
*/

void			new_old_path(t_var *x, char *tmp)
{
	x->tmp_path = ft_strdup(tmp);
	ft_memdel((void**)&x->oldpath);
	x->oldpath = ft_strdup(x->original_path);
	ft_memdel((void**)&x->path);
	x->path = ft_strdup(x->tmp_path);
	ft_memdel((void**)&x->tmp_path);
}

/*
** ---------------------------------------------------------------------------
*/

int				front_cd(t_var *x, char *var, int p)
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
