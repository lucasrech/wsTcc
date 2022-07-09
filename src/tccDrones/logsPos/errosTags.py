from turtle import color
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sklearn.metrics as metric
from math import sqrt
import statistics
import os
import seaborn as sns

def warn(*args, **kwargs):
    pass
import warnings
warnings.warn = warn

# ---------------------------------------------------------------------------------------------------------------------
name495 = ["tag495Ponto1.csv", "tag495Ponto2.csv", "tag495Ponto3.csv", "tag495Ponto4.csv", "tag495Ponto5.csv"]
df495 = pd.DataFrame()
for file in name495:
    nome = os.path.join(r"src\tccDrones\logsPos", file)
    df495 = df495.append(pd.read_csv(nome, sep=";"))
# ---------------------------------------------------------------------------------------------------------------------

# ---------------------------------------------------------------------------------------------------------------------
name69 = ["tag69Ponto1.csv", "tag69Ponto2.csv", "tag69Ponto3.csv", "tag69Ponto4.csv", "tag69Ponto5.csv"]
df69 = pd.DataFrame()
for file in name69:
    nome = os.path.join(r"src\tccDrones\logsPos", file)
    df69 = df69.append(pd.read_csv(nome, sep=";"))
# ---------------------------------------------------------------------------------------------------------------------

# ---------------------------------------------------------------------------------------------------------------------
name94 = ["tag94Ponto1.csv", "tag94Ponto2.csv", "tag94Ponto3.csv", "tag94Ponto4.csv", "tag94Ponto5.csv"]
df94 = pd.DataFrame()
for file in name94:
    nome = os.path.join(r"src\tccDrones\logsPos", file)
    df94 = df94.append(pd.read_csv(nome, sep=";"))
# ---------------------------------------------------------------------------------------------------------------------

