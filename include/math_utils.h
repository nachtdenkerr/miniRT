/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:37:08 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/08 11:51:58 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "structs.h"

t_point		point_at(t_ray *ray, double t);

double		vec_dot(t_vector a, t_vector b);
double		vec_length(t_vector v);

t_vector	vec_init(t_point start, t_point end);
t_vector	vec_add(t_vector a, t_vector b);
t_vector	vec_sub(t_vector a, t_vector b);
t_vector	vec_scale(t_vector v, double s);
t_vector	vec_cross(t_vector a, t_vector b);
t_vector	vec_normalize(t_vector v);
t_vector	vec_reflect(t_vector v, t_vector n);

double		deg_to_rad(double angle);
t_vector	create_point(double x, double y, double z);


#endif