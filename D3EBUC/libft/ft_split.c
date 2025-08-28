/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:03:02 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/10/31 13:44:03 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(const char *str, char c)
{
	int		in_word;
	size_t	count;

	in_word = 0;
	count = 0;
	while (*str)
	{
		if (*str != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

static size_t	calculate_every_word(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	free_memory(char **trunks, size_t i)
{
	while (i--)
		free(trunks[i]);
}

static int	split_helper(char **trunks, const char *s, char c)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_len = calculate_every_word(s, c);
			trunks[i] = (char *)malloc((word_len + 1) * sizeof(char));
			if (!trunks[i])
			{
				free_memory(trunks, i);
				return (0);
			}
			ft_strlcpy(trunks[i], s, word_len + 1);
			s += word_len;
			i++;
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	size_t	word_count;
	char	**trunks;

	if (s == NULL)
		return (NULL);
	word_count = ft_countword(s, c);
	trunks = malloc((word_count + 1) * sizeof(char *));
	if (!trunks)
		return (NULL);
	trunks[word_count] = NULL;
	if (!split_helper(trunks, s, c))
	{
		free(trunks);
		return (NULL);
	}
	return (trunks);
}
