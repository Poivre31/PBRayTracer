import numpy as np
from math import cos,sin
from matplotlib import pyplot as plt

def PDF(theta, k):
    A = np.pi * (2 * k + 1) / 2
    return (k + np.cos(theta) * np.cos(theta)) / A

def CDF(x, k):
    x = np.clip(x, 0, np.pi)
    A = np.pi * (2 * k + 1) / 2
    return (2 * x*(2*k+1) + np.sin(2*x)) / A / 4


def invCDF(y, k):
    A = np.pi * (2 * k + 1) / 2
    x = np.pi * y
    def g(x):
        return 2 * x*(2*k+1) + np.sin(2*x) - 4 * A * y
    def dg(x):
        return 4 * k + 2 + 2 * np.cos(2*x)
    
    for i in range(4):
        x = x - g(x)/dg(x)

    return x

def integrate(x,y):
    I = np.dot(x[1:]-x[:-1], y[1:] + y[:-1])
    return I / 2


k = .1
n = 1000
x = np.linspace(0, np.pi, n)
y = PDF(x, k)

u = np.random.uniform(0,1,n)
theta = invCDF(u,k)

lightDir = np.array([2.,3.,-1.])
lightDir /= np.dot(lightDir,lightDir)**.5
orthVec = np.array([1., 1., -(lightDir[0] + lightDir[1])/lightDir[2]])
orthVec /= np.dot(orthVec,orthVec)**.5

X = np.empty(n)
Y = np.empty(n)
Z = np.empty(n)
foundTheta = np.empty(n)
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

for i in range(n):
    u = lightDir * cos(theta[i]) + np.cross(lightDir,orthVec) * sin(theta[i])
    phi = np.random.uniform(0, 2*np.pi)
    v = u*cos(phi) + np.cross(lightDir,u)*sin(phi) + lightDir * np.dot(lightDir, u) * (1 - cos(phi))
    X[i] = v[0]
    Y[i] = v[1]
    Z[i] = v[2]
    foundTheta[i] = np.arccos(np.dot(v,lightDir))

ax.scatter(X,Y,Z)

plt.show()