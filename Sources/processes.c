#include "../minishell.h"

void	connect_pipes(int i)
{
	int	fd[2];

	if (pipe(fd) == -1)
		printf("Error while creating a pipe\n");
	if (g_g.cmds[i - 1].out != 1)
		close(fd[1]);
	else
		g_g.cmds[i - 1].out = fd[1];
	if (g_g.cmds[i].in != 0)
		close(fd[0]);
	else
		g_g.cmds[i].in = fd[0];
}

void	fd_close(void)
{
	int	i;

	i = 0;
	while (i < g_g.pipam)
	{
		if (g_g.cmds[i].out != 1)
			close(g_g.cmds[i].out);
		if (g_g.cmds[i].in != 0)
			close(g_g.cmds[i].in);
		i++;
	}
}

void	child_process(int num)
{
	char	**env;

	if (!(ft_strncmp_quote(g_g.cmds[num].args[0], "./minishell")))
		update_lvl(1);
	env = list_to_arr();
	if (g_g.pipam != 1 || !check_builtin(g_g.cmds[num].name))
	{
		if ((dup2(g_g.cmds[num].out, 1) == -1)
			|| (dup2(g_g.cmds[num].in, 0) == -1))
			print_error("Error...Can't duplicate\n");
		fd_close();
		g_g.cmds[num].out = 1;
	}
	if (g_g.cmds[num].args[0][0] == '.' || g_g.cmds[num].args[0][0] == '/')
	{
		execve(g_g.cmds[num].name, g_g.cmds[num].args, env);
		printf("%s: command not found\n", g_g.cmds[num].args[0]);
		ft_error("", 127);
	}
	else
		is_builtins(num, env);
}
