#include "../shell.h"

/* Reversely compare strings(size-bounded) */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	if (!n)
		return (0);
	i = 0;
	while (i < n && st1[i] && st2[i] && st1[i] == st2[i])
		i++;
	if (i < n)
		return (st1[i] - st2[i]);
	else
		return (0);
}

int	ft_strncmp_quote(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	while (st1[i] && st2[i] && st1[i] == st2[i])
		i++;
	return (st1[i] - st2[i]);
}
