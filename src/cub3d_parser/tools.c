/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:23 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/17 16:14:24 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h" 

static size_t	ft_countword(const char *str)
{
	int		in_word;
	size_t	count;

	in_word = 0;
	count = 0;
	while (*str)
	{
		if (!isspace(*str) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (isspace(*str))
			in_word = 0;
		str++;
	}
	return (count);
}

static size_t	calculate_every_word(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && !isspace(s[len]))
		len++;
	return (len);
}

static void	free_memory(char **trunks, size_t i)
{
	while (i--)
		free(trunks[i]);
}

static int	split_helper(char **trunks, const char *s)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		if (!isspace(*s))
		{
			word_len = calculate_every_word(s);
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

char	**ft_split_space(const char *s)
{
	size_t	word_count;
	char	**trunks;

	if (s == NULL)
		return (NULL);
	word_count = ft_countword(s);
	trunks = malloc((word_count + 1) * sizeof(char *));
	if (!trunks)
		return (NULL);
	trunks[word_count] = NULL;
	if (!split_helper(trunks, s))
	{
		free(trunks);
		return (NULL);
	}
	return (trunks);
}
