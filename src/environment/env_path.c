/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 16:44:32 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/03 12:39:50 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "executer.h"
#include "messages.h"
#include "ui.h"
#include <sys/stat.h>
#include <unistd.h>
#include <libft.h>

static char	*pathjoin(char *path, char *file)
{
	char	*result;

	result = ft_strjoin(path, "/");
	if (result == NULL)
	{
		printerror(MSG_MEMORY, ERROR, 0);
		return (NULL);
	}
	result = ft_strjoin_free1(result, file);
	if (result == NULL)
	{
		printerror(MSG_MEMORY, ERROR, 0);
		return (NULL);
	}
	return (result);
}

static char	*file_exists(char *path)
{
	struct stat	buff;

	if (stat(path, &buff) == 0 && S_ISREG(buff.st_mode))
		return (path);
	return (NULL);
}

static char	*path_resolve(char *filepath, t_env *env, char *file)
{
	size_t	i;
	char	**path;

	i = 0;
	path = ft_split(env_get(env, "PATH"), ':');
	if (path == NULL)
		return (NULL);
	while (path[i])
	{
		filepath = pathjoin(path[i], file);
		if (filepath == NULL)
		{
			command_gen_free(path);
			return (NULL);
		}
		if (file_exists(filepath) != NULL)
		{
			command_gen_free(path);
			return (filepath);
		}
		free(filepath);
		i++;
	}
	command_gen_free(path);
	return (NULL);
}

char		*env_file_resolve(t_env *env, char *file)
{
	char		*cwd;
	char		*filepath;

	if (file == NULL)
		return (NULL);
	if ((file[0] == '.' || file[0] == '/') && file_exists(file) != NULL)
		return (ft_strdup(file));
	filepath = NULL;
	if (file[0] == '.')
	{
		cwd = getcwd(NULL, 0);
		filepath = pathjoin(cwd, file);
		free(cwd);
		if (filepath == NULL)
		{
			printerror(MSG_MEMORY, ERROR, 0);
			return (NULL);
		}
		if (file_exists(filepath) != NULL)
			return (filepath);
		free(filepath);
	}
	return (path_resolve(filepath, env, file));
}
