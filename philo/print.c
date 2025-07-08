/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:39:43 by asezgin           #+#    #+#             */
/*   Updated: 2025/07/08 09:56:05 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phlio.h"
#include <unistd.h>

char	*ft_lltoa(long long n)
{
	char			*str;
	long long		tmp = n;
	int				len = (n <= 0);

	while (tmp && ++len)
		tmp /= 10;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
char	*ft_itoa(int n)
{
	return (ft_lltoa(n));
}
int ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	write_status(long long timestamp, int id, const char *msg)
{
	char	*time_str = ft_lltoa(timestamp);
	char	*id_str = ft_itoa(id);

	if (time_str && id_str)
	{
		write(1, time_str, ft_strlen(time_str));
		write(1, " ", 1);
		write(1, id_str, ft_strlen(id_str));
		write(1, " ", 1);
		write(1, msg, ft_strlen(msg));
		write(1, "\n", 1);
	}
	free(time_str);
	free(id_str);
}
