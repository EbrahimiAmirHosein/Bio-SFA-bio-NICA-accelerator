#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void axpy(int n, double a, double x[], double y[])
{
    for (int i = 0; i < n; i++)
    {
        y[i] += a * x[i];
    }
}

double dot(int n, double x[], double y[])
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
        result += x[i] * y[i];
    }
    return result;
}

void scal(int n, double a, double x[])
{
    for (int i = 0; i < n; i++)
    {
        x[i] *= a;
    }
}

/*
 * Solve a * x = b, where a is upper triangular.
 * The solution is written into b.
 */
void triangular_solve(int n, double a[], double b[])
{
    for (int k = n - 1; k >= 0; k--)
    {
        b[k] /= a[k + k * n];
        axpy(k, -b[k], &a[k * n], b);
    }
}

/*
 * Solve transpose(a) * x = b, where a is upper triangular.
 * The solution is written into b.
 */
void triangular_solve_transpose(int n, double a[], double b[])
{
    for (int k = 0; k < n; k++)
    {
        b[k] -= dot(k, &a[k * n], b);
        b[k] /= a[k + k * n];
    }
}

/*
 * Invert a, where a is upper triangular.
 * The inverse is written into a.
 */
void triangular_invert(int n, double a[])
{
    for (int k = 0; k < n; k++)
    {
        a[k + k * n] = 1.0 / a[k + k * n];
        scal(k, -a[k + k * n], &a[k * n]);

        for (int j = k + 1; j < n; j++)
        {
            axpy(k, a[k + j * n], &a[k * n], &a[j * n]);
            a[k + j * n] *= a[k + k * n];
        }
    }
}

/*
 * Find the upper triangular matrix r such that a = transpose(r) * r, where a is positive definite.
 * The result is written into the upper triangle of a.
 * Returns: 0 if successful;
 *          j>0 if the leading jth minor of a is not positive definite.
 */
int cholesky(int n, double a[])
{
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < j; k++)
        {
            a[k + j * n] =
                (a[k + j * n] - dot(k, &a[k * n], &a[j * n])) / a[k + k * n];
        }

        double s = a[j + j * n] - dot(j, &a[j * n], &a[j * n]);
        if (s <= 0.0)
        {
            return j + 1;
        }

        a[j + j * n] = sqrt(s);
    }

    return 0;
}

double calculate_vsmall()
{
    double vsmall = 1e-60;
    do
    {
        vsmall += vsmall;
    } while ((vsmall * .1 + 1.) <= 1. || (vsmall * .2 + 1.) <= 1.);
    return vsmall;
}

#define n 3
#define q n
#define meq 0
#define factorized 0

/**
 * @brief 
 * Minimize 1/2 x.T G x - av.T x Subject to C.T x >= b
 * 

 * @param G input 
 * @param av input
 * @param xv inout ->   solution x to the minimisation problem
 * 
 * @param C is specialized hardcoded identity matrix (3x3)
 * @param b is specialized hardcoded zero matrix (3x1)
 * @return - automaticly updated xv solution 
 */
