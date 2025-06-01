/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:32:52 by riramana          #+#    #+#             */
/*   Updated: 2025/05/13 14:34:21 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_operation(char *op)
{
	int	i;

	i = 0;
	while (op[i])
		i++;
	write(1, op, i);
	write(1, "\n", 1);
}
