/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:32:26 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/16 19:20:27 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# ifndef NUM_THREADS
#  define NUM_THREADS 1
# endif

# define LEAKS 1
# define INTERVAL 0.5
# define INTERVAL_VEC 0.1
# define FUZZ 0.5
# define IR 1.5
# define PI M_PI
# define INF DBL_MAX
# define T_MIN 0.001
# define HEIGHT 768
# define WIDTH 1024
# define SAMPLE_P_PIX 1
# define DEPTH 1

typedef struct s_material	t_material;
typedef struct s_obj		t_obj;

enum e_keyboard_key
{
	SPACE = 49,
	ESCAPE = 53,
	ENTER = 36,
	BACKSP = 51,
	F1 = 122,
	F2 = 120,
	A = 0,
	W = 13,
	D = 2,
	S = 1,
	LEFT = 123,
	UP = 126,
	RIGHT = 124,
	DOWN = 125,
	EIGHT = 91,
	FOUR = 86,
	TWO = 84,
	SIX = 88,
	ONE = 83,
	THREE = 85,
	FIVE = 87,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
	RIGHT_MOUSE = 2,
	LEFT_MOUSE = 1,
};

typedef enum e_id
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	PROMPT,
	SCENE,
	ALL
}	t_id;

typedef struct s_data
{
	void				**img;
	char				**add_r;
	int					bits_ppix[2];
	int					line_length[2];
	int					endian[2];
}						t_data;

typedef struct s_quadratic_equation
{
	double				a;
	double				half_b;
	double				c;
	double				delta;
	double				k;
}						t_quadra;

typedef struct s_color
{
	double				r;
	double				g;
	double				b;
}						t_color;

typedef struct s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct s_disk
{
	t_vector			center;
	t_vector			normal;
	double				radius;
}						t_disk;

typedef struct s_rayon
{
	t_vector			origine;
	t_vector			direction;
}						t_rayon;

typedef struct s_hit_record
{
	t_obj				*hit_obj;
	t_vector			p;
	t_vector			normal;
	double				t;
	int					front_face;
	t_material			*mat_ptr;
}						t_hit;

typedef struct s_material
{
	int					(*scatter)(const t_rayon *r, const t_hit *rec,
			t_color *attenuation, t_rayon *scattered);
	t_color				albedo;
	double				specular;
	t_color				albedo1;
	double				fuzz;
	double				ir;
}						t_material;

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
	t_vector			dir_ax;
	struct s_plane		*next;
	struct s_plane		*prev;
}						t_plane;

typedef struct s_cylinder
{
	t_vector			center;
	t_vector			dir_ax;
	double				diameter;
	double				height;
	double				radius;
	double				ratio;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}						t_cylinder;

typedef struct s_cone
{
	t_vector			center;
	t_vector			dir_ax;
	double				diameter;
	double				height;
	double				radius;
	double				sin_angle;
	double				cos_angle;
	double				tan_angle;
	double				ratio;
	struct s_cone		*next;
	struct s_cone		*prev;
}						t_cone;

typedef struct s_obj
{
	t_id				type;
	int					n;
	t_material			mat;
	char				*xpm;
	int					bump_height;
	int					bump_width;
	void				*bump_map;
	int					*bump_map_addr;
	unsigned char		*checker_texture;
	double				checker_size;
	union
	{
		t_cylinder		cy;
		t_plane			pl;
		t_sphere		sp;
		t_cone			co;
	}					u_;
	struct s_obj		*next;
	struct s_obj		*prev;
}						t_obj;

typedef struct s_rtx
{
	t_vector			horizon;
	t_vector			vertical;
	t_vector			start;
	t_vector			w;
	t_vector			u;
	t_vector			v;
	double				theta;
	double				h;
	double				t_u;
	double				t_v;
	double				viewport_height;
	double				viewport_width;
	t_rayon				r;
	t_color				pixel_color;
}						t_rtx;

typedef struct s_minirt
{
	char				**argv;
	int					argc;
	double				amb_light_ratio;
	t_color				amb_light_color;
	t_vector			cam_origin;
	t_vector			cam_vec_dir;
	int					cam_fov;
	int					cam_param_display;
	void				*hit_obj_xpm;
	void				*hit_obj_xpm_addr;
	t_obj				*hit_obj;
	int					prompt_stat;
	pthread_mutex_t		mutex;
	int					y;
	t_rtx				r;
	int					s_pixel;
	int					depth;
	t_data				img;
	t_list				*params;
	char				*k;
	float				f[3];
	char				*prompt;
	t_light				*li;
	t_obj				*obj;
	void				*mlx;
	void				*win;
	char				*title;
	double				speculaire;
	double				ambiante;
	double				light_dist;
}						t_minirt;

typedef struct s_th
{
	pthread_t			thread;
	t_minirt			*s;
}						t_th;

int			red_cross(t_minirt *s);
void		print_cone(t_cone *co, int nb);
void		print_obj(t_obj *obj);
void		print_params(t_minirt *s);

