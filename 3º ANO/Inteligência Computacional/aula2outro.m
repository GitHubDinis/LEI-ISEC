clear all

load myNet

Dadosteste = load('optdigits.tes');

x = Dadosteste(:, 1:64)';
targets = Dadosteste(:, 65)';
t = full(ind2vec(targets + 1));

y = net(x);

plotconfusion(t, y);