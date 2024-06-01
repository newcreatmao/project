#encoding:utf-8
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
from scipy.stats import pearsonr

x = np.array([18.04531,24.155025,30.165375,54.159495,93.82,140.77])
y = np.array([21,24,27,30,33,36])
y1 = np.array([400,500,605,605,1032,1486])
y2 = np.array([10123,12345,15678,18901,23456,29635])
y3 = np.array([21.4,33,51.8,71.5,261.7,1024.8])
y4 = np.array([373.87,611,585,596,449,420])
y5 = np.array([107.8,111.1,113.5,114.7,121,134])
result = []
pc = pearsonr(x,y)
pc1 = pearsonr(x,y1)
pc2 = pearsonr(x,y2)
pc3 = pearsonr(x,y3)
pc4 = pearsonr(x,y4)
pc5 = pearsonr(x,y5)
result.append(round(pc[0],2))
result.append(round(pc1[0],2))
result.append(round(pc2[0],2))
result.append(round(pc3[0],2))
result.append(round(pc4[0],2))
result.append(round(pc5[0],2))

plt.rcParams['font.sans-serif'] = ['SimHei'] # 显示中文
X = ['政府积极\n政策数量','纯电动汽车\n最高续航里程','新能源汽车\n专利公开量','充电桩\n数量','电能每年\n平均价格','二氧化碳\n排放量']
fig = plt.figure()
plt.bar(X, result, color="steelblue")

for a,b in zip(X,result):   #柱子上的数字显示
    plt.text(a,b,'%.2f'%b,ha='center',va='bottom',fontsize=7)
print(result)



plt.xlabel("分类")
plt.ylabel("相关系数")
plt.title("发展得分及各相关系数的联系")

plt.show()
plt.savefig("barChart.jpg")


# # ����ع�ϵ��
# slope, intercept = np.polyfit(x, y, 1)

# # �����������
# plt.scatter(x, y)
# plt.plot(x, slope * x + intercept, color='red')

# plt.show()

# x = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
# y = np.array([2.5, 4.5, 4.8, 5.5, 6.0, 7.0, 7.8, 8.0, 9.0, 9.5])

# # �������ʽ�ع�ϵ��
# coefs = np.polyfit(x, y, 3)

# # ʹ��np.poly1d����������һ������ʽ��϶���
# poly = np.poly1d(coefs)

# # �����µĺ����꣬ʹ��������߸���ƽ��
# new_x = np.linspace(min(x), max(x), 1000)

# # �����������
# plt.scatter(x, y)
# plt.plot(new_x, poly(new_x), color='red')

# plt.show()

# import numpy as np
# import matplotlib.pyplot as plt
# from scipy.optimize import curve_fit

# def func(x, a, b, c):
#     return a * np.exp(-b * x) + c

# # ����ģ������
# x_data = np.linspace(0, 4, 50)
# y_data = func(x_data, 2.5, 1.3, 0.5) + 0.2 * np.random.normal(size=len(x_data))

# # ʹ��curve_fit��������Ϸ���������
# popt, pcov = curve_fit(func, x_data, y_data)

# # ����ԭʼ���ݺ��������
# plt.scatter(x_data, y_data, label="Data")
# plt.plot(x_data, func(x_data, *popt), color='red', label="Fitted curve")
# plt.legend()
# plt.show()

