#ifndef EXEC_H
#define EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "vars.h"
#include "tree.h"
#include "built_ins.h"
#include "exec_utils.h"

int	ft_exec(t_tree *t, t_env *env);

#endif
