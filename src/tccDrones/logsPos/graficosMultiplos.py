from cv2 import dft
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sklearn.metrics as metric
from math import sqrt
import statistics

dfQuadrado = pd.read_csv (r"src\tccDrones\logsPos\logChild0.csv", sep=";")
dfZigzag = pd.read_csv (r"src\tccDrones\logsPos\logChild1.csv", sep=";")
dfPercurso = pd.read_csv (r"src\tccDrones\logsPos\logChild2.csv", sep=";")
dfPercurso1 = pd.read_csv (r"src\tccDrones\logsPos\logChild3.csv", sep=";")

dfFollowOne = pd.read_csv (r"src\tccDrones\logsPos\logFollow1.csv", sep=";")
dfFollowTwo = pd.read_csv (r"src\tccDrones\logsPos\logFollow2.csv", sep=";")

# print(dfPercurso.tail())

# -------------------------------- QUADRADO -------------------------------------------------------------------------
def Plot3DGPSChildPontosQuadrado():
    xlineGPSQuadrado = dfQuadrado['GPSChildX'].values
    ylineGPSQuadrado = dfQuadrado['GPSChildY'].values
    zlineGPSQuadrado = dfQuadrado['GPSChildZ'].values

    xlineTagQuadrado = dfQuadrado['GPSMotherX'].values + dfQuadrado['tagX'].values
    ylineTagQuadrado = dfQuadrado['GPSMotherY'].values + dfQuadrado['tagY'].values 
    zlineTagQuadrado = dfQuadrado['GPSMotherZ'].values - dfQuadrado['tagZ'].values

    xlinePontos = dfQuadrado['pontosX'].values
    ylinePontos = dfQuadrado['pontosY'].values
    zlinePontos = 9 - dfQuadrado['pontosZ'].values

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.plot3D(xlineGPSQuadrado, ylineGPSQuadrado, zlineGPSQuadrado, 'blue', label='Posição do VANT')
    ax.plot3D(xlinePontos, ylinePontos, zlinePontos, 'green', label='Rota planejada')
    ax.plot3D(xlineTagQuadrado, ylineTagQuadrado, zlineTagQuadrado, 'red', label='Leituras da etiqueta')

    ax.set_title("Rota 3D VANT servo 1")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.set_zlabel('Posição em $Z$ (m)', fontsize=12)
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

    ax.plot(xlineGPSQuadrado, ylineGPSQuadrado, 'blue', label='Posição do VANT')
    ax.plot(xlinePontos, ylinePontos, 'green', label='Rota planejada')
    ax.plot(xlineTagQuadrado, ylineTagQuadrado, 'red', label='Leituras da etiqueta')
    ax.set_title("Rota nos eixos X e Y VANT servo 1")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_xlim([-2.5, 2])
    ax.set_ylim([-2.5, 2])

def PlotZGPSChildPontosQuadrado():
    zlineGPSQuadrado = dfQuadrado['GPSChildZ'].values
    indexLineGPSQuadrado = dfQuadrado['GPSChildZ'].index

    zlineTagQuadrado = dfQuadrado['GPSMotherZ'].values - dfQuadrado['tagZ'].values
    indexLineTagQuadrado = dfQuadrado['tagZ'].index
    
    zlinePontos = 9 - dfQuadrado['pontosZ'].values
    indexLinePontos = dfQuadrado['pontosZ'].index

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(indexLineGPSQuadrado, zlineGPSQuadrado, 'blue', label='Posição do VANT')
    ax.plot(indexLinePontos, zlinePontos, 'green', label='Rota planejada')
    ax.plot(indexLineTagQuadrado, zlineTagQuadrado, 'red', label='Leituras da etiqueta')
    ax.set_title("Rota no eixo Z VANT servo 1")
    ax.set_ylabel('Posição em $Z$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')

