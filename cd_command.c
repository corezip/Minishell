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
** Front_path
** ---------------------------------------------------------------------------
** Se encarga de verificar que el pedazo de path al que se trata de llegar
** sea correcto pero en forma de introduccirse en carpetas.
*/

// void				new_front(t_var *x, char *var)
// {
// 	if (!ft_strcmp(var, "-"))
// 	{
// 		trabajar aqui!!!!!!!
// 	}
// }

int					front_path(t_var *x, char *var)
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
		x->tmp_path = ft_strdup(x->f_tmp2);
		ft_memdel((void**)&x->f_tmp);
		ft_memdel((void**)&x->f_tmp2);
		return (1);
	}
	// else
	// 	new_front(x, var);
	ft_memdel((void**)&x->f_tmp);
	ft_memdel((void**)&x->f_tmp2);
	return (0);
}

/*
** Back_path
** ---------------------------------------------------------------------------
** Se encarga de verificar que el pedazo de path al que se trata de llegar
** sea correcto pero en forma de salirse en carpetas.
*/

int					back_path(t_var *x)
{
	char			*tmp;

	tmp = ft_strsub(x->path_back, 0, ft_strlen(x->path_back) -
	ft_strlen(ft_strrchr(x->path_back, '/')));
	if (ft_strlen(tmp) <= 0)
		tmp = ft_strdup("/");
	if (access(tmp, F_OK) == 0)
	{
		x->tmp_path = ft_strdup(tmp);
		x->path_back = ft_strdup(tmp);
		ft_memdel((void**)&tmp);
		return (1);
	}
	else
		ft_memdel((void**)&tmp);
	return (0);
}

/*
** Bonus_cd
** ---------------------------------------------------------------------------
** Funcion que se utiliza para liberar un poco de lineas de la funcion
** cd_access.
*/

void				bonus_cd(t_var *x)
{
	ft_memdel((void**)&x->path);
	x->path = ft_strdup(x->tmp_path);
	cd_mod(x);
}

/*
** Cd_access
** ---------------------------------------------------------------------------
** Se encarga de obtener cada parte del path al que se quiere llegar, y
** mandando a las 2 funciones responsables de ir avanzando o retrocediendo en
** las carpetas.
*/

void				cd_access(t_var *x, char **var)
{
	x->i = -1;
	x->oldpath = ft_strdup(x->path);
	x->path_back = ft_strdup(x->path);
	if (!ft_strcmp(var[1], "/"))
		x->cd_tmp = ft_strsplit(var[1], '-');
	else
		x->cd_tmp = ft_strsplit(var[1], '/');
	while (x->cd_tmp[++x->i])
	{
		if (!ft_strcmp(".", x->cd_tmp[x->i]))
			return ;
		else if (!ft_strcmp("..", x->cd_tmp[x->i]))
			x->flag = back_path(x);
		else
			x->flag = front_path(x, x->cd_tmp[x->i]);
		if (x->flag == 0)
		{
			ft_printfcolor("cd: no such file or directory: %s\n",
				x->cd_tmp[x->i], 34);
			ft_memdel((void**)&x->cd_tmp);
			return ;
		}
	}
	ft_memdel((void**)&x->cd_tmp);
	bonus_cd(x);
}
