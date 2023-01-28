/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:34:39 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/28 18:27:50 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <stdlib.h>

/***********/
/* structs */
/***********/

/* for tokens */
enum TYPE {
	PIPE,
	REDIR_INPUT,
	HERE_DOC,
	REDIR_OUTPUT,
	APPEND,
   	WORD
};

typedef struct s_tokens
{
	enum TYPE type;
	char *token;	
	struct s_tokens *next;
}t_tokens;

/***********/
/* parsing */
/***********/

/* lex_utils.c */
int	quote_len(char *s, int *i);

/* lexer_pre_check.c */
int	lex_error_check(char *input);

/* lexer.c */
t_tokens	*lexer(t_tokens *token_lst, char *input);
t_tokens	*innit_token(char *input, int token_type);
t_tokens	*innit_token_word(char *input, int *i);
void		add_token(t_tokens **token_lst, t_tokens *token);

/* expander.c */
t_tokens	*expander(t_tokens *token, char **envp);

/* env_var_utils.c */
char	*get_var(char *token, char **envp);

/* parser.c */
int	parse(char *input, char **envp);

/**********/
/* basics */
/**********/

/* main.c */
int		minishell(char **envp);

/* mini_utils.c */
char	*user_input(void);


#endif
