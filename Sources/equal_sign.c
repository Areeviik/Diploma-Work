#include "../shell.h"

void	equal_handling_third(char **s)
{
	t_list	*tmp;

	if (s[1])
		tmp = ft_lstnew(s[0], s[1], 0);
	else
		tmp = ft_lstnew(s[0],
				NULL, 0);
	tmp->equal_sign = 1;
	ft_lstadd_front(&g_g.lenv, tmp);
}

void	equal_handling_sec(char **s)
{
	t_list	*tmp;
	int		flag;

	flag = 0;
	tmp = g_g.lenv;
	while (tmp)
	{
		if (!ft_strncmp_quote(s[0], tmp->var))
		{
			if (s[1])
			{
				tmp->val = s[1];
				tmp->equal_sign = 0;
			}
			else
				tmp->equal_sign = 1;
			flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!flag)
		equal_handling_third(s);
}

void	equal_handling(int num)
{
	int		i;
	char	**s;

	i = 0;
	while (g_g.cmds[num].args[i])
	{
		if (!equal_is_present(g_g.cmds[num].args[i]))
		{
			ft_putstr_fd(g_g.cmds[num].args[i], 2);
			g_g.status = 127;
			ft_putstr_fd(" : command not found\n", 2);
			return ;
		}
		i++;
	}
	i = 0;
	while (g_g.cmds[num].args[i])
	{
		s = ft_split_for_export(g_g.cmds[num].args[i]);
		equal_handling_sec(s);
		i++;
	}
}
