#include "../shell.h"

void	free_all(void)
{
	if (g_g.cmds)
		free(g_g.cmds);
	if (g_g.e)
		free(g_g.e);
	if (g_g.qchecker)
		free(g_g.qchecker);
}

void	free_glob(void)
{
	int	i;

	i = 0;
	if (g_g.e)
		free(g_g.e);
	if (g_g.qchecker)
		free(g_g.qchecker);
	if (g_g.cmds)
	{
		while (i < g_g.pipam)
		{
			if (g_g.cmds[i].args)
				free_darray(g_g.cmds[i].args);
			if (g_g.cmds[i].name)
				free(g_g.cmds[i].name);
			i++;
		}
		free(g_g.cmds);
		g_g.cmds = NULL;
	}
}

void	free_env(void)
{
	t_list	*tmp;

	tmp = g_g.lenv;
	while (tmp)
	{
		ft_lstdel(&g_g.lenv, tmp);
		tmp = g_g.lenv;
	}
}

void	free_darray(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
