"""
Fault Analysis in Industrial Equipment (Analyzing the p-value associated with the Augmented Dickey Fuller (ADF) stationarity test)
"""

# Libraries used
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import pickle
from pandas.tseries.offsets import Minute
from statsmodels.tsa.stattools import adfuller
import seaborn as sns
from statsmodels.tsa.seasonal import seasonal_decompose
from statsmodels.tsa.stattools import adfuller

# Uploading the Excel file
dataLoading = pd.ExcelFile("C:/Users/Utilizador/Downloads/Material_Projeto/Material_Projeto/DadosProjeto/Dados 2019.xlsx")

# Variable that contains a list of DataFrames with the processed data
dataCleaned = [] 

# Column definition
shortColumns = ["BA1", "BA2", "BA3",
                "VB1", "VB2", "VB3",
                "TOB1", "TOB2", "TOB3",
                "PB1", "PB2", "PB3",
                "CBA",
                "TEuBA1", "TEvBA1", "TEwBA1", "TRLABA1", "TRLCABA1",
                "TEuBA2", "TEvBA2", "TEwBA2", "TRLABA2", "TRLCABA2",
                "TEuBA3", "TEvBA3", "TEwBA3", "TRLABA3", "TRLCABA3",
                "VRBA1", "VRBA2", "VRBA3"]

dateRangeAnually2017 = [["2017-01-01 00:00:00", "2017-02-01 00:00:00"],
                    ["2017-02-01 00:01:00", "2017-02-28 23:59:00"],
                    ["2017-03-01 00:00:00", "2017-04-01 00:00:00"],
                    ["2017-04-01 00:01:00", "2017-05-01 00:00:00"],
                    ["2017-05-01 00:01:00", "2017-06-01 00:00:00"],
                    ["2017-06-01 00:01:00", "2017-07-01 00:00:00"],
                    ["2017-07-01 00:01:00", "2017-08-01 00:00:00"],
                    ["2017-08-01 00:01:00", "2017-09-01 00:00:00"],
                    ["2017-09-01 00:01:00", "2017-10-01 00:00:00"],
                    ["2017-10-01 00:01:00", "2017-11-01 00:00:00"],
                    ["2017-11-01 00:01:00", "2017-12-01 00:00:00"],
                    ["2017-12-01 00:01:00", "2018-01-01 00:00:00"]
                   ]

dateRangeAnually2018 = [["2018-01-01 00:01:00", "2018-02-01 00:00:00"],
                        ["2018-02-01 00:01:00", "2018-02-28 23:59:00"],
                        ["2018-03-01 00:00:00", "2018-04-01 00:00:00"],
                        ["2018-04-01 00:01:00", "2018-05-01 00:00:00"],
                        ["2018-05-01 00:01:00", "2018-06-01 00:00:00"],
                        ["2018-06-01 00:01:00", "2018-07-01 00:00:00"],
                        ["2018-07-01 00:01:00", "2018-08-01 00:00:00"],
                        ["2018-08-01 00:01:00", "2018-09-01 00:00:00"],
                        ["2018-09-01 00:01:00", "2018-10-01 00:00:00"],
                        ["2018-10-01 00:01:00", "2018-11-01 00:00:00"],
                        ["2018-11-01 00:01:00", "2018-12-01 00:00:00"],
                        ["2018-12-01 00:01:00", "2019-01-01 00:00:00"]
                       ]

dateRangeAnually2019 = [["2019-01-01 00:01:00", "2019-02-01 00:00:00"],
                        ["2019-02-01 00:01:00", "2019-02-28 23:59:00"],
                        ["2019-03-01 00:00:00", "2019-04-01 00:00:00"],
                        ["2019-04-01 00:01:00", "2019-05-01 00:00:00"],
                        ["2019-05-01 00:01:00", "2019-06-01 00:00:00"],
                        ["2019-06-01 00:01:00", "2019-07-01 00:00:00"],
                        ["2019-07-01 00:01:00", "2019-08-01 00:00:00"],
                        ["2019-08-01 00:01:00", "2019-09-01 00:00:00"],
                        ["2019-09-01 00:01:00", "2019-10-01 00:00:00"],
                        ["2019-10-01 00:01:00", "2019-11-01 00:00:00"],
                        ["2019-11-01 00:01:00", "2019-12-01 00:00:00"],
                        ["2019-12-01 00:01:00", "2019-12-31 23:59:00"]
                       ]

