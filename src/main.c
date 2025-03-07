/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:04:14 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/03/07 00:00:50 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_cmd_list(t_cmd *cmd_list)
{
    t_cmd *current = cmd_list;
    while (current)
    {
        t_token *token = current->token;
        while (token)
        {
            printf("%s ", token->value);
            token = token->next;
        }
        printf("\n");
        current = current->next;
    }
}

int main(int ac, char **av, char **envp)
{

	(void) ac;
	(void) av;

	char	*input;
	t_token	*tokens;
	t_token	*current;
	char	*expanded_value;
	t_env	*env = init_env(envp); 
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!check_two_pipes(input))
			{
				free(input);
				write(2, "tnakkkkkt", 10);
				return(1);
			}
		input = handle_pipe_end(input);
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);

		char *checked_input = check_unclosed_quotes(input);
        if (!checked_input)
        {
            free(input);
            continue; // Restart loop if unclosed quotes exist
        }
        input = checked_input;
		
		tokens = tokenizer(input);
		// int pipe_status = check_pipe_postion(tokens, &input);
		// if (check_two_pipes(tokens) || check_redirection_err(tokens) || pipe_status == 1)
		// {
		// 	free_token(tokens);
		// 	return (1);
		// }
		
		current = tokens;
		while (current)
		{
			if (current->type == WORD)
			{
				expanded_value = expand_variables(current->value, env);
				if (expanded_value)
				{
					free(current->value);
					current->value = expanded_value;
				}
			}
			current = current->next;
		}
		
		t_cmd *cmds = split_by_pipe(tokens);
		remove_pipe_node(cmds);
		print_cmd_list(cmds);
		
		free(tokens);
		free(input);
	}
	return (0);
}