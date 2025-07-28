/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:07:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/28 12:29:45 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "MLX42.h"

// Both POINT and VECTOR have 3 components x,y,z
// The struct can have 2 aliases t_vector and t_point
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
} t_vector,	t_point;

typedef struct s_ray
{
	t_point		origin;
	t_vector	dir;
}				t_ray;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ambient
{
	double	ratio; // [0.0, 1.0]
	t_color	color;
}				t_ambient;

typedef struct s_camera
{
	t_point		position;
	t_vector	orientation;
	double		fov; // [0, 180]
}				t_camera;

typedef struct s_light
{
	t_point		position;
	double		brightness; // [0.0, 1.0]
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_point		center;
	double		radius;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_point		point;
	t_vector	normal;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_point		center;
	t_vector	axis;
	double		raidus;
	double		height;
	t_color		color;
}				t_cylinder;

// For bonus
typedef struct s_cone
{
	t_point		apex;
	t_vector	axis;
	double		angle;
	t_color		color;
}				t_cone;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights; // support multiple lights for bonus
	int			light_count;

	t_sphere	*spheres;
	int			sphere_count;

	t_plane		*planes;
	int			plane_count;

	t_cylinder	*cylinders;
	int			cylinder_count;

	t_cone		*cones; // bonus
	int			cone_count;
}				t_scene;

typedef struct s_minirt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
}				t_minirt;

#endif
