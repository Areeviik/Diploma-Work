#include "../shell.h"

int	count_list_elements(void)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = g_g.lenv;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**list_to_arr(void)
{
	char	**arr;
	int		count;
	int		i;
	t_list	*temp;

	i = 0;
	temp = g_g.lenv;
	count = count_list_elements();
	arr = malloc(sizeof(char *) * (count + 1));
	while (i != count)
	{
		arr[i] = ft_strjoin(temp->var, "=");
		if (temp->val)
			arr[i] = ft_strjoin(arr[i], temp->val);
		i++;
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}
