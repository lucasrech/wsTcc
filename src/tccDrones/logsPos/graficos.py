from cv2 import dft
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


dfQuadrado = pd.read_csv (r"src\tccDrones\logsPos\logQuadrado.csv", sep=";")
dfZigzag = pd.read_csv (r"src\tccDrones\logsPos\logZigzag.csv", sep=";")
dfPercurso = pd.read_csv (r"src\tccDrones\logsPos\logPercurso.csv", sep=";")


dfQuadradoTag = dfQuadrado.loc[: , ['tagX','tagY', 'tagZ']]
dfQuadradoChildGPS = dfQuadrado.loc[: , ['GPSChildX','GPSChildY', 'GPSChildZ']]
dfQuadradoMotherGPS = dfQuadrado.loc[: , ['GPSMotherX','GPSMotherY', 'GPSMotherZ']]
dfQuadradoPontos = dfQuadrado.loc[: , ['pontosX','pontosY', 'pontosZ']]

dfZigzagTag = dfZigzag.loc[: , ['tagX','tagY', 'tagZ']]
dfZigzagChildGPS = dfZigzag.loc[: , ['GPSChildX','GPSChildY', 'GPSChildZ']]
dfZigzagMotherGPS = dfZigzag.loc[: , ['GPSMotherX','GPSMotherY', 'GPSMotherZ']]
dfZigzagPontos = dfZigzag.loc[: , ['pontosX','pontosY', 'pontosZ']]

dfPercursoTag = dfPercurso.loc[: , ['tagX','tagY', 'tagZ']]
dfPercursoChildGPS = dfPercurso.loc[: , ['GPSChildX','GPSChildY', 'GPSChildZ']]
dfPercursoMotherGPS = dfPercurso.loc[: , ['GPSMotherX','GPSMotherY', 'GPSMotherZ']]
dfPercursoPontos = dfPercurso.loc[: , ['pontosX','pontosY', 'pontosZ']]

xlineTagQuadrado = dfQuadrado['GPSChildX'].values
ylineTagQuadrado = dfQuadrado['GPSChildY'].values
zlineTagQuadrado = dfQuadrado['GPSChildZ'].values

xlineTagPontos = dfQuadradoPontos['pontosX'].values
ylineTagPontos = dfQuadradoPontos['pontosY'].values
zlineTagPontos = dfQuadradoPontos['pontosZ'].values


print(dfQuadrado)

fig = plt.figure()

ax = plt.axes(projection='3d')

ax.plot3D(xlineTagQuadrado, ylineTagQuadrado, zlineTagQuadrado, 'gray')
# ax.plot3D(xlineTagPontos, ylineTagPontos, zlineTagPontos, 'green')


plt.show()