# This method assumes that there are no duplicate timestamps in each Excel sheet and that they are ordered in ascending order

    # dataToClean -> DataFrame that contains the data values ​​to be processed
    # columnsNames -> Name of the columns associated with the dataFrame to be returned
    # indexToUse -> Index of the dataFrame to be returned

def processData(dataToClean, columnsNames, indexToUse):
    dummyDf = pd.DataFrame(np.nan,
                           index = indexToUse,
                           columns = columnsNames,
                           dtype = "float64")

    # Columns must be analyzed in pairs
    columnsToAnalyze = dataToClean.columns.size // 2 
    # Number of lines resulting from the periods and frequency defined when creating the DateTimeIndex object
    numRows = len(indexToUse) 
    # Column number to insert values ​​into the dataFrame to be used to receive the data
    numColumnToInsertValues = 0 

    # Initial conditions of the column indexes to remove information
    # Variable i will correspond to the timestamps of the variables present in the different columns
    i = 0 
    # Variable j will correspond to the values ​​of the variables present in the different columns
    j = 1 
    # Corresponds to the line number containing the timestamp to be analyzed
    rowToProcess = 0 

    #Initial condition of the index responsible for quantifying the number of iterations necessary in order to analyze the dataFrame correctly
    pairsOfColumnsProcessed = 0

    while pairsOfColumnsProcessed < columnsToAnalyze:    
        for numberRow in range(numRows):
            if dummyDf.index[numberRow] == dataToClean.iloc[rowToProcess,i]: # Comparison of two timestamps
                dummyDf.iloc[numberRow, numColumnToInsertValues] = dataToClean.iloc[rowToProcess,j]
                rowToProcess += 1
            else:
                dummyDf.iloc[numberRow, numColumnToInsertValues] = np.nan
        
        i += 2
        j += 2
        rowToProcess = 0
        numColumnToInsertValues += 1
        pairsOfColumnsProcessed += 1 

    return dummyDf

for index in range(len(dataLoading.sheet_names)):
    dataToFormat = pd.read_excel(dataLoading, dataLoading.sheet_names[index], skiprows = [0,1,2,3,4,5])
    indexToUse = pd.date_range(start = dateRangeAnually2019[index][0], end = dateRangeAnually2019[index][1], freq = "T")
    dataCleaned.append(processData(dataToFormat, shortColumns, indexToUse))
    
#Concatenation of processed data into a single DataFrame object
data2017 = pd.concat(dataCleaned) 

# Segmentation at a monthly level
data2017.loc["2018-08", ["VB1","VB2","VB3"]].describe()

# Segmentation at an annual level
data2017.loc["2019", ["VB1","VB2","VB3"]].describe()

# Process of creating a graph with data and respective labels using matplotlib
fig, ax = plt.subplots()
ax.plot(data2017.loc["2017"]["VB1"], color = "blue", label = "VB1 (mm/s)")
ax.plot(data2017.loc["2017"]["VB2"], color = "orange", label = "VB2 (mm/s)")
ax.plot(data2017.loc["2017"]["VB3"], color = "green", label = "VB3 (mm/s)")
ax.legend()
ax.set(title = "Dados 2017 Vibração - Bomba de Aparas", xlabel = "Meses")
plt.show()

# Count of null values ​​present in each column
cols_with_missing_values = (data2017.loc["2019"].isnull().sum()) 

#Count of null values ​​present in columns VB1, VB2 and VB3
cols_with_missing_values = (data2017.loc["2019"][["VB1", "VB2","VB3"]].isnull().sum()) 

# Process of serialization and deserialization of data to be analyzed using pickle
filename = "C:/Users/Utilizador/Downloads/Material_Projeto/Material_Projeto/dataProcessed"
data = pickle.load(open(filename, "rb"))

data.loc["2017"][["VB1", "VB2", "VB3"]].describe() #Segmentação anual das variáveis a serem analisadas
data.loc["2018"][["VB1", "VB2", "VB3"]].describe() #Segmentação anual das variáveis a serem analisadas
data.loc["2019"][["VB1", "VB2", "VB3"]].describe() #Segmentação anual das variáveis a serem analisadas

