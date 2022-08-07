/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:35 by alemarti          #+#    #+#             */
/*   Updated: 2022/03/22 16:57:09 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int		count_words(const char *s, char c);
static char		*stralloc(const char *s, char c);

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		i;
	int		is_separator;
	int		count;

	i = -1;
	is_separator = 1;
	count = 0;
	if (!s)
		return (NULL);
	res = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[++i])
	{
		if (is_separator == 1 && s[i] != c)
			res[count++] = stralloc(&s[i], c);
		if (s[i] == c)
			is_separator = 1;
		else
			is_separator = 0;
	}
	res[count_words(s, c)] = 0;
	return (res);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;
	int	is_separator;

	count = 0;
	is_separator = 1;
	i = 0;
	while (s[i])
	{
		if (is_separator == 1 && s[i] != c)
			count++;
		if (s[i] == c)
			is_separator = 1;
		else
			is_separator = 0;
		i++;
	}
	return (count);
}

static char	*stralloc(const char *s, char c)
{
	char	*res;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
	}
	res = ft_substr(s, 0, count);
	return (res);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}