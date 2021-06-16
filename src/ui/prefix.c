/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prefix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 10:14:07 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/08 16:36:22 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "messages.h"
#include "environment.h"
#include <libft.h>
#include <unistd.h>

void	printprefix(t_env *env)
{
	char	*folder;
	char	*user;
	char	*clr;

	folder = ft_strrchr(env_get(env, "PWD"), '/') + 1;
	user = env_get(env, "USER");
	if (user == NULL)
		user = "";
	if (folder == (char*)0x1)
		folder = "";
	else
	{
		if (ft_strlen(folder) == 0)
			folder = "/";
	}
	clr = env->last_status == 0 ? CLR_GRN : CLR_RED;
	write(STDERR_FILENO, CLR_YLW, ft_strlen(CLR_YLW));
	write(STDERR_FILENO, user, ft_strlen(user));
	write(STDERR_FILENO, " ", 1);
	write(STDERR_FILENO, CLR_CYAN, ft_strlen(CLR_CYAN));
	write(STDERR_FILENO, folder, ft_strlen(folder));
	write(STDERR_FILENO, " ", 1);
	write(STDERR_FILENO, clr, ft_strlen(clr));
	write(STDERR_FILENO, "|> ", 3);
	write(STDERR_FILENO, CLR_RST, ft_strlen(CLR_RST));
}
