#include "../shell.h"

/*
*The atoi function skips all white-space characters at the beginning of the string, 
*converts the subsequent characters as part of the number, 
*and then stops when it encounters the first character that isn't a number.
*/

int	ft_atoi(const char *str)
{
	int	i;
	int	min;
	int	num;

	i = 0;
	num = 0;
	min = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		num = num * 10;
		num = num + str[i] - '0';
		i++;
	}
	return (num * min);
}
