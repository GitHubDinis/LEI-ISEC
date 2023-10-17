clear all
close all

load Bp.mat

% inputs

TBill = Bp(1:254, 1);
Earnings = Bp(1:254, 2);
Dividend = Bp(1:254, 3);
Current = Bp(1:254, 4);

% target

NextW = Bp(1:254, 5);

% define input matrix

P = [TBill Earnings Dividend Current]';

% define target vector
T = NextW';

opt_mlp = 1;
P = rescale(P);

if opt_mlp % MLP
    net = fitnet([10 5]);
    net = train(net, P, T);
else % RBF
    net = newrb(P, T, 0.1, 0.5, 100, 10);
end

y = net(P);
perf = perform(net, T, y) %% MSE = sum((T-y).^2)/size(y, 2)

plot(1:size(y, 2), T, 1:size(y, 2), y)
xlabel('Semanas');
ylabel('Valor do Indice');
title('For training data only');

save minhaNet.mat net
