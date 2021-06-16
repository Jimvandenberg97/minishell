/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 18:13:13 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/11/23 14:07:39 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "messages.h"
#include "ui.h"

int		builtin_pwd(char **args, t_env *env)
{
	char *pwd;

	(void)args;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		printerror(MSG_PWD_FAIL, ERROR, EXIT_FAILURE);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
