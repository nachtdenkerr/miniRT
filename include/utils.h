/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:09:24 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/04 15:26:57 by jmutschl         ###   ########.fr       */
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

#endif