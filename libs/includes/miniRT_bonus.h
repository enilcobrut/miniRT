#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "libft.h"
# include "ft_printf_fd.h"
# include "get_next_line.h"
# include "mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <time.h>
# include <math.h>
# include <float.h>
# include <pthread.h>

# define MAX_PATH 1024
# define PARSING 0
# define LEAKS 0
# define PRINT 1
# define EXEC 1
# define INTERVAL 0.3
# define INTERVAL_VEC 0.01
# define PI M_PI
# define INF DBL_MAX
# define T_MIN 0.001
#define HEIGHT 768
#define WIDTH 1024

typedef struct s_material t_material;

enum e_keyboard_key
{
	SPACE = 49,
	ESCAPE = 53,
	ENTER = 36,
	BACKSP = 51,
};

typedef enum e_id
{
	SPHERE = 1,
	PLANE,
	CYLINDER,
	PROMPT,
	SCENE,
	ALL
}			t_id;

typedef struct	s_data {
	void	**img;
	char	**add_r;
	int		bits_per_pixel[2];
	int		line_length[2];
	int		endian[2];
}				t_data;

typedef struct	s_color
{
	double 	r;
	double 	g;
	double 	b;
}				t_color;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct s_rayon
{
	t_vector	origine;
	t_vector	direction;
} 				t_rayon;

typedef struct s_hit_record
{
	t_vector	p;
	t_vector	normal;
	double		t;
	int			front_face;
	t_color		color;
	t_material	*mat_ptr;
}		t_hit_record;

typedef struct s_light_scene
{
	t_vector	pos;
	double		lum;
}	t_light_scene;


typedef struct s_material
{
	int	(*scatter)(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered);
	t_color	albedo;
	double	specular;
	t_color	albedo1;
	double	fuzz;
	double	ir;
} t_material;

typedef struct s_light
{
	t_vector			light_axis;
	double				light_brightness_ratio;
	t_color				light_color;
	int					n;
	struct s_light		*next;
	struct s_light		*prev;
}						t_light;

typedef struct s_sphere
{
	t_vector			center_axis;
	float				diameter;
	double				radius;
	float				rayon;
	struct s_sphere		*next;
	struct s_sphere		*prev;
}						t_sphere;

typedef struct s_plane
{
	t_vector			axis;
	t_vector			norm_or_vector;
	struct s_plane		*next;
	struct s_plane		*prev;
}						t_plane;

typedef struct s_cylinder
{
	t_vector			center;
	t_vector			dir_ax;
	float				diameter;
	float				height;
	int					radius;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}						t_cylinder;

typedef struct s_obj
{
	t_id type;
	int n;
	t_material			mat;
	union
	{
		t_cylinder		cy;
		t_plane			pl;
		t_sphere		sp;
	} u;
	struct s_obj *next;
	struct s_obj *prev;
} t_obj;

typedef struct s_minirt
{
	int					samples_per_pixel;
	int					depth;
	int					buf[HEIGHT + 32][WIDTH];
	t_data				img;
	t_list				*params;
	char				*k;
	float				f[3];
	char				*prompt;
	double				amb_light_ratio;
	t_color				amb_light_color;
	t_vector			cam_origin;
	t_vector			cam_vec_dir;
	int					cam_fov;
	int					cam_param_display;
	t_light				*li;
	t_obj				*obj;
	char				**argv;
	int					argc;
	void				*mlx;
	void				*win;
	char				*title;
	void				*bump_map;
	int					*bump_map_addr;
	int					bump_height;
	int					bump_width;
}	t_minirt;

void	print_spheres(t_minirt *s, int i);
void	print_planes(t_minirt *s, int i);
void	print_cylinders(t_minirt *s, int i);
void	print_params(t_minirt *s);

/* PARSING ****************************************************************** */

/* -- GET IDENTIFIERS -- */
void	get_identifiers(t_minirt *s, int a, int c, int l);
int		get_ambient_light_scene_par(t_minirt *s, t_list *p);
int		get_camera_par(t_minirt *s, t_list *p);
int		get_light_scene_par(t_minirt *s, t_list *p);
void	get_objects(t_minirt *s, t_list *p);

/* -- GET OBJECTS -- */
int		get_sphere(t_minirt *s, t_list *p);
int		get_plane(t_minirt *s, t_list *p);
int		get_cylinder(t_minirt *s, t_list *p);

/* -- GET PARAMETERS -- */
void	get_params(t_minirt *s);
void	get_params_loop(t_minirt *s, char *tmp, int fd_params);

/* -- MEMORY -- */
void	init_set(t_minirt *s);
void	free_split(char ***str);
void	ft_free(char **to_free);
void	mem_alloc_with_calloc(t_minirt *s, void ***ptr, size_t size);

/* -- PARSING -- */
void	exit_error(t_minirt *s, char *message, int opt);
void	check_void(t_minirt *s, size_t i);
void	check_directory(t_minirt *s);
void	check_extension_rt(t_minirt *s);

/* -- TOOLS AXIS -- */
void	get_axis(t_minirt *s, t_vector *p, char *str, char *tmp);
void	check_float_format(t_minirt *s, char *str);
void	get_tab_to_point(t_minirt *s, t_vector *p);
void	check_axis_format(t_minirt *s, char *axis, char *tmp);
void	check_vector_range(t_minirt *s, t_vector *p);

/* -- TOOLS RGB -- */
char	**get_next_rgb(char **rgb, int *color);
int		is_rgb(int color);
void	check_integer_format(t_minirt *s, char *str);
t_color	get_rgb_str_to_color(t_minirt *s,  char *str, char *tmp);
void	check_format_rgb(t_minirt *s, char *str);

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

