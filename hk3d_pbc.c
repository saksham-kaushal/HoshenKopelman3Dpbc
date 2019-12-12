/*
To compile - gcc -o hk3d_pbc hk3d_pbc.c -Wall
To execute - ./hk3d_pbc

Tobin Fricke's implementation of the
   Hoshen-Kopelman algorithm for
   cluster labeling.

   Copyright (c) September 9, 2000, by Tobin Fricke <tobin@splorg.org>
   Distributed under the terms of the GNU Public License.

   Modified 2002-03-09 Tobin Fricke
   Modified substantially 2004-04-21 by Tobin Fricke
   http://www.ocf.berkeley.edu/~fricke/projects/hoshenkopelman/hoshenkopelman.html

*/

/* ****************************************************
   The program reads in a matrix from standard input, runs the HK algorithm on
   it, and prints out the results.  The form of the input is three integers giving the
   dimensions of the matrix, followed by the matrix elements (with data separated by
   whitespace).  

a sample input file is the following:

3 8 8
1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 1
1 0 0 0 0 1 0 1
1 0 0 1 0 1 0 1
1 0 0 1 0 1 0 1
1 0 0 1 1 1 0 1
1 1 1 1 0 0 0 1
0 0 0 1 1 1 0 1 
1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 1
1 0 0 0 0 1 0 1
1 0 0 1 0 1 0 1
1 0 0 1 0 1 0 1
1 0 0 1 1 1 0 1
1 1 1 1 0 0 0 1
0 0 0 1 1 1 0 1 
1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 1
1 0 0 0 0 1 0 1
1 0 0 1 0 1 0 1
1 0 0 1 0 1 0 1
1 0 0 1 1 1 0 1
1 1 1 1 0 0 0 1
0 0 0 1 1 1 0 1 

this sample input gives the following output:

 --output-- 
 
  1   1   1   1   1   1   1   1 
  0   0   0   0   0   0   0   1 
  1   0   0   0   0   1   0   1 
  1   0   0   1   0   1   0   1 
  1   0   0   1   0   1   0   1 
  1   0   0   1   1   1   0   1 
  1   1   1   1   0   0   0   1 
  0   0   0   1   1   1   0   1 


  1   1   1   1   1   1   1   1 
  0   0   0   0   0   0   0   1 
  1   0   0   0   0   1   0   1 
  1   0   0   1   0   1   0   1 
  1   0   0   1   0   1   0   1 
  1   0   0   1   1   1   0   1 
  1   1   1   1   0   0   0   1 
  0   0   0   1   1   1   0   1 


  1   1   1   1   1   1   1   1 
  0   0   0   0   0   0   0   1 
  1   0   0   0   0   1   0   1 
  1   0   0   1   0   1   0   1 
  1   0   0   1   0   1   0   1 
  1   0   0   1   1   1   0   1 
  1   1   1   1   0   0   0   1 
  0   0   0   1   1   1   0   1 


1 clusters reported in pbc

+++++++++++++++++++++++++++++++++++++++++++++++++

2 10 15
1 0 1 1 0 0 1 1 1 1 1 1 1 1 0 
0 0 1 0 0 1 0 0 1 1 1 0 0 0 1 
0 1 1 1 1 0 0 0 0 1 0 1 1 1 1 
1 0 1 1 0 1 0 0 0 0 1 1 0 0 1 
0 0 1 1 0 0 0 0 1 0 0 0 1 0 1 
1 0 1 0 1 0 0 0 1 0 0 1 0 1 1 
1 1 0 0 1 0 1 1 1 1 1 1 1 1 0 
1 0 0 1 1 1 0 0 1 1 1 0 0 1 1 
1 1 0 1 1 1 0 1 0 1 0 0 1 0 0 
0 0 1 0 0 1 1 0 1 1 0 1 1 0 0 
1 0 1 1 0 0 1 1 1 1 1 1 1 1 0 
0 0 1 0 0 1 0 0 1 1 1 0 0 0 1 
0 1 1 1 1 0 0 0 0 1 0 1 1 1 1 
1 0 1 1 0 1 0 0 0 0 1 1 0 0 1 
0 0 1 1 0 0 0 0 1 0 0 0 1 0 1 
1 0 1 0 1 0 0 0 1 0 0 1 0 1 1 
1 1 0 0 1 0 1 1 1 1 1 1 1 1 0 
1 0 0 1 1 1 0 0 1 1 1 0 0 1 1 
1 1 0 1 1 1 0 1 0 1 0 0 1 0 0 
0 0 1 0 0 1 1 0 1 1 0 1 1 0 0 

this sample input gives the following output:

 --output-- 
 
  1   0   2   2   0   0   3   3   3   3   3   3   3   3   0 
  0   0   2   0   0   4   0   0   3   3   3   0   0   0   3 
  0   2   2   2   2   0   0   0   0   3   0   3   3   3   3 
  3   0   2   2   0   5   0   0   0   0   3   3   0   0   3 
  0   0   2   2   0   0   0   0   3   0   0   0   6   0   3 
  3   0   2   0   3   0   0   0   3   0   0   3   0   3   3 
  3   3   0   0   3   0   3   3   3   3   3   3   3   3   0 
  3   0   0   3   3   3   0   0   3   3   3   0   0   3   3 
  3   3   0   3   3   3   0   7   0   3   0   0   3   0   0 
  0   0   2   0   0   3   3   0   3   3   0   3   3   0   0 


  1   0   2   2   0   0   3   3   3   3   3   3   3   3   0 
  0   0   2   0   0   4   0   0   3   3   3   0   0   0   3 
  0   2   2   2   2   0   0   0   0   3   0   3   3   3   3 
  3   0   2   2   0   5   0   0   0   0   3   3   0   0   3 
  0   0   2   2   0   0   0   0   3   0   0   0   6   0   3 
  3   0   2   0   3   0   0   0   3   0   0   3   0   3   3 
  3   3   0   0   3   0   3   3   3   3   3   3   3   3   0 
  3   0   0   3   3   3   0   0   3   3   3   0   0   3   3 
  3   3   0   3   3   3   0   7   0   3   0   0   3   0   0 
  0   0   2   0   0   3   3   0   3   3   0   3   3   0   0 


7 clusters reported in pbc

*********************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "parameters.h"

#define max(a,b) (a>b?a:b)

void print_matrix(int ***matrix, int l, int m, int n);
int hoshen_kopelman(int boundary, int ***matrix, int l, int m, int n);
void check_labelling(int boundary, int ***matrix, int l, int m, int n);
void uf_initialize(int max_labels);
int uf_find(int x);
int uf_union(int x, int y);
int uf_make_set(void);
void uf_initialize(int max_labels);
void uf_done(void);
int get_up(int i, int m);
int get_left(int j, int n);
int get_down(int i, int m);
int get_right(int j, int n);
int get_front(int k, int l);
int get_back(int k, int l);

//##########################################################

int *labels;
int n_labels = 0;     /* length of the labels array */

