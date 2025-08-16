import numpy as np
from math import cos, sin
from matplotlib import pyplot as plt

def PDF(theta, k):
    A = 2. * (k + 1./3)
    return (k + np.cos(theta) * np.cos(theta)) / A

def CDF(x, k):
    x = np.clip(x, 0, np.pi)
    A = 2. * (k + 1./3)
    return (k + 1/3 - np.cos(x) * (k + np.cos(x) * np.cos(x) / 3)) / A

def solveCubic(p,q):
    u1 = -q / 2 + np.sqrt(q * q / 4 + p * p * p / 27)
    u2 = -q / 2 - np.sqrt(q * q / 4 + p * p * p / 27)
    return np.cbrt(u1) + np.cbrt(u2)    

def invCDF(y, k):
    A = 2. * (k + 1./3)
    q = 3 * A * y - 1 - 3 * k
    p = 3 * k
    u = solveCubic(p,q)
    return np.arccos(u)

k = .2
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
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

for i in range(n):
    u = lightDir * cos(theta[i]) + np.cross(lightDir,orthVec) * sin(theta[i])
    phi = np.random.uniform(0, 2*np.pi)
    v = u*cos(phi) + np.cross(lightDir,u)*sin(phi) + lightDir * np.dot(lightDir, u) * (1 - cos(phi))
    X[i] = v[0]
    Y[i] = v[1]
    Z[i] = v[2]

ax.scatter(X,Y,Z)

plt.show()