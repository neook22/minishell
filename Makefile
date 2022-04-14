SRC=dyna_mem.c varexpand.c get_token.c utils.c tree.c exec.c exec_utils.c vars.c built_cd.c built_export.c built_unset.c builtins.c environnement.c main.c
SRCDIR=src
OBJ=${SRC:.c=.o}
OBJDIR=obj
INCLDIR=incl
TESTDIR=test
NAME=minishell
CFLAGS=-Wall -Wextra -Werror -I ${INCLDIR}

#${NAME} : ${addprefix ${OBJDIR}/, ${OBJ}} libft/libft.a
#	gcc ${CFLAGS} -o ${NAME} $^ -L libft -lft -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew//opt/readline/include

${NAME} : ${addprefix ${OBJDIR}/, ${OBJ}} libft/libft.a
	gcc ${CFLAGS} -o ${NAME} $^ -L libft -lft -lreadline


libft/libft.a:
	cd libft && make

${OBJDIR}/%.o: ${SRCDIR}/%.c
	gcc ${CFLAGS} -c $< -o $@

test_%: ${TESTDIR}/test_%.c ${addprefix ${OBJDIR}/, ${OBJ}} libft/libft.a
	gcc ${CFLAGS} -o $@ $^ -L libft -lft

all: ${NAME}
	@#empty

clean:
	rm -f ${addprefix ${OBJDIR}/, ${OBJ}}
	cd libft/ && make clean

fclean: clean 
	rm -f minishell
	cd libft/ && make fclean

re: fclean
	make

bonus: all
	@#empty

.PHONY: re fclean clean all bonus
