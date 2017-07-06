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

int					num_list(t_var *x)
{
	int				i;
	t_list			*tmp;

	i = 0;
	tmp = x->head;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	free(tmp);
	return (i);
}

int					cd_dash(t_var *x)
{
	t_list			*tmp2;
	char			*oldpath;
	char			*path;

	tmp2 = x->head;
	while (tmp2)
	{
		if (!ft_strncmp("PWD=", tmp2->content, 4))
			path = ft_strdup(ft_strchr(tmp2->content, '=') + 1);
		else if (!ft_strncmp("OLDPWD=", tmp2->content, 7))
			oldpath = ft_strdup(ft_strchr(tmp2->content, '=') + 1);
		tmp2 = tmp2->next;
	}
	ft_memdel((void**)&x->path);
	ft_memdel((void**)&x->oldpath);
	ft_memdel((void**)&x->tmp_path);
	x->path = ft_strdup(oldpath);
	x->oldpath = ft_strdup(path);
	x->tmp_path = ft_strdup(oldpath);
	ft_memdel((void**)&path);
	ft_memdel((void**)&oldpath);
	return (1);
}

void				cd_pre_2(t_var *x, char **var, int i, char ***matrix)
{
	char			*tmp;
	char			*final;

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
	*matrix[1] = ft_strdup(final);
	*matrix[2] = NULL;
	cd_access(x, *matrix);
}

void				pre_cd(t_var *x, char **var)
{
	int				i;
	char			**matrix;

	i = 0;
	while (var[i])
		i++;
	matrix = (char**)malloc(sizeof(char*) * 3);
	matrix[0] = ft_strdup("cd");
	if (i > 2)
		cd_pre_2(x, var, 0, &matrix);
	else
		cd_access(x, var);
	memdelmat(matrix);
}

/*
** Cd_mod
** ---------------------------------------------------------------------------
** Se encarga de hacer los cambios en los path(nuevo y viejo).
*/

// void				cd_mod(t_var *x)
// {
// 	char			*tmp;

// 	if (chdir(x->path) == 0)
// 	{
// 		del_env(x, "PWD");
// 		tmp = ft_strjoin("PWD=", x->path);
// 		x->tmp = ft_lstnew(tmp, ft_strlen(tmp) + 1);
// 		ft_lstaddback(&x->head, x->tmp);
// 		ft_memdel((void**)&tmp);
// 		del_env(x, "OLDPWD");
// 		tmp = ft_strjoin("OLDPWD=", x->oldpath);
// 		x->tmp = ft_lstnew(tmp, ft_strlen(tmp) + 1);
// 		ft_lstaddback(&x->head, x->tmp);
// 		ft_memdel((void**)&tmp);
// 	}
// 	else
// 		ft_printfcolor("Error chdir\n");
// }
