/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmnasfa <hmnasfa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:56:54 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/02/27 11:37:23 by hmnasfa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void remove_pipe_node(t_cmd	*cmd_list)
{
	t_cmd *current_cmd;
	t_token *tokens;
	t_token *prev;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		tokens = current_cmd->token;
		prev = NULL;
		
		while (tokens && tokens->next)
		{
			prev = tokens;
			tokens = tokens->next;
		}
		
		if (tokens && tokens->type == PIPE)
		{
			if (prev)
				prev->next = NULL;
			free(tokens);
		}
		current_cmd = current_cmd->next;
	}
}

t_cmd	*split_by_pipe(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;
	t_token	*start;
	t_token *end;

	start = tokens;
	end = tokens;
	cmd_list = NULL;
	current_cmd = NULL;

	while (end)
	{
		if (end->type == PIPE || end->next == NULL)
		{
			new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
				return (NULL);

			t_token *next_token = end->next;
			if (end->type == PIPE)
				end->next = NULL;
			
			new_cmd->token = start;
			new_cmd->next = NULL;
			
			if (!cmd_list)
				cmd_list = new_cmd;
			else
				current_cmd->next = new_cmd;
			current_cmd = new_cmd;

            start = next_token;
            end = next_token;
		}
		else
			end = end->next;
	}
	return (cmd_list);
}

