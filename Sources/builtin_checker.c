#include "../minishell.h"

int	check_builtin(char *s)
{
	char	*str;

	if (!(ft_strncmp_quote("exit", s)))
		return (1);
	str = to_lower(s);
	if (!(ft_strncmp_quote("echo", str)) || !(ft_strncmp_quote("pwd", str))
		|| !(ft_strncmp_quote("cd", str)) || !(ft_strncmp_quote("env", str))
		|| !(ft_strncmp_quote("export", str))
		|| !(ft_strncmp_quote("unset", str)) || equal_is_present(str))
		return (1);
	else
		return (0);
}

int	func1(char *str, int num)
{
	if (!(ft_strncmp_quote("echo", str)))
	{
		if (g_g.cmds[num].args[1] == NULL)
			ft_putstr_fd("\n", g_g.cmds[num].file_fd);
		else
			ft_echo(g_g.cmds[num].args, num);
	}
	else if (!(ft_strncmp_quote("pwd", str)))
		ft_pwd(num);
	else if (!(ft_strncmp_quote("env", str)))
	{
		if (is_env_arg(num) || !g_g.cmds[num].args
			|| is_space(g_g.cmds[num].args[1]))
			print_list();
	}
	else if (!(ft_strncmp_quote("unset", str)))
	{
		if (space_is_present(num))
			ft_unset(g_g.cmds[num].args);
		else
			print_error("Error: not a valid identifier\n");
	}
	else
		return (0);
	return (1);
}

int	func2(char *str, int num)
{
	if (!(ft_strncmp_quote("cd", str)))
		ft_cd(g_g.cmds[num].args[1]);
	else if (!(ft_strncmp_quote("export", str)))
	{
		if (space_is_present(num))
			ft_export(g_g.cmds[num].args);
		else
			print_error("Error: not a valid identifier\n");
	}
	else if (equal_is_present(str))
		equal_handling(num);
	else
		return (0);
	return (1);
}

void	is_builtins(int num, char **env)
{
	char	*str;

	g_g.status = 0;
	if (!(ft_strncmp_quote("exit", g_g.cmds[num].name)))
		ft_atoi_exit(g_g.cmds[num].str_arg);
	str = to_lower(g_g.cmds[num].name);
	if (!func1(str, num) && !func2(str, num))
	{
		if (ft_strncmp_quote("exit", g_g.cmds[num].name) != 0)
		{
			plz_exec(env, g_g.cmds[num].name, num);
			printf("%s: command not found\n", g_g.cmds[num].args[0]);
			ft_error("", 127);
		}
	}
	free_darray(env);
	if (g_g.fork_flag)
		ft_error("", 0);
	else
		update_();
}