//##########################################################

int main(void)
{
	int l=L, m=M, n=N; 		// l,m,n - number of elements along z, x and y dimensions.
	int ***matrix;
	
	if (l && m && n)  
	{
		//memory management - allocate memory to matrix data structure
		matrix = (int ***)calloc(m, sizeof(int**));
		for (int i=0; i<l; i++)
		{
			matrix[i] = (int **)calloc(m, sizeof(int*));
			for (int j=0; j<m; j++)
			{
				matrix[i][j] = (int *)calloc(n,sizeof(int));
				for (int k=0; k<n; k++)
				{
					scanf("%d",&(matrix[i][j][k]));		//READS Input File.
				}
			}
		}
		
		//Run HK algorithm for OBC first, followed by PBC
		int clusters = hoshen_kopelman(0,matrix,l,m,n);
		int new_clusters = hoshen_kopelman(1,matrix,l,m,n);
		
		//check labelling constraints
		check_labelling(1,matrix,l,m,n);
		
		//memory management - free labels data structure
		uf_done();

		//print output matrix
		//printf("\n--output--\n\n");
		//Print Number of clusters in topmost line of the file.
		printf("%d\n", new_clusters);					//Print number of clusters
		print_matrix(matrix,l,m,n);					//Function below prints the cluster labels
		
		//memory management - free matrix data structure
		for (int i=0; i<l; i++)
		{
			for (int j=0; j<m; j++)
			{
				free(matrix[i][j]);
			}
			free(matrix[i]);
		}
		free(matrix);
		return 0;
	}
}

//##########################################################

//Prints a three dimensional matrix

