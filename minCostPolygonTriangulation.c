#include <stdio.h>
#include <limits.h>
#include <math.h>

typedef struct point {
	double x;
	double y;
}point;

double distance ( point a, point b ) {
	return sqrt ((pow((a.y - b.y), 2) + pow((a.x - b.x), 2)) );
}

double min (double a, double b) {
	return a >= b ? b : a;
}

double getCost ( point p[], int i, int j, int k ) {
	point a = p[i], b = p[j], c = p[k];
	return ( distance (a, b) + distance (b, c) + distance (c, a) );
}

double minCostPolygonTriagulation ( point p[], int i, int j ) {
	int k;
	double res = INT_MAX;
	// if there are less than 3 points between i & j, its of no use doing this
	if ( j <= i+2 )
		return 0;

	for ( k = i+1; k < j; k++ ) {
		res = min ( res,
				min ( min( minCostPolygonTriagulation(p, i, k ), minCostPolygonTriagulation(p, k, j) ),
					getCost(p, i, j, k ) ) ) ;
	}
	return res;
}

int main (int argc, char **argv) {
	point p[] = {
					{0, 0},
					{0, 2},
					{1, 2},
					{2, 1},
					{1, 0},
	};

	printf ( "Minimum cost = %f.\n", minCostPolygonTriagulation(p, 0, 4) );
	return 0;
}
