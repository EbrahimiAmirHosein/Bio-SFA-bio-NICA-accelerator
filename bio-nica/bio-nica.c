#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#include "solve_QP.h"

#include "data_(10000).h"

// #include "data_(100000).h"
// #include "data_(20000).h"
// #include "data_(50000).h"
// #include "data_(80000).h"

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define N 3

int main()
{
    srand(time(NULL));

    //===============================================
   

    int samples = 10000;
    int trials = 1;
    int idx[10000];

    int n_rand = 0;

    const int x_dim = 3;
    const int s_dim = 3;
    const int n_dim = 3;

    double decay = 0;
    double eta;
    double step = 0;

    double xt[3][1];
    double x_bar[x_dim][1];
    double y_bar[s_dim][1];
    double n_bar[n_dim][1];

    double y[3];
    double W_xt[3];
    double MT_y[3][1];
    double M[3][3];
    double M_T[n_dim][s_dim];
    double W[s_dim][n_dim];

    double outer1[3];
    double outer2[3];
    double outer3[3];
    double res_outer[3][3];
    double resp_outer[3][3];
    double M_MT[3][3];
    double G[9];
    //===============================================


    for (size_t i = 0; i < 3; i++)
    {
         x_bar[i][0] = 0;
        y_bar[i][0] = 0;
        n_bar[i][0] = 0;
    }
    

    for (int trial = 0; trial < trials; trial++)
    {
        for (int i = 0; i < samples; i++)
        {
            n_rand = rand() % 10000 + 1;
            idx[i] = n_rand;
        }

        eta = 0.01;
        decay = 0.001;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                M[i][j] = 0;
                M_T[i][j] = 0;
                W[i][j] = 0;
                MT_y[i][j] = 0;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == j)
                {
                    M[i][j] = 1.0;
                }
            }
        }

        W[0][0] = 0.94441678;
        W[0][1] =  0.2629107;
        W[0][2] =  -0.19736997;
        W[1][0] = 0.15817837;
        W[1][1] = -0.88970283;
        W[1][2] = -0.42826216;
        W[2][0] = 0.28819532;
        W[2][1] =  -0.37323831;
        W[2][2] = 0.88183707;


        clock_t t;
        t = clock();

        for (int i_sample = 0; i_sample < 10000; i_sample++)
        {           


            for (size_t z = 0; z < 3; z++)
            { 

                xt[z][0] = New_X[i_sample][z];
               
                W_xt[z] = 0;
            }

            for (int i = 0; i < 3; i++)
            {
                for (int k = 0; k < 3; k++)
                {
                    W_xt[i] += W[i][k] * xt[k][0];
                    M_T[i][k] = M[k][i];
                    M_MT[i][k] = 0;
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        M_MT[i][j] += M[i][k] * M_T[k][j];
                        
                    }
                }
            }

            

            
    
            G[0] = M_MT[0][0];
            G[1] = M_MT[0][1];
            G[2] = M_MT[0][2];
            G[3] = M_MT[1][0];
            G[4] = M_MT[1][1];
            G[5] = M_MT[1][2];
            G[6] = M_MT[2][0];
            G[7] = M_MT[2][1];
            G[8] = M_MT[2][2];

            int stat = solve_qp(G, W_xt, y);       


            MT_y[0][0] = 0;
            MT_y[1][0] = 0;
            MT_y[2][0] = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int k = 0; k < 3; k++)
                {
                    MT_y[i][0] += M_T[i][k] * y[k];
                }
            }


            for (size_t i = 0; i < 3; i++)
            {
                x_bar[i][0] += (xt[i][0] - x_bar[i][0]) / (i_sample + 1);
                y_bar[i][0] += (y[i] - y_bar[i][0]) / min(i_sample + 1, 100);
                n_bar[i][0] += (MT_y[i][0] - n_bar[i][0]) / min(i_sample + 1, 100);
            }
            step = eta / (1 + decay * i_sample);

            for (size_t i = 0; i < 3; i++)
            {
                outer1[i] = y[i] - y_bar[i][0];
                outer2[i] = xt[i][0] - x_bar[i][0];
                outer3[i] = MT_y[i][0] - n_bar[i][0];
            }

            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                {
                    res_outer[i][j] = outer1[i] * outer2[j];
                    resp_outer[i][j] = outer1[i] * outer3[j];
                }
            }

            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                {   
                    W[i][j] += step * (res_outer[i][j] - W[i][j]);

                    M[i][j] += step * (resp_outer[i][j] - M[i][j]);
                }
            }


           

        }

        t = clock() - t ;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("M: \n");
        for (size_t i = 0; i < s_dim; i++)
        {   printf("\n");
            for (size_t j = 0; j < s_dim; j++)
            {
                printf(" %f " , M[i][j]);
            }
            
        }
        printf("\n");
        printf("W: \n");
        for (size_t i = 0; i < s_dim; i++)
        {   printf("\n");
            for (size_t j = 0; j < s_dim; j++)
            {
            printf(" %f  " , W[i][j]);
            }
            
        }
         printf("\n \n Took %f seconds to execute\n", time_taken);

                
    }

    return 0;
}
