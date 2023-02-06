/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:31:35 by htam              #+#    #+#             */
/*   Updated: 2022/12/12 15:31:37 by htam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_gnljoin(char *s1, char *s2)
{
	int		n;
	int		i;
	char	*newstr;

	n = 0;
	i = 0;
	if (!s1)
		return (NULL);
	newstr = malloc(sizeof(*newstr) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	while (s1[n])
	{
		newstr[n] = s1[n];
		n++;
	}
	while (s2[i])
	{
		newstr[n + i] = s2[i];
		i++;
	}
	newstr[n + i] = 0;
	free(s1);
	return (newstr);
}

char	*ft_substr_mod(char const *s, unsigned int start, size_t len)
{
	unsigned int		n;
	unsigned int		i;
	char				*substr;

	n = 0;
	i = 0;
	substr = malloc(sizeof(*substr) * (len + 1));
	if (!substr)
		return (NULL);
	while (s[n])
	{
		if (n >= start && i < len)
		{
			substr[i] = s[n];
			i++;
		}
		n++;
	}
	substr[i] = 0;
	if (substr[0] == 0)
	{
		free(substr);
		return (NULL);
	}
	return (substr);
}
