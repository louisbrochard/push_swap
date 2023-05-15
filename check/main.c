/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisbrochard <louisbrochard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:27:42 by louisbrocha       #+#    #+#             */
/*   Updated: 2023/05/15 16:20:47 by louisbrocha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;
    char    *str;

    if (argc == 1)
        return (0);
    if (ft_check_arg(argv) == 1)
        ft_exit_error(NULL, NULL);
    if (argc <= 2)
        return (0);
    if (ft_is_sorted(argv) == 0)
        return (0);
    ft_init(&stack_a, &stack_b, argc, argv);
    str = get_next_line(0);
    while (str != NULL)
    {
        ft_move(str, stack_a, stack_b);
        str = get_next_line(0);
    }
    free(str);
    ft_check_stack(stack_a, stack_b);
    ft_lst_del(&stack_a);
    ft_lst_del(&stack_b);
    free(stack_a);
    free(stack_b);
    return (0);
}