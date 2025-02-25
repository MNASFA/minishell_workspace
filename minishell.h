/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmnasfa <hmnasfa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:52:42 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/02/25 14:00:15 by hmnasfa          ###   ########.fr       */
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


void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char *input);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_isalnum(int c);
char    *ft_strcpy(char *s1, char *s2);
size_t	ft_strlen(const char *str);
t_token	*tokenizer(char *input);
t_env	*init_env(char **envp);

char	*expand_variables(char	*str, t_env *env);


#endif