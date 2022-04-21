#include "../minishell.h"

void	waiting(void)
{
	int	j;
	int	status;

	fd_close();
	sig_ignore();
	j = -1;
	while (j++ < g_g.pipam)
		wait(&status);
	g_g.status = WEXITSTATUS(status);
	sig_init();
}

void	starting_processes(int i)
{
	pid_t	pid;

	g_g.fork_flag = 0;
	if (g_g.cmds[0].name != NULL && g_g.pipam == 1
		&& check_builtin(g_g.cmds[0].name) && !is_space(g_g.cmds[0].name)
		&& (g_g.status != 130 || !g_g.hdoc))
		child_process(0);
	else
	{
		while (g_g.cmds[i].name != NULL && i < g_g.pipam
			&& !is_space(g_g.cmds[i].name) && (g_g.status != 130 || !g_g.hdoc))
		{
			g_g.fork_flag = 1;
			pid = fork();
			if (pid == 0)
			{
				sig_default();
				child_process(i);
			}
			i++;
		}
		waiting();
	}
	update_status();
}

void	start(char *str)
{
	char	**spl;
	int		i;

	i = -1;
	spl = ft_split(str, '|');
	g_g.pipam = rows_amount(spl);
	g_g.cmds = malloc(sizeof (t_cmds) * g_g.pipam);
	if (!g_g.cmds)
		ft_error("Can't malloc struct\n", 0);
	while (spl[++i])
		main_parsing(spl[i], i);
	g_g.cmds[i].name = NULL;
	starting_processes(0);
}
