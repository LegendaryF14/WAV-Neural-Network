//last try before i go insane

#include <stdio.h>
#include <time.h>
#include <math.h>//needs work check gender b
#include <stdlib.h>

#define SPEED 0.1
#define WEIGHT_FILE "more10.txt"
#define TRAIN_FILE "train.txt"
#define NUM_TRAIN 5
#define loop 1000
#define NUM_IN 3
#define NUM_HI 3
#define NUM_OU 2

float sigmoid(float input)
{
    float stat;
    stat = 1.0/(1.0 + exp(-input));
    return stat;
}

float node_delta(float target,float out)
{
    float node = target - out;
    node = -node;
    float buff = 1-out;
    buff = buff*out;
    node = node * buff;

    return node;
}

float update_out_w(float outp_o,float target, float weight, float outp_h )
{
    float buff;
    buff = node_delta(target,outp_o);
    buff = buff*outp_h;
    buff = buff*SPEED;
    weight = weight - buff;
    return weight;

}

float update_out_b(float outp_o,float target, float weight)
{
    float buff;
    buff = node_delta(target,outp_o);
    buff = buff*SPEED;
    weight = weight - buff;
    return weight;
}

float nodeh_delta(float target_o, float out_o,float w_o, float target_1,float out_1,float w_1,float out_h)
{
    float stat,buffer,hip;
    stat = node_delta(target_o,out_o);
    stat = stat*w_o;
    buffer = node_delta(target_1,out_1);
    buffer = buffer*w_1;
    stat = stat + buffer;
    hip = 1-out_h;
    hip = hip*out_h;
    hip = hip*stat;

    return hip;

}

float update_hidden_w(float target_o, float out_o,float w_o, float target_1,float out_1,float w_1,float out_h,float in,float w)
{
    float stat,buffer;
    stat = nodeh_delta(target_o,out_o,w_o,target_1,out_1,w_1, out_h);
    stat = stat*in;
    w = w -stat;

    return w;
}


float update_hidden_b(float target_o, float out_o,float w_o, float target_1,float out_1,float w_1,float out_h,float b)
{
    float stat,buffer;
    stat = nodeh_delta(target_o,out_o,w_o,target_1,out_1,w_1, out_h);
    b = b -stat;

    return b;
}


int main()
{

    float weigh_h[NUM_IN][NUM_HI];
    float weigh_o[NUM_HI][NUM_OU];
    float bias_h[NUM_HI];
    float bias_o[NUM_OU];

    float buffer;

    float net_h[NUM_HI];
    float net_o[NUM_OU];
    float out_h[NUM_HI];
    float out_o[NUM_OU];


    float Error;
    float target[NUM_TRAIN][NUM_OU];
    float inpu[NUM_TRAIN][NUM_IN];

    float updat_h[NUM_IN][NUM_HI];
    float updat_o[NUM_HI][NUM_OU];

    float updat_h_b[NUM_HI];
    float updat_o_b[NUM_OU];
    int f,g,h,l,n,o,t;


    FILE *other;
    other = fopen(WEIGHT_FILE,"r");
        for(f=0;f<NUM_HI;f++)
        {
            for(g=0;g<NUM_IN;g++)
            {
            fscanf(other,"%f",&weigh_h[g][f]);
            }
            fscanf(other,"%f",&bias_h[f]);
            printf("bias %f \t",bias_h[f]);
        }

        for(h=0;h<NUM_OU;h++)
        {
            for(l=0;l<NUM_HI;l++)
            {
            fscanf(other,"%f",&weigh_o[l][h]);
            }
            fscanf(other,"%f",&bias_o[l]);
             printf("weight %f\n",bias_o[l]);
        }



    FILE *thingy;
    thingy = fopen(TRAIN_FILE,"r");

      for(n=0;n<NUM_TRAIN;n++)
      {
        for(t=0;t<NUM_IN;t++)
        {
        fscanf(thingy,"%f",&inpu[n][t]);
        inpu[n][t] = inpu[n][t]*0.01;
        printf("%f\n",inpu[n][t]);

        }
        for(o=0;o<NUM_OU;o++)
        {
        fscanf(thingy,"%f",&target[n][o]);
        target[n][o] = target[n][o]*0.01;
        printf("%f\n",target[n][o]);
        }

      }

int p;
for(p=0;p<loop;p++)//runs epochs
{

int k,i,m,v,j,z,u,q,r,a,c,d,e;


for(k=0;k<NUM_TRAIN;k++)
{
    for(i=0;i<NUM_HI;i++)
    {
    net_h[i] = bias_h[i];
        for(j=0;j<NUM_IN;j++)
        {
        net_h[i] += weigh_h[j][i]*inpu[k][j];
        }

    out_h[i] = sigmoid(net_h[i]);
    }
    for(m=0;m<NUM_OU;m++)
    {
    net_o[m] = bias_o[m];
        for(v=0;v<NUM_HI;v++)
        {
            net_o[m] += weigh_o[v][m];
        }
    out_o[m] = sigmoid(net_o[m]);
    }

    Error  = out_o[0]-target[k][0];
    buffer = out_o[1]-target[k][1];
    printf("out %f %f\n",out_o[0], out_o[1]);
    Error = Error*Error;
    buffer = buffer*buffer;

    printf("Cost = %f\n\n",Error+buffer);

    //start backpropogation
    for(q=0;q<NUM_OU;q++)//change these m and v
    {
            for(r=0;r<NUM_HI;r++)
            {
            updat_o[r][q] = update_out_w(out_o[q],target[k][q],weigh_o[r][q],out_h[r]);
            }
            updat_o_b[q] = update_out_b(out_o[q],target[k][q],bias_o[q]);
    }


    for(u=0;u<NUM_HI;u++)
    {
        for(z=0;z<NUM_IN;z++)
        {
        updat_h[z][u] = update_hidden_w(target[k][0],out_o[0],weigh_o[u][0],target[k][1],out_o[1],weigh_o[u][1],out_h[u],inpu[k][z],weigh_h[z][u]);
        }
        updat_h_b[u] = update_hidden_b(target[k][0],out_o[0],weigh_o[u][0],target[k][1],out_o[1],weigh_o[u][1],out_h[u],bias_h[u]);
    }

//actually update weights
    for(a=0;a<NUM_OU;a++)//change these m and v
    {
            for(c=0;c<NUM_HI;c++)
            {
            weigh_o[c][a] = updat_o[c][a];
            }
           bias_o[a] = updat_o_b[a];
    }

     for(d=0;d<NUM_HI;d++)
    {
        for(e=0;e<NUM_IN;e++)
        {
        weigh_h[e][d] = updat_h[e][d];
        }
        bias_h[d] = updat_h_b[d];
    }

}
}

for(f=0;f<NUM_HI;f++)
        {
            for(g=0;g<NUM_IN;g++)
            {
            printf("%f\n",weigh_h[g][f]);
            }

            printf("%f \n",bias_h[f]);
        }

        for(h=0;h<NUM_OU;h++)
        {
            for(l=0;l<NUM_HI;l++)
            {
            printf("%f\n",weigh_o[l][h]);
            }
             printf("%f\n",bias_o[l]);
        }

    return 0;
}
