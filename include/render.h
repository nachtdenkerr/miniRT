/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:46:15 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/28 16:46:44 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math_utils.h"

double	hit_sphere(t_sphere sphere, t_ray ray);
double	hit_cylinder(t_cylinder cyl, t_ray ray);
double	hit_plane(t_plane plane, t_ray ray);

#endif