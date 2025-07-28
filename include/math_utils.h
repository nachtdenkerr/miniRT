/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:37:08 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/28 12:22:06 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H
# include <math.h>
# include "structs.h"

double		vec_dot(t_vector a, t_vector b);
double		vec_length(t_vector v);
t_vector	vec_add(t_vector a, t_vector b);
t_vector	vec_sub(t_vector a, t_vector b);
t_vector	vec_scale(t_vector v, double s);
t_vector	vec_cross(t_vector a, t_vector b);
t_vector	vec_normalize(t_vector v);
t_vector	vec_reflect(t_vector v, t_vector n);

#endif