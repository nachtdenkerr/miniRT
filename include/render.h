/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:46:15 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/05 13:18:55 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math_utils.h"

double	hit_sphere(t_sphere sphere, t_ray ray);
double	hit_cylinder(t_cylinder cyl, t_ray ray);
double	hit_plane(t_plane plane, t_ray ray);
void	init_ray(t_ray *ray, t_scene *scene, int i, int j);
void	minirt(t_minirt *mrt);

#endif