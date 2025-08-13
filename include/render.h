/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:46:15 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/13 18:02:24 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math_utils.h"
# include "utils.h"

# ifndef SHININESS
#  define SHINIESS 32
# endif

// hit record related functions
typedef struct s_cone_var
{
	t_point		p;
	t_vector	u;
	t_vector	v;
	t_vector	w;
	t_vector	normal;
	double		m;
	double		n;
	double		k;
	double		a;
	double		half_b;
	double		c;
	double		tx_minus;
	double		tx_plus;
	double		delta;
	double		s;
}				t_cone_var;

typedef struct s_triangle_var
{
	t_point		e1;
	t_vector	e2;
	t_vector	ray_cross_e2;
	t_vector	s_cross_e1;
	t_vector	s;
	t_vector	normal;
	t_vector	intersection_point;
	double		determinant;
	double		inverse_determinant;
	double		u;
	double		v;
	double		t;
}				t_triangle_var;

void	update_hit_record(t_hit_record *rec, t_point point, t_vector normal,
			t_color color);
double	*solve_t_values(t_cylinder *cyl, t_ray *ray, t_vector axis);
bool	check_t_value(t_cylinder *cyl, t_ray *ray,
			t_hit_record *rec, double t_value);

// intersection functions
bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec);
bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec);
bool	hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit_record *rec);
bool	hit_cone(t_cone *cone, t_ray *ray, t_hit_record *rec);
bool	hit_triangle(t_triangle *tri, t_ray *ray, t_hit_record *rec);

bool	hit_sphere_wrapper(void *data, t_ray *ray, t_hit_record *rec);
bool	hit_cylinder_wrapper(void *data, t_ray *ray, t_hit_record *rec);
bool	hit_plane_wrapper(void *data, t_ray *ray, t_hit_record *rec);
bool	hit_cone_wrapper(void *data, t_ray *ray, t_hit_record *rec);
bool	hit_triangle_wrapper(void *data, t_ray *ray, t_hit_record *rec);

bool	hit_object(t_ray *ray, t_scene *scene, t_hit_record *rec);

void	init_ray(t_ray *ray, t_scene *scene, int i, int j);

// texture mapping functions
t_color	starry_sky_color(t_ray *ray);
void    checker_texture_init(t_texture *checker, double width, double height,
        double scale_val);
t_color	checker_texture(t_texture checker, double u, double v);
void	get_sphere_uv(t_hit_record *rec, t_point sp_center, double radius);
void	get_plane_uv(t_hit_record *rec, t_point point);

// lighting functions
bool	is_in_shadow(t_scene *scene, t_light *light, t_ray *shadow);
t_color	specular_lighting(t_color color, t_ray *ray,
			t_light *light, t_hit_record *rec);
t_color	diffuse_lighting(t_color color, t_light *light, t_hit_record *rec);
t_color	combine_lighting(t_color color, t_scene *scene,
t_hit_record rec, t_ray *ray);
t_color	starry_sky_color(t_ray *ray);

t_color	calculate_color(t_ray *ray, t_scene *scene, int depth);
void	minirt(t_minirt *mrt);

//cone_triangle_helper.c
bool	calculate_cone(t_cone_var *var, double *t);
void	init_cone_var(t_cone_var *var, t_cone *cone, t_ray *ray);
void	ft_swap(double *x, double *y);

#endif