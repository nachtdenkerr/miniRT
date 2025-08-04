/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:40:47 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/04 15:31:14 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_empty_or_comment(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (1);
	if (line[i] == '#')
		return (1);
	return (0);
}

int	check_if_unit_vector(t_vector vec)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (fabs(len - 1) > EPSILON)
		return (1);
	return (0);
}

void	validate_element_counts(t_scene *scene)
{
	if (scene->ambiant_count == 0)
		missing_element_exit(1);
	else if (scene->ambiant_count > 1)
		error_too_many_elements(1);
	if (scene->camera_count == 0)
		missing_element_exit(2);
	else if (scene->camera_count > 1)
		error_too_many_elements(2);
	if (scene->light_count == 0)
		missing_element_exit(3);
	if (scene->sphere_count == 0 && scene->plane_count
		&& scene->cylinder_count == 0 && scene->cone_count == 0)
		missing_element_exit(4);
}

int	ft_atoi_color(char *str, int *flag)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		*flag = 1;
		return (0);
	}
	while (str[i] >= '0' && str[i] <= '9' && result < 256)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || result > 255)
		*flag = 1;
	return (result);
}

double	ft_atof(char *str, int *flag, int sign, int i)
{
	double	result;
	double	frac;

	result = 0;
	frac = 0.1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
		sign = -1;
	else if (str[i] != '+')
		i--;
	i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	if (str[i] == '.')
	{
		while (str[++i] >= '0' && str[i] <= '9')
		{
			result += (str[i] - '0') * frac;
			frac *= 0.1;
		}
	}
	if (str[i] != '\0')
		*flag = 1;
	return (result * sign);
}
