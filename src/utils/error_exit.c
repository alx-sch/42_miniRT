/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:38:42 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/29 16:23:56 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains a functions for terminating the program in a controlled
manner whenever an error occurs (such as invalid user input, failed file opening,
memory allocation errors, etc.). Before terminating the program, error messages
are printed to stderr, and all dynamically allocated memory within the `rt`
structure is deallocated.
*/

#include "main.h"

// IN FILE

void	cleanup_error_exit(char *msg, t_rt *rt);

/**
Checks the value of errno:
 -	If errno is zero, prints a custom error message.
 -	If errno is non-zero, prints both a custom error message
 	and the system error message.

In either case, all resources in the `rt` structure are freed before the
program exits.

 @param msg 	Custom error message to print.
 @param rt 		Pointer to the main structure of the program.
				Pass `NULL` if `rt` is not initialized.
*/
void	cleanup_error_exit(char *msg, t_rt *rt)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (errno != 0)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	ft_putstr_fd(RESET, STDERR_FILENO);
	cleanup(&rt);
	exit(EXIT_FAILURE);
}
