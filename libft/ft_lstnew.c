/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:29:41 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/10 19:17:17 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newl;

	newl = (t_list *)malloc(sizeof(t_list));
	if (newl == NULL)
		return (NULL);
	if (content == NULL)
	{
		newl->content = NULL;
		newl->content_size = 0;
	}
	else
	{
		newl->content = malloc(sizeof(content));
		if (newl->content == NULL)
		{
			free(newl);
			return (NULL);
		}
		ft_memcpy((newl->content), content, content_size);
		newl->content_size = content_size;
	}
	newl->next = NULL;
	return (newl);
}
