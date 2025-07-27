/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:07:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/27 19:11:56 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vector {
	double x;
	double y;
	double z;
} t_vector;

typedef struct s_color {
	int r;
	int g;
	int b;
} t_color;

typedef struct s_ambient {
	double ratio; // [0.0, 1.0]
	t_color color;
} t_ambient;

typedef struct s_camera {
	t_vector position;
	t_vector orientation;
	double fov; // [0, 180]
} t_camera;

typedef struct s_light {
	t_vector position;
	double brightness; // [0.0, 1.0]
	t_color color;
} t_light;

typedef struct s_sphere {
	t_vector center;
	double diameter;
	t_color color;
} t_sphere;

typedef struct s_plane {
	t_vector point;
	t_vector normal;
	t_color color;
} t_plane;

typedef struct s_cylinder {
	t_vector center;
	t_vector axis;
	double diameter;
	double height;
	t_color color;
} t_cylinder;

// For bonus
typedef struct s_cone {
	t_vector apex;
	t_vector axis;
	double angle;
	t_color color;
} t_cone;

typedef struct s_scene {
	t_ambient ambient;
	t_camera camera;
	t_light *lights; // support multiple lights for bonus
	int light_count;

	t_sphere *spheres;
	int sphere_count;

	t_plane *planes;
	int plane_count;

	t_cylinder *cylinders;
	int cylinder_count;

	t_cone *cones; // bonus
	int cone_count;
} t_scene;

typedef struct s_ray {
	t_vector origin;
	t_vector direction;
} t_ray;

typedef struct s_mlx {
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
	int bpp;
	int size_line;
	int endian;
} t_mlx;

#endif
