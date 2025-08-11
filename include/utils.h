/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:09:24 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/11 10:31:47 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

//cleanup.c
void		cleanup_scene(t_scene *scene);
void		free_arr(char **arr);

//error_exit
void		malloc_failure_exit(void);
void	malloc_failure_obj_creation_exit(t_scene *scene, char **tokens);
void		error_exit(const char *msg);

//color
t_color		create_color(int r, int g, int b);
t_color		color_clamp(t_color c);
t_color		color_scale(t_color c, double s);
t_color		color_mult(t_color a, t_color b);
t_color		color_add(t_color color_a, t_color color_b);
u_int32_t	combine_color(t_color a);
void		print_vector(const char *name, t_vector v);

#endif