from cv2 import dft
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


dfQuadrado = pd.read_csv (r"src\tccDrones\logsPos\logQuadrado.csv", sep=";")
dfZigzag = pd.read_csv (r"src\tccDrones\logsPos\logZigzag.csv", sep=";")
dfPercurso = pd.read_csv (r"src\tccDrones\logsPos\logPercurso.csv", sep=";")

print(dfQuadrado)

def Plot3DGPSChildPontosQuadrado():
    xlineGPSQuadrado = dfQuadrado['GPSChildX'].values
    ylineGPSQuadrado = dfQuadrado['GPSChildY'].values
    zlineGPSQuadrado = dfQuadrado['GPSChildZ'].values

    xlineTagQuadrado = dfQuadrado['GPSMotherX'].values + dfQuadrado['tagX'].values
    ylineTagQuadrado = dfQuadrado['GPSMotherY'].values + dfQuadrado['tagY'].values 
    zlineTagQuadrado = dfQuadrado['GPSMotherZ'].values - dfQuadrado['tagZ'].values

    xlinePontos = dfQuadrado['pontosX'].values
    ylinePontos = dfQuadrado['pontosY'].values
    zlinePontos = dfQuadrado['pontosZ'].values - 3

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.plot3D(xlineGPSQuadrado, ylineGPSQuadrado, zlineGPSQuadrado, 'blue', label='UAV Position')
    ax.plot3D(xlinePontos, ylinePontos, zlinePontos, 'green', label='Planned route')

    ax.plot3D(xlineTagQuadrado, ylineTagQuadrado, zlineTagQuadrado, 'red', label='Tag readings')

    ax.set_title("3D Routes")
    ax.set_xlabel('Pose in $X$', fontsize=12)
    ax.set_ylabel('Pose in $Y$', fontsize=12)
    ax.set_zlabel('Pose in $Z$', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_zlim3d([2, 4])

def PlotXYGPSChildPontosQuadrado():
    xlineGPSQuadrado = dfQuadrado['GPSChildX'].values
    ylineGPSQuadrado = dfQuadrado['GPSChildY'].values

    xlineTagQuadrado = dfQuadrado['GPSMotherX'].values + dfQuadrado['tagX'].values
    ylineTagQuadrado = dfQuadrado['GPSMotherY'].values + dfQuadrado['tagY'].values
    
    xlinePontos = dfQuadrado['pontosX'].values
    ylinePontos = dfQuadrado['pontosY'].values

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(xlineGPSQuadrado, ylineGPSQuadrado, 'blue', label='UAV Position')
    ax.plot(xlinePontos, ylinePontos, 'green', label='Planned route')
    ax.plot(xlineTagQuadrado, ylineTagQuadrado, 'red', label='Tag readings')
    ax.set_title("Routes in X and Y position")
    ax.set_xlabel('Pose in $X$', fontsize=12)
    ax.set_ylabel('Pose in $Y$', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_xlim([-1.5, 2])
    ax.set_ylim([-1.5, 2])

def PlotZGPSChildPontosQuadrado():
    zlineGPSQuadrado = dfQuadrado['GPSChildZ'].values
    indexLineGPSQuadrado = dfQuadrado['GPSChildZ'].index

    zlineTagQuadrado = dfQuadrado['GPSMotherZ'].values - dfQuadrado['tagZ'].values
    indexLineTagQuadrado = dfQuadrado['tagZ'].index
    
    zlinePontos = dfQuadrado['pontosZ'].values - 3
    indexLinePontos = dfQuadrado['pontosZ'].index

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(indexLineGPSQuadrado, zlineGPSQuadrado, 'blue', label='UAV Position')
    ax.plot(indexLinePontos, zlinePontos, 'green', label='Planned route')
    ax.plot(indexLineTagQuadrado, zlineTagQuadrado, 'red', label='Tag readings')
    ax.set_title("Planned route x Route executed in Z position")
    ax.set_ylabel('Pose in $Z$', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')

def main():
    Plot3DGPSChildPontosQuadrado()
    PlotXYGPSChildPontosQuadrado()
    PlotZGPSChildPontosQuadrado()
    plt.show()


if __name__ == "__main__":
    main()
    