void print_matrix(int ***matrix, int l, int m, int n)
{
	for (int i=0; i<l; i++)
	{
		for (int j=0; j<m; j++)
		{
			for (int k=0; k<n; k++)
			{
				printf("%d ",matrix[i][j][k]);
			}
			printf("\n");
		}
		//printf("\n\n");
	}
}

//----------------------------------------------------------

//Hoshen Kopelman Algorithm subroutine

int hoshen_kopelman(int boundary, int ***matrix, int l, int m, int n)
{
	//boundary = 0 - open boundary conditions
	if (boundary == 0)
	{
		//initialize cluster labels, maximum number of clusters = half the number of sites in 3D lattice
		uf_initialize(l*m*n/2);
		for (int i=0; i<l; i++)
		{
			for (int j=0; j<m; j++)
			{
				for (int k=0; k<n; k++)
				{
					if (matrix[i][j][k])		//check neighbours only if the given site is occupied
					{
						int front = (i==0 ? 0 : matrix[i-1][j][k]);		//look ahead
						int up = (j==0 ? 0 : matrix[i][j-1][k]);		//look up
						int left = (k==0 ? 0 : matrix[i][j][k-1]);		//look left
						
						switch (!!front + !!up + !!left)		// direction in which an occupied site exists = 1, else 0
						{
							case 0:
								matrix[i][j][k] = uf_make_set();      // create a new cluster
								break;
							case 1:                              // part of an existing cluster
								matrix[i][j][k] = max(front,max(up,left));       // whichever neighbouring cluster number is nonzero is labelled
								break;
							case 2:                              // this site binds two clusters
								matrix[i][j][k] = (!!front == 0 ? uf_union(left,up) : (!!up == 0 ? uf_union(front,left) : uf_union(front,up)));
								break;
							case 3:                              // this site binds three clusters
	  							matrix[i][j][k] = uf_union(left,up);
	  							matrix[i][j][k] = uf_union(front,left);
	  							matrix[i][j][k] = uf_union(front,up);
	  							break;
	  					}
					}
				}
			}
		}
		int total_clusters = labels[0];
		return total_clusters;
	}
	
	//boundary = 0 - periodic boundary conditions
	else if (boundary == 1)
	{
		for (int i=0; i<l; i++)
		{
			for (int j=0; j<m; j++)
			{
				for (int k=0; k<n; k++)
				{
					if (matrix[i][j][k])		//check neighbours only if the given site is occupied
					{
						int front = matrix[get_front(i,l)][j][k];	//look ahead
						int up = matrix[i][get_up(j,m)][k];    		//look up  
						int left = matrix[i][j][get_left(k,n)];  	//look left  

						switch (!!front + !!up + !!left)		// direction in which an occupied site exists = 1, else 0
						{
							case 0:
								break;			//retain old cluster number for a site with no neighbour along any of the given directions
							case 1:								// part of an existing cluster
								// whichever neighbouring cluster number is nonzero is labelled
								if (front) {matrix[i][j][k] = front;}
								if (up) {matrix[i][j][k] = up;}
								if (left) {matrix[i][j][k] = left;}
								break;
							case 2:                              // this site binds two clusters
								matrix[i][j][k] = (!!front == 0 ? uf_union(left,up) : (!!up == 0 ? uf_union(front,left) : uf_union(front,up)));
								break;
							case 3:                              // this site binds three clusters
	  							matrix[i][j][k] = uf_union(left,up);
	  							matrix[i][j][k] = uf_union(front,left);
	  							matrix[i][j][k] = uf_union(front,up);
	  							break;
						}
					}
				}
			}
		}
		
		//sequential numbering of clusters using new labels for clusters
		int *new_labels_pbc = calloc(sizeof(int), n_labels); // allocate array, initialized to zero
		for (int i=0; i<l; i++)
		{
			for (int j=0; j<m; j++)
			{
				for (int k=0; k<n; k++)
				{
					if (matrix[i][j][k])
					{
						int x = uf_find(matrix[i][j][k]);
						if (new_labels_pbc[x] == 0)
						{
							new_labels_pbc[0]++;
							new_labels_pbc[x] = new_labels_pbc[0];
						}
						matrix[i][j][k] = new_labels_pbc[x];
					}
				}
			}
		}
		
		int total_clusters = new_labels_pbc[0];
		free(new_labels_pbc);
		return total_clusters;			// return total number of clusters in pbc
	}
	else
	{
		printf("possible boundary conditions :\n 0-open\n1-periodic\n");
		return 0;
	}
}

