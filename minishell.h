/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 20:04:45 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/16 20:04:47 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef	struct			s_var
{
	char				*path;
	char				*tmp_path;
	char				*oldpath;
	char				*path_back;
	char				*name;
	char				**command;
	char				**dir;
	int					flag;
	int					i;
	t_list				*head;
	t_list				*tmp;
}						t_var;

void					getcommand(char **line, t_var *x);
void					print_echo(int j, char *comandos);
void					init_var(t_var *x);
void					get_env(t_var *x);
void					set_env(t_var *x, char **str);
void					print_env(t_var *x);
void					command_ls(t_var *x, char **var);
void					del_env(t_var *x, char *str);
void					choose_echo(int i, char **var, t_var *x);
void					all_command(t_var *x);
int						front_path(t_var *x, char *var);
int						back_path(t_var *x);
int						cd_access(t_var *x, char **var);
char					**matrix_list(t_var *x);

#endif
