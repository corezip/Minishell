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
** Nwe_front
** ---------------------------------------------------------------------------
** Se encarga de verificar que el path sea "/" junto con algo mas.
*/

int					new_front(t_var *x, char *var)
{
	char 			*tmp;

	if (!ft_strcmp(var, "-"))
		return (cd_dash(x));
	else
	{
		tmp = ft_strjoin("/", var);
		if (access(tmp, F_OK) == 0)
		{
			new_paths(x, tmp);
			ft_memdel((void**)&tmp);
			return (1);
		}
	}
	return (0);
}

/*
** Front_path
** ---------------------------------------------------------------------------
** Se encarga de verificar que el pedazo de path al que se trata de llegar
** sea correcto pero en forma de introduccirse en carpetas.
*/

int					front_path(t_var *x, char *var, int p)
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
		p = 1;
	}
	else
		p = new_front(x, var);
	ft_memdel((void**)&x->f_tmp);
	ft_memdel((void**)&x->f_tmp2);
	return (p);
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

	ft_memdel((void**)&x->cd_tmp);
	ft_memdel((void**)&x->path);
	x->path = ft_strdup(x->tmp_path);
	x->no = 0;
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
		else if(var[1][0] == '~' && x->no == 0)
			x->flag = cd_usr(x, var);
		else if (!ft_strcmp("..", x->cd_tmp[x->i]))
			x->flag = back_path(x);
		else
			x->flag = front_path(x, x->cd_tmp[x->i], 0);
		if (x->flag == 0)
		{
			ft_printfcolor("%s %s\n", x->error, 39, x->cd_tmp[x->i], 97);
			ft_memdel((void**)&x->cd_tmp);
			return ;
		}
	}
	bonus_cd(x);
}
