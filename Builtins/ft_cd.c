#include "../shell.h"

void	cd_minus(char *str)
{
	t_list	*tmp;
	char	*old;

	getcwd(str, 1024);
	tmp = find_element("OLDPWD");
	old = tmp->val;
	check_oldpwd(str);
	tmp = find_element("PWD");
	getcwd(str, 1024);
	tmp->val = str;
	printf("%s\n", tmp->val);
	chdir(old);
	free(str);
}

void	cd_done(t_list *tmp, char *str, char *old)
{
	check_oldpwd(old);
	tmp = find_element("PWD");
	getcwd(str, 1024);
	tmp->val = str;
}

void	ft_cd1(char *p, char *str, char *res, t_list *tmp)
{
	char	*old;

	getcwd(str, 1024);
	old = str;
	if (chdir(p) == -1)
	{	
		res = ft_strjoin(res, "/");
		if (p != NULL)
			res = ft_strjoin(res, p);
		if (!chdir(res))
			cd_done(tmp, str, old);
		else
		{
			printf("cd: %s: No such file or directory\n", p);
			g_g.status = 1;
		}
	}
	else
		cd_done(tmp, str, old);
	free(str);
}

/**
* The function changes the directory and updates the OLDPWD and PWD fields
* of the environment properly.
**/

void	ft_cd(char *p)
{	
	char	*str;
	t_list	*tmp;
	char	*res;

	str = malloc(sizeof(char *) * 1024);
	if (p == NULL || p[0] == '~')
	{
		getcwd(str, 1024);
		check_oldpwd(str);
		tmp = find_element("HOME");
		res = tmp->val;
		if (p)
			p = p + 2;
	}
	if (p != NULL && p[0] == '-' && p[1] == '\0')
		cd_minus(str);
	else
		ft_cd1(p, str, res, tmp);
}
