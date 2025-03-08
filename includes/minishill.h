/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishill.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:10:19 by asaadeh           #+#    #+#             */
/*   Updated: 2025/02/27 15:53:08 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum s_enum
{
	TOKEN_PIPE, // |
	TOKEN_WORD, // CMD, ARG
	TOKEN_REDIRECT_IN, // <
	TOKEN_REDIRECT_OUT, // >
	TOKEN_APPEND, // >>
	TOKEN_HEREDOC, // <<
	TOKEN_EOF // END OF INPUT
}	t_enum;


typedef struct s_node
{
	char			*node;
	struct s_node	*next;
}					t_node;

typedef	struct	s_cmd_list
{
	struct s_cmd_list	*next;
	char				*value;
	t_enum	type;
}	t_cmd_list;

typedef struct s_cmd
{
	char			**args;
	char *input_file;  // <
	char *output_file; // >
	int append;        // >> = 1, > = 0
	// char			*pipe;
}					t_cmd;

typedef struct s_minishell
{
	char			*name;
	char			**token_space;
	t_node			*token_list;
	char			**token_pipe;
	char			*quoted;
	t_cmd			*cmd_l;
}					t_minishell;

typedef struct	s_parser
{
	// t_enum		type;
	t_minishell	*shell_tokens;
	t_cmd		*cmds;
}	t_parser;

int					split_pipe(t_minishell *shell, char operator);
t_node				*create_node_list(char **tokens);
int					split(t_minishell *shell);
int					closed_quotes(t_minishell *shell, char qoute);
void				split_quotes(t_minishell *shell, char operator);
int					split_space(t_minishell *shell);