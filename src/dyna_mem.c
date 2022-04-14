#include <stdlib.h>
#include "libft.h"
#include "dyna_mem.h"

// !!! (TODO think about) 
// here and elsewhere pb, if t_dyna contains pointer,
// how to free them upon error??

// init dynamic memory (don't alloc the struct itself only the buffer)
t_dyna	*ft_init_dyna(t_dyna *dyn)
{
	const size_t	dfl_sz = 64;

	dyn->buff = malloc(dfl_sz);
	if (!dyn->buff)
		return (NULL);
	dyn->i = 0;
	dyn->sz = dfl_sz;
	return (dyn);
}

// copy src_sz bytes from src at the end of dst (realloc if needed)
t_dyna	*ft_dyna_append(t_dyna *dst, void *src, size_t src_sz)
{
	void	*tmp_buff;

	if (!dst->buff)
		return (NULL);
	if (dst->i + src_sz > dst->sz)
	{
		tmp_buff = malloc(2 * (dst->i + src_sz));
		if (!tmp_buff)
		{
			free(dst->buff);
			dst->buff = NULL;
			return (NULL);
		}
		ft_memcpy(tmp_buff, dst->buff, dst->i);
		dst->buff = tmp_buff;
		dst->sz = 2 * (dst->i + src_sz);
	}
	ft_memcpy(dst->buff + dst->i, src, src_sz);
	dst->i += src_sz;
	return (dst);
}

// like append but free src after
t_dyna	*ft_dyna_slurp(t_dyna *dst, void *src, size_t src_sz)
{
	dst = ft_dyna_append(dst, src, src_sz);
	free(src);
	return (dst);
}

// append nzeros null bytes at the end of dynamic buffer
t_dyna	*ft_dyna_zeros(t_dyna *dst, size_t nzeros)
{
	char	zero;

	zero = 0;
	while (nzeros--)
		dst = ft_dyna_append(dst, &zero, 1);
	return (dst);
}

// copy the content into a newly alloced (non-dynamic)
// buffer of the right size 
// then free the dynamic memory buffer
void	*ft_dedyna(t_dyna *dyn)
{
	void	*ret;

	ret = malloc(dyn->i);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, dyn->buff, dyn->i);
	free(dyn->buff);
	return (ret);
}
