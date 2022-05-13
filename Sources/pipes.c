#include "../shell.h"

int	plz_get_index(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], "PATH", 4)))
			return (i);
		++i;
	}
	return (0);
}

void	plz_exec(char **env, char *ar, int num)
{
	char	**path;
	int		j;
	char	*final_path;
	char	*cur;

	path = ft_split_for_dot(env[plz_get_index(env)] + 5, ':');
	j = -1;
	while (path[++j])
	{
		cur = ft_strjoin(path[j], "/");
		final_path = ft_strjoin(cur, ar);
		if (execve(final_path, g_g.cmds[num].args, env) == -1)
		{
			free(cur);
			free(final_path);
			continue ;
		}
	}
}

int	get_index(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], "PATH", 4)))
			return (i);
		++i;
	}
	return (0);
}

char	*env_path(char **env, char *ar)
{
	char	**path;
	int		j;
	char	*final_path;
	int		fd;
	char	*cur;

	path = ft_split_for_dot(env[get_index(env)] + 5, ':');
	j = -1;
	while (path[++j])
	{
		cur = ft_strjoin(path[j], "/");
		final_path = ft_strjoin(cur, ar);
		fd = open(final_path, O_RDONLY);
		if (fd > -1)
		{
			close(fd);
			free(cur);
			return (final_path);
		}
		free(cur);
	}
	return (final_path);
}
