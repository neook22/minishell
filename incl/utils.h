#ifndef UTILS_H
# define UTILS_H

// return the first part of str is an allowed_word
// allowed_words is null-terminated
//
// return NULL if 'str' doesn't begin with any words in 'allowed_words'
// eg :
//   first_word("hello world"), {"hello", "bouh", NULL}) -> "hello"
// note :
//   if i < j and word[j] begins with word[i]
//   then first_word can never return word[j]
char	*ft_first_word(char *str, char *const *allowed_words);

int		ft_is_in(char const *charset, char c);

void	ft_free_strtab(char **tab);

#endif
