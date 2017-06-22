/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 19:36:51 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/20 19:36:53 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print_echo
** ---------------------------------------------------------------------------
** esta funcion imprime el comando echo.
*/

void				print_echo(int j, char *comandos)
{
	int				flag;

	flag = 0;
	while (comandos[++j])
	{
		if (comandos[j] == '\\' && comandos[j + 1] == 'n')
		{
			write(1, "\n", 1);
			j += 1;
			flag = 1;
		}
		else if (comandos[j] == '\\' && comandos[j + 1] == 'c')
			break ;
		else
			write(1, &comandos[j], 1);
	}
	if (flag == 0)
		write(1, " ", 1);
}

/*
** Choose_echo
** ---------------------------------------------------------------------------
** esta funcion determina que tipo de imprision vamos a hace, si de variables
** o de comando.
*/

void				choose_echo(int i, char **var, t_var *x)
{
	t_list			*tmp;

	tmp = x->head;
	while (var[i])
	{
		if (ft_strchr(var[i], '$'))
		{
			while (tmp)
			{
				if (!ft_strncmp(ft_strjoin("$", tmp->content),
					ft_strjoin(var[i], "="), ft_strlen(var[i] + 1)))
					ft_printf("%s ", ft_strchr(tmp->content, '=') + 1);
				tmp = tmp->next;
			}
		}
		else
			print_echo(-1, var[i]);
		i++;
	}
	write(1, "\n", 1);
	free(tmp);
}
