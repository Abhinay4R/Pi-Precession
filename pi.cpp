#include <iostream>
#include <cmath>
#include <iomanip>
#include <bits/stdc++.h>
class PiApproximator {
private:
    // Babylonian method for square root calculation
    double babylonianSqrt(double number, double precision = 1e-15) {
        if (number < 0) return -1; // Invalid input
        if (number == 0) return 0;
        
        double x = number;
        double root;
        
        while (true) {
            root = 0.5 * (x + number / x);
            if (abs(root - x) < precision) break;
            x = root;
        }
        return root;
    }
    
    // Taylor series approximation for sine
    double taylorSine(double x, int terms = 10) {
        double result = 0.0;
        double term = x;
        
        for (int n = 0; n < terms; n++) {
            if (n % 2 == 0) {
                result += term;
            } else {
                result -= term;
            }
            
            // Calculate next term: multiply by x^2 and divide by (2n+2)(2n+3)
            term *= x * x / ((2 * n + 2) * (2 * n + 3));
        }
        return result;
    }
    
    // Calculate cosine using sin^2(x) + cos^2(x) = 1
    double calculateCosine(double x) {
        double sinVal = taylorSine(x);
        double cosSquared = 1.0 - sinVal * sinVal;
        
        // Determine sign of cosine based on quadrant
        // For our use case (x/4 where x is close to pi), cosine should be positive
        return babylonianSqrt(cosSquared);
    }
    
    // Calculate tan(x) = sin(x)/cos(x)
    double calculateTan(double x) {
        double sinVal = taylorSine(x);
        double cosVal = calculateCosine(x);
        
        if (abs(cosVal) < 1e-15) {
            throw std::runtime_error("Division by zero in tan calculation");
        }
        
        return sinVal / cosVal;
    }
    
    // Calculate sec^2(x) = 1/cos^2(x)
    double calculateSecSquared(double x) {
        double cosVal = calculateCosine(x);
        if (abs(cosVal) < 1e-15) {
            throw std::runtime_error("Division by zero in sec^2 calculation");
        }
        return 1.0 / (cosVal * cosVal);
    }
    
    // Function f(x) = tan(x/4) - 1
    double function(double x) {
        return calculateTan(x / 4.0) - 1.0;
    }
    
    // Derivative f'(x) = sec^2(x/4) / 4
    double derivative(double x) {
        return calculateSecSquared(x / 4.0) / 4.0;
    }

public:
    // Newton-Raphson method implementation
    double approximatePi(double initialGuess = 3.0, int maxIterations = 100, double tolerance = 1e-15) {
        double x = initialGuess;
        
        std::cout << "Newton-Raphson Iterations for Pi Approximation:" << std::endl;
        std::cout << "Using equation: tan(x/4) - 1 = 0" << std::endl;
        std::cout << "Initial guess: " << x << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        for (int i = 0; i < maxIterations; i++) {
            try {
                double fx = function(x);
                double fpx = derivative(x);
                
                if (abs(fpx) < 1e-15) {
                    std::cout << "Derivative too small, stopping iteration." << std::endl;
                    break;
                }
                
                double nextX = x - fx / fpx;
                
                std::cout << "Iteration " << std::setw(2) << i + 1 << ": " 
                          << std::setprecision(15) << std::fixed << nextX 
                          << " (error: " << std::scientific << abs(nextX - x) << ")" << std::endl;
                
                if (abs(nextX - x) < tolerance) {
                    std::cout << "\nConverged after " << i + 1 << " iterations!" << std::endl;
                    return nextX;
                }
                
                x = nextX;
                
            } catch (const std::exception& e) {
                std::cout << "Error in iteration " << i + 1 << ": " << e.what() << std::endl;
                break;
            }
        }
        
        std::cout << "\nReached maximum iterations (" << maxIterations << ")" << std::endl;
        return x;
    }
    
    // Validate that our approximation is within reasonable bounds
    bool validateBounds(double piApprox) {
        // Lower bound: Pi > 1 (circumference > diameter)
        // Upper bound: Pi < 4 (circle inscribed in square)
        const double lowerBound = 1.0;
        const double upperBound = 4.0;
        
        std::cout << "\nBound Validation:" << std::endl;
        std::cout << "Lower bound (Pi > 1): " << (piApprox > lowerBound ? "PASS" : "FAIL") << std::endl;
        std::cout << "Upper bound (Pi < 4): " << (piApprox < upperBound ? "PASS" : "FAIL") << std::endl;
        
        return (piApprox > lowerBound && piApprox < upperBound);
    }
    
    // Display comparison with known value
    void displayComparison(double piApprox) {
        const double knownPi = 3.141592653589793;
        double error = abs(piApprox - knownPi);
        double relativeError = error / knownPi * 100;
        
        std::cout << "\nResults Comparison:" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "Approximated Pi: " << std::setprecision(15) << std::fixed << piApprox << std::endl;
        std::cout << "Known Pi:        " << std::setprecision(15) << std::fixed << knownPi << std::endl;
        std::cout << "Absolute Error:  " << std::scientific << error << std::endl;
        std::cout << "Relative Error:  " << std::fixed << std::setprecision(10) << relativeError << "%" << std::endl;
    }
};

int main() {
    std::cout << "Pi Approximation using Newton-Raphson Method" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Approach: Solving tan(x/4) - 1 = 0 where x = Pi" << std::endl;
    std::cout << "Using Taylor series for sine and Babylonian method for square root" << std::endl;
    std::cout << std::endl;
    
    PiApproximator approximator;
    
    // Test different initial guesses within bounds
    std::vector<double> initialGuesses = {3.0, 2.5, 3.5, 3.14};
    
    for (double guess : initialGuesses) {
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "Testing with initial guess: " << guess << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        try {
            double piApprox = approximator.approximatePi(guess, 50, 1e-12);
            
            if (approximator.validateBounds(piApprox)) {
                approximator.displayComparison(piApprox);
            } else {
                std::cout << "Warning: Result is outside expected bounds for Pi!" << std::endl;
            }
            
        } catch (const std::exception& e) {
            std::cout << "Error during approximation: " << e.what() << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}
