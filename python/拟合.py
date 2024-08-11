import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
#use
y1 = np.array([100.1262,102.2305,111.2875,299.1899,566.4,774.4])
x1 = np.array([21,24,27,30,33,36])
x2 = np.array([400,500,605,605,1032,1486])
x3 = np.array([10123,12345,15678,18901,23456,29635])
x4 = np.array([107.8,111.1,113.5,114.7,121,134])
y = []

for i in range(0,6):
    u = 4547.4656 - 78.7724*x1[i] + 0.4837*x2[i] + 0.1203*x3[i] - 38.9488*x4[i]
    y.append(u)
    
print(y)
slope, intercept = np.polyfit(y1, y, 1)
plt.scatter(y1, y)
plt.plot(y1, slope * y1 + intercept, color='red')
plt.show()
