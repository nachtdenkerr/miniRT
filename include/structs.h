/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:07:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/05 13:25:32 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42.h"
# include "../lib/libft/include/libft.h"
# include "../lib/libft/include/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# ifndef EPSILON
#  define EPSILON 1e-6
# endif
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
	t_point		hit_point;
	int			hit_found;
}				t_ray;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ambient
{
	double	brightness; // [0.0, 1.0]
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
	double		radius;
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
	int			ambiant_count;
	t_camera	camera;
	int			camera_count;
	t_light		*lights; // support multiple lights for bonus
	int			light_count;
	int			l_index;
	t_sphere	*spheres;
	int			sphere_count;
	int			sp_index;
	t_plane		*planes;
	int			plane_count;
	int			pl_index;
	t_cylinder	*cylinders;
	int			cylinder_count;
	int			cy_index;
	t_cone		*cones; // bonus
	int			cone_count;
	int			co_index;
}				t_scene;

typedef struct s_minirt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
}				t_minirt;

#endif
