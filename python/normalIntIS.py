import numpy as np
from math import sqrt, atan
from matplotlib import pyplot as plt

def f(x, sigma = 1):
    return np.exp( - x * x / (2 * sigma * sigma)) / (sqrt(2 * np.pi) * sigma)

def integrateTrapezoidal(x, y):
    return np.dot(x[1:] - x[:-1], y[1:] + y[:-1]) / 2

def integrateMC(a,b,n):
    x = np.random.uniform(a,b,n)
    y = f(x)
    return (b - a) * np.sum(y) / n

def integrateISlorentz(a,b,n):
    u = np.random.uniform(-1,1,n) * .5 * atan(2 * a)
    x = .5 * np.tan(2 * u)
    
    y = f(x)
    return np.sum(y * (1 + 4 * x * x)) / n / (b - a) * np.pi / 2


a,b,n = -20, 20, 100

x = np.linspace(a,b,n)
y = f(x)
I1 = integrateTrapezoidal(x,y)
I2 = integrateMC(a,b,n)
I3 = integrateISlorentz(a,b,n)

print(f"Trapezoidal: {I1:.5f}\n Monte Carlo: {I2:.5f}\n Importance sampling: {I3:.5f}")

def estimateVariance(fonction,a,b,n, N):
    estimates = np.empty(N)
    for i in range(N):
        estimates[i] = fonction(a,b,n)
    return np.var(estimates)

var = estimateVariance(integrateMC, a, b, n, 1000)

print(f"MC std: {sqrt(var):.5f}")