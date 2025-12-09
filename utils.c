#include "cub3d.h"

double	dist(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); // formule de la norme d'un vecteur
}

double	normalise_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return angle;
}
