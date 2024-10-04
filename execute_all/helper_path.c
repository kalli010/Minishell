/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 05:52:36 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/04 06:49:52 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **allocate_options(int count)
{
    char **op;

    op = (char **)malloc((count + 2) * sizeof(char *));
    if (!op)
        return (NULL);
    op[count + 1] = NULL;
    return (op);
}

void free_options(char **op, int i)
{
    while (i > 0)

        free(op[--i]);
    free(op);
}

char **get_options(t_helper *helper, t_list *list)
{
    int count;
    char **op;

    count = count_arg(list);
    if (count < 1)
        return (NULL);
    op = allocate_options(count);
    if (!op)
        return (NULL);
    op[0] = get_path(helper, list);
    if (!op[0])
        return (free(op),NULL);
    list = list->next;
    int i = 1;
    while (list && list->type == OPTIONS)
    {
        op[i] = ft_strdup(list->content);
        if (!op[i])
        {
            free_options(op, i); 
            return (NULL);
        }
        list = list->next;
		i++;
    }
    return (op);
}
