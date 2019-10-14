#ifndef PID_H
#define PID_H

#include <vector>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  double runTwiddle(double cte);

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;

  double tolerance = 0.001; // tolerance of the twiddle algorithm
  int itTwiddle = 0;
  int itParam = 0; // iteration between the 3 parameters of the PID contoller for the twiddle
  const int nMax = 100;
  int n = 0;
  double error = 0;
  double best_error = 10000;
  std::vector<double> p;
  std::vector<double> dp;
  int idRun = 0;
};

#endif  // PID_H