def processDataWeekly(data):
    indexWeekly = pd.date_range(start = "2017-01-01 00:00:00", end = "2019-12-31 23:59:00", freq = "W")
    size = len(indexWeekly) - 1
    minute = Minute(1)
    weeklyNanValues = []

    for i in range(size):
        startWeek = indexWeekly[i]
        endWeek = indexWeekly[i + 1] - minute
        labelOfWeek = " :: ".join([str(startWeek), str(endWeek)])
        
        vb1 = data.loc[startWeek:endWeek][["VB1"]].isnull().sum()["VB1"]
        vb2 = data.loc[startWeek:endWeek][["VB2"]].isnull().sum()["VB2"]
        vb3 = data.loc[startWeek:endWeek][["VB3"]].isnull().sum()["VB3"]
        values = {"VB1": vb1, "VB2": vb2, "VB3": vb3}

        df = pd.DataFrame(data = values,
                          index = [labelOfWeek],
                          columns = ["VB1", "VB2", "VB3"])
        
        weeklyNanValues.append(df)

    dfWeekly = pd.concat(weeklyNanValues)
    return dfWeekly

# Process data weekly
weeksProcessed = processDataWeekly(data)

# Segmentation of data at a weekly level analyzing the number of missing values
weeksProcessed.loc["2017-01-01 00:00:00 :: 2017-01-07 23:59:00":"2017-12-24 00:00:00 :: 2017-12-30 23:59:00"] #Ano 2017
weeksProcessed.loc["2017-12-31 00:00:00 :: 2018-01-06 23:59:00":"2018-12-23 00:00:00 :: 2018-12-29 23:59:00"] #Ano 2018
weeksProcessed.loc["2018-12-30 00:00:00 :: 2019-01-05 23:59:00":"2019-12-22 00:00:00 :: 2019-12-28 23:59:00"] #Ano 2019

# Count the number of missing values ​​using a quarter as a time frame
data.loc["2019-01-01 00:00:00":"2019-03-31 23:59:00"][["VB1", "VB2","VB3"]].isnull().sum() #1º trimestre
data.loc["2019-04-01 00:00:00":"2019-06-30 23:59:00"][["VB1", "VB2","VB3"]].isnull().sum() #2º trimestre
data.loc["2019-07-01 00:00:00":"2019-09-30 23:59:00"][["VB1", "VB2","VB3"]].isnull().sum() #3º trimestre
data.loc["2019-10-01 00:00:00":"2019-12-31 23:59:00"][["VB1", "VB2","VB3"]].isnull().sum() #4º trimestre


# Downsample the data to a 5-minute frequency
dataToResample = data.copy()
dataToResample = dataToResample.resample("5min", closed = "right", label = "right").mean() #Downsampling

dataToResample.loc["2017", ["VB1","VB2","VB3"]].describe()
dataToResample.loc["2018", ["VB1","VB2","VB3"]].describe()
dataToResample.loc["2019", ["VB1","VB2","VB3"]].describe()

dataToResample.loc["2017", ["VB1","VB2","VB3"]].isnull().sum()

# Process resampled data weekly
weeksResampled = processDataWeekly(dataToResample)

# Segmentation of data at a weekly level by analyzing the number of missing values
weeksResampled.loc["2017-01-01 00:00:00 :: 2017-01-07 23:59:00":"2017-12-24 00:00:00 :: 2017-12-30 23:59:00"] #Ano 2017
weeksResampled.loc["2017-12-31 00:00:00 :: 2018-01-06 23:59:00":"2018-12-23 00:00:00 :: 2018-12-29 23:59:00"] #Ano 2018
weeksResampled.loc["2018-12-30 00:00:00 :: 2019-01-05 23:59:00":"2019-12-22 00:00:00 :: 2019-12-28 23:59:00"] #Ano 2019

