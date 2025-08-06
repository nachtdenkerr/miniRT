/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:46:15 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/06 19:53:26 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math_utils.h"
# include "utils.h"

bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec);
bool	hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit_record *rec);
bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec);
bool	hit_cone(t_cone *cone, t_ray *ray, t_hit_record *rec);
bool	hit_sphere_wrapper(void *data, t_ray *ray, t_hit_record *rec);
bool	hit_cylinder_wrapper(void *data, t_ray *ray, t_hit_record *rec);
bool	hit_plane_wrapper(void *data, t_ray *ray, t_hit_record *rec);
bool	hit_cone_wrapper(void *data, t_ray *ray, t_hit_record *rec);
bool	hit_object(t_ray *ray, t_scene *scene, t_hit_record *rec);
void	init_ray(t_ray *ray, t_scene *scene, int i, int j);

t_color	specular_lighting(t_color color, t_ray *ray,
			t_light *light, t_hit_record *rec);
t_color	diffuse_lighting(t_color color, t_light *light, t_hit_record *rec);
		
void	minirt(t_minirt *mrt);

#endif