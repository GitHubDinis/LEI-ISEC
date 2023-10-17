% IC 23-23
% Tesla Data till now (treino)

clear all
close all

DataTable = readtable('Tesla Stock Price (2010 to 2023).csv');

%%

Close = DataTable.AdjClose(1:end-500);
Volume = DataTable.Volume(1:end-500);
Open = DataTable.Open(1:end-500);
High = DataTable.High(1:end-500);
Low = DataTable.Low(1:end-500);

CloseNextDay = DataTable.AdjClose(2:end-500+1);

%%

P = [Close Volume Open High Low]';
T = CloseNextDay';

net = fitnet([10]);
view(net);

net = train(net, P, T);

%%

y = net(P);
perf = perform(net, T, y);

plot(1:size(y,2), T, 1:size(y,2),y)
xlabel('Dias');
ylabel('Valor do Indice');
title('For training data only');

%%

save MyTesla.mat net