def doTag495():
    xTruePonto1 = np.full(100, 0)
    yTruePonto1 = np.full(100, 0)
    zTruePonto1 = np.full(100, 2.36)

    xTruePonto2 = np.full(100, 0.6)
    yTruePonto2 = np.full(100, 0.35)
    zTruePonto2 = np.full(100, 2.36)

    xTruePonto3 = np.full(100, 0.6)
    yTruePonto3 = np.full(100, -0.35)
    zTruePonto3 = np.full(100, 2.36)

    xTruePonto4 = np.full(100, -0.6)
    yTruePonto4 = np.full(100, 0.35)
    zTruePonto4 = np.full(100, 2.36)

    xTruePonto5 = np.full(100, -0.6)
    yTruePonto5 = np.full(100, -0.35)
    zTruePonto5 = np.full(100, 2.36)

    df495["Ponto"] = 1
    df495["Ponto"][100:200] = 2
    df495["Ponto"][200:300] = 3
    df495["Ponto"][300:400] = 4
    df495["Ponto"][400:500] = 5

    # --------- MEDIA --------------------------
    xMediaPonto1 = statistics.mean(df495[:100]["X"])
    yMediaPonto1 = statistics.mean(df495[:100]["Y"])
    zMediaPonto1 = statistics.mean(df495[:100]["Z"])
    xMediaPonto2 = statistics.mean(df495[100:200]["X"])
    yMediaPonto2 = statistics.mean(df495[100:200]["Y"])
    zMediaPonto2 = statistics.mean(df495[100:200]["Z"])
    xMediaPonto3 = statistics.mean(df495[200:300]["X"])
    yMediaPonto3 = statistics.mean(df495[200:300]["Y"])
    zMediaPonto3 = statistics.mean(df495[200:300]["Z"])
    xMediaPonto4 = statistics.mean(df495[300:400]["X"])
    yMediaPonto4 = statistics.mean(df495[300:400]["Y"])
    zMediaPonto4 = statistics.mean(df495[300:400]["Z"])
    xMediaPonto5 = statistics.mean(df495[400:500]["X"])
    yMediaPonto5 = statistics.mean(df495[400:500]["Y"])
    zMediaPonto5 = statistics.mean(df495[400:500]["Z"])
    # --------- MEDIANA --------------------------
    xMedianaPonto1 = statistics.median(df495[:100]["X"])
    yMedianaPonto1 = statistics.median(df495[:100]["Y"])
    zMedianaPonto1 = statistics.median(df495[:100]["Z"])
    xMedianaPonto2 = statistics.median(df495[100:200]["X"])
    yMedianaPonto2 = statistics.median(df495[100:200]["Y"])
    zMedianaPonto2 = statistics.median(df495[100:200]["Z"])
    xMedianaPonto3 = statistics.median(df495[200:300]["X"])
    yMedianaPonto3 = statistics.median(df495[200:300]["Y"])
    zMedianaPonto3 = statistics.median(df495[200:300]["Z"])
    xMedianaPonto4 = statistics.median(df495[300:400]["X"])
    yMedianaPonto4 = statistics.median(df495[300:400]["Y"])
    zMedianaPonto4 = statistics.median(df495[300:400]["Z"])
    xMedianaPonto5 = statistics.median(df495[400:500]["X"])
    yMedianaPonto5 = statistics.median(df495[400:500]["Y"])
    zMedianaPonto5 = statistics.median(df495[400:500]["Z"])

    # --------- DESVIO MEDIO --------------------------
    xStDevPonto1 = statistics.stdev(df495[:100]["X"])
    yStDevPonto1 = statistics.stdev(df495[:100]["Y"])
    zStDevPonto1 = statistics.stdev(df495[:100]["Z"])
    xStDevPonto2 = statistics.stdev(df495[100:200]["X"])
    yStDevPonto2 = statistics.stdev(df495[100:200]["Y"])
    zStDevPonto2 = statistics.stdev(df495[100:200]["Z"])
    xStDevPonto3 = statistics.stdev(df495[200:300]["X"])
    yStDevPonto3 = statistics.stdev(df495[200:300]["Y"])
    zStDevPonto3 = statistics.stdev(df495[200:300]["Z"])
    xStDevPonto4 = statistics.stdev(df495[300:400]["X"])
    yStDevPonto4 = statistics.stdev(df495[300:400]["Y"])
    zStDevPonto4 = statistics.stdev(df495[300:400]["Z"])
    xStDevPonto5 = statistics.stdev(df495[400:500]["X"])
    yStDevPonto5 = statistics.stdev(df495[400:500]["Y"])
    zStDevPonto5 = statistics.stdev(df495[400:500]["Z"])

    # --------- ERRO QUADRATICO MEDIO | RAIZ QUADRADO DO ERRO MÉDIO --------------------------
    mseXPonto1 = metric.mean_squared_error(xTruePonto1, df495[:100]["X"])
    rmseXPonto1 = sqrt(mseXPonto1)
    mseYPonto1 = metric.mean_squared_error(yTruePonto1, df495[:100]["Y"])
    rmseYPonto1 = sqrt(mseYPonto1)
    mseZPonto1 = metric.mean_squared_error(zTruePonto1, df495[:100]["Z"])
    rmseZPonto1 = sqrt(mseZPonto1)
    mseXPonto2 = metric.mean_squared_error(xTruePonto2, df495[100:200]["X"])
    rmseXPonto2 = sqrt(mseXPonto2)
    mseYPonto2 = metric.mean_squared_error(yTruePonto2, df495[100:200]["Y"])
    rmseYPonto2 = sqrt(mseYPonto2)
    mseZPonto2 = metric.mean_squared_error(zTruePonto2, df495[100:200]["Z"])
    rmseZPonto2 = sqrt(mseZPonto2)
    mseXPonto3 = metric.mean_squared_error(xTruePonto3, df495[200:300]["X"])
    rmseXPonto3 = sqrt(mseXPonto3)
    mseYPonto3 = metric.mean_squared_error(yTruePonto3, df495[200:300]["Y"])
    rmseYPonto3 = sqrt(mseYPonto3)
    mseZPonto3 = metric.mean_squared_error(zTruePonto3, df495[200:300]["Z"])
    rmseZPonto3 = sqrt(mseZPonto3)
    mseXPonto4 = metric.mean_squared_error(xTruePonto4, df495[300:400]["X"])
    rmseXPonto4 = sqrt(mseXPonto4)
    mseYPonto4 = metric.mean_squared_error(yTruePonto4, df495[300:400]["Y"])
    rmseYPonto4 = sqrt(mseYPonto4)
    mseZPonto4 = metric.mean_squared_error(zTruePonto4, df495[300:400]["Z"])
    rmseZPonto4 = sqrt(mseZPonto4)
    mseXPonto5 = metric.mean_squared_error(xTruePonto5, df495[400:500]["X"])
    rmseXPonto5 = sqrt(mseXPonto5)
    mseYPonto5 = metric.mean_squared_error(yTruePonto5, df495[400:500]["Y"])
    rmseYPonto5 = sqrt(mseYPonto5)
    mseZPonto5 = metric.mean_squared_error(zTruePonto5, df495[400:500]["Z"])
    rmseZPonto5 = sqrt(mseZPonto5)

    # --------- MAX E MIN --------------------------
    xMaxPonto1 = df495[:100]["X"].max()
    yMaxPonto1 = df495[:100]["Y"].max()
    zMaxPonto1 = df495[:100]["Z"].max()
    xMaxPonto2 = df495[100:200]["X"].max()
    yMaxPonto2 = df495[100:200]["Y"].max()
    zMaxPonto2 = df495[100:200]["Z"].max()
    xMaxPonto3 = df495[200:300]["X"].max()
    yMaxPonto3 = df495[200:300]["Y"].max()
    zMaxPonto3 = df495[200:300]["Z"].max()
    xMaxPonto4 = df495[300:400]["X"].max()
    yMaxPonto4 = df495[300:400]["Y"].max()
    zMaxPonto4 = df495[300:400]["Z"].max()
    xMaxPonto5 = df495[400:500]["X"].max()
    yMaxPonto5 = df495[400:500]["Y"].max()
    zMaxPonto5 = df495[400:500]["Z"].max()

    xMinPonto1 = df495[:100]["X"].min()
    yMinPonto1 = df495[:100]["Y"].min()
    zMinPonto1 = df495[:100]["Z"].min()
    xMinPonto2 = df495[100:200]["X"].min()
    yMinPonto2 = df495[100:200]["Y"].min()
    zMinPonto2 = df495[100:200]["Z"].min()
    xMinPonto3 = df495[200:300]["X"].min()
    yMinPonto3 = df495[200:300]["Y"].min()
    zMinPonto3 = df495[200:300]["Z"].min()
    xMinPonto4 = df495[300:400]["X"].min()
    yMinPonto4 = df495[300:400]["Y"].min()
    zMinPonto4 = df495[300:400]["Z"].min()
    xMinPonto5 = df495[400:500]["X"].min()
    yMinPonto5 = df495[400:500]["Y"].min()
    zMinPonto5 = df495[400:500]["Z"].min()

    d = {'Ponto' : [1,2,3,4,5],
         'Media_X' : [xMediaPonto1, xMediaPonto2, xMediaPonto3, xMediaPonto4, xMediaPonto5],
         'Media_Y' : [yMediaPonto1, yMediaPonto2, yMediaPonto3, yMediaPonto4, yMediaPonto5],
         'Media_Z' : [zMediaPonto1, zMediaPonto2, zMediaPonto3, zMediaPonto4, zMediaPonto5],
         'Mediana_X' : [xMedianaPonto1, xMedianaPonto2, xMedianaPonto3, xMedianaPonto4, xMedianaPonto5],
         'Mediana_Y' : [yMedianaPonto1, yMedianaPonto2, yMedianaPonto3, yMedianaPonto4, yMedianaPonto5],
         'Mediana_Z' : [zMedianaPonto1, zMedianaPonto2, zMedianaPonto3, zMedianaPonto4, zMedianaPonto5],
         'StDev_X' : [xStDevPonto1, xStDevPonto2, xStDevPonto3, xStDevPonto4, xStDevPonto5],
         'StDev_Y' : [yStDevPonto1, yStDevPonto2, yStDevPonto3, yStDevPonto4, yStDevPonto5],
         'StDev_Z' : [zStDevPonto1, zStDevPonto2, zStDevPonto3, zStDevPonto4, zStDevPonto5],
         'Max_X' : [xMaxPonto1, xMaxPonto2, xMaxPonto3, xMaxPonto4, xMaxPonto5],
         'Max_Y' : [yMaxPonto1, yMaxPonto2, yMaxPonto3, yMaxPonto4, yMaxPonto5],
         'Max_Z' : [zMaxPonto1, zMaxPonto2, zMaxPonto3, zMaxPonto4, zMaxPonto5],
         'Min_X' : [xMinPonto1, xMinPonto2, xMinPonto3, xMinPonto4, xMinPonto5],
         'Min_Y' : [yMinPonto1, yMinPonto2, yMinPonto3, yMinPonto4, yMinPonto5],
         'Min_Z' : [zMinPonto1, zMinPonto2, zMinPonto3, zMinPonto4, zMinPonto5],
         'mse_X' : [mseXPonto1, mseXPonto2, mseXPonto3, mseXPonto4, mseXPonto5],
         'mse_Y' : [mseYPonto1, mseYPonto2, mseYPonto3, mseYPonto4, mseYPonto5],
         'mse_Z' : [mseZPonto1, mseZPonto2, mseZPonto3, mseZPonto4, mseZPonto5],
         'rmse_X' : [rmseXPonto1, rmseXPonto2, rmseXPonto3, rmseXPonto4, rmseXPonto5],
         'rmse_Y' : [rmseYPonto1, rmseYPonto2, rmseYPonto3, rmseYPonto4, rmseYPonto5],
         'rmse_Z' : [rmseZPonto1, rmseZPonto2, rmseZPonto3, rmseZPonto4, rmseZPonto5]
         }

    dfSave = pd.DataFrame(data=d)
    dfSave.to_csv("errosTag495.csv", index=False)
    return dfSave
