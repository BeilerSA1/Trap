//Samuel Beiler ~ COMP 322.A ~ Implementing Trapizoidal Integration
//Last Modified: 9/6/2018

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

//Input value, Stores the function being integrated, Returns function value at value x
double function(double x); 

//Input a bound, Function integrated for the solving of the definite integral, Returns definite integral at bound x 
double integratedFunction(double x);

//Input, lower bound, upper bound, and interval size, Calculates Trap. Integration of function, Returns integration
double trapIntegrate(double lowbound, double upbound,int interNum);

int main()
{
	double truSolution; //Stores true solution done via definite integration
	double trapSolution; //Stores solution from trapizoidal integration 

	//0.0 Header info
	printf("%s\n","Samuel Beiler ~ COMP322.A ~ Implementing Trapizoidal Integration");
	printf("%s\n%s\n\n","This process will run trapizoidal integration", "with varying step levels on a specified function.");
	
	//1.0 Table Creation
	printf("%10s%23s%23s\n", "# of Steps", "Integration", "Error");
	truSolution = integratedFunction(10) - integratedFunction(1);

	//2.0 Loops through interval sizes, solving Trap. Integration for each 
	//Runs and prints trap. integration starting with 64 intervals, 
	//doubles every run up through 2^29
	for(int i = 64; i <= 1 << 29; i= i*2)
	{
		trapSolution = trapIntegrate(1,10,i);
		printf("%10d%23.10e%23.10e\n",i, trapSolution, truSolution-trapSolution);//Output row
	}

	//3.0 Completion
	printf("%s\n","Program Complete");
	return 0;
}

double function(double x)
{
	return(exp(-0.1*x)*sin(5*x));//Returns function(x)
}

double integratedFunction(double x)
{
	double a = -0.1; //Filler variable to keep definite integral form
	double b = 5; //Filler variable to keep definite integral form
	return((exp(a*x)*(a*sin(b*x)-b*cos(b*x)))/(a*a+b*b));//Returns integrated function, Integration from Schaum's Mathematical Handbook
}

double trapIntegrate(double lowbound, double upbound,int interNum)
{
	double sum = 0;//Stores sum of area under curve
	double step = ((upbound-lowbound)/interNum);//Interval size
	for(double i = 1; i < interNum-1; i++)//Run through all intervals
	{
		sum += 2*function(lowbound+i*step);
	}
	sum+= (function(lowbound)+function(upbound));
	return sum*step/2.0;
}