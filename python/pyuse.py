#encoding:utf-8
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
from scipy.stats import pearsonr

x = np.array([100.1262,102.2305,111.2875,299.1899,566.4,774.4])
y = np.array([21,24,27,30,33,36])
y1 = np.array([400,500,605,605,1032,1486])
y2 = np.array([10123,12345,15678,18901,23456,29635])
y3 = np.array([21.4,33,51.8,71.5,261.7,1024.8])
y4 = np.array([373.87,611,585,596,449,420])
y5 = np.array([107.8,111.1,113.5,114.7,121,134])
y6 = np.array([0.039257479,0.046831616,0.052357504,0.148444505,0.275754625,0.356298035])
y7 = np.array([2679.2375,2454.8482,2394.6645,2274.1287,1997.7107,2059.6966])
y8 = np.array([0.955541412,0.953173199,0.947723153,0.866391281,0.744051078,0.685538003])


result = []
pc = pearsonr(x,y)
pc1 = pearsonr(x,y1)
pc2 = pearsonr(x,y2)
pc3 = pearsonr(x,y3)
pc4 = pearsonr(x,y4)
pc5 = pearsonr(x,y5)
pc6 = pearsonr(x,y6)
pc7 = pearsonr(x,y7)
pc8 = pearsonr(x,y8)

result.append(round(pc[0],2))
result.append(round(pc1[0],2))
result.append(round(pc2[0],2))
result.append(round(pc3[0],2))
result.append(round(pc4[0],2))
result.append(round(pc5[0],2))
result.append(round(pc6[0],2))
result.append(round(pc7[0],2))
result.append(round(pc8[0],2))

plt.rcParams['font.sans-serif'] = ['SimHei'] # 显示中文
X = ['政府\n积极政策\n数量','纯电动汽车\n最高续航里程','新能源\n汽车专利\n公开量','充电桩\n数量','电能每年\n平均价格','二氧化碳\n排放量','新能源\n渗透率','燃油汽车\n销量','燃油汽车\n渗透率']
fig = plt.figure()
plt.bar(X, result, color="steelblue")

for a,b in zip(X,result):   #柱子上的数字显示
    plt.text(a,b,'%.2f'%b,ha='center',va='bottom',fontsize=10)
print(result)



plt.xlabel("分类")
plt.ylabel("相关系数")
plt.title("零销售量及各统计数据的相关系数")

plt.show()
plt.savefig("barChart.jpg")



