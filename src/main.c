/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:10:17 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/06 11:59:39 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
void print_scene(t_scene *scene);

void	fill_image_with_color(mlx_image_t *img)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	color;

	for (uint32_t y = 0; y < img->height; ++y)
	{
		for (uint32_t x = 0; x < img->width; ++x)
		{
			r = (x * 255) / img->width;
			g = (y * 255) / img->height;
			b = 255;
			color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
			mlx_put_pixel(img, x, y, color);
		}
	}
}

void	close_mrt(void *param)
{
	t_minirt	*mrt;

	mrt = (t_minirt *)param;
	if (mrt)
	{
		if (mrt->img)
		{
			mlx_delete_image(mrt->mlx, mrt->img);
		}
		if (mrt->mlx)
		{
			mlx_close_window(mrt->mlx);
			mlx_terminate(mrt->mlx);
		}
		cleanup_scene(mrt->scene);
		free(mrt);
	}
	exit(0);
}

void	esc_key(mlx_key_data_t keydata, void *param)
{
	t_minirt	*mrt;

	mrt = (t_minirt *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		close_mrt(mrt);
	}
}

t_minirt	*init_minirt(t_scene *scene)
{
	mlx_t				*mlx;
	t_minirt			*mrt;
	static mlx_image_t	*image;

	mrt = malloc(sizeof(t_minirt));
	if (!mrt)
		return (NULL);
	mlx = mlx_init(800, 600, "miniRT", true);
	if (!mlx)
		return (perror(mlx_strerror(mlx_errno)), free(mrt), NULL);
	image = mlx_new_image(mlx, 800, 600);
	if (!image)
		return (mlx_close_window(mlx), mlx_terminate(mlx),
			perror(mlx_strerror(mlx_errno)), free(mrt), NULL);
	mrt->mlx = mlx;
	mrt->img = image;
	mrt->scene = scene;
	mlx_close_hook(mlx, &close_mrt, mrt);
	mlx_key_hook(mlx, &esc_key, mrt);
	return (mrt);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_minirt	*mrt;

	(void)argv;
	if (argc != 2)
		error_exit("Usage: ./miniRT scene.rt");
	parse_scene(argv[1], &scene);
	//print_scene(&scene);
	//cleanup_scene(&scene);
	mrt = init_minirt(&scene);
	if (!mrt)
		return (cleanup_scene(&scene), EXIT_FAILURE);
	minirt(mrt);
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
	//fill_image_with_color(mrt->img);
	mlx_loop(mrt->mlx);
	return (0);
}