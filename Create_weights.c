#include <stdio.h>
#include <stdlib.h>
#include <time.h>


float rand01()//number between 0,1
{
    return (float)rand()/RAND_MAX;
}

float randm()//this givs me a number btween -2,2
{
   float stat =  rand01() - 0.5;
   return stat;
}


int main()
{
    srand(time(NULL));
    //create output text file with random weights and biases
   FILE *other;
   other = fopen("more11.txt","w");
   int array[14];
   int j,k;
    for(k=0;k<3;k++)
    {
        fprintf(other,"%f \n",randm());
    }

    fclose(other);
    return 0;
}
