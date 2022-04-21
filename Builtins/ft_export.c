#include "../minishell.h"

void	ft_export_sec(void)
{
	while (g_g.e->tmp)
	{
		if (!ft_strncmp_quote(g_g.e->s[0], g_g.e->tmp->var))
		{
			if (g_g.e->s[1])
			{
				g_g.e->tmp->val = without_quotes(g_g.e->s[1]);
				g_g.e->tmp->equal_sign = 0;
			}
			else if (g_g.e->flag)
				g_g.e->tmp->equal_sign = 1;
			g_g.e->tmp->exp = 1;
			g_g.e->flag1 = 1;
			free(g_g.e->s[1]);
			free(g_g.e->s[0]);
			break ;
		}
		g_g.e->tmp = g_g.e->tmp->next;
	}
}

void	ft_export_third(void)
{
	if (!g_g.e->flag1)
	{
		if (g_g.e->s[1])
			g_g.e->tmp = ft_lstnew(without_quotes(g_g.e->s[0]), without_quotes(g_g.e->s[1]), 1);
		else
			g_g.e->tmp = ft_lstnew(without_quotes(g_g.e->s[0]), NULL, 1);
		if (g_g.e->flag)
			g_g.e->tmp->equal_sign = 1;
		ft_lstadd_front(&g_g.lenv, g_g.e->tmp);
		free(g_g.e->s[0]);
		free(g_g.e->s[1]);
	}
}

void	ft_export(char **args)
{
	g_g.e = malloc(sizeof(t_exp));
	if (args[1] == NULL || is_space(args[1]))
		print_export();
	else
	{
		g_g.e->i = 1;
		while (args[g_g.e->i])
		{
			if ((args[g_g.e->i][0] >= '0' && args[g_g.e->i][0] <= '9')
				|| args[g_g.e->i][0] == '?')
			{
				ft_putstr_fd("Error: not an identifier\n", 2);
				g_g.e->i++;
				g_g.status = 1;
				continue ;
			}
			g_g.e->flag1 = 0;
			g_g.e->flag = equal_is_present(args[g_g.e->i]);
			g_g.e->s = ft_split_for_export(args[g_g.e->i]);
			g_g.e->tmp = g_g.lenv;
			ft_export_sec();
			ft_export_third();
			g_g.e->i++;
		}
	}
}
