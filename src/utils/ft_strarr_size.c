//TODO:: add header

#include "../../includes/minishell.h"

size_t
    ft_strarr_size(char **str_arr)
{
    size_t  size;

    size = 0;
    while(str_arr && str_arr[size])
        ++size;
    return (size);
}