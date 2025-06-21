/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:52:54 by odana             #+#    #+#             */
/*   Updated: 2025/05/23 09:04:38 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_itoa(int n)
{
	int			len;
	char		*result;
	const char	*digits = "0123456789";
	long		nbr;

	nbr = n;
	len = ft_numlen(nbr);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len] = '\0';
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		result[--len] = digits[nbr % 10];
		nbr /= 10;
	}
	return (result);
}
