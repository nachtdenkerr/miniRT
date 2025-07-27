/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:10:17 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/27 19:12:20 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main(int argc, char **argv)
{
	t_scene scene;
	t_mlx mlx;

	if (argc != 2)
		error_exit("Usage: ./miniRT scene.rt");

	parse_scene(argv[1], &scene);

	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		error_exit("MLX init failed");
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 800, 600, "miniRT");

	// TODO: render scene here

	mlx_hook(mlx.win_ptr, 17, 0, close_window, &mlx); // Red cross
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);       // ESC key
	mlx_loop(mlx.mlx_ptr);

	return (0);
}
