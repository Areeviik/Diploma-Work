#include "../minishell.h"

void	quote_checker_norme(char *s, int *i)
{
	g_g.qchecker->str[g_g.qchecker->j] = s[*i];
	g_g.qchecker->j++;
	(*i)++;
}

char	*quote_checker(char *s, int *i, char c)
{
	g_g.qchecker = malloc(sizeof(t_qchecker));
	g_g.qchecker->str = malloc((ft_strlen(s) + 1) * sizeof(char));
	(*i)++;
	while (s[*i] != c && s[*i])
	{
		if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\0' && c != '\'')
		{	
			g_g.qchecker->tmp = g_g.qchecker->str;
			g_g.qchecker->ret = dollar_sign(s, i);
			if (g_g.qchecker->ret != NULL)
				g_g.qchecker->str = ft_strjoin(g_g.qchecker->tmp,
						g_g.qchecker->ret);
			else
				return ("");
			g_g.qchecker->j = ft_strlen(g_g.qchecker->str);
			while (s[*i] != ' ' && s[*i] != '\0' && s[*i]
				!= '\'' && s[*i] != '\"')
				(*i)++;
		}
		else
			quote_checker_norme(s, i);
	}
	g_g.qchecker->str[g_g.qchecker->j] = '\0';
	return (g_g.qchecker->str);
}
