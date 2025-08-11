/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:40:42 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/11 11:20:01 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "render.h"

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
void	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sp;
	t_object	obj;
	int			flag;

	flag = 0;
	sp = malloc(1 * sizeof(t_sphere));
	if (!sp)
		malloc_failure_obj_creation_exit(scene, tokens);
	obj.type = SPHERE;
	obj.data = sp;
	// obj.mat = REFLECTIVE;
	obj.hit = &hit_sphere_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || (tokens[4] && tokens[5]))
		invalid_argc_exit(tokens, NULL, scene, 2);
	sp->center = parse_vector(tokens[1], tokens, scene);
	sp->radius = ft_atof(tokens[2], &flag, 1, 0) / 2;
	if (flag || sp->radius <= 0.0)
		invalid_arg_exit(tokens, scene, 1);
	sp->color = parse_color(tokens[3], tokens, scene);
	sp->mat_value = -1.0;
	if (tokens[4])
		sp->type = get_material(tokens[4], &sp->mat_value, tokens, scene);
	else
		sp->type = NORMAL;
}

void	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		*pl;
	t_object	obj;

	pl = malloc(1 * sizeof(t_plane));
	if (!pl)
		malloc_failure_obj_creation_exit(scene, tokens);
	obj.type = PLANE;
	obj.data = pl;
	obj.hit = &hit_plane_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || (tokens[4] && tokens[5]))
		invalid_argc_exit(tokens, NULL, scene, 3);
	pl->point = parse_vector(tokens[1], tokens, scene);
	pl->normal = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(pl->normal))
		invalid_arg_exit(tokens, scene, 2);
	pl->color = parse_color(tokens[3], tokens, scene);
	pl->mat_value = -1.0;
	if (tokens[4])
		pl->type = get_material(tokens[4], &pl->mat_value, tokens, scene);
	else
		pl->type = NORMAL;
}

void	parse_cylinder(char **tokens, t_scene *scene, int flag)
{
	t_cylinder	*cy;
	t_object	obj;

	cy = malloc(1 * sizeof(t_cylinder));
	if (!cy)
		malloc_failure_obj_creation_exit(scene, tokens);
	obj.type = CYLINDER;
	obj.data = cy;
	obj.hit = &hit_cylinder_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5] || (tokens[6] && tokens[7]))
		invalid_argc_exit(tokens, NULL, scene, 4);
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
		cy->type = get_material(tokens[6], &cy->mat_value, tokens, scene);
	else
		cy->type = NORMAL;
}

void	parse_cone(char **tokens, t_scene *scene)
{
	t_cone		*co;
	t_object	obj;
	int			flag;

	flag = 0;
	co = malloc(1 * sizeof(t_cone));
	if (!co)
		malloc_failure_obj_creation_exit(scene, tokens);
	obj.type = CONE;
	obj.data = co;
	obj.hit = &hit_cone_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || (tokens[5] && tokens[6]))
		invalid_argc_exit(tokens, NULL, scene, 5);
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
		co->type = get_material(tokens[5], &co->mat_value, tokens, scene);
	else
		co->type = NORMAL;
}

void	parse_triangle(char **tokens, t_scene *scene)
{
	t_triangle	*tr;
	t_object	obj;

	tr = malloc(1 * sizeof(t_triangle));
	if (!tr)
		malloc_failure_obj_creation_exit(scene, tokens);
	obj.type = TRIANGLE;
	obj.data = tr;
	obj.hit = &hit_triangle_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || (tokens[5] && tokens[6]))
		invalid_argc_exit(tokens, NULL, scene, 9);
	tr->v1 = parse_vector(tokens[1], tokens, scene);
	tr->v2 = parse_vector(tokens[2], tokens, scene);
	tr->v3 = parse_vector(tokens[3], tokens, scene);
	tr->color = parse_color(tokens[4], tokens, scene);
	tr->mat_value = -1.0;
	if (tokens[5])
		tr->type = get_material(tokens[5], &tr->mat_value, tokens, scene);
	else
		tr->type = NORMAL;
}
