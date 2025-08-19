import numpy as np
from math import sqrt, atan
from matplotlib import pyplot as plt

x = np.linspace(-5,5,1000)
y = np.exp(-x*x/2)/sqrt(2*np.pi)

def invCDF(y):
    u = np.log(1 / y - 1)
    return - sqrt(np.pi/8) * u

u = np.random.uniform(0,1,100000)
normal = invCDF(u)

plt.plot(x,y)
plt.hist(normal,2000,density=True)
plt.show()