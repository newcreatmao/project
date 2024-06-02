#encoding:utf-8
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

# 定义微分方程
def model(y, t, alpha, beta, gamma, delta):
    E = y
    dEdt = alpha * E * (1 - E) - beta * E + gamma * (1 - E) - delta * E
    return dEdt

# 初始条件
E0 = 0.1  # 初始市场份额（假设初始新能源汽车占10%）
t = np.linspace(0, 50, 500)  # 时间范围

# 参数
alpha = 0.07#政府积极政策数量，0.93
beta =  0.03#纯电动汽车最高续航里程，0.97
gamma =  0.03#新能源汽车专利公开量，0.97
delta =  0.05#二氧化碳排放量，0.95

# 求解微分方程
E = odeint(model, E0, t, args=(alpha, beta, gamma, delta))

# 绘图
plt.plot(t, E, label='Electric Vehicles')
plt.plot(t, 1 - E, label='Fuel Vehicles')
plt.xlabel('Time')
plt.ylabel('Market Share')
plt.legend()
plt.title('Market Share of Electric and Fuel Vehicles Over Time')
plt.show()
