"""
Fault Analysis in Industrial Equipment (Analyzing the p-value associated with the Augmented Dickey Fuller (ADF) stationarity test)
"""

# Libraries used
import pandas as pd
import numpy as np
from statsmodels.tsa.stattools import adfuller
import matplotlib.pyplot as plt
import pickle
from statsmodels.nonparametric.smoothers_lowess import lowess
import matplotlib.dates as mdates

# Uploading the Excel file
filename = "C:/Users/Utilizador/Downloads/Material_Projeto/Material_Projeto/dataProcessed"
data = pickle.load(open(filename, "rb"))

# Describe annual segments for the specified variables
print(data.loc["2017"][["VB1", "VB2", "VB3"]].describe())
print(data.loc["2018"][["VB1", "VB2", "VB3"]].describe())
print(data.loc["2019"][["VB1", "VB2", "VB3"]].describe())

# Downsample the data to a 5-minute frequency
dataToResample = data.copy()
dataToResample = dataToResample.resample("5min", closed="right", label="right").mean()

# Extract specific periods for analysis
firstTimeSeries = dataToResample.loc["2017-11-05 00:00:00":"2018-01-20 23:59:00"][["VB1", "VB2", "VB3"]]
secondTimeSeries = dataToResample.loc["2018-02-04 00:00:00":"2018-10-27 23:59:00"][["VB1", "VB2", "VB3"]]
thirdTimeSeries = dataToResample.loc["2018-11-04 00:00:00":"2019-02-16 23:59:00"][["VB1", "VB2", "VB3"]]

# Describe time series
print(firstTimeSeries.describe())
print(secondTimeSeries.describe())
print(thirdTimeSeries.describe())

# Check for missing values in time series
print(firstTimeSeries.isnull().sum())
print(secondTimeSeries.isnull().sum())
print(thirdTimeSeries.isnull().sum())

# # Filling in missing values (Linear Interpolation)
secondTimeSeries.interpolate(method='linear', inplace=True)


def processStatisticsDailyWithMovingAverage(data, key, window=15):
    indexDaily = pd.date_range(start="2018-02-04 00:00:00", end="2018-10-27 23:59:00", freq="D")
    size = len(indexDaily)
    minute = pd.Timedelta(minutes=1)
    dailyStatsValues = []

    for i in range(size):
        if i < window - 1:
            continue  # Skip initial days where the window is not fully available
        
        startDay = indexDaily[i - window + 1]
        endDay = indexDaily[i] + pd.Timedelta(days=1) - minute  # End of the current day
        labelOfDay = " :: ".join([str(startDay), str(endDay)])

        dayData = data.loc[startDay:endDay][key]

        if not dayData.var():
            # If the variance is zero, there's no need to calculate stationarity statistics
            dayStationarity = np.nan
        else:
            dayStationarity = adfuller(dayData)[1]

        values = {"Média": dayData.mean(), "Desvio-Padrão": dayData.std(), "Cof. Variação": dayData.std() / dayData.mean(),
                  "Máx": dayData.max(), "Min": dayData.min(), "Amplitude": dayData.max() - dayData.min(),
                  "Kurtosis": dayData.kurt(), "p-Value": dayStationarity}

        df = pd.DataFrame(data=values,
                          index=[labelOfDay],
                          columns=["Média", "Desvio-Padrão", "Cof. Variação", "Máx",
                                   "Min", "Amplitude", "Kurtosis", "p-Value"])

        dailyStatsValues.append(df)

    dfDaily = pd.concat(dailyStatsValues)
    return dfDaily

# Calculate daily statistics
statsVB1 = processStatisticsDailyWithMovingAverage(secondTimeSeries, "VB1")
statsVB2 = processStatisticsDailyWithMovingAverage(secondTimeSeries, "VB2")
statsVB3 = processStatisticsDailyWithMovingAverage(secondTimeSeries, "VB3")

# Calculate day rolling average for 'Média' and 'p-Value'
rolling_mean_Mean = statsVB3["2018-02-04 00:00:00":"2018-10-27 23:59:00"]["Média"]
rolling_mean_Pvalue = statsVB3["2018-02-04 00:00:00":"2018-10-27 23:59:00"]["p-Value"]

# Apply LOWESS filter to the rolling mean of 'Média' and 'p-Value'
lowess_mean = lowess(rolling_mean_Mean, np.arange(len(rolling_mean_Mean)), frac=0.15)
lowess_pvalue = lowess(rolling_mean_Pvalue, np.arange(len(rolling_mean_Pvalue)), frac=0.15)

# Plot the results
fig, ax1 = plt.subplots(figsize=(12, 6))

rolling_mean_Mean.index = pd.to_datetime([idx.split(" :: ")[0] for idx in rolling_mean_Mean["2018-02-04 00:00:00":"2018-10-27 23:59:00"].index], format='%Y-%m-%d %H:%M:%S')

ax2 = ax1.twinx()
ax1.plot(rolling_mean_Mean["2018-02-04 00:00:00":"2018-10-27 23:59:00"].index, lowess_mean[:, 1], 'g-', label='Mean')
ax2.plot(rolling_mean_Mean["2018-02-04 00:00:00":"2018-10-27 23:59:00"].index, lowess_pvalue[:, 1], 'r-', label='p-Value')

# Format the date ticks on the x-axis
ax1.xaxis.set_major_locator(mdates.WeekdayLocator(interval=2))
ax1.xaxis.set_major_formatter(mdates.DateFormatter('%d/%m'))
plt.rcParams['xtick.labelsize'] = 13
fig.autofmt_xdate()

ax2.axhline(y=0.05, color='red', linestyle='--', linewidth=0.8, label='Threshold 0.05')

ax1.set_xlabel('Date')
ax1.set_ylabel('VCP3', color='g')
ax2.set_ylabel('p-Value', color='r')

plt.title('15-Day Rolling Mean of VCP3 and p-Value with LOWESS Filter (Daily)')
ax1.legend(loc='upper left')
ax2.legend(loc='upper right')
plt.show()