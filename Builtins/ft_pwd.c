#include "../shell.h"

/* The function mimics the behavior of pwd command in bash.*/

void	ft_pwd(int num)
{
	char	*str;

	str = malloc(sizeof(char *) * 1024);
	if (!str)
		ft_error("Can't malloc\n", 0);
	getcwd(str, 1024);
	ft_putstr_fd(str, g_g.cmds[num].file_fd);
	ft_putstr_fd("\n", g_g.cmds[num].file_fd);
	free(str);
}

void	check_oldpwd(char *value)
{
	t_list	*tmp;
	t_list	*old;

	old = find_element("OLDPWD");
	if (!old)
	{
		tmp = ft_lstnew("OLDPWD", without_quotes(value), 1);
		ft_lstadd_front(&g_g.lenv, tmp);
	}
	else
		old->val = without_quotes(value);
}
