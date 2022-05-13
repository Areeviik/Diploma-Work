#include "../shell.h"

void	print_error(char *s)
{
	write(2, s, ft_strlen(s));
}

void	puterror(char *str)
{
	write(2, str, ft_strlen(str));
	exit(0);
}

void	ft_error(char *str, int code)
{
	print_error(str);
	update_lvl(0);
	// free_env();
	// free_all();
	exit (code);
}

/* The function outputs the environment. */

void	print_list(void)
{
	t_list	*tmp;

	tmp = g_g.lenv;
	while (g_g.lenv)
	{
		if (g_g.lenv->exp && g_g.lenv->val)
			printf("%s=%s\n", g_g.lenv->var, g_g.lenv->val);
		else if (g_g.lenv->exp && g_g.lenv->equal_sign)
			printf("%s=\n", g_g.lenv->var);
		g_g.lenv = g_g.lenv->next;
	}
	g_g.lenv = tmp;
}

void	print_export(void)
{
	t_list	*tmp;

	tmp = g_g.lenv;
	while (g_g.lenv)
	{
		if (g_g.lenv->val && g_g.lenv->exp)
			printf("declare -x %s=\"%s\"\n", g_g.lenv->var, g_g.lenv->val);
		else if (g_g.lenv->exp && g_g.lenv->equal_sign)
			printf("declare -x %s=\"\"\n", g_g.lenv->var);
		else if (g_g.lenv->exp)
			printf("declare -x %s\n", g_g.lenv->var);
		g_g.lenv = g_g.lenv->next;
	}
	g_g.lenv = tmp;
}
