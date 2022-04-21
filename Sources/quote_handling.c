#include "../minishell.h"

char	*without_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		ft_error("Can't malloc\n", 0);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	q_norme(char **buf, char *s, int *i, int *len)
{
	char	*res;

	res = buf[0];
	buf[0] = ft_strjoin(res, quote_checker(s, i, '\''));
	*len = ft_strlen(buf[0]);
}

void	quote_norme(int *i, char *s, char **buf, int *len)
{
	char	*res;
	char	*ret;

	while (s[*i] != ' ' && s[*i] != '\0' && s[*i] != '>' && s[*i] != '<')
	{
		res = buf[0];
		if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\0')
		{
			ret = dollar_sign(s, i);
			if (ret != NULL)
				buf[0] = ft_strjoin(res, ret);
			*len = ft_strlen(buf[0]);
		}
		else if (s[*i] == '\"')
		{
			buf[0] = ft_strjoin(res, quote_checker(s, i, '\"'));
			*len = ft_strlen(buf[0]);
		}
		else if (s[*i] == '\'')
			q_norme(buf, s, i, len);
		else if (s[*i] != '\0')
			buf[0][(*len)++] = s[*i];
		(*i)++;
	}
}

char	*quote_handling(char *s, int *i)
{
	int		len;
	char	*buf;

	len = 0;
	buf = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!buf)
		ft_error("Can't malloc", 0);
	quote_norme(i, s, &buf, &len);
	if (len == 0)
		return (NULL);
	buf[len] = '\0';
	return (buf);
}
