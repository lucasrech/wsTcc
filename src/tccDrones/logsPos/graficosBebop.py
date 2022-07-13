from cv2 import dft
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sklearn.metrics as metric
from math import sqrt
import statistics

dfBebop = pd.read_csv (r"src\tccDrones\logsPos\logBebop.csv", sep=";")


print(dfBebop.shape)


xlineBebopQuadrado = dfBebop['x'][:].values
ylineBebopQuadrado = dfBebop['y'][:].values
zlineBebopQuadrado = dfBebop['z'][:].values

fig = plt.figure()
ax = plt.axes()
ax.plot(xlineBebopQuadrado, ylineBebopQuadrado, 'green', label='UAV Position in X and Y axis')
ax.set_title("Position in X and Y position")
ax.set_xlabel('Pose in $X$', fontsize=12)
ax.set_ylabel('Pose in $Y$', fontsize=12)
ax.legend(loc='best', shadow=True, fontsize='small')


fig = plt.figure()
ax = plt.axes()
ax.plot(dfBebop['x'].index, xlineBebopQuadrado, 'green', label='UAV Position in X-axi')
ax.set_title("Position in X-axi")
# ax.set_xlabel('Pose in $X$', fontsize=12)
ax.set_ylabel('Pose in $X$', fontsize=12)
ax.legend(loc='best', shadow=True, fontsize='small')

fig = plt.figure()
ax = plt.axes()
ax.plot(dfBebop['y'].index, ylineBebopQuadrado, 'green', label='UAV Position in Y-axi')
ax.set_title("Position in Y-axi")
# ax.set_xlabel('Pose in $X$', fontsize=12)
ax.set_ylabel('Pose in $Y$', fontsize=12)
ax.legend(loc='best', shadow=True, fontsize='small')

fig = plt.figure()
ax = plt.axes()
ax.plot(dfBebop['z'].index, zlineBebopQuadrado, 'green', label='UAV Position in Z-axi')
ax.set_title("Position in Z-axi")
# ax.set_xlabel('Pose in $X$', fontsize=12)
ax.set_ylabel('Pose in $Z$', fontsize=12)
ax.legend(loc='best', shadow=True, fontsize='small')

fig = plt.figure()
ax = plt.axes(projection='3d')

ax.plot3D(xlineBebopQuadrado, ylineBebopQuadrado, zlineBebopQuadrado, 'green', label='UAV Position')

ax.set_title("3D Position")
ax.set_xlabel('Pose in $X$', fontsize=12)
ax.set_ylabel('Pose in $Y$', fontsize=12)
ax.set_zlabel('Pose in $Z$', fontsize=12)
ax.legend(loc='best', shadow=True, fontsize='small')
# ax.set_zlim3d([2, 4])

plt.show()