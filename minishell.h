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

/*
** ---------------------------------------------------------------------------
** Path: en el que nos encontramos.
** ---------------------------------------------------------------------------
** Tmp_path: path temporal donde guardaremos el path donde nos econtramos
** para despues pasarlo al oldpath.
** ---------------------------------------------------------------------------
** Oldpath: Path donde donde nos encotramos la vez pasada de usar cd.
** ---------------------------------------------------------------------------
** Original_path: Path de seguridad por si al usar cd falla la carpeta donde
** estamos.
** ---------------------------------------------------------------------------
*/

typedef	struct			s_var
{
	char				*path;
	char				*tmp_path;
	char				*oldpath;
	char				*original_path;
	char				*name;
	char				*n;
	char				**command;
	char				**dir;
	char				*f_tmp;
	char				*f_tmp2;
	char				**cd_tmp;
	char				*error;
	char				**matrix;
	int					flag;
	int					ret;
	int					no;
	int					i;
	int					z;
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
void					cd_mod(t_var *x);
void					slash_found(char **var, t_var *x, int i);
void					memdelmat(char **comandos);
void					access_cd_2(t_var *x, char **var, int i);
void					new_old_path(t_var *x, char *tmp);
void					memdelmat(char **comandos);
void					get_path(t_var *x);
char					**matrix_list(t_var *x);
char					**ft_split_whitespaces(char *str);
char					*readline(void);
char					**matrix_list(t_var *x);
int						cd_error(t_var *x, char *line);
int						command_cmp(t_var *x, char **var, int i, int j);
int						num_list(t_var *x);
int						front_cd(t_var *x, char *var, int p);
int						comas(char *line);

#endif
