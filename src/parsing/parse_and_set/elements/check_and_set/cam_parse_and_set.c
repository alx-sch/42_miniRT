/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_set_camera.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:58 by nholbroo          #+#    #+#             */
/*   Updated: 2024/12/06 12:57:03 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*Checks if the camera's field of view is valid.
It can only consist of numbers and/or a newline character.
It can only be between 0 and 180. If an error occurs, sets the
right error code and returns that error code. Returns 0 upon success.*/
static int	camera_field_of_view(t_scene *scene, int *parsing_error)
{
	if (!only_numbers_and_newline(scene->pars.elem_data[3]))
		return (set_error_and_return(NULL, &parsing_error, \
		ERR_CAM_FIELD_OF_VIEW));
	scene->cam.fov = ft_atoi(scene->pars.elem_data[3]);
	if (scene->cam.fov < 0 || scene->cam.fov > 180)
		return (set_error_and_return(NULL, &parsing_error, \
		ERR_CAM_FIELD_OF_VIEW));
	return (0);
}

/*Parses and sets a camera object.
1. Checks if there's a correct amount of fields (4).
2. Checks if the coordinates are valid.
3. Checks if the orientation vector is valid.
4. Checks if the field of view is valid (between 0 and 180).
Sets all values and returns 0 upon success, and an error code upon error.*/
int	parse_and_set_camera(t_scene *scene)
{
	if (!correct_amt_of_fields(scene->pars.elem_data, 4))
		return (ERR_CAM_FIELDS);
	if (check_coordinates(scene->pars.elem_data[1], &scene->pars.error_code, \
	ERR_CAM_COOR_FIELDS) != 0)
		return (scene->pars.error_code);
	set_coordinates(scene->pars.elem_data[1], &scene->cam.position.x, \
	&scene->cam.position.y, &scene->cam.position.z);
	if (check_orientation_vector(scene->pars.elem_data[2], \
	&scene->pars.error_code, ERR_CAM_VECTOR_FIELDS) != 0)
		return (scene->pars.error_code);
	set_orientation_vector(scene->pars.elem_data[2], &scene->cam.orientation.x, \
	&scene->cam.orientation.y, &scene->cam.orientation.z);
	if (camera_field_of_view(scene, &scene->pars.error_code) != 0)
		return (scene->pars.error_code);
	return (0);
}