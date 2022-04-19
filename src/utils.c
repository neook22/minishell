#include <stdlib.h>
#include "libft.h"

char	*ft_first_word(char *str, char *const *allowed_words)
{
	while (*allowed_words)
	{
		if (!ft_strncmp(str, *allowed_words, ft_strlen(*allowed_words)))
			return (*allowed_words);
		allowed_words++;
	}
	return (NULL);
}

int	ft_is_in(char const *charset, char c)
{
	while (*charset)
	{
		if (c == *(charset++))
			return (1);
	}
	return (0);
}

void	ft_free_strtab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}
