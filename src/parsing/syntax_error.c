/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:40 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/03/06 23:58:48 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_token(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

	// Handle Unclosed Quotes

// char	*check_unclosed_quotes(char *input)
// {
// 	int single_quote;
// 	int double_quote;
// 	int i;
// 	char *new_input;
// 	char *temp;

// 	single_quote = 0;
// 	double_quote = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' && double_quote == 0)
// 			single_quote = !single_quote;
// 		if (input[i] == '"' && single_quote == 0)
// 			double_quote = !double_quote;
// 		i++;
// 	}
// 	while (single_quote || double_quote)
// 	{
// 		new_input = readline("> ");
// 		if (!new_input)
// 		{
// 			printf("\nminishell: unexpected EOF while looking for matching quote\n");
// 			return (NULL);
// 		}
// 		temp = input;
// 		input = ft_strjoin(input, new_input);
// 		free(temp);
// 		free(new_input);
		
// 		// Recheck for unclosed quotes0
// 		i = 0;
// 		while (input[i])
// 		{
// 			if (input[i] == '\'' && double_quote == 0 )
// 				single_quote = !single_quote;
// 			if (input[i] == '"' && single_quote == 0)
// 				double_quote = !double_quote;
// 			i++;
// 		}
// 	}
// 	return (input);
// }
int track_quotes(char *input)
{
	int track_d_quotes = 0;
	int track_s_quotes = 0;
	char type_quote;
	int i = 0;
	while (input[i])
	{
		if(input[i] == '\"' && track_s_quotes == 0)
		{
			type_quote = '\"';
			track_d_quotes++;
		}
		else if (input[i] == '\'' && track_d_quotes == 0)
		{
			type_quote = '\'';
			track_s_quotes++;
		}
		i++;	
	}
	if (track_d_quotes != 0 && track_d_quotes % 2 != 0)
		return (2);
	else if (track_s_quotes % 2 != 0 && track_s_quotes != 0)
		return (1);
	else
		return(0);
}

char	*check_unclosed_quotes(char *input)
{
	int track;
	// char type_quote;
	char *newinput;

	track = track_quotes(input);
	while(track != 0)
	{
		newinput = readline("> ");
		if (!newinput)
		{
			printf("\nminishell: unexpected EOF while looking for matching quote\n");
			return (NULL);
		}
		input = ft_strjoin(input, "\n");
		input = ft_strjoin(input, newinput);
		free(newinput);
		track = track_quotes(input);
	}
	return(input);
}

int check_redirection_err(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == HEREDOC || tokens->type == APPEND)
		{
			if (!tokens->next || tokens->next->type != WORD)
			{
				if (tokens->next)
					printf("minishell: syntax error near unexpected token `%s'\n", tokens->next->value);
				else
					printf("minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
			if (tokens->next && (tokens->next->type == REDIR_IN || tokens->next->type == REDIR_OUT 
								|| tokens->next->type == HEREDOC || tokens->next->type == APPEND))
			{
				printf("minishell: syntax error near unexpected token `%s'\n", tokens->next->value);
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int check_two_pipes(char *input)
{
	int i = 0;
	int j;
	while (input[i])
	{
		if(input[i] == '|')
		{
			j = 1;
			while(input[i+j] && (input[i + j] == 32 || input[i+j] == '\t'))
				j++;
			if(input[i + j] == '|')
				return(0);
		}
		i++;
	}
	return(1);
}
int is_end(char *input)
{
	int len;

	len = ft_strlen(input);
	len--;
	while(input[len] && (input[len] == 32 || input[len] == '\t'))
		len--;
	if(input[len] == '|')
		return(0);
	return(1);
}
char *handle_pipe_end(char *input)
{
	int check;
	char *str;

	check = is_end(input);
	while(!check)
	{
		str = readline("> ");
		if (!str)
		{
			printf("\nminishell: unexpected EOF while looking for matching quote\n");
			return (NULL);
		}
		input = ft_strjoin(input, str);
		free(str);
		check = is_end(input);
	}
	return(input);
}