# Counting the number of missing values ​​using a quarter as a time frame
dataToResample.loc["2019-01-01 00:00:00":"2019-03-31 23:59:00"][["VB1", "VB2","VB3"]].isnull().sum() #1º trimestre
dataToResample.loc["2019-04-01 00:00:00":"2019-06-30 23:59:00"][["VB1", "VB2","VB3"]].isnull().sum() #2º trimestre
dataToResample.loc["2019-07-01 00:00:00":"2019-09-30 23:59:00"][["VB1", "VB2","VB3"]].isnull().sum() #3º trimestre
dataToResample.loc["2019-10-01 00:00:00":"2019-12-31 23:59:00"][["VB1", "VB2","VB3"]].isnull().sum() #4º trimestre

# Writing in an Excel file
writer = pd.ExcelWriter("C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/2º SEMESTRE/Projeto/Semanas2019Resampled.xlsx")
weeksResampled.loc["2018-12-30 00:00:00 :: 2019-01-05 23:59:00":"2019-12-22 00:00:00 :: 2019-12-28 23:59:00"].to_excel(writer, "2019")
writer.close()

Weeks2017 = weeksResampled.loc["2017-01-01 00:00:00 :: 2017-01-07 23:59:00":"2017-12-24 00:00:00 :: 2017-12-30 23:59:00"].copy()
Weeks2018 = weeksResampled.loc["2017-12-31 00:00:00 :: 2018-01-06 23:59:00":"2018-12-23 00:00:00 :: 2018-12-29 23:59:00"].copy()
Weeks2019 = weeksResampled.loc["2018-12-30 00:00:00 :: 2019-01-05 23:59:00":"2019-12-22 00:00:00 :: 2019-12-28 23:59:00"].copy()
l = [Weeks2017, Weeks2018, Weeks2019]
totalWeeks = pd.concat(l)

#-> From 05/11/2017 to 20/01/2018
#-> From 04/02/2018 to 27/10/2018
#-> From 04/11/2018 to 16/02/2019

firstTimeSeries = dataToResample.loc["2017-11-05 00:00:00":"2018-01-20 23:59:00"][["VB1", "VB2","VB3"]]
secondTimeSeries = dataToResample.loc["2018-02-04 00:00:00":"2018-10-27 23:59:00"][["VB1", "VB2","VB3"]]
thirdTimeSeries = dataToResample.loc["2018-11-04 00:00:00":"2019-02-16 23:59:00"][["VB1", "VB2","VB3"]]

# General statistics of defined time series
firstTimeSeries.describe()
secondTimeSeries.describe()
thirdTimeSeries.describe()

# Characterization in terms of missing values ​​of the defined time series
firstTimeSeries.isnull().sum()
secondTimeSeries.isnull().sum()
thirdTimeSeries.isnull().sum()

# Filling in missing values (Linear Interpolation)
secondTimeSeries.interpolate(method='linear', inplace=True)

fig, axs = plt.subplots(3, 1, figsize=(10, 8), sharex=True)
axs[0].plot(secondTimeSeries.loc["2018"]["VB1"], color="blue")
axs[0].set_ylabel("VCP 1 (mm/s)")
axs[1].plot(secondTimeSeries.loc["2018"]["VB2"], color="orange")
axs[1].set_ylabel("VCP 2 (mm/s)")
axs[2].plot(secondTimeSeries.loc["2018"]["VB3"], color="green")
axs[2].set_ylabel("VCP 3 (mm/s)")
plt.xlabel("Mounths")
plt.suptitle("2018 Data - Chip Pump Vibration")
plt.show()

