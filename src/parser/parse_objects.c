/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:40:42 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:03 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "render.h"

void	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sp;
	t_object	obj;
	int			flag;

	flag = 0;
	sp = malloc(1 * sizeof(t_sphere));
	if (!sp)
		malloc_failure_obj_creation_exit(scene);
	obj.type = SPHERE;
	obj.data = sp;
	obj.hit = &hit_sphere_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		invalid_argc_exit(tokens, NULL, scene, 2);
	sp->center = parse_vector(tokens[1], tokens, scene);
	sp->radius = ft_atof(tokens[2], &flag, 1, 0) / 2;
	if (flag || sp->radius <= 0.0)
		invalid_arg_exit(tokens, scene, 1);
	sp->color = parse_color(tokens[3], tokens, scene);
}

void	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		*pl;
	t_object	obj;

	pl = malloc(1 * sizeof(t_plane));
	if (!pl)
		malloc_failure_obj_creation_exit(scene);
	obj.type = PLANE;
	obj.data = pl;
	obj.hit = &hit_plane_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		invalid_argc_exit(tokens, NULL, scene, 3);
	pl->point = parse_vector(tokens[1], tokens, scene);
	pl->normal = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(pl->normal))
		invalid_arg_exit(tokens, scene, 2);
	pl->color = parse_color(tokens[3], tokens, scene);
}

void	parse_cylinder(char **tokens, t_scene *scene, int flag)
{
	t_cylinder	*cy;
	t_object	obj;

	cy = malloc(1 * sizeof(t_cylinder));
	if (!cy)
		malloc_failure_obj_creation_exit(scene);
	obj.type = CYLINDER;
	obj.data = cy;
	obj.hit = &hit_cylinder_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5] || tokens[6])
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
}

void	parse_cone(char **tokens, t_scene *scene)
{
	t_cone		*co;
	t_object	obj;
	int			flag;

	flag = 0;
	co = malloc(1 * sizeof(t_cone));
	if (!co)
		malloc_failure_obj_creation_exit(scene);
	obj.type = CONE;
	obj.data = co;
	obj.hit = &hit_cone_wrapper;
	scene->objects[scene->obj_index] = obj;
	scene->obj_index++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || tokens[5])
		invalid_argc_exit(tokens, NULL, scene, 5);
	co->apex = parse_vector(tokens[1], tokens, scene);
	co->axis = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(co->axis))
		invalid_arg_exit(tokens, scene, 6);
	co->angle = ft_atof(tokens[3], &flag, 1, 0);
	if (flag || co->angle <= 0.0 || co->angle >= 180)
		invalid_arg_exit(tokens, scene, 7);
	co->color = parse_color(tokens[4], tokens, scene);
}
