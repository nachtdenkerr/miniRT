#include <stdio.h>
#include <stdbool.h>
#include "structs.h"

// Forward declarations for object printing
void print_sphere(void *data);
void print_plane(void *data);
void print_cylinder(void *data);

void print_color(t_color color)
{
    printf("Color: (r=%d, g=%d, b=%d)\n", color.r, color.g, color.b);
}

void print_vector(const char *label, t_vector v)
{
    printf("%s: (x=%.2f, y=%.2f, z=%.2f)\n", label, v.x, v.y, v.z);
}

// Print one ambient
void print_ambient(t_ambient a)
{
    printf("Ambient:\n  Brightness: %.2f\n  ", a.brightness);
    print_color(a.color);
}

// Print one camera
void print_camera(t_camera c)
{
    printf("Camera:\n");
    print_vector("  Position", c.position);
    print_vector("  Orientation", c.orientation);
    printf("  FOV: %.2f\n", c.fov);
}

// Print one light
void print_light(t_light l)
{
    printf("Light:\n");
    print_vector("  Position", l.position);
    printf("  Brightness: %.2f\n", l.brightness);
    print_color(l.color);
}

void print_cone(void *data)
{
    t_cone *c = (t_cone *)data;
    if (!c) return;
    print_vector("    Apex", c->apex);
    print_vector("    Axis", c->axis);
    printf("    Angle: %.2f\n", c->angle);
    print_color(c->color);
    switch (c->type)
    {
        case REFLECTIVE:
            printf("MIRROR: %.2f\n", c->mat_value);
            break;
        case CHECKER:
            printf("CHESS: %.2f\n", c->mat_value);
            break;
        default:
            break;
    }
}


void print_object(t_object *obj)
{
    if (!obj) return;
    printf("Object: ");
    switch (obj->type) {
        case SPHERE:
            printf("Sphere\n");
            print_sphere(obj->data);
            break;
        case PLANE:
            printf("Plane\n");
            print_plane(obj->data);
            break;
        case CYLINDER:
            printf("Cylinder\n");
            print_cylinder(obj->data);
            break;
        case CONE:
            printf("Cone\n");
            print_cone(obj->data);
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

void print_sphere(void *data)
{
    t_sphere *s = (t_sphere *)data;
    if (!s) return;
    print_vector("    Center", s->center);
    printf("    Radius: %.2f\n", s->radius);
    print_color(s->color);
    switch (s->type)
    {
        case REFLECTIVE:
            printf("MIRROR: %.2f\n", s->mat_value);
            break;
        case CHECKER:
            printf("CHESS: %.2f\n", s->mat_value);
            break;
        default:
            break;
    }
}

void print_plane(void *data)
{
    t_plane *p = (t_plane *)data;
    if (!p) return;
    print_vector("    Point", p->point);
    print_vector("    Normal", p->normal);
    print_color(p->color);
    switch (p->type)
    {
        case REFLECTIVE:
            printf("MIRROR: %.2f\n", p->mat_value);
            break;
        case CHECKER:
            printf("CHESS: %.2f\n", p->mat_value);
            break;
        default:
            break;
    }
}

void print_cylinder(void *data)
{
    t_cylinder *c = (t_cylinder *)data;
    if (!c) return;
    print_vector("    Center", c->center);
    print_vector("    Axis", c->axis);
    printf("    Radius: %.2f, Height: %.2f\n", c->radius, c->height);
    print_color(c->color);
    switch (c->type)
    {
        case REFLECTIVE:
            printf("MIRROR: %.2f\n", c->mat_value);
            break;
        case CHECKER:
            printf("CHESS: %.2f\n", c->mat_value);
            break;
        default:
            break;
    }
}

void print_scene(t_scene *scene)
{
    if (!scene) return;

    printf("=== Scene ===\n");

    // Ambient
    print_ambient(scene->ambient);

    // Camera
    print_camera(scene->camera);

    // Lights
    printf("\nLights (%d):\n", scene->light_count);
    for (int i = 0; i < scene->light_count; ++i)
        print_light(scene->lights[i]);

    // Objects
    printf("\nObjects (%d):\n", scene->obj_capacity);
    for (int i = 0; i < scene->obj_capacity; ++i)
	{
        print_object(&scene->objects[i]);
	}
	if (1)
		printf("done\n");
}
