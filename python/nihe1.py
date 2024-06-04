#encoding:utf-8
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

# ����΢�ַ���
def model(y, t, alpha, beta, gamma, delta):
    E = y
    dEdt = alpha * E * (1 - E) - beta * E + gamma * (1 - E) - delta * E
    return dEdt

# ��ʼ����
E0 = 0.1  # ��ʼ�г��ݶ�����ʼ����Դ����ռ10%��
t = np.linspace(0, 50, 500)  # ʱ�䷶Χ

# ����
alpha = 0.06#����Դ����ר����������0.97�����綯�������������̣�0.97
beta =  0.05#������̼�ŷ�����0.95
gamma =  0.07#������������������0.93��
delta =  0.0266#�����������أ�ȡ����ƽ��ֵ

# ���΢�ַ���
E = odeint(model, E0, t, args=(alpha, beta, gamma, delta))

# ��ͼ
plt.plot(t, E, label='Electric Vehicles')
plt.plot(t, 1 - E, label='Fuel Vehicles')
plt.xlabel('Time')
plt.ylabel('Market Share')
plt.legend()
plt.title('Market Share of Electric and Fuel Vehicles Over Time')
plt.show()
