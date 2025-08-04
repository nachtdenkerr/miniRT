/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:11:48 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/02 12:06:18 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	if (!lst || !f)
		return ;
	while (temp != NULL)
	{
		(*f)(temp->content);
		temp = temp->next;
	}
}

static t_list	*mapiter(t_list *lst, t_list *finallst, void *(*f)(void *),
							void (*del)(void *))
{
	void	*void_content;
	t_list	*temp;

	temp = finallst;
	while (lst != NULL)
	{
		void_content = f(lst->content);
		temp = ft_lstnew(void_content);
		if (!temp)
		{
			del(void_content);
			ft_lstclear(&finallst, del);
			return (NULL);
		}
		ft_lstadd_back(&finallst, temp);
		lst = lst->next;
	}
	return (finallst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*finallst;
	void	*void_content;

	if (!lst || !f)
		return (NULL);
	temp = lst;
	void_content = f(lst->content);
	finallst = ft_lstnew(void_content);
	if (finallst == NULL)
	{
		del(void_content);
		return (NULL);
	}
	lst = lst->next;
	finallst = mapiter(lst, finallst, f, del);
	lst = temp;
	return (finallst);
}
