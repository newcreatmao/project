#encoding:utf-8
import numpy as np
import pandas as pd
import statsmodels.api as sm

x = np.array([18.04531,24.155025,30.165375,54.159495,93.82,140.77])
y = np.array([21,24,27,30,33,36])
y1 = np.array([400,500,605,605,1032,1486])
y2 = np.array([10123,12345,15678,18901,23456,29635])
y3 = np.array([21.4,33,51.8,71.5,261.7,1024.8])
y4 = np.array([373.87,611,585,596,449,420])
y5 = np.array([107.8,111.1,113.5,114.7,121,134])

z = sm.add_constant(y) #生成自变量
z1 = sm.add_constant(y1) #生成自变量
z2 = sm.add_constant(y2) #生成自变量
z3 = sm.add_constant(y3) #生成自变量
z4 = sm.add_constant(y4) #生成自变量
z5 = sm.add_constant(y5) #生成自变量

model = sm.OLS(x, z) #生成模型
result = model.fit() #模型拟合
result.summary() #模型描述