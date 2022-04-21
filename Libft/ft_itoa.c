/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:08:49 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/18 17:10:03 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	get_nb_digit(long n, int sign)
{
	unsigned int	nb_digit;

	if (n == 0)
		return (1);
	nb_digit = 0;
	while (n > 0)
	{
		n /= 10;
		nb_digit++;
	}
	if (sign == -1)
		nb_digit++;
	return (nb_digit);
}

static void	convert_nb(char *outstr, long n, unsigned int nb_digit,
		int sign)
{
	outstr[nb_digit] = '\0';
	outstr[--nb_digit] = n % 10 + '0';
	n /= 10;
	while (n > 0)
	{
		outstr[--nb_digit] = n % 10 + '0';
		n /= 10;
	}
	if (sign == -1)
		outstr[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*outstr;
	long			n_l;
	unsigned int	nb_digit;
	int				sign;

	sign = 1;
	if (n < 0)
	{
		n_l = (long)n * -1;
		sign = -1;
	}
	else
		n_l = n;
	nb_digit = get_nb_digit(n_l, sign);
	outstr = malloc(sizeof(char) * (nb_digit + 1));
	if (!outstr)
		return (NULL);
	convert_nb(outstr, n_l, nb_digit, sign);
	return (outstr);
}
