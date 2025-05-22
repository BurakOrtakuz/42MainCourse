/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:35:45 by bortakuz          #+#    #+#             */
/*   Updated: 2023/11/27 15:39:05 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# define IN_FILE 1
# define OUT_FILE 2

# define DEFAULT "\033[0m"
# define YELLOW "\033[0;33m"

# define BT_ECHO "echo"
# define BT_CD "cd"
# define BT_PWD "pwd"
# define BT_EXIT "exit"
# define BT_EXPORT "export"
# define BT_UNSET "unset"
# define BT_ENV "env"

# define WORD 1
# define PIPE 2
# define RED_APPEND 3
# define RED_CREATE 4
# define RED_INPUT 5
# define HEREDOC 6

typedef struct s_data
{
	int		return_code;
	int		sig_flag;
	int		exit_flag;
	int		pipe_count;
	int		*opened_pipes;
	char	**env;
}	t_data;

typedef struct s_redir
{
	char	*path;
	int		type;
	int		appendmode;
}	t_redir;

typedef struct s_command
{
	char	*command;
	char	**heredoc_delim;
	char	**arguments;
	t_redir	**redirections;
	int		out;
	int		in;
}	t_command;

typedef struct s_token
{
	char	*data;
	int		type;
}	t_token;

extern t_data	*g_data;

char		*ft_take_env(char *token);
int			ft_matrix_len(void **arr);
char		**ft_dup_matrix(char **arr);
int			ft_is_delimitter(char chr);
int			ft_is_quote(char chr);
int			ft_env_line_len(char *s);
void		ft_add_arr(void ***arr, void *new);
void		ft_add_arr_token(t_token ***arr, t_token *new);
void		ft_add_arr_command(t_command ***arr, t_command *new);
void		ft_add_arr_str(char ***arr, char *new);
void		ft_add_arr_redir(t_redir ***arr, t_redir *new);
void		ft_add_arr_pipeline(t_command ***arr, t_command *new);
void		ft_add_arr_int(int **arr, int len, int new);
void		ft_signal(void);
void		ft_signal_handler(int sig);
char		*ft_prompt(void);
char		*ft_create_prompt(void);
void		ft_execute(char *input);
t_token		**ft_lexer(char *str);
t_token		*ft_create_token(char *data, int type);
t_token		*ft_redir_token(char *str, int *i);
void		ft_execute(char *input);
t_command	**ft_parse_pipes(t_token **tokens, int start, int end);
t_command	**ft_get_commands(t_token **tokens, int start, int end);
int			ft_redir_word_token(t_command *cmd, t_token **tokens, int i);
int			ft_redir_heredoc(t_command *cmd, t_token **tokens, int *i);
int			ft_redir_input(t_command *cmd, t_token **tokens, int *i);
int			ft_redir_output(t_command *cmd, t_token **tokens, int *i);
void		ft_redir_error(t_token *token);
void		ft_free_arr(void **arr, void (*f)(void *));
void		ft_free_arr_str(char **arr);
void		ft_free_command(t_command *cmd);
void		*ft_return_command_free(t_command *cmd);
void		ft_free_arr_command(t_command **commands);
void		ft_free_redir(t_redir *redir);
void		ft_free_arr_pipeline(t_command **pipes);
void		ft_free_pipeline(t_command **pipe);
void		ft_free_token(t_token *token);
void		ft_free_arr_token(t_token **tokens);
void		clean_null_arguments(t_command *cmd);
void		*ft_error_command_arr(t_command **commands, t_token *token);
void		*ft_error_command(t_command *cmd);
void		*ft_error_pipeline(t_command **pipes, t_token *token);
void		ft_put_errno_msg(char *msg);
void		ft_put_error(void);
void		ft_put_err_line(char *msg, char *data);
int			ft_get_heredoc(t_command **pipes);
int			ft_heredoc(t_command *cmd);
void		ft_run_sep_pipes(t_command **pipes);
void		ft_execute_commands(t_command **cmds);
int			ft_run_command(t_command *cmd);
void		ft_parse_quote(t_command *cmd);
char		*ft_parse_quote_first(char *token);
void		ft_quote_len(char *token, int *end, char quote);
void		ft_free_str_join(char **str, char *append);
void		get_len_of_word(char *s, int *end);
void		ft_connect_pipes(t_command **cmd);
void		ft_close_pipes(void);
char		*change_env_with_back(char *s);
void		replace_with(char **str, char *a, char *b);
char		*get_env(char *arr);
int			ft_env_index(char *name);

int			ft_is_letter_underscore(char c);
int			ft_is_alnum_underscore(char c);
int			ft_builtin_check(char *command);
int			ft_is_num_str(char *str);
int			ft_path_check(char *file);
int			ft_execute_builtin(t_command *cmd);
int			ft_env(t_command *cmd);
int			ft_pwd(t_command *cmd);
int			ft_exit(t_command *cmd);
int			ft_echo(t_command *cmd);
int			ft_export(t_command *cmd);
char		*ft_get_env(char *s);
char		*ft_get_env_front(char *s);
int			ft_env_check(char *s);
int			ft_cd(t_command *cmd);
int			ft_unset(t_command *cmd);
void		ft_export_sort(t_command *cmd);
void		ft_settle_env(char *name, char *back);
int			ft_open_redirs(t_command *cmd);
int			ft_execute_redir(t_command *cmd);
char		*find_in_path(char *file);
int			is_reg_file(char *path);
int			is_file_exist(char *path);
int			ft_start_process(t_command *cmd, char *cmdpath);
void		ft_free_matrix(void **arr);
void		ft_parser(t_token **token);
void		ft_env_del(char *del);
t_token		*ft_get_next_token(char *str);
void		update_env_path(void);
int			ft_check_interpret(t_token **tokens);
int			ft_check_quotes(char *input);
void		check_errors(t_command *cmd, char *path);
void		ft_redir_error(t_token *token);
void		*ft_error_command_arr(t_command **commands, t_token *token);
void		*ft_error_command(t_command *cmd);
char		*ft_expander(char *token);
void		ft_file_error(t_command *cmd, char *path);

#endif