# ---------------------------------------------------------------------------------------------------------

# ---------------------------------------------------------------------------------------------------------
def doTag69():
    xTruePonto1 = np.full(100, 0)
    yTruePonto1 = np.full(100, 0)
    zTruePonto1 = np.full(100, 2.36)

    xTruePonto2 = np.full(100, 0.6)
    yTruePonto2 = np.full(100, 0.35)
    zTruePonto2 = np.full(100, 2.36)

    xTruePonto3 = np.full(100, 0.6)
    yTruePonto3 = np.full(100, -0.35)
    zTruePonto3 = np.full(100, 2.36)

    xTruePonto4 = np.full(100, -0.6)
    yTruePonto4 = np.full(100, 0.35)
    zTruePonto4 = np.full(100, 2.36)

    xTruePonto5 = np.full(100, -0.6)
    yTruePonto5 = np.full(100, -0.35)
    zTruePonto5 = np.full(100, 2.36)

    df69["Ponto"] = 1
    df69["Ponto"][100:200] = 2
    df69["Ponto"][200:300] = 3
    df69["Ponto"][300:400] = 4
    df69["Ponto"][400:500] = 5

    # --------- MEDIA --------------------------
    xMediaPonto1 = statistics.mean(df69[:100]["X"])
    yMediaPonto1 = statistics.mean(df69[:100]["Y"])
    zMediaPonto1 = statistics.mean(df69[:100]["Z"])
    xMediaPonto2 = statistics.mean(df69[100:200]["X"])
    yMediaPonto2 = statistics.mean(df69[100:200]["Y"])
    zMediaPonto2 = statistics.mean(df69[100:200]["Z"])
    xMediaPonto3 = statistics.mean(df69[200:300]["X"])
    yMediaPonto3 = statistics.mean(df69[200:300]["Y"])
    zMediaPonto3 = statistics.mean(df69[200:300]["Z"])
    xMediaPonto4 = statistics.mean(df69[300:400]["X"])
    yMediaPonto4 = statistics.mean(df69[300:400]["Y"])
    zMediaPonto4 = statistics.mean(df69[300:400]["Z"])
    xMediaPonto5 = statistics.mean(df69[400:500]["X"])
    yMediaPonto5 = statistics.mean(df69[400:500]["Y"])
    zMediaPonto5 = statistics.mean(df69[400:500]["Z"])
    # --------- MEDIANA --------------------------
    xMedianaPonto1 = statistics.median(df69[:100]["X"])
    yMedianaPonto1 = statistics.median(df69[:100]["Y"])
    zMedianaPonto1 = statistics.median(df69[:100]["Z"])
    xMedianaPonto2 = statistics.median(df69[100:200]["X"])
    yMedianaPonto2 = statistics.median(df69[100:200]["Y"])
    zMedianaPonto2 = statistics.median(df69[100:200]["Z"])
    xMedianaPonto3 = statistics.median(df69[200:300]["X"])
    yMedianaPonto3 = statistics.median(df69[200:300]["Y"])
    zMedianaPonto3 = statistics.median(df69[200:300]["Z"])
    xMedianaPonto4 = statistics.median(df69[300:400]["X"])
    yMedianaPonto4 = statistics.median(df69[300:400]["Y"])
    zMedianaPonto4 = statistics.median(df69[300:400]["Z"])
    xMedianaPonto5 = statistics.median(df69[400:500]["X"])
    yMedianaPonto5 = statistics.median(df69[400:500]["Y"])
    zMedianaPonto5 = statistics.median(df69[400:500]["Z"])

    # --------- DESVIO MEDIO --------------------------
    xStDevPonto1 = statistics.stdev(df69[:100]["X"])
    yStDevPonto1 = statistics.stdev(df69[:100]["Y"])
    zStDevPonto1 = statistics.stdev(df69[:100]["Z"])
    xStDevPonto2 = statistics.stdev(df69[100:200]["X"])
    yStDevPonto2 = statistics.stdev(df69[100:200]["Y"])
    zStDevPonto2 = statistics.stdev(df69[100:200]["Z"])
    xStDevPonto3 = statistics.stdev(df69[200:300]["X"])
    yStDevPonto3 = statistics.stdev(df69[200:300]["Y"])
    zStDevPonto3 = statistics.stdev(df69[200:300]["Z"])
    xStDevPonto4 = statistics.stdev(df69[300:400]["X"])
    yStDevPonto4 = statistics.stdev(df69[300:400]["Y"])
    zStDevPonto4 = statistics.stdev(df69[300:400]["Z"])
    xStDevPonto5 = statistics.stdev(df69[400:500]["X"])
    yStDevPonto5 = statistics.stdev(df69[400:500]["Y"])
    zStDevPonto5 = statistics.stdev(df69[400:500]["Z"])

    # --------- ERRO QUADRATICO MEDIO | RAIZ QUADRADO DO ERRO MÉDIO --------------------------
    mseXPonto1 = metric.mean_squared_error(xTruePonto1, df69[:100]["X"])
    rmseXPonto1 = sqrt(mseXPonto1)
    mseYPonto1 = metric.mean_squared_error(yTruePonto1, df69[:100]["Y"])
    rmseYPonto1 = sqrt(mseYPonto1)
    mseZPonto1 = metric.mean_squared_error(zTruePonto1, df69[:100]["Z"])
    rmseZPonto1 = sqrt(mseZPonto1)
    mseXPonto2 = metric.mean_squared_error(xTruePonto2, df69[100:200]["X"])
    rmseXPonto2 = sqrt(mseXPonto2)
    mseYPonto2 = metric.mean_squared_error(yTruePonto2, df69[100:200]["Y"])
    rmseYPonto2 = sqrt(mseYPonto2)
    mseZPonto2 = metric.mean_squared_error(zTruePonto2, df69[100:200]["Z"])
    rmseZPonto2 = sqrt(mseZPonto2)
    mseXPonto3 = metric.mean_squared_error(xTruePonto3, df69[200:300]["X"])
    rmseXPonto3 = sqrt(mseXPonto3)
    mseYPonto3 = metric.mean_squared_error(yTruePonto3, df69[200:300]["Y"])
    rmseYPonto3 = sqrt(mseYPonto3)
    mseZPonto3 = metric.mean_squared_error(zTruePonto3, df69[200:300]["Z"])
    rmseZPonto3 = sqrt(mseZPonto3)
    mseXPonto4 = metric.mean_squared_error(xTruePonto4, df69[300:400]["X"])
    rmseXPonto4 = sqrt(mseXPonto4)
    mseYPonto4 = metric.mean_squared_error(yTruePonto4, df69[300:400]["Y"])
    rmseYPonto4 = sqrt(mseYPonto4)
    mseZPonto4 = metric.mean_squared_error(zTruePonto4, df69[300:400]["Z"])
    rmseZPonto4 = sqrt(mseZPonto4)
    mseXPonto5 = metric.mean_squared_error(xTruePonto5, df69[400:500]["X"])
    rmseXPonto5 = sqrt(mseXPonto5)
    mseYPonto5 = metric.mean_squared_error(yTruePonto5, df69[400:500]["Y"])
    rmseYPonto5 = sqrt(mseYPonto5)
    mseZPonto5 = metric.mean_squared_error(zTruePonto5, df69[400:500]["Z"])
    rmseZPonto5 = sqrt(mseZPonto5)

    # --------- MAX E MIN --------------------------
    xMaxPonto1 = df69[:100]["X"].max()
    yMaxPonto1 = df69[:100]["Y"].max()
    zMaxPonto1 = df69[:100]["Z"].max()
    xMaxPonto2 = df69[100:200]["X"].max()
    yMaxPonto2 = df69[100:200]["Y"].max()
    zMaxPonto2 = df69[100:200]["Z"].max()
    xMaxPonto3 = df69[200:300]["X"].max()
    yMaxPonto3 = df69[200:300]["Y"].max()
    zMaxPonto3 = df69[200:300]["Z"].max()
    xMaxPonto4 = df69[300:400]["X"].max()
    yMaxPonto4 = df69[300:400]["Y"].max()
    zMaxPonto4 = df69[300:400]["Z"].max()
    xMaxPonto5 = df69[400:500]["X"].max()
    yMaxPonto5 = df69[400:500]["Y"].max()
    zMaxPonto5 = df69[400:500]["Z"].max()

    xMinPonto1 = df69[:100]["X"].min()
    yMinPonto1 = df69[:100]["Y"].min()
    zMinPonto1 = df69[:100]["Z"].min()
    xMinPonto2 = df69[100:200]["X"].min()
    yMinPonto2 = df69[100:200]["Y"].min()
    zMinPonto2 = df69[100:200]["Z"].min()
    xMinPonto3 = df69[200:300]["X"].min()
    yMinPonto3 = df69[200:300]["Y"].min()
    zMinPonto3 = df69[200:300]["Z"].min()
    xMinPonto4 = df69[300:400]["X"].min()
    yMinPonto4 = df69[300:400]["Y"].min()
    zMinPonto4 = df69[300:400]["Z"].min()
    xMinPonto5 = df69[400:500]["X"].min()
    yMinPonto5 = df69[400:500]["Y"].min()
    zMinPonto5 = df69[400:500]["Z"].min()

    d = {'Ponto' : [1,2,3,4,5],
         'Media_X' : [xMediaPonto1, xMediaPonto2, xMediaPonto3, xMediaPonto4, xMediaPonto5],
         'Media_Y' : [yMediaPonto1, yMediaPonto2, yMediaPonto3, yMediaPonto4, yMediaPonto5],
         'Media_Z' : [zMediaPonto1, zMediaPonto2, zMediaPonto3, zMediaPonto4, zMediaPonto5],
         'Mediana_X' : [xMedianaPonto1, xMedianaPonto2, xMedianaPonto3, xMedianaPonto4, xMedianaPonto5],
         'Mediana_Y' : [yMedianaPonto1, yMedianaPonto2, yMedianaPonto3, yMedianaPonto4, yMedianaPonto5],
         'Mediana_Z' : [zMedianaPonto1, zMedianaPonto2, zMedianaPonto3, zMedianaPonto4, zMedianaPonto5],
         'StDev_X' : [xStDevPonto1, xStDevPonto2, xStDevPonto3, xStDevPonto4, xStDevPonto5],
         'StDev_Y' : [yStDevPonto1, yStDevPonto2, yStDevPonto3, yStDevPonto4, yStDevPonto5],
         'StDev_Z' : [zStDevPonto1, zStDevPonto2, zStDevPonto3, zStDevPonto4, zStDevPonto5],
         'Max_X' : [xMaxPonto1, xMaxPonto2, xMaxPonto3, xMaxPonto4, xMaxPonto5],
         'Max_Y' : [yMaxPonto1, yMaxPonto2, yMaxPonto3, yMaxPonto4, yMaxPonto5],
         'Max_Z' : [zMaxPonto1, zMaxPonto2, zMaxPonto3, zMaxPonto4, zMaxPonto5],
         'Min_X' : [xMinPonto1, xMinPonto2, xMinPonto3, xMinPonto4, xMinPonto5],
         'Min_Y' : [yMinPonto1, yMinPonto2, yMinPonto3, yMinPonto4, yMinPonto5],
         'Min_Z' : [zMinPonto1, zMinPonto2, zMinPonto3, zMinPonto4, zMinPonto5],
         'mse_X' : [mseXPonto1, mseXPonto2, mseXPonto3, mseXPonto4, mseXPonto5],
         'mse_Y' : [mseYPonto1, mseYPonto2, mseYPonto3, mseYPonto4, mseYPonto5],
         'mse_Z' : [mseZPonto1, mseZPonto2, mseZPonto3, mseZPonto4, mseZPonto5],
         'rmse_X' : [rmseXPonto1, rmseXPonto2, rmseXPonto3, rmseXPonto4, rmseXPonto5],
         'rmse_Y' : [rmseYPonto1, rmseYPonto2, rmseYPonto3, rmseYPonto4, rmseYPonto5],
         'rmse_Z' : [rmseZPonto1, rmseZPonto2, rmseZPonto3, rmseZPonto4, rmseZPonto5]
         }

    dfSave = pd.DataFrame(data=d)
    dfSave.to_csv("errosTag69.csv", index=False)
    return dfSave
