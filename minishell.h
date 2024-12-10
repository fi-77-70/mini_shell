#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <signal.h>
#include "libs/libft/libft.h"
#include "libs/ft_printf/ft_printf.h"

#define CMD			2
#define ARG			3
#define	PIPE		4
#define RED_OUT		5
#define APP_OUT		6
#define	RED_IN		7
#define	HERE_DOC	8

typedef struct s_args{
	char 			*token;
	int				type;
	struct	s_args	*next;
	struct	s_args	*prev;
}	t_args;

typedef	struct s_cmds{
	char			*cmd;
	char			**args;
	t_args			*redir;
	int				here_fds[2];
	struct	s_cmds	*next;
} t_cmds;

typedef struct s_menu
{
	int		fd_out;
	int		fd_in;
	int		is_child;
	int		*pid_arr;
	int		return_code;
	char	*til;
	char	**line;
	char	**env;
	t_args	**mshh;
	t_cmds	**cmds;
}	t_menu;

t_cmds		**ft_cmd_div(t_args *msh);
t_args		*lexer(t_args **mshh, char **line, t_menu *menu);
void		echo_shell(t_args *args);
int			is_cmd(char *str);
void		expand(t_args **args, t_menu *menu);
char		*ft_expander(char *str, int i, t_menu *menu);
char		*get_var_name(char *env_var);
char		*ft_final_expand(char *str, char *var, char *var_name, int n);
int 		ft_input_check(t_args **mshh);
void		free_all(t_menu *menu);
int			pid_get(t_menu *menu);
void		process_handler(t_menu *menu);
void	 	dup_arrr(char **map, t_menu **menu);
char		*env_get(char *name, t_menu *menu);
void		free_line(char **line);
void		free_list(t_args **mshh);
void		wait_for_process(t_menu *menu);
int			handle_pipes(t_cmds **cmds, t_menu *menu);
void		handle_builts(t_cmds *cmds, t_menu *menu);
int			ft_change_dir(t_cmds *cmds, t_menu *menu);
void		write_error_message(char *str);
int			is_white_space(char c);
int			check_dir(char *str);
int			check_acess_file(char *str, int	per, t_menu *menu);
void		built_exit(t_cmds *cmds, t_menu *menu);
void		free_mid_process(t_menu *menu);
int			ft_is_built(t_cmds *cmds);
void		ft_here_doc(t_menu *menu);
unsigned long long	ft_atoll(char *str);

int			ft_pwd(t_cmds *cmds, t_menu *menu);
int			ft_echo(t_cmds *cmds, t_menu *menu);


#endif