#key -> Represents the analysis variable that you want to obtain statistics
def processStatisticsWeekly(data, key):
    indexWeekly = pd.date_range(start = "2018-02-04 00:00:00", end = "2018-10-28 00:00:00", freq = "W")
    size = len(indexWeekly) - 1
    minute = Minute(1)
    weeklyStatsValues = []

    for i in range(size):
        startWeek = indexWeekly[i]
        endWeek = indexWeekly[i + 1] - minute
        labelOfWeek = " :: ".join([str(startWeek), str(endWeek)])
        
        weekMedian = data.loc[startWeek:endWeek][key].mean()
        weekStd = data.loc[startWeek:endWeek][key].std()
        weekMax = data.loc[startWeek:endWeek][key].max()
        weekMin = data.loc[startWeek:endWeek][key].min()
        weekKurtosis = data.loc[startWeek:endWeek][key].kurt()
        weekCofVariation = weekStd / weekMedian
        weekAmpl = weekMax - weekMin
        weekStationarity = adfuller(data.loc[startWeek:endWeek][key])[1]
        
        values = {"Média": weekMedian, "Desvio-Padrão": weekStd, "Cof. Variação": weekCofVariation, "Máx": weekMax,
                  "Min": weekMin, "Amplitude": weekAmpl, "Kurtosis": weekKurtosis, "p-Value": weekStationarity}

        df = pd.DataFrame(data = values,
                          index = [labelOfWeek],
                          columns = ["Média", "Desvio-Padrão", "Cof. Variação", "Máx",
                                     "Min", "Amplitude", "Kurtosis", "p-Value"])
        
        weeklyStatsValues.append(df)

    dfWeekly = pd.concat(weeklyStatsValues)
    return dfWeekly

statsVB1 = processStatisticsWeekly(secondTimeSeries, "VB1")
statsVB2 = processStatisticsWeekly(secondTimeSeries, "VB2")
statsVB3 = processStatisticsWeekly(secondTimeSeries, "VB3")

# Process of creating a graph with data and respective labels using matplotlib
labels = ["2018-02-04", "2018-02-11", "2018-02-18", "2018-02-25", "2018-03-04", "2018-03-11", "2018-03-18", "2018-03-25",
          "2018-04-01", "2018-04-08", "2018-04-15", "2018-04-22", "2018-04-29", "2018-05-06", "2018-05-13", "2018-05-20",
          "2018-05-27", "2018-06-03", "2018-06-10", "2018-06-17", "2018-06-24", "2018-07-01", "2018-07-08", "2018-07-15",
          "2018-07-22", "2018-07-29", "2018-08-05", "2018-08-12", "2018-08-19", "2018-08-26", "2018-09-02", "2018-09-09",
          "2018-09-16", "2018-09-23", "2018-09-30", "2018-10-07", "2018-10-14", "2018-10-21"]

fig, ax = plt.subplots()
ax.plot(statsVB1.loc[:]["p-Value"], color = "blue", label = "VB1 (mm/s)")
ax.plot(statsVB2.loc[:]["p-Value"], color = "orange", label = "VB2 (mm/s)")
ax.plot(statsVB3.loc[:]["p-Value"], color = "green", label = "VB3 (mm/s)")
ax.legend()
ax.set(title = "Evolução do p-value", xlabel = "Semanas")
plt.xticks(np.arange(len(labels)), labels)
fig.autofmt_xdate()
plt.show()

labels1 = ["2018-03-04", "2018-03-11", "2018-03-18", "2018-03-25"]

plt.figure(figsize=(10, 6))
plt.plot(statsVB3.loc['2018-03-04':'2018-04-01']["p-Value"], color="green", label="VB1 (mm/s)")
plt.title('P-Value Variation (2018-03)')
plt.xlabel('Date')
plt.ylabel('p-value')
plt.grid(True)
plt.xticks(np.arange(len(labels1)), labels1)
fig.autofmt_xdate()
plt.show()

fig, axs = plt.subplots(3, 1, figsize=(10, 8), sharex=True)
axs[0].plot(statsVB1.loc[:]["p-Value"], color="blue")
axs[0].set_ylabel("VCP 1 (mm/s)")
axs[0].axhline(y=0.05, color='r', linestyle='--')
axs[0].legend(["p-Value", "Threshold 0.05"])
axs[1].plot(statsVB2.loc[:]["p-Value"], color="orange")
axs[1].set_ylabel("VCP 2 (mm/s)")
axs[1].axhline(y=0.05, color='r', linestyle='--')
axs[1].legend(["p-Value", "Threshold 0.05"])
axs[2].plot(statsVB3.loc[:]["p-Value"], color="green")
axs[2].set_ylabel("VCP 3 (mm/s)")
axs[2].axhline(y=0.05, color='r', linestyle='--')
axs[2].legend(["p-Value", "Threshold 0.05"])
plt.xlabel("Weeks", fontsize=10)  # Definindo o tamanho da fonte para o eixo x
plt.suptitle("Evolução Semanal do P-Value")
plt.xticks(np.arange(len(labels)), labels, fontsize=7)  # Definindo o tamanho da fonte para os rótulos do eixo x
fig.autofmt_xdate()
plt.show()


