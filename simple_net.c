//2 node neural net

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_TRAIN 8
#define WEIGHT_FILE "more11.txt"
#define TRAIN_FILE "train.txt"
#define loo 100
#define SPEED 0.1

float node_delta(float target,float out)
{
    float stat,buffer;
    stat = target - out;
    stat = -1*stat;
    buffer = 1 - out;
    buffer = buffer * out;
    stat = stat *buffer;
    return stat;
}

//get sigmoid functionssss

float new_variable(float weight,float dcost)
{
    float stat;
    stat = dcost*0.1;//here is eta or speed
    weight = weight - stat;
    return weight;
}


float sigmoid(float inpu)//this is the sigmoid function
{
    float output;
    output = 1.0/(1.0+exp(-inpu));
    return output;
}

int randm()
{
    float stat;
    stat= (float)rand()/RAND_MAX;
    stat = stat*NUM_TRAIN;
    return stat;
}

int main()
{

    //parameters
    int k,j;
    float input[NUM_TRAIN][2];
    float bias;
    float weights[2];
    float net;
    float out;
    float dcdp,dpdz,dzdw1,dzdw2,dzdb,dcdw1,dcdw2,dcdb;

    float cost;
    float target[NUM_TRAIN];
    float update[3];
    float buff;


    FILE *weigh;
    weigh = fopen(WEIGHT_FILE,"r");
    fscanf(weigh,"%f",&weights[0]);
    fscanf(weigh,"%f",&weights[1]);
    fscanf(weigh,"%f",&bias);

    FILE *trainer;
    trainer = fopen(TRAIN_FILE,"r");
    for(j=0;j<NUM_TRAIN;j++)
    {
        fscanf(trainer,"%f",&input[j][0]);
        input[j][0]= input[j][0]*0.01;
        fscanf(trainer,"%f",&input[j][1]);
        input[j][1]= input[j][1]*0.01;
        fscanf(trainer,"%f",&target[j]);
        printf("trraget scan = %f",target[j]);

    }
int l,p;
for(l=0;l<loo;l++)
{

for(k=0;k<NUM_TRAIN;k++)
{
    p = randm();
    printf("Int p %d",p);

    net = bias;
    net+= weights[0]*input[p][0];
    net+= weights[1]*input[p][1];

    out = sigmoid(net);
    printf("out %f\n",out);

    cost = target[p] - out;
    cost = cost*cost;
    printf("Cost : %f\n",cost);


    dcdp = out - target[p];
    dcdp = dcdp*2;

    dpdz = 1 - out;
    dpdz = dpdz*out;

    dzdw1 = input[p][0];
    dzdw2 = input[p][1];
    dzdb = 1;

    dcdw1 = dcdp*dpdz*dzdw1;
    dcdw2 = dcdp*dpdz*dzdw2;
    dcdb = dcdp*dpdz*dzdb;

    weights[0] -= SPEED*dcdw1;
    weights[1] -= SPEED*dcdw2;
    bias -= SPEED*dcdb;



 /*   printf("Cost : %f\n",cost);*/

    //backpropgat
    /*buff = node_delta(target[p],out);
    printf("tagert %f\n",target[p]);

    update[0] = buff*input[p][0];
    update[1] = buff*input[p][1];
    update[2] = buff;//for bias

    //update weights
    weights[0] = new_variable(weights[0],update[0]);
    weights[1] = new_variable(weights[1],update[1]);
    bias = new_variable(bias,update[2]);
*/




}
}
    printf("New weights and bias: %f \n %f\n %f",weights[0],weights[1],bias);



    return 0;
}