/* PRINT ******************************************************************** */
int			print_color(t_color color);
void		print_sphere(t_sphere *sp, int nb);
void		print_plane(t_plane *pl, int nb);
void		print_cylinder(t_cylinder *cy, int nb);
void		print_lights(t_light *li);

/* PARSING ****************************************************************** */
/* -- GET IDENTIFIERS -- */
void		get_identifiers(t_minirt *s, int a, int c, int l);
int			get_ambient_light_scene_par(t_minirt *s, t_list *p);
int			get_camera_par(t_minirt *s, t_list *p);
int			get_light_scene_par(t_minirt *s, t_list *p);
void		get_objects(t_minirt *s, t_list *p);

/* -- GET OBJECTS -- */
int			get_sphere(t_minirt *s, t_list *p);
int			get_plane(t_minirt *s, t_list *p);
int			get_cylinder(t_minirt *s, t_list *p, t_cylinder *cy,
				t_obj *new_obj);
void		get_cone(t_minirt *s, t_list *p, t_obj *new_obj, t_cone *co);
void		check_xpm(t_minirt *s, t_obj *obj);

/* -- GET PARAMETERS -- */
void		get_params(t_minirt *s);
void		get_params_loop(t_minirt *s, char *tmp, int fd_params);

/* -- MEMORY -- */
void		init_set(t_minirt *s);
void		ft_free(char **to_free);

/* -- PARSING -- */
void		exit_error(t_minirt *s, char *message, int opt);
void		check_void(t_minirt *s, size_t i);
void		check_directory(t_minirt *s);
void		check_extension_rt(t_minirt *s);

/* -- TOOLS AXIS -- */
void		get_axis(t_minirt *s, t_vector *p, char *str, char *tmp);
void		check_float_format(t_minirt *s, char *str);
void		get_tab_to_point(t_minirt *s, t_vector *p);
void		check_axis_format(t_minirt *s, char *axis, char *tmp);
void		check_vector_range(t_minirt *s, t_vector *p);

/* -- TOOLS RGB -- */
char		**get_next_rgb(char **rgb, int *color);
int			is_rgb(int color);
void		check_integer_format(t_minirt *s, char *str);
t_color		get_rgb_str_to_color(t_minirt *s, char *str, char *tmp);
void		check_format_rgb(t_minirt *s, char *str);

int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

/* -- TOOLS GENERAL -- */
double		ft_atof(t_minirt *s, char *str, double res, double res2);
void		init_int_tab(int *i, int a, int b, int c);
int			is_void(char *str, int end);
int			nb_arg_tab(char **tab);
int			check_float_atof(t_minirt *s, char *str, int i);

/* DEAL KEY ***************************************************************** */
void		function_keys(int key, t_minirt *s);
void		move_cam_or_obj(t_minirt *s, int key);
int			key_press(int key, t_minirt *s);

/* CAM MOV */
void		move_cam_or(t_minirt *s, int key);
void		move_cam_vec(t_minirt *s, int key);

/* DISPLAY */
void		itof_to_win(t_minirt *s, double n, int x, int y);
void		itoa_to_win(t_minirt *s, int n, int x, int y);
void		display_param_cam(t_minirt *s);

/* OBJ MOV */
void		move_cy_or(t_minirt *s, int key);
void		move_cy_vec(t_minirt *s, int key);
void		move_co_or(t_minirt *s, int key);
void		move_co_vec(t_minirt *s, int key);
void		move_sp_or(t_minirt *s, int key);
void		move_pl_or(t_minirt *s, int key);
void		move_pl_vec(t_minirt *s, int key);

/* PROMPT */
void		type_key(t_minirt *s, char *tmp, int key);
void		key_backspace(t_minirt *s, char *tmp);
void		display_prompt_status(t_minirt *s);
int			key_enter(t_minirt *s);
void		get_prompt(t_minirt *s, int key);

/* PRINT */
void		print_list_id(void);
char		*ft_itof_print_next(int len, long tmp, char *str);
char		*ft_itof_print(double n, char *str, char *integer, char *tmp_);
void		print_rgb(t_color color, int fd);
void		print_axis(t_vector vec, int fd);

/* MOUSE */
void		clic_button(t_minirt *s, int i, int x, int y);
void		scroll_on_cylinder(t_minirt *s, int i);
void		scroll_on_sphere(t_minirt *s, int i);
void		scroll_on_cone(t_minirt *s, int i);
int			button_press(int i, int x, int y, t_minirt *s);

void		display_hit_obj_params(t_minirt *s);
void		hit_something(t_minirt *s, int x, int y);

/* TOOLS */
int			is_key_move(int key);
int			vec_limit(double value);
void		key_up_vec(double *value);
void		key_down_vec(double *value);

/* FILES BACKUP */
void		write_lights(t_minirt *s, int fd);
void		write_sp_cy(t_obj *obj, int fd);
void		write_co(t_obj *obj, int fd);
void		write_pl(t_obj *obj, int fd);
void		write_params(t_minirt *s, int fd);
void		export_file_save(t_minirt *s, int opt);
void		print_atof(double n, int fd);