# ---------------------------------------------------------------------------------------------------------

# ---------------------------------------------------------------------------------------------------------
def doTag94():
    xTruePonto1 = np.full(100, 0)
    yTruePonto1 = np.full(100, 0)
    zTruePonto1 = np.full(100, 2.36)

    xTruePonto2 = np.full(100, 0.6)
    yTruePonto2 = np.full(100, 0.35)
    zTruePonto2 = np.full(100, 2.36)

    xTruePonto3 = np.full(100, 0.6)
    yTruePonto3 = np.full(100, -0.35)
    zTruePonto3 = np.full(100, 2.36)

    xTruePonto4 = np.full(100, -0.6)
    yTruePonto4 = np.full(100, 0.35)
    zTruePonto4 = np.full(100, 2.36)

    xTruePonto5 = np.full(100, -0.6)
    yTruePonto5 = np.full(100, -0.35)
    zTruePonto5 = np.full(100, 2.36)

    df94["Ponto"] = 1
    df94["Ponto"][100:200] = 2
    df94["Ponto"][200:300] = 3
    df94["Ponto"][300:400] = 4
    df94["Ponto"][400:500] = 5

    # --------- MEDIA --------------------------
    xMediaPonto1 = statistics.mean(df94[:100]["X"])
    yMediaPonto1 = statistics.mean(df94[:100]["Y"])
    zMediaPonto1 = statistics.mean(df94[:100]["Z"])
    xMediaPonto2 = statistics.mean(df94[100:200]["X"])
    yMediaPonto2 = statistics.mean(df94[100:200]["Y"])
    zMediaPonto2 = statistics.mean(df94[100:200]["Z"])
    xMediaPonto3 = statistics.mean(df94[200:300]["X"])
    yMediaPonto3 = statistics.mean(df94[200:300]["Y"])
    zMediaPonto3 = statistics.mean(df94[200:300]["Z"])
    xMediaPonto4 = statistics.mean(df94[300:400]["X"])
    yMediaPonto4 = statistics.mean(df94[300:400]["Y"])
    zMediaPonto4 = statistics.mean(df94[300:400]["Z"])
    xMediaPonto5 = statistics.mean(df94[400:500]["X"])
    yMediaPonto5 = statistics.mean(df94[400:500]["Y"])
    zMediaPonto5 = statistics.mean(df94[400:500]["Z"])
    # --------- MEDIANA --------------------------
    xMedianaPonto1 = statistics.median(df94[:100]["X"])
    yMedianaPonto1 = statistics.median(df94[:100]["Y"])
    zMedianaPonto1 = statistics.median(df94[:100]["Z"])
    xMedianaPonto2 = statistics.median(df94[100:200]["X"])
    yMedianaPonto2 = statistics.median(df94[100:200]["Y"])
    zMedianaPonto2 = statistics.median(df94[100:200]["Z"])
    xMedianaPonto3 = statistics.median(df94[200:300]["X"])
    yMedianaPonto3 = statistics.median(df94[200:300]["Y"])
    zMedianaPonto3 = statistics.median(df94[200:300]["Z"])
    xMedianaPonto4 = statistics.median(df94[300:400]["X"])
    yMedianaPonto4 = statistics.median(df94[300:400]["Y"])
    zMedianaPonto4 = statistics.median(df94[300:400]["Z"])
    xMedianaPonto5 = statistics.median(df94[400:500]["X"])
    yMedianaPonto5 = statistics.median(df94[400:500]["Y"])
    zMedianaPonto5 = statistics.median(df94[400:500]["Z"])

    # --------- DESVIO MEDIO --------------------------
    xStDevPonto1 = statistics.stdev(df94[:100]["X"])
    yStDevPonto1 = statistics.stdev(df94[:100]["Y"])
    zStDevPonto1 = statistics.stdev(df94[:100]["Z"])
    xStDevPonto2 = statistics.stdev(df94[100:200]["X"])
    yStDevPonto2 = statistics.stdev(df94[100:200]["Y"])
    zStDevPonto2 = statistics.stdev(df94[100:200]["Z"])
    xStDevPonto3 = statistics.stdev(df94[200:300]["X"])
    yStDevPonto3 = statistics.stdev(df94[200:300]["Y"])
    zStDevPonto3 = statistics.stdev(df94[200:300]["Z"])
    xStDevPonto4 = statistics.stdev(df94[300:400]["X"])
    yStDevPonto4 = statistics.stdev(df94[300:400]["Y"])
    zStDevPonto4 = statistics.stdev(df94[300:400]["Z"])
    xStDevPonto5 = statistics.stdev(df94[400:500]["X"])
    yStDevPonto5 = statistics.stdev(df94[400:500]["Y"])
    zStDevPonto5 = statistics.stdev(df94[400:500]["Z"])

    # --------- ERRO QUADRATICO MEDIO | RAIZ QUADRADO DO ERRO MÉDIO --------------------------
    mseXPonto1 = metric.mean_squared_error(xTruePonto1, df94[:100]["X"])
    rmseXPonto1 = sqrt(mseXPonto1)
    mseYPonto1 = metric.mean_squared_error(yTruePonto1, df94[:100]["Y"])
    rmseYPonto1 = sqrt(mseYPonto1)
    mseZPonto1 = metric.mean_squared_error(zTruePonto1, df94[:100]["Z"])
    rmseZPonto1 = sqrt(mseZPonto1)
    mseXPonto2 = metric.mean_squared_error(xTruePonto2, df94[100:200]["X"])
    rmseXPonto2 = sqrt(mseXPonto2)
    mseYPonto2 = metric.mean_squared_error(yTruePonto2, df94[100:200]["Y"])
    rmseYPonto2 = sqrt(mseYPonto2)
    mseZPonto2 = metric.mean_squared_error(zTruePonto2, df94[100:200]["Z"])
    rmseZPonto2 = sqrt(mseZPonto2)
    mseXPonto3 = metric.mean_squared_error(xTruePonto3, df94[200:300]["X"])
    rmseXPonto3 = sqrt(mseXPonto3)
    mseYPonto3 = metric.mean_squared_error(yTruePonto3, df94[200:300]["Y"])
    rmseYPonto3 = sqrt(mseYPonto3)
    mseZPonto3 = metric.mean_squared_error(zTruePonto3, df94[200:300]["Z"])
    rmseZPonto3 = sqrt(mseZPonto3)
    mseXPonto4 = metric.mean_squared_error(xTruePonto4, df94[300:400]["X"])
    rmseXPonto4 = sqrt(mseXPonto4)
    mseYPonto4 = metric.mean_squared_error(yTruePonto4, df94[300:400]["Y"])
    rmseYPonto4 = sqrt(mseYPonto4)
    mseZPonto4 = metric.mean_squared_error(zTruePonto4, df94[300:400]["Z"])
    rmseZPonto4 = sqrt(mseZPonto4)
    mseXPonto5 = metric.mean_squared_error(xTruePonto5, df94[400:500]["X"])
    rmseXPonto5 = sqrt(mseXPonto5)
    mseYPonto5 = metric.mean_squared_error(yTruePonto5, df94[400:500]["Y"])
    rmseYPonto5 = sqrt(mseYPonto5)
    mseZPonto5 = metric.mean_squared_error(zTruePonto5, df94[400:500]["Z"])
    rmseZPonto5 = sqrt(mseZPonto5)

    # --------- MAX E MIN --------------------------
    xMaxPonto1 = df94[:100]["X"].max()
    yMaxPonto1 = df94[:100]["Y"].max()
    zMaxPonto1 = df94[:100]["Z"].max()
    xMaxPonto2 = df94[100:200]["X"].max()
    yMaxPonto2 = df94[100:200]["Y"].max()
    zMaxPonto2 = df94[100:200]["Z"].max()
    xMaxPonto3 = df94[200:300]["X"].max()
    yMaxPonto3 = df94[200:300]["Y"].max()
    zMaxPonto3 = df94[200:300]["Z"].max()
    xMaxPonto4 = df94[300:400]["X"].max()
    yMaxPonto4 = df94[300:400]["Y"].max()
    zMaxPonto4 = df94[300:400]["Z"].max()
    xMaxPonto5 = df94[400:500]["X"].max()
    yMaxPonto5 = df94[400:500]["Y"].max()
    zMaxPonto5 = df94[400:500]["Z"].max()

    xMinPonto1 = df94[:100]["X"].min()
    yMinPonto1 = df94[:100]["Y"].min()
    zMinPonto1 = df94[:100]["Z"].min()
    xMinPonto2 = df94[100:200]["X"].min()
    yMinPonto2 = df94[100:200]["Y"].min()
    zMinPonto2 = df94[100:200]["Z"].min()
    xMinPonto3 = df94[200:300]["X"].min()
    yMinPonto3 = df94[200:300]["Y"].min()
    zMinPonto3 = df94[200:300]["Z"].min()
    xMinPonto4 = df94[300:400]["X"].min()
    yMinPonto4 = df94[300:400]["Y"].min()
    zMinPonto4 = df94[300:400]["Z"].min()
    xMinPonto5 = df94[400:500]["X"].min()
    yMinPonto5 = df94[400:500]["Y"].min()
    zMinPonto5 = df94[400:500]["Z"].min()

    d = {'Ponto' : [1,2,3,4,5],
         'Media_X' : [xMediaPonto1, xMediaPonto2, xMediaPonto3, xMediaPonto4, xMediaPonto5],
         'Media_Y' : [yMediaPonto1, yMediaPonto2, yMediaPonto3, yMediaPonto4, yMediaPonto5],
         'Media_Z' : [zMediaPonto1, zMediaPonto2, zMediaPonto3, zMediaPonto4, zMediaPonto5],
         'Mediana_X' : [xMedianaPonto1, xMedianaPonto2, xMedianaPonto3, xMedianaPonto4, xMedianaPonto5],
         'Mediana_Y' : [yMedianaPonto1, yMedianaPonto2, yMedianaPonto3, yMedianaPonto4, yMedianaPonto5],
         'Mediana_Z' : [zMedianaPonto1, zMedianaPonto2, zMedianaPonto3, zMedianaPonto4, zMedianaPonto5],
         'StDev_X' : [xStDevPonto1, xStDevPonto2, xStDevPonto3, xStDevPonto4, xStDevPonto5],
         'StDev_Y' : [yStDevPonto1, yStDevPonto2, yStDevPonto3, yStDevPonto4, yStDevPonto5],
         'StDev_Z' : [zStDevPonto1, zStDevPonto2, zStDevPonto3, zStDevPonto4, zStDevPonto5],
         'Max_X' : [xMaxPonto1, xMaxPonto2, xMaxPonto3, xMaxPonto4, xMaxPonto5],
         'Max_Y' : [yMaxPonto1, yMaxPonto2, yMaxPonto3, yMaxPonto4, yMaxPonto5],
         'Max_Z' : [zMaxPonto1, zMaxPonto2, zMaxPonto3, zMaxPonto4, zMaxPonto5],
         'Min_X' : [xMinPonto1, xMinPonto2, xMinPonto3, xMinPonto4, xMinPonto5],
         'Min_Y' : [yMinPonto1, yMinPonto2, yMinPonto3, yMinPonto4, yMinPonto5],
         'Min_Z' : [zMinPonto1, zMinPonto2, zMinPonto3, zMinPonto4, zMinPonto5],
         'mse_X' : [mseXPonto1, mseXPonto2, mseXPonto3, mseXPonto4, mseXPonto5],
         'mse_Y' : [mseYPonto1, mseYPonto2, mseYPonto3, mseYPonto4, mseYPonto5],
         'mse_Z' : [mseZPonto1, mseZPonto2, mseZPonto3, mseZPonto4, mseZPonto5],
         'rmse_X' : [rmseXPonto1, rmseXPonto2, rmseXPonto3, rmseXPonto4, rmseXPonto5],
         'rmse_Y' : [rmseYPonto1, rmseYPonto2, rmseYPonto3, rmseYPonto4, rmseYPonto5],
         'rmse_Z' : [rmseZPonto1, rmseZPonto2, rmseZPonto3, rmseZPonto4, rmseZPonto5]
         }

    dfSave = pd.DataFrame(data=d)
    dfSave.to_csv("errosTag94.csv", index=False)

    return dfSave
