/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:38:44 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/13 15:43:33 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "utils.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

//error.c
void		file_open_error_exit(char *filename);
void		unknown_identifier_exit(char **tokens);
void		error_too_many_elements(int x);
void		missing_element_exit(int x);
void		free_and_failed_malloc(char **tokens, t_scene *scene);

//error_two.c
void		not_valid_format_exit(char **tokens, t_scene *scene, int x);
void		invalid_argc_exit(char **tokens, char **arr, t_scene *scene, int x);
void		invalid_vector_val_exit(char *str, char **tokens,
				char **arr, t_scene *scene);
void		invalid_color_val_exit(char *str, char **tokens,
				char **arr, t_scene *scene);
void		invalid_arg_exit(char **tokens, t_scene *scene, int x);

//gnl_helper.c
size_t		ft_strlen_gnl(const char *s);
void		*ft_memmove_gnl(void *dst, const void *src, size_t len);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
char		*ft_strchr_gnl(const char *s, int c);

//gnl.c
char		*get_next_line(int fd);

//init.c
void		reset_index(t_scene *scene);
void		init_element_counts(t_scene *scene);
void		init_element_arrays(t_scene *scene);

//parse_object.c
void		parse_sphere(char **tokens, t_scene *scene);
void		parse_plane(char **tokens, t_scene *scene);
void		parse_cylinder(char **tokens, t_scene *scene, int flag);
void		parse_cone(char **tokens, t_scene *scene);
void		parse_triangle(char **tokens, t_scene *scene);

//parse_elements.c
void		parse_ambient(char **tokens, t_scene *scene);
void		parse_camera(char **tokens, t_scene *scene);
void		parse_light(char **tokens, t_scene *scene);
t_color		parse_color(char *str, char **tokens, t_scene *scene);
t_vector	parse_vector(char *str, char **tokens, t_scene *scene);

//parse_scene.c
void		parse_scene(char *filename, t_scene *scene);

//parse_utils
int			is_empty_or_comment(const char *line);
int			check_if_unit_vector(t_vector vec);
void		validate_element_counts(t_scene *scene);
int			ft_atoi_color(char *str, int *flag);
double		ft_atof(char *str, int *flag, int sign, int i);

//parse_utils_two.c
int			is_not_valid_format(char *str);
void		invalid_mat_val_exit(char *str, char **tokens,
				char **arr, t_scene *scene);
t_mat		get_material(char *str, double *value, char **tokens,
				t_scene *scene);
void		init_cy(t_cylinder *cy, char **tokens, t_scene *scene, int flag);
void		init_co(t_cone *co, char **tokens, t_scene *scene, int flag);

#endif