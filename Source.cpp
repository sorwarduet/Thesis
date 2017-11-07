

//All Header File 
#include<cstdio>
#include<iostream>
#include<cmath>
#include<complex>
#include<algorithm>
#include<stdlib.h>

using namespace std;
typedef complex<double>cmp;

#include"fun.h"

// All define value
#define N 256
#define RAND_MAX 256
//All function phototype
void genPDF(double **pdf, double P, double pctg, double radius, double val);


using namespace std;

int main()
{

	//Main function variable for genpPDF
	double **pdf = (double **)malloc(N*sizeof(double));
	for (int i = 0;i < N;i++)
		pdf[i]= (double *)malloc(N*sizeof(double));
	double **mask = (double **)malloc(N*sizeof(double));
	for (int i = 0;i < N;i++)
		mask[i] = (double *)malloc(N*sizeof(double));
	double P=6,pctg=.33,radius=0.1,val=.5;
	//Function call genPDP return pdf value
	//pdf = genPDF(DN,P,pctg , 2 ,0.1,0);	% generates the sampling PDF

	genPDF(pdf, P, pctg, radius, val);
	genSampling(mask,pdf,10,60)
	
	//printf("working.......");

	for (int i = 0;i<N;i++)
	{
		for (int j = 0;j<N;j++)
		{

			printf("%.10lf  ",pdf[i][j]);
			//printf("%.lf  ", mask[i][j]);
		}
		//printf("\n");
	}

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
	double minval = 0,maxval = 1,m=0;
	int sx = N,sy=N,temp = 0;
	double PCTG = floor(pctg*sx*sy);

	//Two dimensional  Array
	double **r = (double **)malloc(N*sizeof(double));
	for (i = 0;i < N;i++)
	   r[i] = (double *)malloc(N*sizeof(double));

	double **X= (double **)malloc(N*sizeof(double));
	for (i = 0;i < N;i++)
		X[i] = (double *)malloc(N*sizeof(double));

	double **Y = (double **)malloc(N*sizeof(double));
	for (i = 0;i < N;i++)
		Y[i] = (double *)malloc(N*sizeof(double));

		//one dimensional  Array
	double *x= (double *)malloc(N*sizeof(double));
	double *y = (double *)malloc(N*sizeof(double));
	double *idx=(double *)malloc(60000*sizeof(double));
	double sumValue, value, N_floor;



	if (temp == 0)  //For 2-D
	{
		linspace(-1, 1, N, y);
		linspace(-1, 1, N, x);
		meshgrid(X,Y,x, y);


		switch (disType)
		{
		case 1:
		{

			for (i = 0;i<N;i++)
			{
				for (j = 0;j<N;j++)
				{
					r[i][j] = max(fabs(X[i][j]), fabs(Y[i][j]));

				}
			}
			break;

		}
		default:
		{
			for (i = 0;i<N;i++)
			{
				for (j = 0;j<N;j++)
				{
					r[i][j] = sqrt(pow(X[i][j], 2) + pow(Y[i][j], 2));
					m = max(m, r[i][j]);  //For max value

										  //r[i][j]=r[i][j]/max(fabs(r[i][j]),fabs(r[i][j+1]));
				}
			}
			for (i = 0;i<N;i++)
			{
				for (j = 0;j<N;j++)
				{
					r[i][j] = r[i][j] / m;

				}
			}


		}
		}  //end swtich



	} // end if
	else  //For !-D
	{
		linspace(-1, 1, max(sx, sy), y);

		for (i = 0;i<1;i++)
		{
			for (j = 0;j<N;j++)
			{
				r[i][j] = fabs(y[j]);
			}
		}

	}


	/*
	For this function
	idx = find(r<radius);

	pdf = (1-r).^p; pdf(idx) = 1;
	*/

	for (i = 0;i<N;i++)
	{
		for (j = 0;j<N;j++)
		{
			if (r[i][j]<radius)
			{
				pdf[i][j] = 1;
			}
			else
			{
				pdf[i][j] = pow((1 - r[i][j]), P);
			}

		}
	}
	sumValue = sum(pdf);
	if (floor(sumValue)>PCTG)
	{
		printf("infeasible without undersampling dc, increase p");
	}


	//begin bisection


	while (1)
	{
		value = (minval + maxval) / 2;

		for (i = 0;i<N;i++)
		{
			for (j = 0;j<N;j++)
			{
				if (r[i][j]>1)
				{
					pdf[i][j] = 1;
				}
				else if (r[i][j]<radius)
				{
					pdf[i][j] = 1;
				}

				else
				{
					pdf[i][j] = pow((1 - r[i][j]), P) + value;
				}

			}
		}
		N_floor = floor(sum(pdf));

		//printf("%lf vs %lf",N,PCTG);
		if (N_floor>PCTG)
		{
			maxval = value;
		}
		else if (N_floor<PCTG)
		{
			minval = value;
		}
		else if (N_floor == PCTG)
		{
			break;
		}


	}







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



void genSampling(double **mask, double **pdf, int iter, int tol)
{

	int i, j, n;
	double K = 0.0;
	double minIntr = 1e99;
	double **minIntrVec = (double **)malloc(N*sizeof(N));
	for (i = 0;i < N;i++)
	{
		minIntrVec[i] = (double *)malloc(N*sizeof(N));
	}
	double **tmp = (double **)malloc(N*sizeof(N));
	for (i = 0;i < N;i++)
	{
		tmp[i] = (double *)malloc(N*sizeof(N));
	}
	double **valueForDiv = (double **)malloc(N*sizeof(N));
	for (i = 0;i < N;i++)
	{
		valueForDiv[i] = (double *)malloc(N*sizeof(N));
	}
	cmp **TMP = (cmp **)malloc(N*sizeof(cmp));
	for (i = 0;i < N;i++)
		TMP[i]= (cmp *)malloc(N*sizeof(cmp));

	double Value, ValueToMax1, ValueToMax, stat;



	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (pdf[i][j] > 1)
			{
				pdf[i][j] = 1;
			}
			K += pdf[i][j];
		}

	} //end for loop

	  //printf("K=%lf ",K);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			minIntrVec[i][j] = 0;

		}

	}






	for (n = 1; n <= iter; n++)
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				tmp[i][j] = 0.0;
			}
		}//end lopp for tmp zero

		Value = sum(tmp);

		while ((fabs(Value - K))>(double)tol)
		{
			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{

					//printf("%lf ",((double)(rand()%256) / (RAND_MAX)));
					tmp[i][j] = ((double)(rand() % 256) / (RAND_MAX))<pdf[i][j];  // assign logical value
				}
			}



			Value = sum(tmp);
			//printf("%lf \t",Value);
		} // end while loop




		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				valueForDiv[i][j] = tmp[i][j] / pdf[i][j];

			}
		}


		//		for (i = 0; i < 256; i++)
		//		{
		//			for (j = 0; j < 256; j++)
		//			{
		//				printf("%.3lf  ",valueForDiv[i][j]);
		//
		//			}
		//
		//			printf("\n");
		//		}






		ifft(TMP,valueForDiv); // call ifft2 function

		ValueToMax = sqrt(TMP[0][0].real() * TMP[0][0].real() + TMP[0][0].imag() * TMP[0][0].imag());

		for (i = 1;i<N;i++)
		{
			for (j = 1;j<N;j++)
			{
				ValueToMax1 = sqrt(TMP[i][j].real() * TMP[i][j].real() + TMP[i][j].imag() * TMP[i][j].imag());
				if (ValueToMax<ValueToMax1)
				{
					ValueToMax = ValueToMax1;
				}


			}
		}
		if (ValueToMax<minIntr)
		{
			minIntr = ValueToMax;

			for (i = 0;i<N;i++)
			{
				for (j = 0;j<N;j++)
				{
					valueForDiv[i][j] = tmp[i][j];
				}
			}


		}
		stat = ValueToMax;


	} // end n loop

	for (i = 0;i<N;i++)
	{
		for (j = 0;j<N;j++)
		{

			//printf("%.10lf  ",pdf[i][j]);
			//printf("%.lf  ",valueForDiv[i][j]);

			mask[i][j] = valueForDiv[i][j] / 4;
		}
		//printf("\n");
	}

	for (int i = 0;i < N;i++)
		free(minIntrVec[i]);
	free(minIntrVec);
	for (int i = 0;i < N;i++)
		free(tmp[i]);
	free(tmp);
	for (int i = 0;i < N;i++)
		free(valueForDiv[i]);
	free(valueForDiv);




}  // end GenSampling Function

