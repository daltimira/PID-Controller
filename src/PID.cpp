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

  // for the twiddle
  /*p.push_back(0);
  p.push_back(0);
  p.push_back(0);*/
  p.push_back(Kp);
  p.push_back(Kd);
  p.push_back(Ki);

  dp.push_back(0.1);
  dp.push_back(0.1);
  dp.push_back(0.1);
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
  double sum_dp = dp[0]+dp[1]+dp[2];
  UpdateError(cte);
  double steer = -p[0]*p_error - p[1]*d_error - p[2]*i_error;
  std::cout <<  p[0] << ", " << p[1] << ", " << p[2] <<  std::endl;
  if (sum_dp > tolerance) {
    n++;

    if (startUpdate) {
      itParam++;
      if (itParam>2) itParam=0;
      p[itParam] += dp[itParam];
      n = 0;
      error = 0;
      idRun = 1;
      startUpdate = false;
      steer = 0;
    }

    if (n>(2*nMax)) {
      error = error/nMax;
      n = 0;
      //std::cout << error << ":" <<  p[0] << ", " << p[1] << ", " << p[2] <<  best_error << std::endl;
      if (idRun ==1) {
        if (error < best_error) {
          best_error = error;
          dp[itParam] *= 1.1;
          std::cout << "error: " << error << ", best error: " <<  best_error << std::endl;
          std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
        } else {
          p[itParam] -= 2*dp[itParam];
          idRun = 2;
          error = 0;
        }
      } else {
        if (idRun == 2) {
          idRun = 1;
          startUpdate = true;
          if (error < best_error) {
            best_error = error;
            dp[itParam] *= 1.1;
            std::cout << "error: " << error << ", 2" <<  "best error: " <<  best_error << std::endl;
            std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
          } else {
            p[itParam] += dp[itParam];
            dp[itParam] *= 0.9;
          }
        }
      }
      error = 0;
    } else {
      if (n>= nMax) {
        error += cte*cte;
        //std::cout << "error: " << error << std::endl;
      }
    }

   } else {
    // finish the optimization of the parameters
    std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
   }
   return steer;
}