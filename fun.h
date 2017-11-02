#pragma once

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

void meshgrid(double *x, double *y)
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