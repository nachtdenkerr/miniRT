/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:10:17 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/28 10:47:55 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_minirt(void)
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
	return (mrt);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_minirt	*mrt;

	if (argc != 2)
		error_exit("Usage: ./miniRT scene.rt");
	parse_scene(argv[1], &scene);
	mrt = init_minirt();
	if (!mrt)
		return (EXIT_FAILURE);
	mrt->scene = &scene;
	// TODO: render scene here
	return (0);
}
