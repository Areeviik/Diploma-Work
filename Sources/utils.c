#include "../shell.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	space_is_present(int num)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (g_g.cmds[num].args[i])
	{
		while (g_g.cmds[num].args[i][j])
		{
			if (g_g.cmds[num].args[i][j] == ' ')
				return (0);
			j++;
		}	
		i++;
	}
	return (1);
}

int	equal_is_present(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_env_arg(int num)
{
	int		i;
	char	*str;

	i = 1;
	while (g_g.cmds[num].args[i])
	{
		str = to_lower(g_g.cmds[num].args[i]);
		if (ft_strncmp_quote("env",
				str))
			return (0);
		else
			i++;
	}
	return (1);
}

void	env_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}
