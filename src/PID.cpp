#include "PID.h"
#include <iostream>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
}

void PID::UpdateError(double cte) {
  d_error = cte-p_error;
  p_error = cte;
  i_error += cte;
}

double PID::TotalError() {
  double error = -Kp*p_error - Kd*d_error - Ki*i_error;
  return error;
}

double PID::runTwiddle(double cte) {
  error += cte*cte;
  if (n==0) {
    Init(p[0],p[1],p[2]);
  }
  UpdateError(cte);
  double steer_value = TotalError();
  n++;

  if (startUpdate) {
    startUpdate = false;
    itParam++;
    if (itParam>2) itParam=0;
    p[itParam] += dp[itParam];
    n = 0;
    error = 0;
    idRun = 1; 
  }

  if (n>nMax) {
    error = error/nMax;
    n = 0;
    //std::cout << error << ":" <<  p[0] << ", " << p[1] << ", " << p[2] <<  best_error << std::endl;
    if (idRun ==1) {
      if (error < best_error) {
        best_error = error;
        dp[itParam] *= 1.1;
        //std::cout << "error 1 : " << error << ", best error: " <<  best_error << std::endl;
        //std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
        //std::cout << dp[0] << ", " << dp[1] << ", " << dp[2] << std::endl;
        startUpdate = true;
      } else {
        p[itParam] -= 2*dp[itParam];
        // perform a second run
        idRun = 2;
        error = 0;
        //std::cout << "else1 : " << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
        //std::cout << dp[0] << ", " << dp[1] << ", " << dp[2] << std::endl;
      }
    } else {
      if (idRun == 2) {
        startUpdate = true; // once we finish the second run, it is time to try a new set of parameters 'p'
        if (error < best_error) {
          best_error = error;
          dp[itParam] *= 1.1;
          //std::cout << "error: " << error << ", 2" <<  "best error: " <<  best_error << std::endl;
          //std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
          //std::cout << dp[0] << ", " << dp[1] << ", " << dp[2] << std::endl;
        } else {
          p[itParam] += dp[itParam];
          dp[itParam] *= 0.9;
          //std::cout << "else2: " << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
          //std::cout << dp[0] << ", " << dp[1] << ", " << dp[2] << std::endl;
        }
      }
    }
    error = 0;
  }

  double sum_dp = dp[0]+dp[1]+dp[2];
  if (sum_dp < tolerance) {
    std::cout << "Best p[0] p[1] p[2]: " << p[0] << p[1] << p[2] << " ";
  }


  return steer_value;
}
  

  
