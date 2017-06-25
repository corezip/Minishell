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

/*
** Init_var
** ---------------------------------------------------------------------------
** Esta funcion inicializa las variables de la estructuras.
*/

void				init_var(t_var *x)
{
	struct stat		filestat;
	struct passwd	*pw;

	x->path = (char *)malloc(sizeof(100));
	x->path = ft_strdup(getcwd(NULL, 0));
	get_env(x);
	lstat(x->path, &filestat);
	pw = getpwuid(filestat.st_uid);
	x->name = pw->pw_name;
	x->flag = 1;
}

/*
** Getcommand
** ---------------------------------------------------------------------------
** Esta funcion separa el comando introducido para su seleccion de proceso.
*/

void				getcommand(char **line, t_var *x)
{
	char			**comandos;

	comandos = ft_strsplit(*line, ' ');
	if (!ft_strcmp(comandos[0], "echo"))
		choose_echo(1, comandos, x);
	else if (!ft_strcmp(comandos[0], "pwd"))
		ft_printf("%s\n", x->path);
	else if (!ft_strcmp(comandos[0], "cd"))
		cd_access(x, comandos);
	else if (!ft_strcmp(comandos[0], "setenv"))
		set_env(x, comandos);
	else if (!ft_strcmp(comandos[0], "unsetenv"))
		del_env(x, comandos[1]);
	else if (!ft_strcmp(comandos[0], "env"))
		print_env(x);
	else if (command_cmp(x, comandos) == 1)
		return ;
	else
		ft_printf("zsh: command not found: %s\n", comandos[0]);
	ft_memdel((void**)&comandos);
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
	char			**fake;

	x = (t_var *)malloc(sizeof(t_var));
	init_var(x);
	fake = ft_strsplit(av[0], '/');
	while (1)
	{
		ft_printf("@%s$> ", x->name);
		get_next_line(0, &line);
		if (!ft_strcmp(line, "exit"))
			exit(3);
		if (ft_strlen(line))
			getcommand(&line, x);
	}
	ft_memdel((void**)&line);
	ft_memdel((void**)&x);
	return (ac);
}
