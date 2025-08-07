/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:36:22 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/07 20:12:22 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_color	create_color(int r, int g, int b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

// Add two RGB colors.
t_color	color_add(t_color color_a, t_color color_b)
{
	t_color	color_c;

	color_c.b = color_a.b + color_b.b;
	color_c.r = color_a.r + color_b.r;
	color_c.g = color_a.g + color_b.g;
	return (color_c);
}

// Scale color intensity.
t_color	color_scale(t_color c, double s)
{
	t_color	c_scaled;

	c_scaled.b = (int)round(c.b * s);
	c_scaled.g = (int)round(c.g * s);
	c_scaled.r = (int)round(c.r * s);
	return (c_scaled);
}

// Clamp RGB channels to [0,255].
t_color	color_clamp(t_color c)
{
	t_color	c_clamp;

	c_clamp.r = fmin(fmax(c.r, 0), 255);
	c_clamp.g = fmin(fmax(c.g, 0), 255);
	c_clamp.b = fmin(fmax(c.b, 0), 255);
	return (c_clamp);
}

// Multiply colors component-wise (for light mixing).
t_color	color_mult(t_color a, t_color b)
{
	t_color	c;

	c.r = (int)round((a.r * b.r) / 255);
	c.g = (int)round((a.g * b.g) / 255);
	c.b = (int)round((a.b * b.b) / 255);
	return (c);
}

u_int32_t	combine_color(t_color a)
{
	u_int32_t	c;

	c = (a.r << 24) | (a.g << 16) | (a.b << 8) | 0xFF;
	return (c);
}