/* DISPLAY GENERAL*********************************************************** */
int			push_img_to_win(t_minirt *s, int opt);
void		init_rtx(t_minirt *s);
void		start_ray_tracing(t_minirt *s);

/* DISPLAY SCENE ************************************************************ */
void		display_scene(t_minirt *s);
void		set_face_normal(const t_rayon *r, t_hit *rec,
				t_vector outward_normal);
void		get_prompt_color(t_minirt *s);
void		get_pixels_to_img(t_minirt *s);

/* MAT */
int			super_mod(int div, int mod);
t_vector	reflect(const t_vector v, const t_vector n);
int			near_zero(const t_vector *vec);
int			scat_check(const t_rayon *r, const t_hit *rec, t_color *a,
				t_rayon *s);
int			scat_lamb(const t_rayon *r, const t_hit *rec, t_color *a,
				t_rayon *s);

/* RAYCOLOR */
void		get_light_data(t_minirt *s, t_rayon *r, t_hit *rec,
				t_light *light1);
t_color		compute_lighting(t_rayon *r, t_hit *rec, t_minirt *s);
t_color		ray_color(t_rayon *r, t_minirt *s);

/* HIT ********************************************************************** */
void		apply_bump_map(t_hit *rec);
int			hit(const t_rayon *r, double t_max, t_hit *rec, t_obj *obj);

/* -- HIT CYLINDER -- */
int			hit_cylinder(t_cylinder *cyl, const t_rayon *r, t_hit *rec,
				double t_max);
int			hit_disk(t_disk *disk, const t_rayon *r, double t_max, t_hit *rec);
int			hit_cylinder2(t_cylinder *cyl, const t_rayon *r, t_hit *rec,
				double root);
int			hit_cyl_body(t_cylinder *cyl, const t_rayon *r, t_hit *rec,
				double t_max);

/* -- HIT PLANE -- */
int			hit_plane(t_plane *p, const t_rayon *r, t_hit *rec, double t_max);

/* -- HIT SPHERE -- */
int			hit_sphere(t_sphere *sp, const t_rayon *r, t_hit *rec,
				double t_max);

/* -- HIT CONE -- */
int			check_soluce(t_quadra *qe, double t_max, const t_rayon *r,
				t_hit *rec);
int			hit_cone_body(t_cone *cone, const t_rayon *r, t_hit *rec,
				double t_max);
int			hit_cone(t_cone *cone, const t_rayon *r, t_hit *rec, double t_max);

/* COLOR TOOLS ************************************************************** */
t_color		clamp_color(t_color color);
t_color		color_mul(t_color a, t_color b);
t_color		color_add_(t_color a, t_color b);
int			write_color(t_color pixel_color, int sample_per_pixel);
t_color		init_color(double r, double g, double b);
t_color		color_mul_scalar(t_color a, double b);
int			get_hexa_color(t_color color);
t_color		map_color(t_color color);
int			print_color(t_color color);

/* RAYON ***************************************************************** */
t_rayon		init_rayon(t_vector origine, t_vector direction);

/* VECTOR OPERATION ******************************************************** */
t_vector	sub_(t_vector v1, t_vector v2);
t_vector	add_(t_vector v1, t_vector v2);
t_vector	div_(t_vector v, float n);
t_vector	mul_(t_vector v, double n);
t_vector	vec_cross(const t_vector u, const t_vector v);

/* VECTOR RANDOM ************************************************************ */
t_vector	vec_random(void);
t_vector	vec_random_2(double min, double max);
t_vector	random_in_unit_sphere(void);
t_vector	random_in_unit_sphere_2(void);

/* VECTOR TOOLS ************************************************************* */
t_vector	get_normalize_vector(t_vector v);
float		get_norme_vector(t_vector v);
t_vector	init_vector(float x, float y, float z);
t_vector	norm_(t_vector a);
double		vec3_length(t_vector a);

/* MATHS RANDOM ************************************************************* */
double		random_double_2(double min, double max);
double		random_double(void);

/* MATHS TOOLS ************************************************************** */
double		degrees_to_radians(double degrees);
double		clamp(double x, double min, double max);
double		ft_sqrt(double number);
double		length_squared(t_vector v);
double		dot(t_vector u, t_vector v);

/* MULTITHREADING *********************************************************** */
void		get_multi_threading(t_minirt *s);
void		*get_y(void *arg);
void		get_pixel_line(t_minirt *s, int y, t_th *t);

/* LINKEDLISTS ************************************************************** */
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

/* -- LIGHT -- */
t_light		*init_light(t_light *new);
t_light		*lst_new_light(int nb);
t_light		*lst_add_light(t_light **lst, t_light *new);
t_light		*lst_last_light(t_light **lst);
int			size_light(t_light *lst);

/* -- CONE -- */
t_cone		*lst_new_cone(void);
t_cone		*lst_add_cone(t_cone **lst, t_cone *new);
t_cone		*lst_last_cone(t_cone **lst);
int			size_cone(t_cone *lst);

#endif