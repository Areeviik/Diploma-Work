#include "../minishell.h"

void	check_redirects(char *s, int i, int num)
{
	if (s[i] == '>')
		g_g.cmds[num].red = 'o';
	else
		g_g.cmds[num].red = 'i';
	s[i] = ' ';
	i++;
	if (s[i] == '>' || s[i] == '<')
	{
		g_g.cmds[num].lvl = 2;
		s[i] = ' ';
		i++;
	}
	else
		g_g.cmds[num].lvl = 1;
}

void	parse_redirects(char *s, int num, int i, int j)
{
	int	sing;
	int	d;

	d = 0;
	sing = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !d)
				sing = !sing;
		else if (s[i] == '\"' && !sing)
				d = !d;
		if ((!sing && !d) && (s[i] == '>' || s[i] == '<'))
		{
			check_redirects(s, i, num);
			j = i;
			i = parse_file(s, i, num);
			while (j != i)
			{
				s[j] = ' ';
				j++;
			}
		}
		else
			i++;
	}
}

void	parse_args(char *s, int num, int i)
{
	int		j;

	j = 1;
	g_g.cmds[num].args = malloc(sizeof(char **) * ((ft_strlen(s) / 2) + 1));
	g_g.cmds[num].args[0] = g_g.cmds[num].name;
	while (s[i])
	{
		i = without_spaces(s, i);
		g_g.cmds[num].args[j] = quote_handling(s, &i);
		if (is_space(g_g.cmds[num].args[j]))
			g_g.cmds[num].args[j] = NULL;
		if (g_g.cmds[num].args[j] != NULL)
			j++;
	}
	g_g.cmds[num].args[j] = NULL;
}

void	treat_redir(int num, int *cmd_fd, int flag)
{
	int	fd;

	fd = open(g_g.cmds[num].file, flag, 0644);
	if (fd == -1)
		print_error("minishell: Failed to open a file\n");
	else
	{
		if (*cmd_fd != 0 && *cmd_fd != 1)
			close(*cmd_fd);
		*cmd_fd = fd;
		g_g.cmds[num].file_fd = fd;
	}
}

int	parse_file(char *s, int i, int num)
{
	int		fd[2];
	pid_t	pid;

	pid = 0;
	i = without_spaces(s, i);
	g_g.cmds[num].file = quote_handling(s, &i);
	if (g_g.cmds[num].red == 'o' && g_g.cmds[num].lvl == 1)
		treat_redir(num, &g_g.cmds[num].out, O_CREAT | O_WRONLY | O_TRUNC);
	else if (g_g.cmds[num].red == 'o' && g_g.cmds[num].lvl == 2)
		treat_redir(num, &g_g.cmds[num].out, O_CREAT | O_WRONLY | O_APPEND);
	else if (g_g.cmds[num].red == 'i' && g_g.cmds[num].lvl == 1)
		treat_redir(num, &g_g.cmds[num].in, O_RDONLY);
	else if (g_g.cmds[num].red == 'i' && g_g.cmds[num].lvl == 2
		&& (g_g.status != 130 || !g_g.hdoc))
		g_g.cmds[num].in = hdoc_fn(g_g.cmds[num].file, fd, 0, pid);
	while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		i++;
	return (i);
}
