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

char				**matrix_list(t_var *x)
{
	t_list			*tmp;
	t_list			*tmp2;
	char			**mat;
	int				i;
	int				j;

	j = -1;
	i = 0;
	tmp = x->head;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	free(tmp);
	tmp2 = x->head;
	mat = (char**)malloc(sizeof(char*) * i + 1);
	while (tmp2)
	{
		mat[++j] = (char*)malloc(sizeof(char) * ft_strlen(tmp2->content) + 1);
		mat[j] = ft_strdup(tmp2->content);
		tmp2 = tmp2->next;
	}
	mat[j] = "\0";
	return (mat);
}
