/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:52:42 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/03/06 23:59:28 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type
{
	WORD, //(COMMANDS, ARGUMENTS, FILENAMES)
	PIPE, // "|"
	REDIR_IN, // "<"
	REDIR_OUT, // ">"
	HEREDOC, // "<<"
	APPEND // ">>"
}	t_token_type;

typedef struct s_token
{
	char	*value;
	t_token_type type;
	struct s_token *next;
}	t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct  s_env	*next;
}	t_env;

typedef struct s_cmd
{
	t_token	*token;
	struct s_cmd *next;
}	t_cmd;


void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char *input);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_isalnum(int c);
char    *ft_strcpy(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
t_token	*tokenizer(char *input);
t_env	*init_env(char **envp);

char	*expand_variables(char	*str, t_env *env);
t_cmd	*split_by_pipe(t_token *tokens);
void	remove_pipe_node(t_cmd	*cmd_list);
char	*check_unclosed_quotes(char *input);
int check_two_pipes(char *input);
int		check_redirection_err(t_token *tokens);
char *handle_pipe_end(char *input);

void	free_token(t_token *tokens);


#endif