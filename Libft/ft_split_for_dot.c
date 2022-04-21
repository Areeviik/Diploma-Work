/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_dot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:09:31 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/18 19:38:14 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	char_count(char const *str, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i++] != c)
			j++;
		if (j)
			count++;
	}
	return (count);
}

char	**ft_split_for_dot(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		count;
	char	**d;

	i = 0;
	k = 0;
	count = char_count(s, c);
	d = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		j = 0;
		while (s[k] && s[k++] != c)
			j++;
		if (j)
		{
			if (s[k] || s[ft_strlen(s) - 1] == c)
				d[i++] = ft_substr(s, (k - j - 1), j);
			else
				d[i++] = ft_substr(s, (k - j), j);
		}
	}
	d[i] = 0;
	return (d);
}
