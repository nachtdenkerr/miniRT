/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:40:42 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/04 15:31:14 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_light(char **tokens, t_scene *scene)
{
	t_light	l;
	int		flag;

	flag = 0;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		invalid_argc_exit(tokens, NULL, scene, 6);
	l.position = parse_vector(tokens[1], tokens, scene);
	l.brightness = ft_atof(tokens[2], &flag, 1, 0);
	if (flag || l.brightness < 0.0 || l.brightness > 1.0)
		invalid_arg_exit(tokens, scene, 8);
	l.color = parse_color(tokens[3], tokens, scene);
	scene->lights[scene->l_index] = l;
	scene->l_index++;
}

void	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	sp;
	int			flag;

	flag = 0;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		invalid_argc_exit(tokens, NULL, scene, 2);
	sp.center = parse_vector(tokens[1], tokens, scene);
	sp.radius = ft_atof(tokens[2], &flag, 1, 0) / 2;
	if (flag || sp.radius <= 0.0)
		invalid_arg_exit(tokens, scene, 1);
	sp.color = parse_color(tokens[3], tokens, scene);
	scene->spheres[scene->sp_index] = sp;
	scene->sp_index++;
}

void	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	pl;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		invalid_argc_exit(tokens, NULL, scene, 3);
	pl.point = parse_vector(tokens[1], tokens, scene);
	pl.normal = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(pl.normal))
		invalid_arg_exit(tokens, scene, 2);
	pl.color = parse_color(tokens[3], tokens, scene);
	scene->planes[scene->pl_index] = pl;
	scene->pl_index++;
}

void	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	cy;
	int			flag;

	flag = 0;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5] || tokens[6])
		invalid_argc_exit(tokens, NULL, scene, 4);
	cy.center = parse_vector(tokens[1], tokens, scene);
	cy.axis = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(cy.axis))
		invalid_arg_exit(tokens, scene, 3);
	cy.radius = ft_atof(tokens[3], &flag, 1, 0) / 2;
	if (flag || cy.radius <= 0.0)
		invalid_arg_exit(tokens, scene, 4);
	cy.height = ft_atof(tokens[4], &flag, 1, 0);
	if (flag || cy.height <= 0.0)
		invalid_arg_exit(tokens, scene, 5);
	cy.color = parse_color(tokens[5], tokens, scene);
	scene->cylinders[scene->cy_index] = cy;
	scene->cy_index++;
}

void	parse_cone(char **tokens, t_scene *scene)
{
	t_cone	co;
	int		flag;

	flag = 0;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || tokens[5])
		invalid_argc_exit(tokens, NULL, scene, 5);
	co.apex = parse_vector(tokens[1], tokens, scene);
	co.axis = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(co.axis))
		invalid_arg_exit(tokens, scene, 6);
	co.angle = ft_atof(tokens[3], &flag, 1, 0);
	if (flag || co.angle <= 0.0 || co.angle >= 180)
		invalid_arg_exit(tokens, scene, 7);
	co.color = parse_color(tokens[4], tokens, scene);
	scene->cones[scene->co_index] = co;
	scene->co_index++;
}
