import numpy as np
from math import cos, sin
from matplotlib import pyplot as plt

def PDF(theta, k):
    A = 1./2
    return 2 * np.cos(theta) * np.sin(theta)

def CDF(x, k):
    x = np.clip(x, 0, np.pi/2)
    A = 1./2
    return (1 - np.cos(2*x)) / 2

def invCDF(y, k):
    A = 1./2
    return np.arccos(1 - 2 * u) / 2

k = .2
n = 2000
x = np.linspace(0, np.pi, n)
y = PDF(x, k)

u = np.random.uniform(0,1,n)
theta = invCDF(u,k)

lightDir = np.array([0.,0.,1.])
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