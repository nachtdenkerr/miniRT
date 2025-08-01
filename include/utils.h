/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:09:24 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/29 19:29:45 by jmutschl         ###   ########.fr       */
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
#endif