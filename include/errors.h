/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:55:16 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/12 17:42:03 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_COLOR			"\033[91m\033[1m" // red and bold
# define RESET			"\033[0m"

# define ERR_ARG			"ERROR: Invalid usage! Use: ./minirt map_file.fdf\n"
# define ERR_FILE_TYPE		"ERROR: Invalid file format! Use: .fdf\n"
# define ERR_MLX			"ERROR: MLX"
# define ERR_MALLOC			"ERROR: malloc() failed"

#endif