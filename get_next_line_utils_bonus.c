/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:47:08 by minkim3           #+#    #+#             */
/*   Updated: 2023/02/05 15:47:10 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	find_char(const char *s, int c)
{
	char	*dummy;
	ssize_t	index;

	dummy = (char *)s;
	index = 0;
	while (*(dummy + index))
	{
		if (((char)*(dummy + index)) == (char)c)
			return (index);
		index++;
	}
	if ((char)c == '\0')
		return (index);
	return (-1);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*append_buffer(char const *s1, char const *s2, size_t len)
{
	char	*arr;
	size_t	len_s1;

	if (s1 == NULL && s2 != NULL)
	{
		arr = malloc(sizeof(char) * (len + 1));
		if (!arr)
			return (NULL);
		ft_strlcpy(arr, s2, len + 1);
		return (arr);
	}
	else if (s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	arr = (char *)malloc(sizeof(char) * (len_s1 + len + 1));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s1, len_s1 + 1);
	ft_strlcat(arr, s2, len_s1 + len + 1);
	free((void *)s1);
	return (arr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int		dst_len;
	unsigned int		src_len;
	unsigned int		cat_size;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	cat_size = dstsize - dst_len - 1;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (*dst)
		dst++;
	if (dstsize > dst_len)
	{
		while ((cat_size) && *src != '\0')
		{
			*dst = *src;
			dst++;
			src++;
			cat_size--;
		}
		*dst = '\0';
	}
	return (dst_len + src_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	index;

	src_len = ft_strlen((char *)src);
	index = 0;
	if (dstsize <= src_len)
	{
		while (index + 1 < dstsize)
		{
			dst[index] = src[index];
			index++;
		}
	}
	else
	{
		while (src[index])
		{
			dst[index] = src[index];
			index++;
		}
	}
	if (dstsize != 0)
		dst[index] = 0;
	return (src_len);
}
