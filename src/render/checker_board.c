/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:05:06 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/07 13:48:23 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	checker_texture(t_texture checker, t_point point)
{
	// bool	is_even;
	int		total_val;
	double	inverse_scale;

	inverse_scale = 1.0 / checker.scale;
	total_val = (int)floor(point.x * inverse_scale)
		+ (int)floor(point.y * inverse_scale)
		+ (int)floor(point.z * inverse_scale);
	if (total_val % 2 == 0)
		return (checker.color1);
	else
		return (checker.color2);
}
