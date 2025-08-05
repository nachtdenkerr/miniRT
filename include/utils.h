/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:09:24 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/05 15:38:49 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

//cleanup.c
void	cleanup_scene(t_scene *scene);
void	free_arr(char **arr);

//error_exit
void	malloc_failure_exit(void);
void	error_exit(const char *msg);

//color
t_color	color_clamp(t_color c);
t_color	color_scale(t_color c, double s);
t_color	color_mult(t_color a, t_color b);
t_color	color_add(t_color color_a, t_color color_b);
u_int32_t	combine_color(t_color a);
void print_vector(const char *name, t_vector v) ;

#endif