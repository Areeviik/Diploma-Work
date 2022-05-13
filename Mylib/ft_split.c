#include "../shell.h"

static int	char_count(char const *str, char c, int i, int count)
{	
	int	j;
	int	s[2];

	s[0] = 0;
	s[1] = 0;
	while (str[i])
	{
		j = 0;
		while (str[i])
		{
			if (str[i] == c && !s[0] && !s[1])
				break ;
			if (str[i] == '\'' && !s[1])
				s[0] = !s[0];
			else if (str[i] == '\"' && !s[0])
				s[1] = !s[1];
			j++;
			i++;
		}
		if (!j)
			i++;
		if (j && !s[0] && !s[1])
			count++;
	}
	return (count);
}

int	current_len(const char *s, int *k, char c)
{
	int	j;
	int	sing;
	int	d;

	sing = 0;
	d = 0;
	j = 0;
	while (s[(*k)])
	{
		if (s[*k] == '\'' && !d)
			sing = !sing;
		if (s[*k] == '\"' && !sing)
			d = !d;
		if (s[(*k)] == c && !sing && !d)
			break ;
		j++;
		(*k)++;
	}
	return (j);
}

/* Split string, with specified character as delimiter, into an array of strings. */

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		count;
	char	**d;

	i = 0;
	k = 0;
	count = char_count(s, c, 0, 0);
	d = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		j = current_len(s, &k, c);
		if (s[k] == '|')
			k++;
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

int	chars_until_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**ft_split_for_export(char const *s)
{
	int		k;
	int		count;
	char	**d;

	count = equal_is_present(s) + 1;
	d = malloc(3 * sizeof(char *));
	k = chars_until_equal(s);
	d[0] = ft_substr(s, 0, k);
	if (count == 2)
	{
		d[1] = ft_substr(s, k + 1, ft_strlen(s) - k - 1);
		d[2] = 0;
	}
	else
		d[1] = 0;
	return (d);
}
