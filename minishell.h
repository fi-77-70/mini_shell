#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs/ft_printf/ft_printf.h"
# include "libs/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define CMD 2
# define ARG 3
# define PIPE 4
# define RED_OUT 5
# define APP_OUT 6
# define RED_IN 7
# define HERE_DOC 8

typedef struct s_args
{
	char			*token;
	int				type;
	struct s_args	*next;
	struct s_args	*prev;
}					t_args;

typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	t_args			*redir;
	int				here_fds[2];
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_menu
{
	int				fd_out;
	int				fd_in;
	int				is_child;
	int				*pid_arr;
	int				return_code;
	char			*til;
	char			**line;
	char			**env;
	t_args			**mshh;
	t_cmds			**cmds;
	t_cmds			**first_cmd;
}					t_menu;

t_cmds				**ft_cmd_div(t_args *msh);
t_args				*lexer(t_args **mshh, char **line, t_menu *menu);
void				echo_shell(t_args *args);
int					check_n_opt(t_cmds *cmds, int *new_line);
int					is_cmd(char *str);
void				expand(t_args **args, t_menu *menu);
char				*ft_expander(char *str, int i, t_menu *menu);
char				*get_var_name(char *env_var);
char				*ft_final_expand(char *str, char *var, char *var_name,
						int n);
int					ft_input_check(t_args **mshh);
void				free_all(t_menu *menu);
int					pid_get(t_menu *menu);
void				process_handler(t_menu *menu);
void				dup_arrr(char **map, t_menu **menu);
char				*env_get(char *name, t_menu *menu);
void				free_line(char **line);
void				free_list(t_args **mshh);
void				wait_for_process(t_menu *menu);
int					handle_pipes(t_cmds **cmds, t_menu *menu);
void				handle_builts(t_cmds *cmds, t_menu *menu);
void				write_error_message(char *str);
int					is_white_space(char c);
int					check_dir(char *str);
int					check_acess_file(char *str, int per, t_menu *menu);
void				built_exit(t_cmds *cmds, t_menu *menu);
void				free_mid_process(t_menu *menu);
int					ft_is_built(t_cmds *cmds);
int					ft_here_doc(t_menu *menu);
unsigned long long	ft_atoll(char *str);

int					ft_pwd(t_cmds *cmds, t_menu *menu);
int					ft_echo(t_cmds *cmds, t_menu *menu);
int					ft_cd(t_cmds *cmds, t_menu *menu);
int					ft_env(t_cmds *cmds, t_menu *menu);
int					ft_export(t_cmds *cmds,t_menu *menu);
int					ft_unset(t_cmds *cmds, t_menu *menu);
void				del_variable(t_menu *menu, const char *key);

int					handle_export_arg(char *arg, t_menu *menu);
void				print_env(t_menu *menu);
int					parse_export_input(const char *input);
void				find_key_value(char *input, char **key, char **value);
int					find_env_index(char **env,const char *key);

int					ft_strclen_custom(const char *str, char c);
int					verify_nbr_args(t_cmds *cmds, t_menu *menu);
int					change_dir(t_menu *menu, char *path);
void				update_env_var(t_menu *menu, const char *key, const char *value);
void				handle_builts(t_cmds *cmds, t_menu *menu);
char				**create_env(char **env, char *new_var);
char				*ft_strjoin3(const char *s1, char c, const char *s2);


char				*ft_expand(char *line, t_menu *menu);
char				*ft_take_out_back(char *str, char out);
char				*get_command_path(t_cmds *cmds, t_menu *menu);
void				reset_ouput(t_menu *menu);

int					handle_redirs(t_cmds *cmd, t_menu *menu);

#endif
