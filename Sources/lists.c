#include "../shell.h"

/*
* Create new list.
*/

t_list	*ft_lstnew(char *var_inf, char *val_inf, int is_exp)
{
	t_list	*l;

	l = (t_list *)malloc(sizeof(t_list));
	if (!l)
		return (0);
	l->var = var_inf;
	l->val = val_inf;
	l->exp = is_exp;
	l->next = NULL;
	l->prev = NULL;
	return (l);
}

t_list	*find_element(char *var_name)
{
	t_list	*tmp;

	tmp = g_g.lenv;
	while (tmp)
	{
		if (!ft_strncmp_quote(tmp->var, var_name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
* Add new element at beginning of list.
*/
void	ft_lstadd_front(t_list **lst, t_list *neww)
{
	if (*lst)
	{
		neww->next = *lst;
		(*lst)->prev = neww;
		*lst = neww;
	}
	else
		*lst = neww;
}

/*
* Delete element from list.
*/

void	ft_lstdel(t_list **lst, t_list *del)
{
	if (*lst == NULL || del == NULL)
		return ;
	if (*lst == del)
		*lst = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del);
	return ;
}
