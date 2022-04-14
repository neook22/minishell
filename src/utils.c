int	ft_is_in(char const *charset, char c)
{
	while (*charset)
	{
		if (c == *(charset++))
			return (1);
	}
	return (0);
}
