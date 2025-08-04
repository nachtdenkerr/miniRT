/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:40:44 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/30 12:45:45 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	count_elements(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens)
		malloc_failure_exit();
	if (!ft_strcmp(tokens[0], "A"))
		scene->ambiant_count++;
	else if (!ft_strcmp(tokens[0], "C"))
		scene->camera_count++;
	else if (!ft_strcmp(tokens[0], "L"))
		scene->light_count++;
	else if (!ft_strcmp(tokens[0], "sp"))
		scene->sphere_count++;
	else if (!ft_strcmp(tokens[0], "pl"))
		scene->plane_count++;
	else if (!ft_strcmp(tokens[0], "cy"))
		scene->cylinder_count++;
	else if (!ft_strcmp(tokens[0], "co"))
		scene->cone_count++;
	else
		unknown_identifier_exit(tokens);
	free_arr(tokens);
}

void	get_element_counts(t_scene *scene, char *filename)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		file_open_error_exit(filename);
	tmp = get_next_line(fd);
	if (!tmp)
		return ((void)close(fd));
	line = ft_strtrim(tmp, "\n");
	free(tmp);
	while (line != NULL)
	{
		if (is_empty_or_comment(line))
			free(line);
		else
			count_elements(line, scene);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		line = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	close(fd);
}

void	parse_element(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		free(line);
		malloc_failure_exit();
	}
	free(line);
	if (!ft_strcmp(tokens[0], "A"))
		parse_ambient(tokens, scene);
	else if (!ft_strcmp(tokens[0], "C"))
		parse_camera(tokens, scene);
	else if (!ft_strcmp(tokens[0], "L"))
		parse_light(tokens, scene);
	else if (!ft_strcmp(tokens[0], "sp"))
		parse_sphere(tokens, scene);
	else if (!ft_strcmp(tokens[0], "pl"))
		parse_plane(tokens, scene);
	else if (!ft_strcmp(tokens[0], "cy"))
		parse_cylinder(tokens, scene);
	else if (!ft_strcmp(tokens[0], "co"))
		parse_cone(tokens, scene);
	free_arr(tokens);
}

void	parse_elements(t_scene *scene, char *filename)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		file_open_error_exit(filename);
	tmp = get_next_line(fd);
	if (!tmp)
		return ((void)close(fd));
	line = ft_strtrim(tmp, "\n");
	free(tmp);
	while (line != NULL)
	{
		if (is_empty_or_comment(line))
			free(line);
		else
			parse_element(line, scene);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		line = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	close(fd);
}

void	parse_scene(char *filename, t_scene *scene)
{
	init_element_counts(scene);
	get_element_counts(scene, filename);
	validate_element_counts(scene);
	init_element_arrays(scene);
	parse_elements(scene, filename);
	reset_index(scene);
}
