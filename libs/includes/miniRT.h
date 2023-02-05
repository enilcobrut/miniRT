#ifndef MINIRT_H
# define MINIRT_H

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
# define PRINT 0
# define EXEC 1
# define INTERVAL 0.1
# define INTERVAL_VEC 0.1
# define PI M_PI
# define INF DBL_MAX

#define HEIGHT 768
#define WIDTH 1024
#define NUMBER_THREAD 4
#define SAMPLE_P_PIX 5
#define DEPTH 5


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

typedef struct s_color
{
	double 	r;
	double 	g;
	double 	b;
}	t_color;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_rayon
{
	t_vector	origine;
	t_vector	direction;
} 			t_rayon;

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
	double				diameter;
	double				radius;
	double				height;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}						t_cylinder;

typedef struct s_obj
{
	t_id				type;
	int					n;
	t_material			mat;
	union
	{
		t_cylinder cy;
		t_plane pl;
		t_sphere sp;
	} u;
	struct s_obj *next;
	struct s_obj *prev;
} t_obj;


typedef struct s_buf
{
	int x;
	int y;
	int hexa;
	int n_object;
	struct s_buf *next;
	struct s_buf *prev;

} t_buf;

typedef struct s_thread
{
	pthread_t		*t;
	pthread_mutex_t count;
} t_thread;

typedef struct s_rtx
{
	t_vector horizon;
	t_vector vertical;
	t_vector lower_left_corner;
	t_vector w;
	t_vector u;
	t_vector v;
	double theta;
	double h;
	double mul_t_u;
	double mul_t_v;
	double viewport_height;
	double viewport_width;
	t_rayon		r;
	t_color	 pixel_color;
} t_rtx;

typedef struct s_minirt
{
	int					on; // bool pour thread
	int					nt; //nb thread
	pthread_t			*t;
	pthread_mutex_t		count;
	int					prompt_stat;
	t_rtx				r;
	int					samples_per_pixel;
	int					depth;
	// t_buf				*b;
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
	t_vector			light_axis;
	double				light_brightness_ratio;
	t_color				light_color;
	t_obj				*obj;
	char				**argv;
	int					argc;
	void				*mlx;
	void				*win;
	char				*title;
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

/* COLOR TOOLS ************************************************************** */

t_color		color_add_(t_color a, t_color b);
t_color		color_mul(t_color a, t_color b);
t_color		init_color(double r, double g, double b);
t_color		color_mul_scalar(t_color a, double b);
t_vector	hexa_to_rgb(int hexa, unsigned char *red, unsigned char *green, unsigned char *blue);
t_color		map_color(t_color color);
int			write_color(t_color	 pixel_color, int sample_per_pixel);

/* DEAL KEY ***************************************************************** */

void	key_backspace(t_minirt *s, char *tmp);
int		key_enter(t_minirt *s);
int		key_press(int key, t_minirt *s);
void	get_prompt(t_minirt *s, int key);

/* -- DISPLAY -- */

void	itof_to_win(t_minirt *s, double n, int x, int y);
void	itoa_to_win(t_minirt *s, int n, int x, int y);
void	display_param_cam(t_minirt *s);

/* -- TOOLS -- */

int	is_key_move(int key);
int	vec_limit(double value);
void	type_key(t_minirt *s, char *tmp, int key);

/* -- MOUSE -- */

int	button_press(int i, int y, int x, t_minirt *s);


/* DISPLAY GENERAL*********************************************************** */

int		get_pixels_to_img(t_minirt *s, int h, int opt);
int		push_img_to_win(t_minirt *s, int opt);
void	start_ray_tracing(t_minirt *s);

/* DISPLAY SCENE ************************************************************ */

void display_scene(t_minirt *s);
t_color		clamp_color(t_color color);
t_color	ray_color(t_rayon *r, t_minirt *s, int depth);
void set_face_normal(const t_rayon *r, t_hit_record *rec, t_vector outward_normal);
int scatter_lambertian(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered);
int scatter_light(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered);
t_vector	refract(const t_vector uv, const t_vector n, double etai_over_etat);
t_vector	reflect(const t_vector v, const t_vector n);
int scatter_metal(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered);
double	reflectance(double cos, double ref_i);
int scatter_dielectric(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered);
int	near_zero(const t_vector *vec);
int	get_buffer(t_minirt *s);

/* HIT ********************************************************************** */
int	hit(const t_rayon *r, double t_min, double t_max, t_hit_record *rec, t_obj *obj);

/* -- HIT CYLINDER -- */
int hit_cylinder(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max);

/* -- HIT PLANE -- */
int hit_plane(t_plane *p, const t_rayon *r, t_hit_record *rec, double t_min, double t_max);

/* -- HIT SHPERE -- */
int	hit_sphere(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max);
int	hit_sphere_2(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max);

/* TOOLS ******************************************************************** */
int			red_cross(t_minirt *s);

/* VECTOR TOOLS *************************************************************** */
double length_squared(t_vector v);
double	dot(t_vector u, t_vector v);
t_vector	get_normalize_vector(t_vector v);
float	get_norme_vector(t_vector v);
t_vector init_vector(float x, float y, float z);
t_rayon	init_rayon(t_vector origine, t_vector direction);
t_vector	sub_(t_vector v1, t_vector v2);
t_vector	add_(t_vector v1, t_vector v2);
t_vector	div_(t_vector v, float n);
t_vector	mul_(t_vector v, double n);
t_color get_rgb(int color);
double	vec3_length(t_vector a);
t_vector	vec3_unit_vector(t_vector a);
t_vector vec_random(void);
t_vector vec_random_2(double min, double max);
t_vector random_in_unit_sphere(void);
t_vector random_in_unit_sphere_2(void);

/* MATHS TOOLS *************************************************************** */
double degrees_to_radians(double degrees);
double random_double_2(double min, double max);
double	random_double(void);
double clamp(double x, double min, double max);
double	degrees_to_radians(double degree);
double ft_sqrt(double number);
t_vector vec_cross(const t_vector u, const t_vector v);

/* MULTITHREADING ************************************************************ */
void *dispatch_thread(void *arg);

/* LINKEDLISTS *************************************************************** */

/* -- CYLINDER -- */
t_cylinder	*init_cylinder(t_cylinder *new);
t_cylinder	*lst_new_cylinder(void);
t_cylinder	*lst_add__cylinder(t_cylinder **lst, t_cylinder *new);
t_cylinder	*lst_last_cylinder(t_cylinder **lst);
int			size_cylinder(t_cylinder *lst);

/* -- OBJ -- */
t_obj	*init_obj_lst(t_obj *new);
t_obj	*lst_new_obj(int type);
t_obj	*lst_add_obj(t_obj **lst, t_obj *new);
t_obj	*lst_last_obj(t_obj **lst);
int	size_obj(t_obj *lst);

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

/* -- BUF -- */
t_buf	*lst_new_buf(int x, int y, int hexa, int n_object);
t_buf	*lst_add_buf(t_buf **lst, t_buf *new);
t_buf	*lst_last_buf(t_buf **lst);
int		size_buf(t_buf *lst);

#endif