#include "../minishell.h"

int	without_spaces(char *s, int i)
{
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	return (i);
}

void	update_(void)
{
	t_list	*tmp;
	int		i;

	tmp = find_element("_");
	i = 0;
	while (g_g.cmds[g_g.pipam - 1].args[i])
		i++;
	if (tmp != NULL)
		tmp->val = g_g.cmds[g_g.pipam - 1].args[i - 1];
}

void	update_lvl(int check)
{
	t_list	*tmp;
	int		lvl;

	tmp = find_element("SHLVL");
	lvl = ft_atoi(tmp->val);
	if (check == 0)
		lvl--;
	else
		lvl++;
	if (tmp != NULL)
		tmp->val = ft_itoa(lvl);
}

void	update_status(void)
{
	t_list	*tmp;

	tmp = find_element("?");
	if (tmp != NULL)
		tmp->val = ft_itoa(g_g.status);
	else
	{
		tmp = ft_lstnew("?", ft_itoa(g_g.status), 0);
		ft_lstadd_front(&g_g.lenv, tmp);
	}
}
