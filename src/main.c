/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmnasfa <hmnasfa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:04:14 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/02/25 14:23:39 by hmnasfa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (!input)
		{
			printf("exit\n");
			break;
		}
		
		if (*input)
			add_history(input);
		
		tokens = tokenizer(input);
		
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
		
		current = tokens;
		while (current)
		{
			printf("%s :: type => %d\n", current->value, current->type);
			current = current->next;
		}
		
		free(tokens);
		free(input);
	}
	return (0);
}
