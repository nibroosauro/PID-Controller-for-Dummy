# The Simplest Explanation about PID (ngl!)
## Chapter 1: Introduction to Control Engineering
$$
u(t) = K_p e(t) + K_i \int_0^t e(\tau) d\tau + K_d \frac{d}{dt}e(t)
$$
That's the well-known PID formula. It's look hairy isn't it? As the name stand for <b>P</b>roportional <b>I</b>ntegral <b>D</b>erivative. Why bother with the whole package of calculus to control such a system?

Well, first of all we have to dig down regarding the very first reason why we needed controller at the first place. Well to be said, a naked system could still be functional but if we talk about automation a tiny error could lead into a huge problem. This is why we needed the control engineering. Hold on, what's the actual job of control engineering? 

The job of control engineering is to make sure the input signal could produce the desired value as the actuators' movement. Sometimes there might be an external factor such as changes in load, temperatire, electrical noise etc, this could lead to deviation in actuator’s behavior if we simply just use voltage value as an input. This is why control engineering come in handy.
## Chapter 2: Introduction to PID Controller 
As we mentioned in chapter one PID controller has three actors; P,I, and D. The main idea about PID is to use feedback to calculate the value between currect point and desired point (error). What happen when the error is known? 

Well, magine you're on a quest to find a hidden treasure. You have a map that shows the location of the treasure (the desired point or setpoint), but you don’t know exactly where you are in relation to it. As you explore, you receive clues (<i>feedback</i>) that tell you how far you are from the treasure (this is the error or the difference between your current location and the treasure's location). Once you know the error, you can make decisions about how to adjust your course to get closer to the treasure. When you first realize how far away you are from the treasure, your instinct is to take a step forward toward the treasure accordingly. If your current position is really far away from the treasure, you might want to run to get there as quick as possible. Although if your current position is really close toward the treasure, you might want to slow down and looking around carefully. 
## Chapter 3: The Effect of the Proportional (P) Variable
You wanted to go to your friend house. Let's say it's 100 meters apart from your current location. The controller would take the difference value between current state and desired state (which is 100 meters), then multiply the value by the <b>P</b> constant value or <b>P</b> gain. Another thing to remember, PID uses feedback. So, somehow you have a tracker device to measure how far apart you are from your friend house.
$$
u(t) = K_p e(t)
$$
$K_p$ is the <b>P</b> gain, which you could change (this variable is customizable).  $e(t)$ is the error as the function of time. Could you imagine what will happen based on the formula? Since at the beginning the value of $e(t)$ is high, $u(t)$ will likely to be a high number. Gradually, as you move closer to your friend house, $e(t)$ will decrease. That will result the change in $u(t)$ proportional with the change in $e(t)$. At some point the value of $e(t)$ will be zero, that means you're at your friend house. Since $e(t)$ is zero, then the system will stop because $u(t)$ will also be zero. 
## Chapter 4: The Effect of the Integral (I) Variable
Why we needed another variable to think of? Isn't <b>P</b> good enough? Well, is not always the case. Sometime more sophiscated system need more complex tools.
## Chapter 5: The Effect of the Derivative (D) Variable
## Chapter 6: Implementing PID in Omniwheel System
## Chapter 7: Code Walkthrough and Explanation
## Resources

