#include "../minishell.h"

/**
 * Unsets the variable from the environment if the variable is present. Outputs errro
 * if the variable is not a valid identifier.
 **/

void	ft_unset(char **args)
{
	int		i;
	t_list	*tmp;

	i = 1;
	while (args[i])
	{
		if ((args[i][0] >= '0' && args[i][0] <= '9') || args[i][0] == '?')
		{
			ft_putstr_fd("Error: not an identifier\n", 2);
			i++;
			g_g.status = 1;
			continue ;
		}
		tmp = find_element(args[i]);
		if (tmp != NULL)
			ft_lstdel(&g_g.lenv, tmp);
		i++;
	}
}