# Creating a line chart
plt.figure(figsize = (12,6))
sns.lineplot(x = secondTimeSeries.index, y = "VB1", data = secondTimeSeries.loc[:, ["VB1"]])
plt.title("VB1 (mm/s)")
plt.show()

# Seasonal Decomposition
analiseSerieTemporal2 = seasonal_decompose(secondTimeSeries.loc["2018-02-04 00:00:00":"2018-10-27 23:59:00"]["VB3"], model="additive", period=8640)
analiseSerieTemporal2.plot()
plt.xticks(fontsize=7)
plt.show()


# Stationarity Verification
def stationarity(data):
    d = pd.DataFrame(index = ["Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro"],
                     columns = ["VB1", "VB2", "VB3"])

    for i in range(3):
        for j in range(9):
            d.loc[d.index[j]][d.columns[i]] = adfuller(data.loc["2018-{}".format(j + 2)][d.columns[i]])[1]

    return d

testAdFullerVB1 = adfuller(secondTimeSeries.loc[:]["VB1"])
testAdFullerVB2 = adfuller(secondTimeSeries.loc[:]["VB2"])
testAdFullerVB3 = adfuller(secondTimeSeries.loc[:]["VB3"])

print(f'VB1 -> ADF Statistic test: {testAdFullerVB1[0]}')
print(f'VB1 -> p-value: {testAdFullerVB1[1]}\n')
print(f'VB2 -> ADF Statistic test: {testAdFullerVB2[0]}')
print(f'VB2 -> p-value: {testAdFullerVB2[1]}\n')
print(f'VB3 -> ADF Statistic test: {testAdFullerVB3[0]}')
print(f'VB3 -> p-value: {testAdFullerVB3[1]}')

testAdFullerMonths = stationarity(secondTimeSeries)

#8 de Junho
print(f'VB1 -> p-value: {round(statsVB1.loc["2018-06-03 00:00:00 :: 2018-06-09 23:59:00"]["p-Value"], 4)}\n')
print(f'VB1 -> p-value: {round(statsVB1.loc["2018-06-10 00:00:00 :: 2018-06-16 23:59:00"]["p-Value"], 4)}\n')
print(f'VB1 -> p-value: {round(statsVB1.loc["2018-06-17 00:00:00 :: 2018-06-23 23:59:00"]["p-Value"], 4)}\n')

#17 de Julho
print(f'VB1 -> p-value: {round(statsVB1.loc["2018-07-15 00:00:00 :: 2018-07-21 23:59:00"]["p-Value"], 4)}\n')
print(f'VB1 -> p-value: {round(statsVB1.loc["2018-07-22 00:00:00 :: 2018-07-28 23:59:00"]["p-Value"], 4)}\n')

#25 de Setembro
print(f'VB1 -> p-value: {round(statsVB1.loc["2018-09-23 00:00:00 :: 2018-09-29 23:59:00"]["p-Value"], 7)}\n')
print(f'VB1 -> p-value: {round(statsVB1.loc["2018-09-30 00:00:00 :: 2018-10-06 23:59:00"]["p-Value"], 5)}\n')
print(f'VB1 -> p-value: {round(statsVB1.loc["2018-10-07 00:00:00 :: 2018-10-13 23:59:00"]["p-Value"], 4)}\n')

#16 de Maio
print(f'VB2 -> p-value: {round(statsVB2.loc["2018-05-13 00:00:00 :: 2018-05-19 23:59:00"]["p-Value"], 4)}\n')
print(f'VB2 -> p-value: {round(statsVB2.loc["2018-05-20 00:00:00 :: 2018-05-26 23:59:00"]["p-Value"], 4)}\n')

#6 de Março
print(f'VB3 -> p-value: {round(statsVB3.loc["2018-03-04 00:00:00 :: 2018-03-10 23:59:00"]["p-Value"], 4)}\n')
print(f'VB3 -> p-value: {round(statsVB3.loc["2018-03-11 00:00:00 :: 2018-03-17 23:59:00"]["p-Value"], 4)}\n')