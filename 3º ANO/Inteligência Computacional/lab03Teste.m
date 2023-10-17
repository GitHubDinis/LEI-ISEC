clear all
load Bp.mat
load minhaNet.mat

TBill = Bp(255:507, 1);
Earnings = Bp(255:507, 2);
Dividend = Bp(255:507, 3);
Current = Bp(255:507, 4);
Next = Bp(255:507, 5);

P = [TBill Earnings Dividend Current]';
T = Next';

P = rescale(P);
% P = rescale(P', 'InputMin', min(P'), 'InputMax', max(P'))';

y = net(P);
perf = perform(net, y, T)