/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:52 by nholbroo          #+#    #+#             */
/*   Updated: 2024/11/26 16:50:38 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Prints out a parsing related error message for program usage, file extension,
file access or not enough object identifiers..*/
void	errors_file(int error_code)
{
	ft_putstr_fd(COLOR_RED, 2);
	if (error_code == ERR_USAGE)
		ft_putstr_fd(ERR_MSG_USAGE, 2);
	else if (error_code == ERR_FILE_EXTENSION)
		ft_putstr_fd(ERR_MSG_FILE_EXTENSION, 2);
	else if (error_code == ERR_FILE_ACCESS)
		perror(ERR_MSG_FILE_ACCESS);
	else if (error_code == ERR_MISSING_IDENTIFIER)
		ft_putstr_fd(ERR_MSG_MISSING_IDENTIFIER, 2);
	ft_putstr_fd(COLOR_RESET, 2);
	exit(error_code);
}

/*Prints out a parsing related error message for failed memory allocation,
several unique elements, an invalid identifier or if the .rt-file is empty.*/
static void	non_element_errors(t_pars *parsing)
{
	if (parsing->error_code == ERR_MEM_ALLOC)
		ft_putstr_fd(ERR_MSG_MEM_ALLOC, 2);
	else if (parsing->error_code == ERR_UNIQUE_ELEM)
		ft_putstr_fd(ERR_MSG_UNIQUE_ELEM, 2);
	else if (parsing->error_code == ERR_INVALID_IDENTIFIER)
		ft_putstr_fd(ERR_MSG_INVALID_IDENTIFIER, 2);
	else if (parsing->error_code == ERR_FILE_EMPTY)
		ft_putstr_fd(ERR_MSG_FILE_EMPTY, 2);
}

void	errors_parsing(t_scene *scene, t_pars *parsing)
{
	ft_putstr_fd(COLOR_RED, 2);
	if (parsing->error_code >= 4 && parsing->error_code <= 8)
		non_element_errors(parsing);
	else if (parsing->error_code >= 9 && parsing->error_code <= 12)
		ambience_errors(parsing);
	else if (parsing->error_code >= 13 && parsing->error_code <= 19)
		camera_errors(parsing);
	else if (parsing->error_code >= 20 && parsing->error_code <= 25)
		light_errors(parsing);
	else if (parsing->error_code >= 26 && parsing->error_code <= 31)
		sphere_errors(parsing, scene->tot_sp);
	else if (parsing->error_code >= 32 && parsing->error_code <= 39)
		plane_errors(parsing, scene->tot_pl);
	else if (parsing->error_code >= 40 && parsing->error_code <= 49)
		cylinder_errors(parsing, scene->tot_cy);
	ft_putstr_fd(COLOR_RESET, 2);
	free_scene_and_exit(scene);
}