/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:21:56 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/23 12:21:09 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//find and return the index of c in str. search for a maximum of n chars
//return -1 if not found
size_t	ft_strnat(const char *str, int c, size_t n)
{
	char	*s1;
	size_t	i;

	i = 0;
	s1 = (char *) str;
	while (s1[i] && i < n)
	{
		if(s1[i] == c)
			return (i);
		i++;
	}
	return (NO_NEW_LINE);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	total_size;
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	i = 0;
	total_size = nmemb * size;
	if (total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	while (i < total_size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

void	*ft_memset(void	*s, int c, size_t n)
{
	while (n--)
	{
		*(char *)(s + n) = c;
	}
	return (s);
}

void	*ft_memmove(void	*dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src > dest)
	{
		while (i < n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	}
	else if (src < dest)
	{
		while (n--)
			*(char *)(dest + n) = *(char *)(src + n);
	}
	return (dest);
}
