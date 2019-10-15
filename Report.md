# Manual adjusting of parameters 

## Steering value

I implemented the PID, initizlizing and started setting the the differential constant (Kd) to zero and the Integral constant (Ki) to zero. 

Different valuest that tried for the Kp:
* 0.5: the vehicle start oscilating and every time the vehicle oscilates more.
* 0.3: start with fewer oscilations, but then the oscilations increases.
* 0.2: the vehicle stills overshoots too much and the oscilations increaser.
* 0.1: Start more estable, les oscilations, but near the curbe start oscilating more.
* 0.05: The vehicle starts going straight, but in the curve it goes out of the road.

Setting the other parameters to zero, the higher the Kp, the more oscilations have. But at the end, after running the vehicle for a while, the vehicle starts oscilating quite a bit.

The larger the Kp values, the vehicle oscilates more. 

Setting a Kp to 0.1 and then using the differential constant to prevent overshooting:

Different values that tried for the Kd:
* 1.0: Definetly keeps the car around in the lane. Still sometimes the car oscilates a bit, but the vehicle keeps quite steedy. 
* 0.5: The vehicle seems to be more stable than 1.0.
* 0.2: Quite worse than the 0.5, when the vehicle reaches a curbe starts oscilating quite a bit.
* 0.4: oscilates more than 0.5
* 0.7 vehicle runs quite stable.

Setting the Ki.
*0.1: runs quite bad,
*1.0: vehicle starts running very badly. out of the road.
* 0.5: similar as 1.0.
* 0.05: starts going out of track.
* 0.001: better.

Seems that Ki cannot have large values, as it is easy to get out of track. 