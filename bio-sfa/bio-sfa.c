#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pbPlots.h"
#include "supportLib.h"
#include <time.h>
#include "data.h"

#define T 100000

double cal_time [100];


int k = 14;


int num_epochs = 50;
long double lr_regulator = 1e5;
long double Reg;
long double eta_w = 2e-4;
long double eta_m = 2e-4;
long double eta_w_ ;
long double eta_m_ ;
int outputdim = 1;


double MinW[1][1] ; /* Identity Matrix with output dim 1 */



double W[1][14] = /*random normal*/
    {
        {0.12573022, 0.13210486, 0.64042265, 0.10490012, 0.53566937,
            0.36159505, 1.30400005, 0.94708096, 0.70373524, 1.26542147,
            0.62327446, 0.04132598, 2.32503077, 0.21879166}};




//  -- some storage arrays to reduce # of allocations

double xt[14][1];     //np.zeros_like(avg)
double xt_old[14][1]; //np.zeros_like(xt_old)
double zt[14][1];     //np.zeros_like(zt)


int t_total = 1;
double W_Zt[1][1];
double y_bar[1][1];
double zt_T[1][14];
double yzt[1][14];
double Wxt[1][1];
double xt_T[1][14];
double WxxT[1][14];
double y_[1][1];
double y_y_T[1][1];
double y_Ty_[1][1];

int main(void)
{
    
    /**
     * @brief Bio-SFA implementation
     * Fit an online Bio-SFA model

     * To extract the learned slow features from new data:
        y = Minv @ W @ (x - avg) 
     *      
     * Parameters:
     * 
     *  X : Data to train the model on. Should have shape (T, n),
            where n is the input dimension and T is the number
            of samples.
        out_dim : int
            Output dimensions of network.
        eta_w : float
            Learning rate for W matrix  
        lr_regulator : float
            Controls learning rate decay, which will follow
            lr_regulator / (t + lr_regulator)
        num_epochs : int
            Number of runs through the training data
        history_length : int
            This function keeps a history of Minv and W. These
            are recorded
        colvar : bool
            If your data is T x n_features, keep this True. But if
            rows correspond to variables, i.e. the data is n_features x T,
        
        -----

        Returns :
            Minv, W, avg, history :
                Minv is the inverse of M, the matrix of lateral inhibitory
                weights, and W is the matrix of feedforward weights. avg is
                the online-learned mean vector.
                history stores a record of the learning. it is a tuple
                    (t, Minv_history, W_history) = history
                where t is an array of timesteps, and Minv_history and
                W_history are the weights saved at those timesteps. The
                timesteps will be log-spaced for better plotting on log-x
                plots.
                
        set to False.             
     */



    //1_  -- are we centering?

    //Already centered

    //2_  -- row variables? No : centered_X[14][T] -> centered_X_T[T][14]

    // static double centered_X_T[100000][14];
    // for (size_t i = 0; i < T; i++)
    // {
    //     for (size_t j = 0; j < 14; j++)
    //     {
    //         centered_X_T[i][j] = 0;
    //     }
    // }

    // for (size_t i = 0; i < 14; i++)
    // {
    //     for (size_t j = 0; j < T; j++)
    //     {
    //         centered_X_T[j][i] = centered_X[i][j];
    //     }
    // }



// -- model initialization

    
    for (size_t i = 0; i < outputdim; i++)
    {
        for (size_t j = 0; j < outputdim; j++)
        {
            if (i == j) MinW[i][j] = 1;
            else MinW[i][j] = 0;
            
        }
        
    }
    





    // double W [1][14];
    // for (size_t i = 0; i < 14; i++)
    // {
    //     W[0][i] = sqrt(log(( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. )) * -2) * cos(( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. )*2*3.14);
    // }

    // for (size_t i = 0; i < 14; i++)
    // {
    //     W[0][i] = W[0][i] / sqrt(14);
    // }







    for (size_t i = 0; i < 14; i++)
    {
        xt[i][0] = 0;
        xt_old[i][0] = 0;
        zt[i][0] = 0;
    }

//  -- training loop


    clock_t t;
    
    t = clock();
    size_t j = 0;
    for (j; j < 1000; j++)
    {

        
        for (size_t k = 0; k < 14; k++)
        {
            xt[k][0] = centered_X_T[j][k];
        }

        

        
// LR schedule
        Reg = lr_regulator / (lr_regulator + j);
        eta_w_ = Reg * eta_w;
        eta_m_ = Reg * eta_m;
//  online centering of inputs
// already been centered

        for (size_t i = 0; i < 14; i++)
        {
            zt[i][0] = xt[i][0];
        }
       
        for (size_t i = 0; i < 14; i++)
        {
            zt[i][0] += xt_old[i][0];
        }

        for (size_t i = 0; i < 14; i++)
        {
            xt_old[i][0] = xt[i][0];
        }

    
        for (size_t i = 0; i < outputdim; i++)
        {
            for (size_t jj = 0; jj < outputdim; jj++)
            {
                W_Zt[i][jj] = 0;
            }
            
        }

        for (size_t k = 0; k < 14; k++)
        {
            W_Zt[0][0] += W[0][k] * zt[k][0];
        }

        y_bar[0][0] = MinW[0][0] * W_Zt[0][0];


        for (size_t i = 0; i < 14; i++)
        {
            zt_T[0][i] = zt[i][0];
        }  


        for (size_t k = 0; k < 14; k++)
        {
            yzt[0][k] = y_bar[0][0] * zt_T[0][k];
        }



        Wxt[0][0] = 0;
        for (size_t k = 0; k < 14; k++)
        {
            Wxt[0][0] += W[0][k] * xt[k][0];
        }

        
        for (size_t i = 0; i < 14; i++)
        {
            xt_T[0][i] = xt[i][0];
        }


        for (size_t k = 0; k < 14; k++)
        {
            WxxT[0][k] = Wxt[0][0] * xt_T[0][k];
        }



        for (size_t i = 0; i < 14; i++)
        {
            W[0][i] += (yzt[0][i] - WxxT[0][i]) * eta_w_;
            
        }

        MinW[0][0] /= (1 - eta_m_);

        
        y_[0][0] = MinW[0][0] * y_bar[0][0];
        
        y_y_T[0][0] = y_[0][0] * y_[0][0];
        
        y_Ty_[0][0] = y_bar[0][0] * y_[0][0];

        MinW[0][0] -= ((eta_m_) / (1.0 + (eta_m_ * y_Ty_[0][0]))) * y_y_T[0][0];

        
    }
        t = clock() - t;

    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    

   
    for (size_t i = 0; i < 14; i++)
    {
        printf("W %f - \n" , W[0][i]);
    }
    printf("----------------\nM %f - \n" , MinW[0][0]);


    printf("Took %f seconds to execute\n" , time_taken);

    return 0;
}