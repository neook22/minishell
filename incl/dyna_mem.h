#ifndef DYNA_MEM_H
# define DYNA_MEM_H

# include <stddef.h>

// (TODO think about)
// maybe add a fun ptr field to use in case of error

/* dynamic array type,
 * buff -> contents
 * i -> first unused index 
 * size_t sz -> size of currently alloced buffer */
typedef struct s_dyna
{
	void	*buff;
	size_t	i;
	size_t	sz;
}	t_dyna;

// init dynamic memory (don't alloc the struct itself only the buffer)
t_dyna	*ft_init_dyna(t_dyna *dyn);

// copy src_sz bytes from src at the end of dst (realloc if needed)
t_dyna	*ft_dyna_append(t_dyna *dst, void *src, size_t src_sz);

// like append but free src after
t_dyna	*ft_dyna_slurp(t_dyna *dst, void *src, size_t src_sz);

// copy the contents into a newly alloced (non-dynamic)
// buffer of the right size,
// then free the dynamic memory buffer
void	*ft_dedyna(t_dyna *dyn);

// append nzeros null bytes at the end of dynamic buffer
t_dyna	*ft_dyna_zeros(t_dyna *dst, size_t nzeros);

#endif
