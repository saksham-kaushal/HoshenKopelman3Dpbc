/*
To compile - gcc -o dataformat2 data_format_2.c
To execute - ./dataformat2
*/


#include <stdio.h>
#include <string.h>
#include "parameters.h"


int main(void)
{
	FILE *inputfp, *outputfp1, *outputfp2;
	inputfp = fopen(INFILE,"r");
	int nconfig=0, configs=CONFIGS, l=L, m=M, n=N;
//	fscanf(inputfp,"%d %d %d %d", &configs, &l, &m, &n);
	for (nconfig=0;nconfig<configs;nconfig++)
  {	
//	int arr[l][m][n];
	char fname1[PATH_LEN], fname2[PATH_LEN];
	snprintf(fname1,PATH_LEN,"%sdata_%d_1.txt",F_DATA_DIR,nconfig);	
	snprintf(fname2,PATH_LEN,"%sdata_%d_2.txt",F_DATA_DIR,nconfig);	
	outputfp1 = fopen(fname1,"w");
	outputfp2 = fopen(fname2,"w");

//	fprintf(outputfp1, "%d %d %d\n",l,m,n);
//	fprintf(outputfp2, "%d %d %d\n",l,m,n);
	int i=0,j=0,k=0;
	float x=0;
	for(i=0;i<l;i++)
	{
		for(j=0;j<m;j++)
		{
			for(k=0;k<n;k++)
			{
				fscanf(inputfp,"%f",&x);
				if (x<0)
				{
					fprintf(outputfp1,"0 ");
					fprintf(outputfp2,"1 ");
				}
				else if (x>0)
				{
					fprintf(outputfp1,"1 ");
					fprintf(outputfp2,"0 ");
				}
				else
				{
					return 1;
				}
				
			}
			fprintf(outputfp1,"\n");
			fprintf(outputfp2,"\n");
		}
	}
  }
	fclose(inputfp);
	fclose(outputfp1);
	fclose(outputfp2);
	return 0;
}
