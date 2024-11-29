# miniRT -- WIP!!

![Screenshot from 2024-04-21 21-10-07](https://github.com/alx-sch/42_pipex/assets/134595144/350670ec-54ee-4629-94ab-0dcb1dd92a9b)


<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/minirt_badge.png" alt="minirt_badge.png" />
</p>

## Projection of 3D scene onto 2D Screen

<div style="display: block;">
<img width="600" alt="Viewpoint_FOV" src="https://github.com/Busedame/miniRT/blob/main/.assets/Viewport_Field_of_View.png">  
</div>

<div style="display: block;">
<img width="830" alt="FOV_frustum" src="https://github.com/Busedame/miniRT/blob/main/.assets/FOV_frustum.png">  
</div>

- The camera has a frustum that defines what it can see (a 3D pyramid-like shape).
- The near plane is the closest part of the frustum to the camera, and it's like a window through which the camera views the 3D world (until the far plane).
- The viewport is the 2D version of that window (the near plane) where the 3D world gets projected and displayed on the screen.

## Ray-Object Intersection

This section explains the mathematical approach to detecting intersections between rays and various geometric objects.

### Ray Equation

A ray is represented as:

$$
P(t) = \text{ray-origin} + t \times \text{ray-dir}
$$

Where:
- **$P(t)$:**  
    The point on the ray at distance \(t\) from the ray's origin.  
    It represents a location along the path defined by the ray, calculated by moving from the ray's starting point in the direction of the ray's direction vector.

- **$\text{ray-origin}$:**  
    The starting point of the ray, represented as a 3D vector.  
    This point marks the location where the ray begins its journey through space (camera).

-  **$\text{ray-dir}$:**  
    The normalized direction vector of the ray.  
    A normalized vector has a magnitude (or length) of 1, ensuring that the scalar \(t\) directly corresponds to the distance traveled along the ray.  
    The direction vector defines the ray's path, indicating the direction in which the ray travels.

- **$t$:**  
    A scalar value indicating the distance along the ray.  
    It scales the direction vector, determining how far along the ray the point \( P(t) \) is. When the direction vector is normalized, the value of \(t\) directly represents the magnitude of the distance from the ray’s origin.

### Plane Intersection

To find the intersection of a ray with a plane, we use the plane equation:

$$
(P - P_0) \cdot n = 0
$$

Where:
- **$P$:**   
    Is any point on the plane.
- **$P_0$**  
    Is a known point on the plane 
- **$n$:**  
    The normal vector of the plane, which is perpendicular to the surface.

Substitute the ray equation ' $P(t) = \text{ray-origin} + t \times \text{ray-dir}$ ' into the plane equation:

$$
(\text{ray-origin} + t \times \text{ray-dir} - P_0) \cdot n = 0
$$

Rearrange terms:

$$
(\text{ray-origin} - P_0) \cdot n + t \times (\text{ray-dir} \cdot n) = 0
$$

Solve for *t*:

$$
t = \frac{(P_0 - \text{ray-origin}) \cdot n}{\text{ray-dir} \cdot n}
$$

- *t* will be **positive** if the denominator ' $\text{ray-dir} \cdot n$ ' is positive, meaning that the ray is moving **towards** the plane. The ray will intersect the plane **in front of the camera**.
- *t* will be **negative** if the denominator ' $\text{ray-dir} \cdot n$ ' is negative, meaning that the ray is moving **away** from the plane. The ray will intersect the **behind the camera**.
- If the denominator ' $\text{ray-dir} \cdot n$ ' is zero  (*t* is undefined or infinite), it means the ray is **parallel** to the plane and does not intersect it.

In the function, we first check if the ray is not parallel to the plane (*t* exists or is defined). If the ray is not parallel, we then check if the intersection happens in front of the camera (*t* is positive). The function returns successfully only if the intersection occurs in front of the camera.

```C
/**
Function to find the intersection of a ray with a plane.

 @param ray_origin	The starting point of the ray (3D vector).
 @param ray_dir 	The normalized direction vector of the ray..
 @param plane 		Pointer to the plane structure.
 @param t 		A pointer to store the distance to the intersection point
			(if found).

 @return 		`1` if an intersection is found (and t is set to the
			intersection distance);
			`0` if there is no intersection within the FOV.

 @note
Due to floating-point precision limitations, directly comparing a dot product to zero 
can be unreliable. A small threshold (1e-6) is used to determine if the ray is parallel 
to the plane. Values below this threshold are considered too close to zero, indicating 
parallelism or preventing division by very small numbers, which could lead to inaccuracies.
*/
*/
int	ray_intersect_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane *plane,
		double *t)
{
	double	denom;
	t_vec3	difference;

	denom = vec3_dot(ray_dir, plane->normal);
	if (fabs(denom) > 1e-6)
	{
		difference = vec3_sub(plane->point_in_plane, ray_origin);
		*t = vec3_dot(difference, plane->normal) / denom;
		if (*t >= 0.0)
			return (1);
	}
	return (0);
}
```

### Quadratic Equation

Intersection calculations with geometric objects like spheres and cylinders are solved using **quadratic equations**. A quadratic equation has the general form:

$$
ax^2 + bx + c = 0
$$

Where:
- **$a$, $b$, $c$:**    
  The coefficients of the equation (quadratic, linear, and constant, respectively).
- **$x$:**    
  The unknown variable we are solving for (in our case, that's *t*, the distance between the camera and the object).

The general solution to a quadratic equation is given by the **quadratic formula**:

$$
x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
$$

Where:
- **$b² - 4ac$** is called the **discriminant**, and it determines the nature of the solutions:
    - If the discriminant is **positive**, there are **two real solutions**, indicating two intersection points.
    - If the discriminant is **zero**, there is **one real solution**, indicating a tangent (one point of intersection).
    - If the discriminant is **negative**, there are **no real solutions**, meaning the ray does not intersect the object.

For a detailed derivation of the quadratic formula, please refer to [ChiliMath Quadratic Formula Derivation](https://www.chilimath.com/lessons/intermediate-algebra/derive-quadratic-formula/).


### Sphere Intersection

To find where a ray intersects a sphere, we start with the general equation of the sphere:

$$
\left( P(t) - \text{sphere-center} \right) \cdot \left( P(t) - \text{sphere-center} \right) = r^2
$$

Where:
- **sphere-center:**  
    The center of the sphere in 3D space, represented as a vector.
  
- **r:**  
    The radius of the sphere.

- **\( $\cdot$ \):**  
    The dot product between two vectors.

Now, substitute the ray equation ' $P(t) = \text{ray-origin} + t \times \text{ray-dir}$ ' into the sphere equation:

$$
\left( \text{ray-origin} + t \times \text{ray-dir} - \text{sphere-center} \right) \cdot \left( \text{ray-origin} + t \times \text{ray-dir} - \text{sphere-center} \right) = r^2
$$

Expanding this gives you a quadratic equation of the form:

$$
At^2 + Bt + C = 0
$$

Where:
- **A:**  
    The coefficient of \( t^2 \), which comes from the dot product of the direction vector with itself.
- **B:**  
    The coefficient of \( t \), which is derived from the ray’s origin and direction in relation to the sphere’s center.
- **C:**  
    The constant term, which is related to the distance between the ray's origin and the sphere’s center.

You can solve this quadratic equation using the quadratic formula:

$$
t = \frac{-B \pm \sqrt{B^2 - 4AC}}{2A}
$$

- If the discriminant \( (B^2 - 4AC) \) is **positive**, there are **two intersections**.
- If the discriminant is **zero**, there is **one intersection** (the ray is tangent to the sphere).
- If the discriminant is **negative**, there are **no intersections**.

