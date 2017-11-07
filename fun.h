#pragma once
#define N 256
#define PI 3.1416

void linspace(double d1, double d2, double n, double *y)
{
	double n1, c;
	n1 = n - 1;
	int i;
	c = ((d2 - d1)*(n1 - 1));
	//printf("%lf\n",c);

	if (c<0)
	{
		if ((d2 - d1)<0)
		{
			for (i = 0;i<n1;i++)
			{
				y[i] = (d1 + ((d2 / n1)*i)) - (d1 / n1)*i;
			}

		}
		else
		{
			for (i = 0;i<n1;i++)
			{
				y[i] = (d1 + i)*((d2 - d1) / n1);
			}

		}

	}
	else
	{
		for (i = 0;i<n1;i++)
		{
			y[i] = d1 + (i*((d2 - d1) / n1));
		}

	}
	y[0] = d1;
	y[(int)n - 1] = d2;
	//printf("%lf",c);
}

void meshgrid(double **X,double **Y, double *x, double *y)
{
	int i, j;
	for (i = 0;i<N;i++)
	{
		for (j = 0;j<N;j++)
		{
			X[i][j] = x[j];
			Y[i][j] = y[i];
		}
	}

}

double sum(double **x)
{
	int i, j;
	double sumOfarra = 0.0;
	for (i = 0;i<N;i++)
	{
		for (j = 0;j<N;j++)
		{
			sumOfarra += x[i][j];

		}
	}
	return sumOfarra;

}



void ifft(cmp **Res2, double **A)
{
	int i, j, k;
	double p;
	cmp **CompNumber = (cmp **)malloc(N*sizeof(cmp));
	for (i = 0;i<N;i++)
	{
		CompNumber[i] = (cmp *)malloc(N*sizeof(cmp));
	}
	cmp **Res1 = (cmp **)malloc(N*sizeof(cmp));
	for (i = 0;i<N;i++)
	{
		Res1[i] = (cmp *)malloc(N*sizeof(cmp));
	}
	for (i = 0;i<N;i++)
	{
		for (j = 0;j<N;j++)
		{
			Res1[i][j].real(0.0);
			Res1[i][j].imag(0.0);
			Res2[i][j].real(0.0);
			Res2[i][j].imag(0.0);
			
		}
	}

	for (i = 0;i<N;i++)
	{
		for (j = 0;j<N;j++)
		{
			p = (2 * PI / N)*(i*j);
			CompNumber[i][j].real(cos(p));
			CompNumber[i][j].imag(sin(-p));

		}

	}

	for (i = 0;i<N;i++)
	{
		for (j = 0;j<N;j++)
		{
			for (k = 0;k<N;k++)
			{
				Res1[i][j].real() += CompNumber[i][k].real()*A[k][j];
				// printf("%f  %f %f  \n",relRs[i][j],rel[i][k],A[i][k]);
				Res1[i][j].imag() += CompNumber[i][k].imag()*A[k][j];
			}
			//printf("%f  ",relRs[i][j]);
			//relRs2[i][j]/=M_S;
			//imRs2[i][j]/=M_S;
		}
	}


	for (i = 0;i<N;i++)
	{
		for (j = 0;j<N;j++)
		{
			for (k = 0;k<N;k++)
			{
				Res2[i][j] += Res1[i][k] * CompNumber[k][j];
				Res2[i][j].real() /= N;
				Res2[i][j].imag() /= N;

			}

		}
	}





	///memory free..........
	for (i = 0;i<N;i++)
	{
		free(CompNumber[i]);
	}
	free(CompNumber);
	for (i = 0;i<N;i++)
	{
		free(Res1[i]);
	}
	free(Res1);



}