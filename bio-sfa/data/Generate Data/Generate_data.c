#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pbPlots.h"
#include "supportLib.h"
#include <time.h>

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    srand ( time(NULL) );
    return min + (rand() / div);
}

double sinw(double x)
{
    int i = 1;
    double cur = x;
    double acc = 1;
    double fact = 1;
    double pow = x;
    while (fabs(acc) > .00000001 && i < 100)
    {
        fact *= ((2 * i) * (2 * i + 1));
        pow *= -1 * x * x;
        acc = pow / fact;
        cur += acc;
        i++;
    }
    return cur;
}
int main(void)
{
    int i, j;
    // time domain length
    int T = 100000;
    // window size
    int m = 4;
    // monomial expansion order
    int order = 2;

    
    // sum_sine
    int Ts = T + m - 1;
    int n_sines = 6;
    int period = 100;
    static double domain[100000];
    double iter = 0;

    for (int i = 0; i < Ts; i++)
    {
        domain[i] = (iter) / period;
        iter++;
    }

    double rates[n_sines];
    for (size_t i = 0; i < n_sines; i++)
    {
        rates[i] = randfrom(0.5, 1.25);
    }
    double rates_2d[n_sines][1];
    for (size_t i = 0; i < n_sines; i++)
    {
        rates_2d[i][1] = rates[i];
    }

    double offset[n_sines];
    for (size_t i = 0; i < n_sines; i++)
    {
        offset[i] = randfrom(1.0, 2 * period);
    }

    double amplitudes[n_sines];
    double sum_amp = 0;
    for (size_t i = 0; i < n_sines; i++)
    {
        amplitudes[i] = randfrom(0.1, 2.0);
        sum_amp += amplitudes[i];
    }
    for (size_t i = 0; i < n_sines; i++)
    {
        amplitudes[i] /= sum_amp;
    }

    double amplitudes_2d[n_sines][1];
    for (size_t i = 0; i < n_sines; i++)
    {
        amplitudes_2d[i][1] = amplitudes[i];
    }

    // creating out product of domain and offset
    for (size_t i = 0; i < n_sines; i++)
    {
        domain[i] = offset[i] * domain[i];
        domain[i] = offset[i] + domain[i];
    }
    static double outProduct[6][100003]; //[numsin][Ts]
    for (size_t i = 0; i < n_sines; i++)
    {
        for (size_t j = 0; j < Ts; j++)
        {
            outProduct[i][j] = domain[j];
        }
    }

    static double SinOutPxRate[6][100003];

    for (size_t y = 0; y < Ts; y++)
    {
        for (size_t x = 0; x < n_sines; x++)
        {
            SinOutPxRate[x][y] = sin(rates_2d[x][0] * outProduct[x][y]);
        }
    }

    static double SinxAmp[6][100003];
    for (size_t y = 0; y < Ts; y++)
    {
        for (size_t x = 0; x < n_sines; x++)
        {
            SinxAmp[x][y] = amplitudes_2d[x][0] * SinOutPxRate[x][y];
        }
    }

    static double sumSinxAmp[1][100003];
    for (size_t i = 0; i < Ts; i++)
    {
        sumSinxAmp[0][i] = 0;
    }

    for (size_t i = 0; i < Ts; i++)
    {
        for (size_t j = 0; j < n_sines; j++)
        {
            sumSinxAmp[0][i] += SinxAmp[j][i];
            sumSinxAmp[0][i] /= 1.25;
        }
    }

    //logisticmap

    static double Series[1][100003];
    for (size_t i = 0; i < Ts; i++)
    {
        Series[0][i] = 0;
    }

    double S_0 = 0.6;

    for (size_t jj = 0; jj < Ts; jj++)
    {
        Series[0][jj] = ((sumSinxAmp[0][jj] * 0.35) + 3.6) * S_0 * (1 - S_0);
        S_0 = Series[0][jj];
    }

    static double signal[100000][4];
    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            signal[i][j] = 0;
        }
    }

    int h = 0;
    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = i; j < m + i; j++)
        {
            signal[i][h] = Series[0][j];
            h++;
        }
        h = 0;
    }

    double mean_signal_Ax0[1][4];
    for (size_t i = 0; i < 4; i++)
    {
        mean_signal_Ax0[0][i] = 0;
    }
    double centered_signal[T][4];
    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            centered_signal[i][j] = 0;
        }
    }

    for (size_t k = 0; k < 4; k++)
    {
        for (size_t i = 0; i < T; i++)
        {
            mean_signal_Ax0[0][k] += signal[i][k];
        }
        mean_signal_Ax0[0][k] /= T;
    }

    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            centered_signal[i][j] = signal[i][j] - mean_signal_Ax0[0][j];
        }
    }

    static double signal_T[4][100000]; //signal [T][4]

    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            signal_T[j][i] = centered_signal[i][j];
        }
    }

    // compute Cov(Signal.T) = (singla.T - mean.axis1) * (singla.T - mean.axis1).T / (T-1)

    //(singla.T - mean.axis1)

    double mean_signalT_Ax1[4][1];
    for (size_t i = 0; i < 4; i++)
    {
        mean_signalT_Ax1[i][0] = 0;
    }
    //mean.axis1
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            mean_signalT_Ax1[i][0] += signal_T[i][j];
        }
        mean_signalT_Ax1[i][0] /= T;
    }

    static double signal_T_centered[4][100000];
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            signal_T_centered[i][j] = 0;
        }
    }
    // (singla.T - mean.axis1)
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            signal_T_centered[i][j] = signal_T[i][j] - mean_signalT_Ax1[i][0];
        }
    }

    // (singla.T - mean.axis1).T
    static double signalT_centered_T[100000][4];
    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            signalT_centered_T[i][j] = 0;
        }
    }
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            signalT_centered_T[j][i] = signal_T_centered[i][j];
        }
    }

    /**
     * @brief 
     *      (singla.T - mean.axis1) * (singla.T - mean.axis1).T ->
     
            (singla.T - mean.axis1) = (4,100000)
            (singla.T - mean.axis1).T = (100000,4)
            outcome = (4,4)
     */

    double Cov_signal_T[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Cov_signal_T[i][j] = 0;
            for (int k = 0; k < T; k++)
            {
                Cov_signal_T[i][j] += signal_T_centered[i][k] * signalT_centered_T[k][j];
            }
            Cov_signal_T[i][j] /= (T - 1);
        }
    }
    /**
     * @brief Convert Cov to `la.inv(la.sqrtm(np.cov(signal.T)))` in python 
     *          
     *          Available in checkbook
     * 
     */
    // FILE *f = fopen("Cov.txt", "wb");
    // for (size_t i = 0; i < 4; i++)
    // {
    //     for (size_t j = 0; j < 4; j++)
    //     {
    //     fprintf(f, "%f%s",Cov_signal_T[i][j],(","));
    //     }
    // }

    FILE *invcov = fopen("inv_sqrtm.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    static double invCov_linear[16];
    double invCov[4][4];
    i = 0;
    while ((read = getline(&line, &len, invcov)) != -1)
    {
        invCov_linear[i] = atof(line);
        i += 1;
    }
    j = 0;
    int c = 0;
    for (size_t i = 0; i < 16; i++)
    {
        invCov[j][c] = invCov_linear[i];
        c++;
        if (i + 1 % 4 == 0)
        {
            j += 1;
            c = 0;
        }
    }

    // now computing signal(10,0000 , 4) * invCov (4 ,4) -> invConvSig [T][4]

    static double invConvSig[100000][4];
    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            invConvSig[i][j] = 0;
        }
    }

    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            for (size_t k = 0; k < 4; k++)
            {
                invConvSig[i][j] += centered_signal[i][k] * invCov[k][j];
            }
        }
    }

    //Computing invConvSig trasnpose
    static double invConvSig_T[4][100000];
    for (size_t i = 0; i < T; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            invConvSig_T[j][i] = invConvSig[i][j];
        }
    }

    int k = 14;
    static double X[14][100000];
    for (size_t i = 0; i < k; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            X[i][j] = 0;
        }
    }

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            X[i][j] = invConvSig_T[i][j];
        }
    }
    for (size_t t = 0; t < T; t++)
    {
        X[m][t] = signal[t][0] * signal[t][0];
        X[m + 1][t] = signal[t][1] * signal[t][0];
        X[m + 2][t] = signal[t][1] * signal[t][1];
        X[m + 3][t] = signal[t][2] * signal[t][0];
        X[m + 4][t] = signal[t][2] * signal[t][1];
        X[m + 5][t] = signal[t][2] * signal[t][2];
        X[m + 6][t] = signal[t][3] * signal[t][0];
        X[m + 7][t] = signal[t][3] * signal[t][1];
        X[m + 8][t] = signal[t][3] * signal[t][2];
        X[m + 9][t] = signal[t][3] * signal[t][3];
    }
    

    // saving x to check if its okay in check-book
    FILE *f1 = fopen("Out/X.txt", "wb");
    for (size_t i = 0; i < k; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
        fprintf(f1, "%f%s",X[i][j],(","));
        }
    } 


    double X_mean[k][1];
    for (size_t i = 0; i < k; i++)
    {
        X_mean[i][0] = 0;
    }

    //mean.axis1
    for (size_t i = 0; i < k; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            X_mean[i][0] += abs(X[i][j]);
        }
        X_mean[i][0] /= T;
    }

    static double centered_X[14][100000];

    for (size_t i = 0; i < k; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            centered_X[i][j] = 0;
        }
    }

    // (X - X.mean.axis1)
    for (size_t i = 0; i < 14; i++)
    {
        for (size_t j = 0; j < T; j++)
        {
            centered_X[i][j] = X[i][j] - X_mean[i][0];
        }
    }
    FILE *f = fopen("Out/Centered_X.txt", "wb");
    for (size_t i = 0; i < 14; i++)
    {
        for (size_t j = 0; j < 100000; j++)
        {
        fprintf(f, "%f%s",centered_X[i][j],(",\n"));
        }
    }
    return 0;
    }