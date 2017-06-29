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

int					cd_new_user_path(t_var *x, char **path)
{
	if (access(*path, F_OK) == 0)
	{
		x->oldpath = ft_strdup(x->path);
		ft_memdel((void**)&x->path);
		x->path = ft_strdup(*path);
		ft_memdel((void**)&*path);
		x->tmp_path = ft_strdup(x->path);
		x->no = 1;
		x->i++;
		return (1);
	}
	ft_memdel((void**)&path);
	return (0);
}

int					cd_usr(t_var *x, char **var)
{
	char			*tmp;
	char			*tmp2;
	t_list			*new;

	new = x->head;
	while (new)
	{
		if (!ft_strncmp("HOME=", new->content, 5))
			tmp = ft_strsub(new->content, 5, ft_strlen(
				ft_strchr(new->content, '=')));
		new = new->next;
	}
	if (var[1][1] == '/')
		tmp2 = ft_strjoin(tmp, ft_strchr(var[1], '/'));
	else
		tmp2 = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	return (cd_new_user_path(x, &tmp2));
}

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