int solve_qp(double G[n * n], double av[n],
             double xv[n])
{
    #pragma HLS pipeline II=1
    // int factorized = 0 ;
    // int n = 3;
    // int q = n;
    // int meq = 0;
    //----------------------
    double C[9];
    C[0] = 1;
    C[1] = 0;
    C[2] = 0;
    C[3] = 0;
    C[4] = 1;
    C[5] = 0;
    C[6] = 0;
    C[7] = 0;
    C[8] = 1;
    //----------------------
    double lagr[3];
    lagr[0] = 0;
    lagr[1] = 0;
    lagr[2] = 0;
    //----------------------
    double obj = 0;
    //----------------------
    double bv[3];
    bv[0] = 0;
    bv[1] = 0;
    bv[2] = 0;
    //----------------------
    int iact[3];
    iact[0] = 0;
    iact[1] = 0;
    iact[2] = 0;
    //----------------------
    int iter[2];
    iter[0] = 0;
    iter[1] = 0;
    //----------------------
    int nact = 0;
    //----------------------
    double work[24];
    for (size_t i = 0; i < 24; i++)
    {
        work[i] = 0;
    }
    //----------------------

    double vsmall = calculate_vsmall();

    int pIterFull = iter[0];
    int pIterPartial = iter[1];
    int r = n <= q ? n : q;
    double *dv = work;
    double *zv = dv + n;
    double *rv = zv + n;
    double *uv = rv + r;
    double *R = uv + r;
    double *sv = R + r * (r + 1) / 2;
    double *nbv = sv + q;
    int work_length = n + n + r + r + r * (r + 1) / 2 + q + q;

    for (int i = 0; i < work_length; i++)
    {
        work[i] = 0.;
    }

    for (int i = 0; i < q; i++)
    {
        iact[i] = 0;
        lagr[i] = 0.;
    }

    // Initialisation. We want:
    // - xv and av to contain G^-1 a, the unconstrained minimum;
    // - J to contain L^-T, the inverse of the upper triangular Cholesky factor of G.

    for (int i = 0; i < n; i++)
    {
        xv[i] = av[i];
    }

    if (!factorized)
    {
        if (cholesky(n, G) != 0)
        { // now the upper triangle of G contains L^T
            return 2;
        }
        triangular_solve_transpose(n, G, xv); // now xv contains L^-1 a
        triangular_solve(n, G, xv);           // now xv contains L^-T L^-1 a = G^-1 a
        triangular_invert(n, G);              // now G contains L^-T
    }

    double *J = G;

    // Set the lower triangle of J to zero.

    for (int j = 0; j < n; j++)
    {
        for (int i = j + 1; i < n; i++)
        {
            J[i + j * n] = 0.;
        }
    }

    // Calculate the objective value at the unconstrained minimum.

    obj = -dot(n, av, xv) / 2.;

    // Store the unconstrained minimum in av for return.

    for (int i = 0; i < n; i++)
    {
        av[i] = xv[i];
    }

    // Calculate the norm of each column of the C matrix.
    // This will be used in our pivoting rule.

    for (int i = 0; i < q; i++)
    {
        nbv[i] = sqrt(dot(n, &C[i * n], &C[i * n]));
    }

    nact = 0;
    pIterPartial = 0;

    for (pIterFull = 1;; (pIterFull)++)
    {

        // Calculate the slack variables C^T xv - bv and store the result in sv.

        for (int i = 0; i < q; i++)
        {
            double temp = dot(n, xv, &C[i * n]) - bv[i];
            sv[i] = fabs(temp) < vsmall ? 0. : temp;
        }
        // Force the slack variables to zero for constraints in the active set,
        // as a safeguard against rounding errors.
        for (int i = 0; i < nact; i++)
        {
            sv[iact[i] - 1] = 0.;
        }

        // Choose a violated constraint to add to the active set.
        // We choose the constraint with the largest violation.
        // The index of the constraint to add is stored in iadd.

        int iadd = 0;
        double max_violation = 0.;
        for (int i = 0; i < q; i++)
        {
            if (sv[i] < -max_violation * nbv[i])
            {
                iadd = i + 1;
                max_violation = -sv[i] / nbv[i];
            }
            else if (i < meq && sv[i] > max_violation * nbv[i])
            {
                iadd = i + 1;
                max_violation = sv[i] / nbv[i];
            }
        }

        if (iadd == 0)
        {
            // All constraints are satisfied. We are at the optimum.

            for (int i = 0; i < nact; i++)
            {
                lagr[iact[i] - 1] = uv[i];
            }
            return 0;
        }

        double slack = sv[iadd - 1];
        double reverse_step = slack > 0.;
        double u = 0;

        for (;; (pIterPartial)++)
        {

            // Set dv = J^T n, where n is the column of C corresponding to the constraint
            // that we are adding to the active set.

            for (int i = 0; i < n; i++)
            {
                dv[i] = dot(n, &J[i * n], &C[(iadd - 1) * n]);
            }

            // Set zv = J_2 d_2. This is the step direction for the primal variable xv.

            for (int i = 0; i < n; i++)
            {
                zv[i] = 0.;
            }
            for (int j = nact; j < n; j++)
            {
                axpy(n, dv[j], &J[j * n], zv);
            }

            // Set rv = R^-1 d_1. This is (the negative of) the step direction for the dual variable uv.

            for (int i = 0; i < nact; i++)
            {
                rv[i] = dv[i];
            }
            for (int i = nact - 1; i >= 0; i--)
            {
                rv[i] /= R[(i + 1) * (i + 2) / 2 - 1];
                axpy(i, -rv[i], &R[i * (i + 1) / 2], rv);
            }

            // Find the largest step length t1 before dual feasibility is violated.
            // Store in idel the index of the constraint to remove from the active set, if we get that far.

            int t1inf = 1, idel;
            double t1;
            for (int i = 0; i < nact; i++)
            {
                if (iact[i] > meq && ((!reverse_step && rv[i] > 0.) || (reverse_step && rv[i] < 0.)))
                {
                    double temp = uv[i] / fabs(rv[i]);
                    if (t1inf || temp < t1)
                    {
                        t1inf = 0;
                        t1 = temp;
                        idel = i + 1;
                    }
                }
            }

            // Find the step length t2 to bring the slack variable to zero for the constraint we are adding to the active set.
            // Store in ztn the rate at which the slack variable is increased. This is used to update the objective value below.

            int t2inf = fabs(dot(n, zv, zv)) <= vsmall;
            double t2, ztn;
            if (!t2inf)
            {
                ztn = dot(n, zv, &C[(iadd - 1) * n]);
                t2 = fabs(slack) / ztn;
            }

            if (t1inf && t2inf)
            {
                // Can step infinitely far; dual problem is unbounded and primal problem is infeasible.
                return 1;
            }

            // We will take a full step if t2 <= t1.
            int full_step = !t2inf && (t1inf || t1 >= t2);
            double step_length = full_step ? t2 : t1;
            double step = reverse_step ? -step_length : step_length;

            if (!t2inf)
            {
                // Update primal variable
                axpy(n, step, zv, xv);

                // Update objective value
                obj += step * ztn * (step / 2. + u);
            }

            // Update dual variable
            axpy(nact, -step, rv, uv);
            u += step;

            if (full_step)
            {
                break;
            }

            // Remove constraint idel from the active set.

            // qr_delete(n, nact, idel, J, R);
            for (int i = idel; i < nact; i++)
            {
                uv[i - 1] = uv[i];
                iact[i - 1] = iact[i];
            }
            uv[nact - 1] = 0.;
            iact[nact - 1] = 0;
            --(nact);

            if (!t2inf)
            {
                // We took a step in primal space, but only took a partial step.
                // So we need to update the slack variable that we are currently bringing to zero.
                slack = dot(n, xv, &C[(iadd - 1) * n]) - bv[iadd - 1];
            }
        }

        // Add constraint iadd to the active set.

        ++(nact);
        uv[nact - 1] = u;
        iact[nact - 1] = iadd;
        // qr_insert(n, nact, dv, J, R);
    }
}