def ErrosQuadrado():
    xTrue = dfQuadrado['GPSChildX'].values
    yTrue = dfQuadrado['GPSChildY'].values
    zTrue = dfQuadrado['GPSChildZ'].values

    xTest = dfQuadrado['GPSMotherX'].values + dfQuadrado['tagX'].values
    yTest = dfQuadrado['GPSMotherY'].values + dfQuadrado['tagY'].values 
    zTest = dfQuadrado['GPSMotherZ'].values - dfQuadrado['tagZ'].values

    mseX = metric.mean_squared_error(xTrue, xTest)
    rmseX = sqrt(mseX)

    mseY = metric.mean_squared_error(yTrue, yTest)
    rmseY = sqrt(mseY)

    mseZ = metric.mean_squared_error(zTrue, zTest)
    rmseZ = sqrt(mseZ)

    erroMaxX = metric.max_error(xTrue, xTest)
    erroMaxY = metric.max_error(yTrue, yTest)
    erroMaxZ = metric.max_error(zTrue, zTest)

    mediaX = statistics.mean(xTest)
    mediaY = statistics.mean(yTest)
    mediaZ = statistics.mean(zTest)

    stDevX = statistics.stdev(xTest)
    stDevY = statistics.stdev(yTest)
    stDevZ = statistics.stdev(zTest)

    medianaX = statistics.median(xTest)
    medianaY = statistics.median(yTest)
    smedianaZ = statistics.median(zTest)

    maxX = xTest.max()
    maxY = yTest.max()
    maxZ = zTest.max()

    minX = xTest.min()
    minY = yTest.min()
    minZ = zTest.min()

    print("\n---------------------------------------------------------------------------------------")
    print("CHILD 0")
    print("ERRO QUADRATICO MEDIO -> X=", mseX, "   Y=", mseY, "   Z=", mseZ )
    print("RAIZ QUADRADA DO ERRO MEDIO -> X=", rmseX, "   Y=", rmseY, "   Z=", rmseZ )
    print("ERRO MAXIMO -> X=", erroMaxX, "   Y=", erroMaxY, "   Z=", erroMaxZ )
    print("---------------------------------------------------------------------------------------\n")
# ---------------------------------------------------------------------------------------------------------

