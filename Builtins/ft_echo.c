#include "../minishell.h"

/**
 * The function checks for the option n. It also checks for valid option n.
 * The option starts with '-' and can be followed by many 'n's. Anything
 * other than the format specified will result in 0. It it is the option n,
 * the 1 will be returned.
 **/

static int	is_with_n(char *args)
{
	int	i;

	i = 1;
	if (ft_strlen(args) < 2 || args[0] != '-' || args[1] != 'n')
		return (0);
	while (args[i])
	{
		if (args[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * The function mimics the behavior of the command echo in bash. It also
 * supports the option -n. Returns 0 on success.
 **/

int	ft_echo(char **args, int num)
{
	int	flag;
	int	i;

	i = 1;
	while (args[i] && is_with_n(args[i]))
		i++;
	if (i != 1)
		flag = 1;
	else
		flag = 0;
	if (!args[i])
	{
		if (!flag)
			ft_putstr_fd("\n", g_g.cmds[num].file_fd);
		return (0);
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], g_g.cmds[num].file_fd);
		if (args[++i])
			ft_putstr_fd(" ", g_g.cmds[num].file_fd);
	}
	if (!flag)
		ft_putstr_fd("\n", g_g.cmds[num].file_fd);
	return (0);
}
