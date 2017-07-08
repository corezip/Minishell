/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 11:03:23 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/19 11:03:25 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print_env
** ---------------------------------------------------------------------------
** Esta funcion imprime la lista que contiene los env.
*/

void				print_env(t_var *x)
{
	t_list			*tmp;

	tmp = x->head;
	while (tmp)
	{
		ft_printfcolor("%s\n", tmp->content, 39);
		tmp = tmp->next;
	}
	free(tmp);
}

/*
** del_env
** ---------------------------------------------------------------------------
** Esta funcion elimina un env, busca el nombre y si lo encuentra lo elimina.
*/

void				del_env(t_var *x, char *str)
{
	t_list			*tmp;
	int				i;
	char			*comp;

	i = 1;
	tmp = x->head;
	comp = ft_strjoin(str, "=");
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, comp, ft_strlen(str + 1)))
		{
			ft_memdel((void**)&tmp->content);
			ft_lstdeletenode(x->head, i);
			tmp = tmp->next;
			break ;
		}
		tmp = tmp->next;
		i++;
	}
	ft_memdel((void**)&comp);
}

/*
** get_env
** ---------------------------------------------------------------------------
** Esta funcion obtiene los environ del sistema y los almacena en una lista.
*/

void				get_env(t_var *x)
{
	extern char		**environ;
	t_list			*tmp;
	int				i;

	i = -1;
	x->head = NULL;
	while (environ[++i])
	{
		tmp = ft_lstnew(environ[i], ft_strlen(environ[i]) + 1);
		ft_lstaddback(&x->head, tmp);
	}
}

/*
** Add_env
** ---------------------------------------------------------------------------
** Esta funcion agrega a la lista un envirion.
*/

void				add_env(t_var *x, char **var)
{
	char			*tmp;
	char			*tmp2;
	t_list			*new;

	tmp = ft_strjoin(var[0], "=");
	tmp2 = ft_strjoin(tmp, var[1]);
	new = ft_lstnew(tmp2, ft_strlen(tmp2) + 1);
	ft_lstaddback(&x->head, new);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
}

/*
** Set_env
** ---------------------------------------------------------------------------
** Esta funcion escogera si envia a imprimir o agregar envirions.
*/

void				set_env(t_var *x, char **str)
{
	char			**var;

	if (!str[1])
		print_env(x);
	else
	{
		var = ft_strsplit(str[1], '=');
		if (var[0] && var[1])
			add_env(x, var);
		memdelmat(var);
		ft_memdel((void**)&var);
	}
}
