/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisbrochard <louisbrochard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:25:47 by louisbrocha       #+#    #+#             */
/*   Updated: 2023/05/05 17:13:34 by louisbrocha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
int cmpfunc(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int get_median(t_stack *stack)
{
    int size = stack->size;
    int *sorted_arr = malloc(sizeof(int) * size);

    if (!sorted_arr)
        exit_error("Error: malloc failed\n");

    // copier les éléments de la pile dans un tableau
    int i = 0;
    while (!is_empty_stack(stack))
    {
        sorted_arr[i] = stack->top->value;
        pop_stack(stack);
        i++;
    }

    // trier le tableau en ordre croissant
    qsort(sorted_arr, size, sizeof(int), cmpfunc);

    // récupérer la valeur médiane
    int median = sorted_arr[size / 2];

    // remettre les éléments dans la pile
    i = size - 1;
    while (i >= 0)
    {
        push_stack(stack, sorted_arr[i]);
        i--;
    }

    free(sorted_arr);

    return median;
}

void quick_sort(t_stack *stack_a, t_stack *stack_b, int size)
{
    if (size <= 1)
        return;

    int pivot = get_median(stack_a);
    int i = -1;
    while (++i < size)
    {
        if (stack_a->top->value < pivot)
            do_pb(stack_a, stack_b);
        else
            do_ra(stack_a);
    }

    int pos_pivot = get_elem_position(stack_a, pivot);
    int size_lower = pos_pivot;
    int size_upper = size - pos_pivot - 1;

    quick_sort(stack_a, stack_b, size_lower);
    while (size_lower--)
        do_ra(stack_a);

    quick_sort(stack_a, stack_b, size_upper);
    while (size_upper--)
        do_rra(stack_a);

    while (!is_empty_stack(stack_b))
    {
        if (stack_b->top->value < pivot)
            do_pa(stack_a, stack_b);
        else
            do_rra(stack_b);
    }
}
*/


static void		ft_median_sort(t_begin *begin, int len, int *r, int *p)
{
	int		i;
	int		median;
	t_pile	*tmp;

	i = 0;
	median = ft_median(&begin->ba, 1, len);
	while (ft_compare_with_median(begin, len - i, median, 1) && i++ < len)
	{
		if (begin->ba->data < median)
		{
			tmp = begin->ba->next;
			begin->bb = ft_push_pile(&begin->bb, &begin->ba);
			begin->ba = tmp;
			ft_instruction(&begin->inst, 4);
			*p = *p + 1;
		}
		else
		{
			begin->ba = ft_rotate_pile(&begin->ba);
			ft_instruction(&begin->inst, 5);
			*r = *r + 1;
		}
	}
}

static void		ft_place(t_begin *begin, int *r)
{
	int		lena;

	lena = ft_find_len(&begin->ba);
	if (*r > (lena / 2) && lena > 3)
	{
		while (*r < lena)
		{
			begin->ba = ft_rotate_pile(&begin->ba);
			ft_instruction(&begin->inst, 5);
			*r = *r + 1;
		}
	}
	else if (lena > 3)
	{
		while (*r)
		{
			begin->ba = ft_reverse_rotate_pile(&begin->ba);
			ft_instruction(&begin->inst, 7);
			*r = *r - 1;
		}
	}
}

void			ft_work_a(t_begin *begin, int len)
{
	int			r;
	int			p;
	t_pile		*tmp;

	r = 0;
	p = 0;
	if (len <= 3)
	{
		ft_sort_min_a(begin);
		return ;
	}
	if (begin->ba != NULL && ft_is_sort(&begin->ba, 1) == 0)
		return ;
	ft_median_sort(begin, len, &r, &p);
	ft_place(begin, &r);
	ft_work_a(begin, (len - p));
	ft_work_b(begin, p);
	while (p-- && begin->bb != NULL)
	{
		tmp = begin->bb->next;
		begin->ba = ft_push_pile(&begin->ba, &begin->bb);
		begin->bb = tmp;
		ft_instruction(&begin->inst, 3);
	}
}