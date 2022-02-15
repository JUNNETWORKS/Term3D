/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 21:55:36 by jtanaka           #+#    #+#             */
/*   Updated: 2022/02/16 01:15:31 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_tmp;
	t_list	*previous;

	lst_tmp = *lst;
	while (lst_tmp)
	{
		del(lst_tmp->content);
		previous = lst_tmp;
		lst_tmp = lst_tmp->next;
		free(previous);
	}
	*lst = NULL;
}

void	*ft_lstclear_and_return_null(t_list **lst, void (*del)(void *))
{
	ft_lstclear(lst, del);
	return (NULL);
}