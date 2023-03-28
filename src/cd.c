#include "minishell.h"

int ft_cd(char **argv, t_data *data)
{
    if (argv[1] == NULL)
        chdir(ft_get_value("HOME", data));
    else
        chdir(argv[1]);
    return (0);
}
