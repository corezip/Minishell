/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsolis <gsolis@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 22:44:27 by gsolis            #+#    #+#             */
/*   Updated: 2017/06/28 22:44:28 by gsolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_count_chars(char *str)
{
	int		i;
	int		sp;
	int		count;

	i = 0;
	sp = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' && str[i])
		{
			i++;
			sp = 1;
		}
		if (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\0')
		{
			count += (sp == 1);
			sp = 0;
			i++;
		}
	}
	return (count);
}

int			ln_word(char *str, int i)
{
	int		len;

	len = 0;
	while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' && str[i])
	{
		len++;
		i++;
	}
	return (len);
}

char		**ft_split_whitespaces(char *str)
{
	char	**ret;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if ((ret = malloc(sizeof(char*) * (ft_count_chars(str) + 1))) == NULL)
		return (NULL);
	while (str[i])
	{
		while ((str[i] == '\t' || str[i] == ' ' || str[i] == '\n') && str[i])
			i++;
		if (str[i])
		{
			k = 0;
			if ((ret[j] = malloc(sizeof(char) * ln_word(str, i) + 1)) == NULL)
				return (NULL);
			while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' && str[i])
				ret[j][k++] = str[i++];
			ret[j++][k] = '\0';
		}
	}
	ret[j] = NULL;
	return (ret);
}
