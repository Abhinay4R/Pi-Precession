# Pi-Precession

This problem in itself required a lot of creative thinking, lot of application of mathematical tools that I studied through my Engineering and High-School classes. The problem statement is very simple, "Find the closest Approximate value of Pi without using any already existing series for it".
My interpretation is that we can use any direct series that exists for the expansion of Pi or its multiples. Many series already exist for the expansion of Pi that require far less computational power as compared to mine, but either ways its my honest attempt at verifying and approximating Pi. 

## Newton Raphson Method for calculating the root of an equation.

Newton-Raphson Method for calculating the root of an equation is known to many as a powerful tool to numerically find roots for a given equation. Newton-Raphson is used in parallel with factorization to calculate roots of a polynomial equation in general. 
The basic procedure to do this is described in detail below:

>Assume the equation we want to solve numerically is f(x)=0, we aspire to find a real number a such that f(a) = 0
>We start with an arbitrary x0 and find the value of f(x0), it is practically impossible for a number chosen at random to be the root of the function f(x). Therefore we will use this initial value to come closer to the required root, this process done indefinitely will eventually end up finding the root of the required equation.
>This begs the question , what actually is the Newton Raphson method: We know that the value of the derivative ( slope ) of this function at x0 gives us the inclination of the function value from the x - axis. Therefore that inclination f'(x0)=f(x0)/delx0 ->delx0 =f(x0)/f'(x0) : more generally delx =f(x)/f'(x) where delx is the difference between the x-coordinate of the point of intersection of the tangent to f(x) at x0 and x-axis, and x0.
>hence if delx  = x0 - x1
>         x1 = x0 - delx
>         x1 = x0 - f(x0)/f'(x0)
>         
>     More generally it is 
> 	     Xn = Xn-1 - f(Xn-1)/f'(Xn-1) 

From this a neat observation can be inferred: we have come closer to the root (or minimum ) of this function we are studying. This observation I'm stating without much rigor and without proof except for visual intuition. 

But how does this relate to approximating Pi in any way? That question can be answered by using the fact that Newton-Raphson Method can be applied to any real valued continuous function, as in proving or stating it we did not use the properties of polynomials anywhere, its just that it is more famously known to find roots of Polynomial equations. 

Therefore my job has now been converted into simply just finding an equation to which Pi must be a root of,  and when written in the function form this function must be a real valued continuous function with computable derivative and function values for a wide range of Real numbers. After a lot of trial and error, i ended up with this equation. 
>		tan(Pi/4)=1
>		 tan(Pi/4)-1 =0
>		 therefore f(x)=tan(x/4)-1 has a root at x = Pi

From above f(x) = tan(x/4)-1
		   f'(x) = sec^2 (x/4)/4
		   therefore we get
		    delx=(4tan(x/4)-4)/(sec^2(x/4))
		    delx=4(sin(x/4)/cos(x/4))-4/(1/cos^2(x/4))
		    delx=4 sin(x/4)cos(x/4)- 4cos^2(x) 

we have encountered another problem, we need to reliably and accurately calculate the sine or cosine of some real numbers. To solve this I could have used Cordic-Algorithms which are used by modern Calculators to calculate the values of sines or cosines of real numbers, but I choose not to simply because that felt like something I couldn't have come up with on my own. I opt to use Taylor's Expansion for the calculation of the sine and hence cosine also can be found reasonably quickly as i do not want to spend computational power on both Sine and cosine separately, when in principle i can use the relation sin^2 x + cos^2 x = 1 , and just calculate the square root very accurately using Babylonian square root algorithm, which i was taught in University. Regardless of the way of calculating the value of the sine and cosine that expression after some finite number of iterations gave me a reasonable approximate of the value of Pi. To fine tune this algorithm one can use Cordic-algorithms instead or make more improvements by calculating or omitting higher order terms in the Taylor's Expansion in a accuracy-computational power trade-off. 
> Taylor approximation of sine(x) = x + x^3 /3! + x^5 /5! { A reasonable approximation with a good accuracy - computational power tradeoff }

But is Pi the only root of the above function? No ofcourse not, and infact any trigonometric equation will have infinite number of solutions to it due to the periodicity of the trigonometric functions. But then this raises a question, how can one know that the value which was output by this program is or is not Pi. 

To tackle this problem, I used some geometry to bound the value of Pi, and hence any random number choosen from this bound will converge in this program to Pi ( when run indefinitely ofcourse). 
### Lower and upper bounds on Pi:

Pi is defined to be the ratio between the circumference and the diameter of any circle. Therefore from visual observations it is trivial that the circumference is greater than its diameter for any circle therefore 1< Pi , note that this argument is not fully rigorous ( can be made rigorous but i have chosen to omit it )

The case for the upper bound is not so trivial. To argue for an upper bound, start with a unit circle, hence the diameter is 2. Now if this circle is inscribed in a square we can deduce that the side of the square is 2. We can infer that the perimeter of this square is greater than the circumference of the circle as the circle is inscribe in the square using the following argument 


