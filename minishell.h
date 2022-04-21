#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_cmds
{
	char	*name;
	char	*file;
	int		file_fd;
	int		in;
	int		out;
	char	red;
	int		lvl;
	char	**args;
	char	*str_arg;
}		t_cmds;

typedef struct s_list
{
	char			*var;
	char			*val;
	int				exp;
	struct s_list	*next;
	struct s_list	*prev;
	int				equal_sign;
}	t_list;

typedef struct s_exp
{
	char	**spl;
	int		i;
	int		len;
	t_list	*tmp;
	char	**s;
	int		flag;
	int		flag1;
}			t_exp;

typedef struct s_qchecker
{
	char	*str;
	int		j;
	char	*tmp;
	char	*ret;
}				t_qchecker;

struct s_global
{
	t_cmds		*cmds;
	t_list		*lenv;
	t_exp		*e;
	t_qchecker	*qchecker;
	int			pipam;
	int			fork_flag;
	int			hdoc;
	int			status;
}	g_g;

/*Libft functions */
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp_quote(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split_for_export(char const *s);
char	*ft_strchr(const char *s, int c);

/*Builtin functions */
void	ft_cd(char *p);
int		ft_echo(char **args, int num);
void	ft_exit(int code);
void	ft_export(char **args);
void	ft_pwd(int num);
void	ft_unset(char **args);

/*Builtin Utils */
void	fill_env(char **env, int argc, char **argv);
void	ft_atoi_exit(char *str);
void	ft_atoi_exit_1(char *str);
void	ft_atoi_exit_2(char *str, int i, int num, int min);
int		check_builtin(char *s);
void	is_builtins(int num, char **env);
void	check_oldpwd(char *value);

/*List functions */
t_list	*ft_lstnew(char *var_inf, char *val_inf, int is_exp);
t_list	*find_element(char *var_name);
void	ft_lstadd_front(t_list **lst, t_list *neww);
void	ft_lstdel(t_list **lst, t_list *del);
void	print_list(void);
char	**list_to_arr(void);

/*Parsing */
void	main_parsing(char *s, int num);
int		parse_file(char *s, int i, int num);
void	parse_redirects(char *s, int num, int i, int j);
void	parse_args(char *s, int num, int i);

/*Signals */
void	sig_init(void);
void	sig_default(void);
void	sig_ignore(void);
void	sig_heredoc(void);
void	ft_cancel(void);
void	reprompt(int sig);
void	sigquit(int sig);
void	interrupt(int sig);
/*Redirections*/

void	heredoc_fn(int num, int *cmd_fd, int flag);
int		hdoc_fn(char *delim, int fd[2], int status, pid_t pid);
void	treat_redir(int num, int *cmd_fd, int flag);

/*Checkings */
int		check_red(char *str);
int		check_sem_and_pipe(char *str);
int		check_quotes(char *str);
char	*quote_checker(char *s, int *i, char c);
char	*without_quotes(char *str);
int		without_spaces(char *s, int i);
char	*quote_handling(char *s, int *i);
void	equal_handling(int num);
char	*quote_checker(char *s, int *i, char c);

/*Processes and Pipes */
void	plz_exec(char **env, char *ar, int num);
void	child_process(int num);
void	connect_pipes(int num);
void	fd_close(void);
char	*env_path(char **env, char *ar);

/*Utils */
char	*to_lower(char *s);
int		space_is_present(int num);
int		is_env_arg(int num);
int		is_space(char *str);
int		equal_is_present(const char *str);
char	**free_matrix(char **s);
int		count_list_elements(void);
int		rows_amount(char **spl);
void	print_error(char *s);
void	ft_error(char *str, int code);
void	print_export(void);
char	*dollar_sign(char *s, int *i);
void	update_(void);
void	update_lvl(int check);
void	update_status(void);
void	ft_putstr_fd(const char *str, int fd);
void	free_all(void);
void	free_glob(void);
void	free_env(void);
void	free_darray(char **str);
void	welcome_text(void);
void	puterror(char *str);
void	start(char *str);
char	**ft_split_for_dot(char const *s, char c);

#endif
