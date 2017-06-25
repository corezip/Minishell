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
** Matrix_list
** ---------------------------------------------------------------------------
** Esta funcion se encarga de crear una matriz doble con todos los datos que
** contiene t_list head(contiene los env), y regresando la.
*/

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
