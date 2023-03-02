/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:34:39 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/02 19:45:28 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include </Users/jkroger/goinfre/.brew/opt/readline/include/readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h> 
# include </Users/jkroger/goinfre/.brew/opt/readline/include/readline/history.h>

extern int	exit_status;

/***********/
/* structs */
/***********/

/* for tokens */
enum TYPE {
	PIPE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	HERE_DOC,
	APPEND,
   	WORD,
	SINGLE_QUOTE
};

typedef struct s_tokens
{
	enum TYPE type;
	char *token;
	struct s_tokens *next;
}t_tokens;

/* for cmds */
typedef struct s_cmds
{
	char			**cmd_split;
	char			*cmd_path;
	int				infile;
	int				outfile;
	char			*err_file;
	int				err;
	
	// int				cmd_amount;//?
	struct s_cmds	*next;
}t_cmds;

/* for norm */
typedef	struct s_get_var
{
	int		i;
	int		j;
	int		k;
	char	*var_value;
	char	*tmp;
}t_get_var;


/*********/
/* lexer */
/*********/

/* lex_utils.c */
int	quote_len(char *s, int *i);
int space_len(char *s, int *i);
int word_len(char *s, int *i);

/* lex_err.c */
int	lex_error_check(char *input);

/* lex_err_red.c */
int	check_redir(char *input);

/* lexer.c */
t_tokens	*lexer(t_tokens *token_lst, char *input);

/* token_innit.c */
t_tokens	*innit_token(char *input, int token_type);
t_tokens	*innit_token_word(char *input, int *i);
void		add_token(t_tokens **token_lst, t_tokens *token);
t_tokens	*innit_redir(char *input, int *i, int type);

/* expander.c */
t_tokens	*expander(t_tokens *token, char **envp);

/* env_var_utils.c */
char	*get_var(char *token, char **envp);
void	var_exist(char *token, char **envp, int *i, char **var_value);

/**********/
/* parser */
/**********/

/* parser.c */
t_cmds	*parse(char *input, char **envp);

/* parsing.c */
int	innit_cmd_struct(t_tokens **token_lst, t_cmds **cmd_lst, char **envp);
void	free_cmd(t_cmds *cmd);

/* cmd_path.c */
char	*ft_find_path(char **env, char *cmd, int *err);

/* redir_handler.c */
void	redir_handler(t_tokens *token, t_cmds *cmd, char **env);

/* heredoc_utils.c */
void	here_doc_loop(t_tokens *token, int fd, char **env);

/* cmd_innit.c */
t_cmds	*innit_cmd(char **envp, t_tokens **token_lst);
void	add_cmd(t_cmds **cmd_lst, t_cmds *cmd);

/* env_list.c */
char	**copy_env(char **envp);
char	**del_env(char **env, char *var);
char	**add_env(char **env, char *var);

/**********/
/* basics */
/**********/

/* main.c */
int		minishell(char **envp);

/* mini_utils.c */
char	*user_input(void);
int		ft_strcmp(const char *s1, const char *s2);

/* signals.c */
void	get_signals(void);

/* ft_error.c */
void	ft_error(char *token, int exit_code);
void	lex_error(char *token);
void	set_err(char *token, int err);

#endif
