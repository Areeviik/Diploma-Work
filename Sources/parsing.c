#include "../shell.h"

char	*dollar_sign(char *s, int *i)
{
	char	*str;
	int		j;
	t_list	*tmp;

	j = 0;
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	(*i)++;
	while (s[*i] != ' ' && s[*i] != '\0' && s[*i] != '\'' && s[*i] != '\"')
	{
		str[j] = s[*i];
		j++;
		(*i)++;
	}
	(*i)--;
	str[j] = '\0';
	tmp = find_element(str);
	if (tmp == NULL)
		return (NULL);
	return (tmp->val);
}

void	init(int num)
{
	g_g.e = NULL;
	g_g.qchecker = NULL;
	g_g.cmds[num].file_fd = 1;
	g_g.cmds[num].in = 0;
	g_g.cmds[num].out = 1;
	g_g.hdoc = 0;
}

void	main_parsing(char *s, int num)
{
	int		i;
	char	*buf;
	int		j;

	if (is_space(s))
		return ;
	init(num);
	parse_redirects(s, num, 0, 0);
	if (num)
		connect_pipes(num);
	buf = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!buf)
		ft_error("Can't malloc", 0);
	g_g.cmds[num].name = NULL;
	i = without_spaces(s, 0);
	while (g_g.cmds[num].name == NULL && s[i])
	{
		g_g.cmds[num].name = quote_handling(s, &i);
		i = without_spaces(s, i);
	}
	j = -1;
	while (++j != i)
		s[j] = ' ';
	g_g.cmds->str_arg = ft_strtrim(s, " ");
	parse_args(s, num, i);
}
