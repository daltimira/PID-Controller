# Manual adjusting of parameters

First I tried to adjust the parameters Kd, Kp and Ki in order to control the steering values.

## Steering value

I first set the Kd and Ki to zero and adjust just the Kp. Here my initial expectations is that the car overshoots and starts oscilating around the target position on the lane.

Different valuest that I tried for the Kp:
* 0.5: the vehicle start oscilating and the vehicle increases the oscilations over time.
* 0.3: fewer oscilations than 0.5, but the oscilations increases over time.
* 0.2: fewer oscilations than 0.3, but the oscilations increases over time..
* 0.1: feels like the vehicle starts more stable, but when the vehicle takes the first curve, the vehicle starts oscilating more.
* 0.05: The vehicle does not oscilates, goes straight. But in the curve, the vehicle goes out of the road. Seems that the error connection is not enough strong.

To sum up, the higher the Kp, the more oscilations it is perceived on the vehicle. Also, with just adjusting the Kp, the oscilations increases over time. However, a very low Kp, the vehicle does not have enough correction from an error, and can go out of the road easily in a curve.

I decided to set Kp to 0.1 and start tunning the Kd in order to reduce the correction as we are approaching the solution. This should prevent overshooting.

Different values that tried for the Kd:
* 1.0: The car is on the center of the lane, but the car seems to oscilates a bit.
* 0.5: The vehicle seems to be more stable than 1.0.
* 0.2: The vehicle behaves quite worse than 0.5. When the vehicle reaches a curve, it starts oscilating quite a bit.
* 0.4: Seems that the vehicle oscilates more than 0.5.
* 0.7: The vehicle runs quite stable.

I decided to set Ki to 0.7.

Finally, I tunned the Ki.

* 0.1: runs quite bad.
* 1.0: vehicle starts running very badly, it gets out of the road immidialty.
* 0.5: similar as 1.0.
* 0.05: starts going out of track.
* 0.001: vehicle behaves quite well.

It seems that the Ki should be quite small, otherwise the vehicle starts showing bad behaviour.

It seems that the behaviour of one parameter depends also on how the other parameters are tunned. So it is better to tune one at a time, and when the behaviour of the vehicle is the expected one for the right tunning of the parameter it is then time to go to next one. It can also be important the order of the parameters you tune. For example, it is better to tune first the Kp, as this is the one that tries to correct the steering value for the error. But by only tunning this parameter, you could observer oscilations on the vehicle. To fix that, it is introduced the Kd, whose goal is to fix the oscilations by adjusting the steering value as we approach the solutions. This helps reducing the overshoot. Finally, the Ki is introduced to system bias, drift or accumulative error.  
