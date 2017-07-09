/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 23:50:30 by gsolis            #+#    #+#             */
/*   Updated: 2017/07/08 23:50:32 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Comas
** ---------------------------------------------------------------------------
** Funcion que busca un punto y coma ';' en el string.
*/

int					comas(char *line)
{
	int				i;

	i = -1;
	while (line[++i])
		if (line[i] == ';')
			return (1);
	return (0);
}

/*
** Matrix_list
** ---------------------------------------------------------------------------
** Esta funcion se encarga de crear una matriz doble con todos los datos que
** contiene t_list head(contiene los env), y regresando la.
*/

char				**matrix_list(t_var *x)
{
	t_list			*tmp;
	char			**mat;
	int				i;
	int				j;

	j = -1;
	i = num_list(x);
	tmp = x->head;
	mat = (char**)malloc(sizeof(char*) * i + 1);
	while (tmp)
	{
		mat[++j] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	j++;
	mat[j] = NULL;
	free(tmp);
	return (mat);
}
