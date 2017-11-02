

//All Header File 
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>

#include"fun.h"

// All define value
#define N 256

//All function phototype
void genPDF(double **pdf, double P, double pctg, double radius, double val);


using namespace std;

int main()
{

	//Main function variable for genpPDF
	double **pdf = (double **)malloc(N*sizeof(double));
	for (int i = 0;i < N;i++)
		pdf[i]= (double *)malloc(N*sizeof(double));
	double P=6,pctg=.33,radius=0.1,val=.5;
	//Function call genPDP return pdf value
	//pdf = genPDF(DN,P,pctg , 2 ,0.1,0);	% generates the sampling PDF

	genPDF(pdf, P, pctg, radius, val);
	
	printf("working.......");

	//Memroy free
	for (int i = 0;i < N;i++)
		free(pdf[i]);
	free(pdf);

	
	cin.get();
	return 0;
}


void genPDF(double **pdf, double P, double pctg, double radius, double val)
{
	int i, j,idxcon=0;
	int disType = 2, disp = 0;
	double minval = 0,maxval = 1;
	int sx = N,sy=N,temp = 0;

	//Two Dimansonal Array
	double **r = (double **)malloc(N*sizeof(double));
	for (i = 0;i < N;i++)
	   r[i] = (double *)malloc(N*sizeof(double));

	double **X= (double **)malloc(N*sizeof(double));
		X[i] = (double *)malloc(N*sizeof(double));

	double **Y = (double **)malloc(N*sizeof(double));
		Y[i] = (double *)malloc(N*sizeof(double));

	double *x= (double *)malloc(N*sizeof(double));
	double *y = (double *)malloc(N*sizeof(double));
	double *idx=(double *)malloc(60000*sizeof(double));
	double sumValue, value, N_floor;






	//Memroy free
	for (int i = 0;i < N;i++)
		free(r[i]);
	free(r);

	for (int i = 0;i < N;i++)
		free(X[i]);
	free(X);
	for (int i = 0;i < N;i++)
		free(Y[i]);
	free(Y);

	free(x);
	free(y);
	free(idx);
	
}