//------------------------------------------------------------

//Initialize labels data structure and number of lebels. First element gives number of clusters.

void uf_initialize(int max_labels) {
  n_labels = max_labels;
  labels = calloc(sizeof(int), n_labels);
  labels[0] = 0;
}

//------------------------------------------------------------

// 'find' subroutine of union-find algorithm. Finds the cluster whose subset is the given cluster.

int uf_find(int x) {
  int y = x;
  while (labels[y] != y)
    y = labels[y];
  
  while (labels[x] != x) {
    int z = labels[x];
    labels[x] = y;
    x = z;
  }
  return y;
}

//-----------------------------------------------------------

//'union' subroutine of union-find algorithm. binds two clusters, i.e. makes one cluster a subset of another.

int uf_union(int x, int y) {
  return labels[uf_find(x)] = uf_find(y);
}

//-----------------------------------------------------------

//creates a new cluster and increases the counter of number of clusters by 1.

int uf_make_set(void) {
  labels[0] ++;
//  printf("%d %d\n",labels[0],n_labels);
  assert(labels[0] <= n_labels);
  labels[labels[0]] = labels[0];
  return labels[0];
}

//-----------------------------------------------------------

//memory management - free labels, data structure containing cluster numbers

void uf_done(void) {
  n_labels = 0;
  free(labels);
  labels = 0;
}

//-----------------------------------------------------------

//get index of elements along different directions in pbc

int get_up(int i, int m)
{
	if (i==0) {return m-1;}
	else {return i-1;}
}

int get_left(int j, int n)
{
	if (j==0) {return n-1;}
	else {return j-1;}
}

int get_front(int k, int l)
{
	if (k==0) {return l-1;}
	else {return k-1;}
}

int get_down(int i, int m)
{
	return i%m;
}

int get_right(int j, int n)
{
	return j%n;
}

int get_back(int k, int l)
{
	return k%l;
}

//----------------------------------------------------------

//Checks that no two occupied adjacent sites have different cluster labels.

void check_labelling(int boundary, int ***matrix, int l, int m, int n)
{
	int North,South,East,West,Front,Back;
	if(boundary == 0)
	{
		for (int i=0; i<l; i++)
		{
			for (int j=0; j<m; j++)
			{
				for (int k=0; k<n; k++)
				{
					if (matrix[i][j][k])
					{
						Front = ( i==0 ? 0 : matrix[i-1][j][k] );
						Back = ( i==l-1 ? 0 : matrix[i+1][j][k] );
						North = ( j==0 ? 0 : matrix[i][j-1][k] );
						South = ( j==m-1 ? 0 : matrix[i][j+1][k] );
						East = ( k==n-1 ? 0 : matrix[i][j][k+1] );
						West = ( k==0 ? 0 : matrix[i][j][k-1] );
					
						assert( North==0 || matrix[i][j][k]==North );
						assert( South==0 || matrix[i][j][k]==South );
						assert( East==0 || matrix[i][j][k]==East );
						assert( West==0 || matrix[i][j][k]==West );
						assert( Front==0 || matrix[i][j][k]==Front );
						assert( Back==0 || matrix[i][j][k]==Back );
      				}
      			}
			}
		}
	}
	else if(boundary == 1)
	{
		for (int i=0; i<l; i++)
		{
			for (int j=0; j<m; j++)
			{
				for (int k=0; k<n; k++)
				{
					if (matrix[i][j][k])
					{
						Front = ( matrix[get_front(i,l)][j][k] );
						Back = ( matrix[get_back(i,l)][j][k] );
						North = ( matrix[i][get_up(j,m)][k] );
						South = ( matrix[i][get_down(j,m)][k] );
						East = ( matrix[i][j][get_right(k,n)] );
						West = ( matrix[i][j][get_left(k,n)] );
					
						assert( Front==0 || matrix[i][j][k]==Front );
						assert( Back==0 || matrix[i][j][k]==Back );
						assert( North==0 || matrix[i][j][k]==North );
						assert( South==0 || matrix[i][j][k]==South );
						assert( East==0 || matrix[i][j][k]==East );
						assert( West==0 || matrix[i][j][k]==West );
					}
				}
			}
		}
	}
	else
	{
		printf("possible boundary conditions :\n 0 - open\n1 - periodic\n");
	}
}

