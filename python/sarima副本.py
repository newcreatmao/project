from statsmodels.graphics.tsaplots import plot_pacf
from statsmodels.graphics.tsaplots import plot_acf
from statsmodels.stats.diagnostic import acorr_ljungbox
from statsmodels.tsa.statespace.sarimax import SARIMAX
from statsmodels.tsa.holtwinters import ExponentialSmoothing
from statsmodels.tsa.stattools import adfuller
import matplotlib.pyplot as plt
from tqdm import tqdm_notebook
import numpy as np
import pandas as pd
from itertools import product
import warnings
warnings.filterwarnings('ignore')
data = pd.read_csv('D:\\project\\python\\11.csv')

plt.figure(figsize=[15, 7.5]); # Set dimensions for figure
plt.plot(data['timestamp'], data['sales'])
plt.title('new energy car')
plt.ylabel('sales')
plt.xlabel('Date')
plt.xticks(rotation=90)
plt.grid(True)
plt.show()
plot_pacf(data['sales']);
plt.show()
plot_acf(data['sales']);
plt.show()
ad_fuller_result = adfuller(data['sales'])
print(f'ADF Statistic: {ad_fuller_result[0]}')
print(f'p-value: {ad_fuller_result[1]}')

data['sales'] = np.log(data['sales'])
data['sales'] = data['sales'].diff()
data = data.drop(data.index[0])
plt.figure(figsize=[15, 7.5]);  # Set dimensions for figure
plt.plot(data['timestamp'],data['sales'])
plt.title("Log Difference of new energy car")
plt.xticks(rotation=90)
plt.show()
# Seasonal differencing
data['sales'] = data['sales'].diff(12)
data = data.drop([1, 2, 3, 4,5,6,7,8,9,10,11,12], axis=0).reset_index(drop=True)
plt.figure(figsize=[15, 7.5]); # Set dimensions for figure
plt.plot(data['timestamp'],data['sales'])
plt.title("Log Difference of new energy car after")
plt.xticks(rotation=90)
plt.show()
ad_fuller_result = adfuller(data['sales'])
print(f'ADF Statistic: {ad_fuller_result[0]}')
print(f'p-value: {ad_fuller_result[1]}')

plot_pacf(data['sales']);
plt.show()
plot_acf(data['sales']);
plt.show()


def optimize_SARIMA(parameters_list, d, D, s, exog):
    """
        Return dataframe with parameters, corresponding AIC and SSE

        parameters_list - list with (p, q, P, Q) tuples
        d - integration order
        D - seasonal integration order
        s - length of season
        exog - the exogenous variable
    """

    results = []

    for param in tqdm_notebook(parameters_list):
        try:
            model = SARIMAX(exog, order=(param[0], d, param[1]), seasonal_order=(param[2], D, param[3], s)).fit(disp=-1)
        except:
            continue

        aic = model.aic
        results.append([param, aic])
    result_df = pd.DataFrame(results)
    result_df.columns = ['(p,q)x(P,Q)', 'AIC']
    # Sort in ascending order, lower AIC is better
    result_df = result_df.sort_values(by='AIC', ascending=True).reset_index(drop=True)

    return result_df
p = range(0, 4, 1)
d = 1
q = range(0, 4, 1)
P = range(0, 4, 1)
D = 1
Q = range(0, 4, 1)
s = 12
parameters = product(p, q, P, Q)
parameters_list = list(parameters)
print(len(parameters_list))
#result_df = optimize_SARIMA(parameters_list, 1, 1, 12, data['sales'])
#print(result_df)
best_model = SARIMAX(data['sales'], order=(0, 1, 2), seasonal_order=(2, 1, 0, 12)).fit(dis=-1)
print(best_model.summary())
#残差分析
best_model.plot_diagnostics(figsize=(15,12));
plt.show()
#print(data)
data['sarima_model'] = best_model.fittedvalues
data['sarima_model'][:12+1] = np.NaN
forecast = best_model.predict(start=data.shape[0], end=data.shape[0] + 24)
forecast = data['sarima_model']._append(forecast)
plt.figure(figsize=(15, 7.5))
plt.plot(forecast, color='r', label='model')
plt.axvspan(data.index[-1], forecast.index[-1], alpha=0.5, color='lightgrey')
plt.plot(data['sales'], label='actual')
plt.legend()
plt.show()
