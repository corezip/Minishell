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

/*
** ---------------------------------------------------------------------------
*/

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

/*
** ---------------------------------------------------------------------------
*/

char				*readline(void)
{
	char			buffsazo[1025];
	int				ret;
	char			*line;

	ret = read(0, buffsazo, 1024);
	if (ret == 0)
	{
		line = ft_strdup("exit");
		return (line);
	}
	buffsazo[ret - 1] = '\0';
	line = ft_strsub(buffsazo, 0, ft_strlen(buffsazo));
	return (line);
} 

/*
** Cd_mod
** ---------------------------------------------------------------------------
** Se encarga de hacer los cambios en los path(nuevo y viejo).
*/

void				cd_mod(t_var *x)
{

	char			*tmp;
	char			*tmp2;
	t_list			*new;

	if (chdir(x->path) == 0)
	{
		del_env(x, "PWD");
		tmp = ft_strjoin("PWD=", x->path);
		new = ft_lstnew(tmp, ft_strlen(tmp) + 1);
		ft_lstaddback(&x->head, new);
		ft_memdel((void**)&tmp);
		del_env(x, "OLDPWD");
		tmp2 = ft_strjoin("OLDPWD=", x->oldpath);
		new = ft_lstnew(tmp2, ft_strlen(tmp2) + 1);
		ft_lstaddback(&x->head, new);
		ft_memdel((void**)&tmp2);
	}
	else
		ft_printfcolor("Error chdir\n");
}