# -------------------------------- ZIGZAG -------------------------------------------------------------------------
def Plot3DGPSChildPontosZigzag():
    xlineGPS = dfZigzag['GPSChildX'].values
    ylineGPS = dfZigzag['GPSChildY'].values
    zlineGPS = dfZigzag['GPSChildZ'].values

    xlineTag = dfZigzag['GPSMotherX'].values + dfZigzag['tagX'].values
    ylineTag = dfZigzag['GPSMotherY'].values + dfZigzag['tagY'].values 
    zlineTag = dfZigzag['GPSMotherZ'].values - dfZigzag['tagZ'].values

    xlinePontos = dfZigzag['pontosX'].values
    ylinePontos = dfZigzag['pontosY'].values
    zlinePontos = 9 - dfZigzag['pontosZ'].values

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.plot3D(xlineGPS, ylineGPS, zlineGPS, 'blue', label='Posição do VANT')
    ax.plot3D(xlinePontos, ylinePontos, zlinePontos, 'green', label='Rota planejada')
    ax.plot3D(xlineTag, ylineTag, zlineTag, 'red', label='Leituras da etiqueta')

    ax.set_title("Rota 3D VANT servo 2")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.set_zlabel('Posição em $Z$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_zlim3d([2, 4])

def PlotXYGPSChildPontosZigzag():
    xlineGPS = dfZigzag['GPSChildX'].values
    ylineGPS = dfZigzag['GPSChildY'].values

    xlineTag = dfZigzag['GPSMotherX'].values + dfZigzag['tagX'].values
    ylineTag = dfZigzag['GPSMotherY'].values + dfZigzag['tagY'].values
    
    xlinePontos = dfZigzag['pontosX'].values
    ylinePontos = dfZigzag['pontosY'].values

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(xlineGPS, ylineGPS, 'blue', label='Posição do VANT')
    ax.plot(xlinePontos, ylinePontos, 'green', label='Rota planejada')
    ax.plot(xlineTag, ylineTag, 'red', label='Leituras da etiqueta')
    ax.set_title("Rota nos eixos X e Y VANT servo 2")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_xlim([-2.5, 2])
    ax.set_ylim([-2.5, 2])

def PlotZGPSChildPontosZigzag():
    zlineGPS = dfZigzag['GPSChildZ'].values
    indexLineGPS = dfZigzag['GPSChildZ'].index

    zlineTag = dfZigzag['GPSMotherZ'].values - dfZigzag['tagZ'].values
    indexLineTag = dfZigzag['tagZ'].index
    
    zlinePontos = 9 - dfZigzag['pontosZ'].values
    indexLinePontos = dfZigzag['pontosZ'].index

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(indexLineGPS, zlineGPS, 'blue', label='Posição do VANT')
    ax.plot(indexLinePontos, zlinePontos, 'green', label='Rota planejada')
    ax.plot(indexLineTag, zlineTag, 'red', label='Leituras da etiqueta')
    ax.set_title("Rota no eixo Z VANT servo 2")
    ax.set_ylabel('Posição em $Z$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')

def ErrosZigzag():
    xTrue = dfZigzag['GPSChildX'].values
    yTrue = dfZigzag['GPSChildY'].values
    zTrue = dfZigzag['GPSChildZ'].values

    xTest = dfZigzag['GPSMotherX'].values + dfZigzag['tagX'].values
    yTest = dfZigzag['GPSMotherY'].values + dfZigzag['tagY'].values 
    zTest = dfZigzag['GPSMotherZ'].values - dfZigzag['tagZ'].values

    mseX = metric.mean_squared_error(xTrue, xTest)
    rmseX = sqrt(mseX)

    mseY = metric.mean_squared_error(yTrue, yTest)
    rmseY = sqrt(mseY)

    mseZ = metric.mean_squared_error(zTrue, zTest)
    rmseZ = sqrt(mseZ)

    erroMaxX = metric.max_error(xTrue, xTest)
    erroMaxY = metric.max_error(yTrue, yTest)
    erroMaxZ = metric.max_error(zTrue, zTest)

    mediaX = statistics.mean(xTest)
    mediaY = statistics.mean(yTest)
    mediaZ = statistics.mean(zTest)

    stDevX = statistics.stdev(xTest)
    stDevY = statistics.stdev(yTest)
    stDevZ = statistics.stdev(zTest)

    medianaX = statistics.median(xTest)
    medianaY = statistics.median(yTest)
    smedianaZ = statistics.median(zTest)

    maxX = xTest.max()
    maxY = yTest.max()
    maxZ = zTest.max()

    minX = xTest.min()
    minY = yTest.min()
    minZ = zTest.min()

    print("\n---------------------------------------------------------------------------------------")
    print("CHILD1")
    print("ERRO QUADRATICO MEDIO -> X=", mseX, "   Y=", mseY, "   Z=", mseZ )
    print("RAIZ QUADRADA DO ERRO MEDIO -> X=", rmseX, "   Y=", rmseY, "   Z=", rmseZ )
    print("ERRO MAXIMO -> X=", erroMaxX, "   Y=", erroMaxY, "   Z=", erroMaxZ )
    print("---------------------------------------------------------------------------------------\n")
# ---------------------------------------------------------------------------------------------------------

# -------------------------------- PERCURSO -------------------------------------------------------------------------
def Plot3DGPSChildPontosPercurso():
    xlineGPS = dfPercurso['GPSChildX'].values
    ylineGPS = dfPercurso['GPSChildY'].values
    zlineGPS = dfPercurso['GPSChildZ'].values

    xlineTag = dfPercurso['GPSMotherX'].values + dfPercurso['tagX'].values
    ylineTag = dfPercurso['GPSMotherY'].values + dfPercurso['tagY'].values 
    zlineTag = dfPercurso['GPSMotherZ'].values - dfPercurso['tagZ'].values

    xlinePontos = dfPercurso['pontosX'].values
    ylinePontos = dfPercurso['pontosY'].values
    zlinePontos = 9 - dfPercurso['pontosZ'].values

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.plot3D(xlineGPS, ylineGPS, zlineGPS, 'blue', label='Posição do VANT')
    ax.plot3D(xlinePontos, ylinePontos, zlinePontos, 'green', label='Rota planejada')
    ax.plot3D(xlineTag, ylineTag, zlineTag, 'red', label='Leituras da etiqueta')

    ax.set_title("Rota 3D VANT servo 3")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.set_zlabel('Posição em $Z$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_zlim3d([2, 4])

def PlotXYGPSChildPontosPercurso():
    xlineGPS = dfPercurso['GPSChildX'].values
    ylineGPS = dfPercurso['GPSChildY'].values

    xlineTag = dfPercurso['GPSMotherX'].values + dfPercurso['tagX'].values
    ylineTag = dfPercurso['GPSMotherY'].values + dfPercurso['tagY'].values
    
    xlinePontos = dfPercurso['pontosX'].values
    ylinePontos = dfPercurso['pontosY'].values

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(xlineGPS, ylineGPS, 'blue', label='Posição do VANT')
    ax.plot(xlinePontos, ylinePontos, 'green', label='Rota planejada')
    ax.plot(xlineTag, ylineTag, 'red', label='Leituras da etiqueta')
    ax.set_title("Rota nos eixos X e Y VANT servo 3")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_xlim([-2.5, 2])
    ax.set_ylim([-2.5, 2])

def PlotZGPSChildPontosPercurso():
    zlineGPS = dfPercurso['GPSChildZ'].values
    indexLineGPS = dfPercurso['GPSChildZ'].index

    zlineTag = dfPercurso['GPSMotherZ'].values - dfPercurso['tagZ'].values
    indexLineTag = dfPercurso['tagZ'].index
    
    zlinePontos = 9 - dfPercurso['pontosZ'].values
    indexLinePontos = dfPercurso['pontosZ'].index

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(indexLineGPS, zlineGPS, 'blue', label='Posição do VANT')
    ax.plot(indexLinePontos, zlinePontos, 'green', label='Rota planejada')
    ax.plot(indexLineTag, zlineTag, 'red', label='Leituras da etiqueta')
    ax.set_title("Rota no eixo Z VANT servo 3")
    ax.set_ylabel('Posição em $Z$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')

def ErrosPercurso():
    xTrue = dfPercurso['GPSChildX'].values
    yTrue = dfPercurso['GPSChildY'].values
    zTrue = dfPercurso['GPSChildZ'].values

    xTest = dfPercurso['GPSMotherX'].values + dfPercurso['tagX'].values
    yTest = dfPercurso['GPSMotherY'].values + dfPercurso['tagY'].values 
    zTest = dfPercurso['GPSMotherZ'].values - dfPercurso['tagZ'].values

    mseX = metric.mean_squared_error(xTrue, xTest)
    rmseX = sqrt(mseX)

    mseY = metric.mean_squared_error(yTrue, yTest)
    rmseY = sqrt(mseY)

    mseZ = metric.mean_squared_error(zTrue, zTest)
    rmseZ = sqrt(mseZ)

    erroMaxX = metric.max_error(xTrue, xTest)
    erroMaxY = metric.max_error(yTrue, yTest)
    erroMaxZ = metric.max_error(zTrue, zTest)

    mediaX = statistics.mean(xTest)
    mediaY = statistics.mean(yTest)
    mediaZ = statistics.mean(zTest)

    stDevX = statistics.stdev(xTest)
    stDevY = statistics.stdev(yTest)
    stDevZ = statistics.stdev(zTest)

    medianaX = statistics.median(xTest)
    medianaY = statistics.median(yTest)
    smedianaZ = statistics.median(zTest)

    maxX = xTest.max()
    maxY = yTest.max()
    maxZ = zTest.max()

    minX = xTest.min()
    minY = yTest.min()
    minZ = zTest.min()

    print("\n---------------------------------------------------------------------------------------")
    print("CHILD2")
    print("ERRO QUADRATICO MEDIO -> X=", mseX, "   Y=", mseY, "   Z=", mseZ )
    print("RAIZ QUADRADA DO ERRO MEDIO -> X=", rmseX, "   Y=", rmseY, "   Z=", rmseZ )
    print("ERRO MAXIMO -> X=", erroMaxX, "   Y=", erroMaxY, "   Z=", erroMaxZ )
    print("---------------------------------------------------------------------------------------\n")
# ---------------------------------------------------------------------------------------------------------
# -------------------------------- PERCURSO -------------------------------------------------------------------------
def Plot3DGPSChildPontosPercurso1():
    xlineGPS = dfPercurso1['GPSChildX'].values
    ylineGPS = dfPercurso1['GPSChildY'].values
    zlineGPS = dfPercurso1['GPSChildZ'].values

    xlineTag = dfPercurso1['GPSMotherX'].values + dfPercurso1['tagX'].values
    ylineTag = dfPercurso1['GPSMotherY'].values + dfPercurso1['tagY'].values 
    zlineTag = dfPercurso1['GPSMotherZ'].values - dfPercurso1['tagZ'].values

    xlinePontos = dfPercurso1['pontosX'].values
    ylinePontos = dfPercurso1['pontosY'].values
    zlinePontos = 9 - dfPercurso1['pontosZ'].values

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.plot3D(xlineGPS, ylineGPS, zlineGPS, 'blue', label='Posição do VANT')
    ax.plot3D(xlinePontos, ylinePontos, zlinePontos, 'green', label='Rota planejada')
    ax.plot3D(xlineTag, ylineTag, zlineTag, 'red', label='Leituras da etiqueta')

    ax.set_title("Rota 3D VANT servo 4")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.set_zlabel('Posição em $Z$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_zlim3d([2, 4])

def PlotXYGPSChildPontosPercurso1():
    xlineGPS = dfPercurso1['GPSChildX'].values
    ylineGPS = dfPercurso1['GPSChildY'].values

    xlineTag = dfPercurso1['GPSMotherX'].values + dfPercurso1['tagX'].values
    ylineTag = dfPercurso1['GPSMotherY'].values + dfPercurso1['tagY'].values
    
    xlinePontos = dfPercurso1['pontosX'].values
    ylinePontos = dfPercurso1['pontosY'].values

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(xlineGPS, ylineGPS, 'blue', label='Posição do VANT')
    ax.plot(xlinePontos, ylinePontos, 'green', label='Rota planejada')
    ax.plot(xlineTag, ylineTag, 'red', label='Leituras da etiqueta')
    ax.set_title("Rota nos eixos X e Y VANT servo 4")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_xlim([-2.5, 2])
    ax.set_ylim([-2.5, 2])

def PlotZGPSChildPontosPercurso1():
    zlineGPS = dfPercurso1['GPSChildZ'].values
    indexLineGPS = dfPercurso1['GPSChildZ'].index

    zlineTag = dfPercurso1['GPSMotherZ'].values - dfPercurso1['tagZ'].values
    indexLineTag = dfPercurso1['tagZ'].index
    
    zlinePontos = 9 - dfPercurso1['pontosZ'].values
    indexLinePontos = dfPercurso1['pontosZ'].index

    fig = plt.figure()
    ax = plt.axes()

    ax.plot(indexLineGPS, zlineGPS, 'blue', label='Posição do VANT')
    ax.plot(indexLinePontos, zlinePontos, 'green', label='Rota planejada')
    ax.plot(indexLineTag, zlineTag, 'red', label='Leituras da etiqueta')
    ax.set_title("Rota no eixo Z VANT servo 4")
    ax.set_ylabel('Posição em $Z$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')

def ErrosPercurso1():
    xTrue = dfPercurso1['GPSChildX'].values
    yTrue = dfPercurso1['GPSChildY'].values
    zTrue = dfPercurso1['GPSChildZ'].values

    xTest = dfPercurso1['GPSMotherX'].values + dfPercurso1['tagX'].values
    yTest = dfPercurso1['GPSMotherY'].values + dfPercurso1['tagY'].values 
    zTest = dfPercurso1['GPSMotherZ'].values - dfPercurso1['tagZ'].values

    mseX = metric.mean_squared_error(xTrue, xTest)
    rmseX = sqrt(mseX)

    mseY = metric.mean_squared_error(yTrue, yTest)
    rmseY = sqrt(mseY)

    mseZ = metric.mean_squared_error(zTrue, zTest)
    rmseZ = sqrt(mseZ)

    erroMaxX = metric.max_error(xTrue, xTest)
    erroMaxY = metric.max_error(yTrue, yTest)
    erroMaxZ = metric.max_error(zTrue, zTest)

    mediaX = statistics.mean(xTest)
    mediaY = statistics.mean(yTest)
    mediaZ = statistics.mean(zTest)

    stDevX = statistics.stdev(xTest)
    stDevY = statistics.stdev(yTest)
    stDevZ = statistics.stdev(zTest)

    medianaX = statistics.median(xTest)
    medianaY = statistics.median(yTest)
    smedianaZ = statistics.median(zTest)

    maxX = xTest.max()
    maxY = yTest.max()
    maxZ = zTest.max()

    minX = xTest.min()
    minY = yTest.min()
    minZ = zTest.min()

    print("\n---------------------------------------------------------------------------------------")
    print("CHILD3")
    print("ERRO QUADRATICO MEDIO -> X=", mseX, "   Y=", mseY, "   Z=", mseZ )
    print("RAIZ QUADRADA DO ERRO MEDIO -> X=", rmseX, "   Y=", rmseY, "   Z=", rmseZ )
    print("ERRO MAXIMO -> X=", erroMaxX, "   Y=", erroMaxY, "   Z=", erroMaxZ )
    print("---------------------------------------------------------------------------------------\n")
# ---------------------------------------------------------------------------------------------------------


def Plot3DGPSChildPontosPercurso2():
    xlineGPS = dfQuadrado['GPSChildX'].values
    ylineGPS = dfQuadrado['GPSChildY'].values
    zlineGPS = dfQuadrado['GPSChildZ'].values

    xlineTag = dfZigzag['GPSChildX'].values
    ylineTag = dfZigzag['GPSChildY'].values 
    zlineTag = dfZigzag['GPSChildZ'].values

    xlinePontos = dfPercurso['GPSChildX'].values
    ylinePontos = dfPercurso['GPSChildY'].values
    zlinePontos = dfPercurso['GPSChildZ'].values

    xlinePontos1 = dfPercurso1['GPSChildX'].values
    ylinePontos1 = dfPercurso1['GPSChildY'].values
    zlinePontos1 = dfPercurso1['GPSChildZ'].values

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.plot3D(xlineGPS, ylineGPS, zlineGPS, 'blue', label='Posição do VANT servo 1')
    ax.plot3D(xlinePontos, ylinePontos, zlinePontos, 'green', label='Posição do VANT servo 3')
    ax.plot3D(xlineTag, ylineTag, zlineTag, 'red', label='Posição do VANT servo 2')
    ax.plot3D(xlinePontos1, ylinePontos1, zlinePontos1, 'purple', label='Posição do VANT servo 4')

    ax.set_title("Rota 3D VANTs servos")
    ax.set_xlabel('Posição em $X$ (m)', fontsize=12)
    ax.set_ylabel('Posição em $Y$ (m)', fontsize=12)
    ax.set_zlabel('Posição em $Z$ (m)', fontsize=12)
    ax.legend(loc='best', shadow=True, fontsize='small')
    ax.set_zlim3d([2, 4])

# ---------------------------------------------------------------------------------------------------------
def main():
    ErrosQuadrado()
    # Plot3DGPSChildPontosQuadrado()
    # PlotXYGPSChildPontosQuadrado()
    # PlotZGPSChildPontosQuadrado()
    
    ErrosZigzag()
    # Plot3DGPSChildPontosZigzag()
    # PlotXYGPSChildPontosZigzag()
    # PlotZGPSChildPontosZigzag()

    ErrosPercurso()
    # Plot3DGPSChildPontosPercurso()
    # PlotXYGPSChildPontosPercurso()
    # PlotZGPSChildPontosPercurso()

    ErrosPercurso1()
    # Plot3DGPSChildPontosPercurso1()
    # PlotXYGPSChildPontosPercurso1()
    # PlotZGPSChildPontosPercurso1()

    # Plot3DGPSChildPontosPercurso2() 
    
    plt.show()

if __name__ == "__main__":
    main()
# ---------------------------------------------------------------------------------------------------------