/* -- TOOLS GENERAL -- */
double	ft_atof(t_minirt *s, char *str, double res, double res2);
void	init_int_tab(int *i, int a, int b, int c);
int		is_void(char *str, int end);
int		nb_arg_tab(char **tab);
int		check_float_atof(t_minirt *s, char *str, int i);

/* DEAL KEY ***************************************************************** */
int		key_release(int key, t_minirt *s);
int		button_press(int i, int y, int x, t_minirt *s);
int		key_press(int key, t_minirt *s);
void	get_prompt_bar(t_minirt *s);
void	display_param_cam(t_minirt *s);

/* DISPLAY GENERAL*********************************************************** */
void	scene_loop(t_minirt *s);
void	start_ray_tracing(t_minirt *s);
int 	get_pixels_to_img(t_minirt *s, int h, int opt);


/* GET BUFFER *************************************************************** */
void	get_buffer(t_minirt *s);

/* DISPLAY SCENE ************************************************************ */
int				rgb_to_int(unsigned char r, unsigned char g, unsigned char b);
float 		max(float t1, float t2);
float 		min(float t1, float t2);
t_vector 	hexa_to_rgb(int hexa, unsigned char *red, unsigned char *green, unsigned char *blue);
t_vector 	init_vector(float x, float y, float z);
t_rayon		init_rayon(t_vector origine, t_vector direction);
t_vector	sub_(t_vector v1, t_vector v2);
t_vector	add_(t_vector v1, t_vector v2);
t_vector	div_(t_vector v, float n);
t_vector	mul_(t_vector v, double n);
t_vector	vector_director(t_minirt *s, int *x, int *y);
void			normalize_vector(t_vector v);
t_color			ray_color(t_rayon *r, t_minirt *s, int depth);
t_vector random_in_unit_sphere();
float		intersection_sphere(t_rayon *r, t_sphere *sp, t_vector *p, t_vector *n);
void 			show_sphere(t_minirt *s, t_sphere *sp, int *x, int *y);
int				push_img_to_win(t_minirt *s, int opt);
int	hit_sphere(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max);
int	hit(const t_rayon *r, double t_max, t_hit_record *rec, t_obj *obj, t_minirt *s);
int	write_color(t_color	 pixel_color, int sample_per_pixel);
void set_face_normal(const t_rayon *r, t_hit_record *rec, t_vector outward_normal);
int scatter_lambertian(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered);
int scatter_metal(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered);
t_vector	reflect(const t_vector v, const t_vector n);

/* TOOLS ******************************************************************** */
int			red_cross(t_minirt *s);
void		put_str(t_minirt *s, int x, int y, char *str);
t_color get_rgb(int color);
double	dot(t_vector u, t_vector v);
t_vector	get_normalize_vector(t_vector v);
t_vector init_vector(float x, float y, float z);
t_rayon	init_rayon(t_vector origine, t_vector direction);
t_vector	sub_(t_vector v1, t_vector v2);
t_vector	add_(t_vector v1, t_vector v2);
t_vector	div_(t_vector v, float n);
t_vector	mul_(t_vector v, double n);
t_color get_rgb(int color);
float	get_norme_vector(t_vector v);
int	near_zero(const t_vector *vec);
t_color map_color(t_color color);

/* VECTOR TOOLS *************************************************************** */
void set_face_normal(const t_rayon *r, t_hit_record *rec, t_vector outward_normal);
t_color get_rgb(int color);
double	vec3_length(t_vector a);
t_vector	vec3_unit_vector(t_vector a);
t_vector vec_random();
t_vector vec_random_2(double min, double max);
t_vector random_in_unit_sphere();
t_vector random_in_unit_sphere_2();
double length_squared(t_vector v);
int scatter_dielectric(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered);

/* MATHS TOOLS *************************************************************** */
double degrees_to_radians(double degrees);
double random_double_2(double min, double max);
double	random_double();
double clamp(double x, double min, double max);
double	degrees_to_radians(double degree);
double ft_sqrt(double number);
t_vector vec_cross(const t_vector u, const t_vector v);

/* LINKEDLISTS *************************************************************** */

/* -- CYLINDER -- */
t_cylinder	*init_cylinder(t_cylinder *new);
t_cylinder	*lst_new_cylinder(void);
t_cylinder	*lst_add__cylinder(t_cylinder **lst, t_cylinder *new);
t_cylinder	*lst_last_cylinder(t_cylinder **lst);
int			size_cylinder(t_cylinder *lst);

/* -- OBJ -- */
t_obj		*init_obj_lst(t_obj *new);
t_obj		*lst_new_obj(int type);
t_obj		*lst_add_obj(t_obj **lst, t_obj *new);
t_obj		*lst_last_obj(t_obj **lst);
int			size_obj(t_obj *lst);

/* -- PLANE -- */
t_plane		*init_plane(t_plane *new);
t_plane		*lst_new_plane(void);
t_plane		*lst_add__plane(t_plane **lst, t_plane *new);
t_plane		*lst_last_plane(t_plane **lst);
int			size_plane(t_plane *lst);

/* -- SPHERE -- */
t_sphere	*init_sphere_lst(t_sphere *new);
t_sphere	*lst_new_sphere(void);
t_sphere	*lst_add__sphere(t_sphere **lst, t_sphere *new);
t_sphere	*lst_last_sphere(t_sphere **lst);
int			size_sphere(t_sphere *lst);

/* BONUS ******************************************************************** */

t_light		*init_light(t_light *new);
t_light		*lst_new_light(int nb);
t_light		*lst_add_light(t_light **lst, t_light *new);
t_light		*lst_last_light(t_light **lst);
int			size_light(t_light *lst);
void display_scene(t_minirt *s);
#endif