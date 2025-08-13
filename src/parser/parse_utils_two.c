/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:04:02 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/13 15:26:36 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_not_valid_format(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (1);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (0);
	return (1);
}

void	invalid_mat_val_exit(char *str, char **tokens,
	char **arr, t_scene *scene)
{
	ft_putstr_fd("Invalid material value: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\nexpected between 0 and 1\n", 2);
	free_arr(tokens);
	free_arr(arr);
	cleanup_scene(scene);
	exit (1);
}

t_mat	get_material(char *str, double *value, char **tokens,
		t_scene *scene)
{
	char	**arr;
	int		flag;

	flag = 0;
	arr = ft_split(str, ':');
	if (!arr)
		free_and_failed_malloc(tokens, scene);
	if (!arr[0] || !arr[1] || arr[2])
		invalid_argc_exit(tokens, arr, scene, 10);
	*value = ft_atof(arr[1], &flag, 1, 0);
	if (flag || *value < 0.0 || *value > 1.0)
		invalid_mat_val_exit(arr[1], tokens, arr, scene);
	if (!ft_strcmp(arr[0], "mr"))
		return (free_arr(arr), REFLECTIVE);
	else if (!ft_strcmp(arr[0], "cb"))
		return (free_arr(arr), CHECKER);
	ft_putstr_fd("Invalid Material identifier\n", 2);
	free_arr(arr);
	free_arr(tokens);
	cleanup_scene(scene);
	exit(1);
}

void	init_co(t_cone *co, char **tokens, t_scene *scene, int flag)
{
	co->apex = parse_vector(tokens[1], tokens, scene);
	co->axis = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(co->axis))
		invalid_arg_exit(tokens, scene, 6);
	co->angle = ft_atof(tokens[3], &flag, 1, 0) * M_PI / 180;
	if (flag || co->angle <= 0.0 || co->angle >= 180)
		invalid_arg_exit(tokens, scene, 7);
	co->color = parse_color(tokens[4], tokens, scene);
	co->mat_value = -1.0;
	if (tokens[5])
		co->mat = get_material(tokens[5], &co->mat_value, tokens, scene);
	else
		co->mat = NORMAL;
}

void	init_cy(t_cylinder *cy, char **tokens, t_scene *scene, int flag)
{
	cy->center = parse_vector(tokens[1], tokens, scene);
	cy->axis = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(cy->axis))
		invalid_arg_exit(tokens, scene, 3);
	cy->radius = ft_atof(tokens[3], &flag, 1, 0) / 2;
	if (flag || cy->radius <= 0.0)
		invalid_arg_exit(tokens, scene, 4);
	cy->height = ft_atof(tokens[4], &flag, 1, 0);
	if (flag || cy->height <= 0.0)
		invalid_arg_exit(tokens, scene, 5);
	cy->color = parse_color(tokens[5], tokens, scene);
	cy->mat_value = -1.0;
	if (tokens[6])
		cy->mat = get_material(tokens[6], &cy->mat_value, tokens, scene);
	else
		cy->mat = NORMAL;
}
