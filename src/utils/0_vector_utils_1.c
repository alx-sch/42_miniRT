/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_vector_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:34 by aschenk           #+#    #+#             */
/*   Updated: 2025/02/18 22:40:24 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Utility functions for working with 3D vectors.
*/

#include "main.h"

// IN FILE:

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mult(t_vec3 v, double scalar);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_dot(t_vec3 v1, t_vec3 v2);

/**
Function to add two 3D vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	The resulting vector after addition.
*/
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

/**
Function to subtract two 3D vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	The resulting vector after subtraction.
*/
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

/**
Function to multiply a 3D vector by a scalar.
 @param v 		The vector to be scaled.
 @param scalar 	The scalar value to multiply the vector by.

 @return 		The resulting vector after scaling.
*/
t_vec3	vec3_mult(t_vec3 vec, double scalar)
{
	t_vec3	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;
	return (result);
}

/**
Function to compute the cross product of two 3D vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	A 3D vector perpendicular to both input vectors.

 @details
The cross product is defined as a vector orthogonal to the plane formed
by the two input vectors.
*/
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}

/**
Function to dot two vectors.
 @param v1 	The first vector.
 @param v2 	The second vector.

 @return 	The dot product of the two vectors.
*/
double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	double	result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (result);
}
