/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 20:04:09 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/16 20:04:10 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				free_struct(t_var *x)
{
	ft_memdel((void**)&x->name);
	ft_memdel((void**)&x->path);
	ft_lstdel(&x->head, ft_bzero);
	ft_memdel((void**)&x);
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
		mat[++j] = (char*)malloc(sizeof(char) * ft_strlen(tmp->content) + 1);
		mat[j] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	j++;
	free(tmp);
	mat[j] = "\0";
	return (mat);
}

/*
** Init_var
** ---------------------------------------------------------------------------
** Esta funcion inicializa las variables de la estructuras.
*/

void				init_var(t_var *x)
{
	t_list			*tmp;
	char			*path;

	path = getcwd(NULL, 0);
	x->path = (char *)malloc(sizeof(100));
	x->path = ft_strdup(path);
	ft_memdel((void**)&path);
	x->oldpath = ft_strdup(x->path);
	get_env(x);
	tmp = x->head;
	while (tmp)
	{
		if (!ft_strncmp("USER=", tmp->content, 5))
			x->name = ft_strsub(tmp->content, ft_strlen((ft_strchr(tmp->content,
				'=') + 1) + 1), ft_strlen((ft_strchr(tmp->content, '=') + 1)));
		tmp = tmp->next;
	}
	free(tmp);
	x->flag = 1;
	x->z = 0;
	x->no = 0;
	x->error = ft_strdup("cd: no such file or directory:");
}

/*
** Getcommand
** ---------------------------------------------------------------------------
** Esta funcion separa el comando introducido para su seleccion de proceso.
*/

void				memdelmat(char **comandos)
{
	int i;

	i = -1;
	while (comandos[++i])
	{
		ft_memdel((void**)&comandos[i]);
	}
}
void				getcommand(char **line, t_var *x)
{
	char			**comandos;
	int i = -1;

	comandos = ft_split_whitespaces(*line);
	if (!ft_strcmp(comandos[0], "echo"))
		choose_echo(1, comandos, x);
	else if (!ft_strcmp(comandos[0], "pwd"))
		ft_printfcolor("%s\n", x->path, 39);
	else if (!ft_strcmp(comandos[0], "cd"))
		access_cd_2(x, comandos, -1);
	else if (!ft_strcmp(comandos[0], "setenv"))
		set_env(x, comandos);
	else if (!ft_strcmp(comandos[0], "unsetenv"))
		del_env(x, comandos[1]);
	else if (!ft_strcmp(comandos[0], "env"))
		print_env(x);
	else if (comandos[0][0] == '/')
		slash_found(comandos, x, 0);
	else if (command_cmp(x, comandos, -1, -1) == 0 && x->z == 1)
		x->z = 0;
	else
		ft_printfcolor("zsh: command not found: %s\n", comandos[0], 97);
	memdelmat(comandos);
}

/*
** Main
** ---------------------------------------------------------------------------
** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

int					main(int ac, char **av)
{
	char			*line;
	t_var			*x;

	x = (t_var *)malloc(sizeof(t_var));
	line = NULL;
	init_var(x);
	while (1)
	{
		ft_printfcolor("%s%s%s ", "@", 36, x->name, 36, "$>", 36);
		if (line)
			ft_memdel((void**)&line);
		line = readline();
		if (!ft_strcmp(line, "exit"))
		{
			free_struct(x);
			return (0);
		}
		if (ft_strlen(line))
			getcommand(&line, x);
	}
	ft_memdel((void**)&line);
	free_struct(x);
	return (ac);
}
