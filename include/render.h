/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:46:15 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/07 13:45:10 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math_utils.h"
# include "utils.h"

# ifndef SHININESS
#  define SHINIESS 32
# endif

void	update_hit_record(t_hit_record *rec, t_point point, t_vector normal,
			t_color color);
double	*solve_t_values(t_cylinder *cyl, t_ray *ray);
bool	check_t_value(t_cylinder *cyl, t_ray *ray,
			t_hit_record *rec, double t_value);

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

t_color	checker_texture(t_texture checker, t_point point);

t_color	specular_lighting(t_color color, t_ray *ray,
			t_light *light, t_hit_record *rec);
t_color	diffuse_lighting(t_color color, t_light *light, t_hit_record *rec);

void	minirt(t_minirt *mrt);

#endif