#include "../minishell.h"

int	rows_amount(char **spl)
{
	int	i;

	i = 0 ;
	while (spl[i])
		++i;
	return (i);
}

void	fill_env(char **env, int ac, char **av)
{
	int		i;
	char	**str;
	t_list	*tmp;

	(void)ac;
	(void)av;
	// welcome_text();
	g_g.status = 0;
	i = 0;
	update_status();
	while (env[i])
	{
		str = ft_split_for_export(env[i]);
		tmp = ft_lstnew(str[0], str[1], 1);
		ft_lstadd_front(&g_g.lenv, tmp);
		i++;
	}
	free(str);
}

char	*to_lower(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[i] != '\0')
	{
		if (s[i] >= 65 && s[i] <= 90)
			str[i] = s[i] + 32;
		else
			str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
