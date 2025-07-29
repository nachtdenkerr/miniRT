/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:10:17 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/29 20:36:49 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_minirt(void)
{
	mlx_t				*mlx;
	t_minirt			*mrt;
	static mlx_image_t	*image;

	mrt = malloc(sizeof(t_minirt));
	if (!mrt)
		return (NULL);
	mlx = mlx_init(800, 600, "miniRT", true);
	if (!mlx)
		return (perror(mlx_strerror(mlx_errno)), free(mrt), NULL);
	image = mlx_new_image(mlx, 800, 600);
	if (!image)
		return (mlx_close_window(mlx), mlx_terminate(mlx),
			perror(mlx_strerror(mlx_errno)), free(mrt), NULL);
	mrt->mlx = mlx;
	mrt->img = image;
	return (mrt);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_minirt	*mrt;

	if (argc != 2)
		error_exit("Usage: ./miniRT scene.rt");
	parse_scene(argv[1], &scene);
	mrt = init_minirt();
	if (!mrt)
		return (EXIT_FAILURE);
	mrt->scene = &scene;
	// TODO: render scene here
	return (0);
}

//void print_vector(const char *name, t_vector v) {
//    printf("%s: (%.6f, %.6f, %.6f)\n", name, v.x, v.y, v.z);
//}

//void print_color(const char *name, t_color c) {
//    printf("%s: (%d, %d, %d)\n", name, c.r, c.g, c.b);
//}

//void print_ambient(const t_ambient *a) {
//    printf("Ambient:\n");
//    printf("  Brightness: %.6f\n", a->brightness);
//    print_color("  Color", a->color);
//}

//void print_camera(const t_camera *c) {
//    printf("Camera:\n");
//    print_vector("  Position", c->position);
//    print_vector("  Orientation", c->orientation);
//    printf("  FOV: %.6f\n", c->fov);
//}

//void print_light(const t_light *l, int idx) {
//    printf("Light #%d:\n", idx);
//    print_vector("  Position", l->position);
//    printf("  Brightness: %.6f\n", l->brightness);
//    print_color("  Color", l->color);
//}

//void print_sphere(const t_sphere *sp, int idx) {
//    printf("Sphere #%d:\n", idx);
//    print_vector("  Center", sp->center);
//    printf("  Radius: %.6f\n", sp->radius);
//    print_color("  Color", sp->color);
//}

//void print_plane(const t_plane *pl, int idx) {
//    printf("Plane #%d:\n", idx);
//    print_vector("  Point", pl->point);
//    print_vector("  Normal", pl->normal);
//    print_color("  Color", pl->color);
//}

//void print_cylinder(const t_cylinder *cy, int idx) {
//    printf("Cylinder #%d:\n", idx);
//    print_vector("  Center", cy->center);
//    print_vector("  Axis", cy->axis);
//    printf("  Radius: %.6f\n", cy->radius);
//    printf("  Height: %.6f\n", cy->height);
//    print_color("  Color", cy->color);
//}

//void print_cone(const t_cone *co, int idx) {
//    printf("Cone #%d:\n", idx);
//    print_vector("  Apex", co->apex);
//    print_vector("  Axis", co->axis);
//    printf("  Angle: %.6f\n", co->angle);
//    print_color("  Color", co->color);
//}

//void print_scene(const t_scene *scene)
//{
//    printf("=========== Scene Info ===========\n");

//    print_ambient(&scene->ambient);
//    printf("Ambient count: %d\n", scene->ambiant_count);

//    print_camera(&scene->camera);
//    printf("Camera count: %d\n", scene->camera_count);

//    printf("Lights (%d):\n", scene->light_count);
//    for (int i = 0; i < scene->light_count; i++)
//        print_light(&scene->lights[i], i);

//    printf("Spheres (%d):\n", scene->sphere_count);
//    for (int i = 0; i < scene->sphere_count; i++)
//        print_sphere(&scene->spheres[i], i);

//    printf("Planes (%d):\n", scene->plane_count);
//    for (int i = 0; i < scene->plane_count; i++)
//        print_plane(&scene->planes[i], i);

//    printf("Cylinders (%d):\n", scene->cylinder_count);
//    for (int i = 0; i < scene->cylinder_count; i++)
//        print_cylinder(&scene->cylinders[i], i);

//    printf("Cones (%d):\n", scene->cone_count);
//    for (int i = 0; i < scene->cone_count; i++)
//        print_cone(&scene->cones[i], i);

//    printf("===================================\n");
//}


//int		main(int argc, char **argv)
//{
//	t_scene scene;

//	(void)argc;
//	parse_scene(argv[1], &scene);
//	print_scene(&scene);
//	cleanup_scene(&scene);
//}