# ---------------------------------------------------------------------------------------------------------

# ---------------------------------------------------------------------------------------------------------
def graphError(dfErro495, dfErro69, dfErro94):
    # fig1 = plt.figure(1)

    labels = ['4.95', '6.9', '9.4']
    x = np.arange(len(labels))  # the label locations
    width = 0.35  # the width of the bars

    erroInX = [dfErro495.loc[0, 'rmse_X'], dfErro69.loc[0, 'rmse_X'], dfErro94.loc[0, 'rmse_X']]
    erroInY = [dfErro495.loc[0, 'rmse_Y'], dfErro69.loc[0, 'rmse_Y'], dfErro94.loc[0, 'rmse_Y']]
    erroInZ = [dfErro495.loc[0, 'rmse_Y'], dfErro69.loc[0, 'rmse_Y'], dfErro94.loc[0, 'rmse_Y']]

    fig, ax = plt.subplots()
    rects = ax.bar(x , erroInX, width, color=['lightsteelblue', 'paleturquoise', 'lightskyblue'])
    ax.set_title('Root mean square error in X-axis with different sizes tags')
    ax.set_xlabel('Size of the tags (cm)')
    ax.set_ylabel('Root mean square error')
    ax.set_xticks(x, labels)
    ax.bar_label(rects, padding=3)

    fig, ax = plt.subplots()
    rects = ax.bar(x , erroInY, width, color=['lightsteelblue', 'paleturquoise', 'lightskyblue'])
    ax.set_title('Root mean square error in Y-axis with different sizes tags')
    ax.set_xlabel('Size of the tags (cm)')
    ax.set_ylabel('Root mean square error')
    ax.set_xticks(x, labels)
    ax.bar_label(rects, padding=3)

    fig, ax = plt.subplots()
    rects = ax.bar(x , erroInZ, width, color=['lightsteelblue', 'paleturquoise', 'lightskyblue'])
    ax.set_title('Root mean square error in Z-axis with different sizes tags')
    ax.set_xlabel('Size of the tags (cm)')
    ax.set_ylabel('Root mean square error')
    ax.set_xticks(x, labels)
    ax.bar_label(rects, padding=3)
   

    

    # fig2 = plt.figure(2)

# ---------------------------------------------------------------------------------------------------------
def main():
   
    dfErro495 = doTag495()
    dfErro69 = doTag69()
    dfErro94 = doTag94()
    graphError(dfErro495, dfErro69, dfErro94)
    plt.show()
    

if __name__ == "__main__":
    main()
# ---------------------------------------------------------------------------------------------------------
