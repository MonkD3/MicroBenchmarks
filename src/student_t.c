#include <math.h>
#include "include/student_t.h"

/*
 * Integrate the value of t=1-@pval quantile of the Student's T distribution
 * with @dof degrees of freedom
 *
 * NOTE: if dof > 3510 then an overflow happens
 */
double t_k_gamma(const double pval, const double dof){
    const double dx = 1e-5; // Integration discretization
    const double target = 1.0 - 0.5*pval; // Target for the integration
    const double k = dof;

    double t = 0.0; // Will hold the value : P(T <= t) = target

    // Ratio of gamma functions
    const double r = (double) (1.0/sqrt(k*M_PI)) * tgammal((long double) 0.5*(k+1.0))/tgammal( (long double) 0.5*k);

    // Cumulative density function of Student's T distribution at t=0.0
    double integral = 0.5;

    // ===== Integrate using Simpson's rule ======
    double eval_a = 1.0;// Evaluation at the start of quadrature interval
    double eval_b; // Evaluation at the end of quadrature interval
                   
    while (integral <= target) {
        eval_b = pow(1.0 + (t+dx)*(t+dx)/k, -0.5*(k+1.0)); 
        integral += r * (dx / 6.0) * (
                 eval_a
               + 4.0 * pow(1.0 + (t+0.5*dx)*(t+0.5*dx)/k, -0.5*(k+1.0)) 
               + eval_b
            );
        t += dx;
        eval_a = eval_b;
    }

    return t;
}
