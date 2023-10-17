% IC 23-23
% Tesla Data till now (teste)

clear all

load MyTesla

DataTable = readtable('Tesla Stock Price (2010 to 2023).csv');

%%

Close = DataTable.AdjClose(end-501:end-1);
Volume = DataTable.Volume(end-501:end-1);
Open = DataTable.Open(end-501:end-1);
High = DataTable.High(end-501:end-1);
Low = DataTable.Low(end-501:end-1);

CloseNextDay = DataTable.AdjClose(end-501+1:end);

%%

P = [Close Volume Open High Low]';
T = CloseNextDay';

y = net(P);
perf = perform(net, T, y); %% MSE = sum((T-y).^2)/size(y,2)

plot(1:size(y,2), T, 1:size(y,2),y)
xlabel('Dias');
ylabel('Valor do Indice');
title('For test data');

