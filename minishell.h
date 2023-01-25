/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:34:39 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/25 10:33:53 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <stdlib.h>

/* structs */

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
int		lexer(t_tokens *token, char *input);

/* parser.c */
int		parse(char *input);

/**********/
/* basics */
/**********/

/* main.c */
int		minishell(void);

/* mini_utils.c */
char	*user_input(void);



#endif
