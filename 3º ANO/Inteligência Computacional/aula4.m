clear all

images = loadMNISTImages('train-images.idx3-ubyte');
labels = loadMNISTLabels('train-labels.idx1-ubyte');

colormap("gray")

for i = 1:25
    subplot(5,5,i)
    digit = reshape(images(:, i), [28, 28]);
    imagesc(digit)
end

disp(labels(1:25));

%% TRAIN

Nimages = 60000;

x = images(:, 1:Nimages);
T = labels(1:Nimages,:)';

t = full(ind2vec(T+1));

net = patternnet(10);
net = train(net, x, t);

view(net);

y = net(x);
perf = perform(net, t, y);

classes = vec2ind(y);
plotconfusion(t, y);

save myModel net

%% TEST

clear all

load myModel

imagesTest = loadMNISTImages('t10k-images.idx3-ubyte');
labelsTest = loadMNISTLabels('t10k-labels.idx1-ubyte');

numEx = 10000;
x = imagesTest(:, 1:numEx);
Teste = labelsTest(1:numEx,:)';
t = full(ind2vec(Teste + 1));

y = net(x);

plotconfusion(t, y);

%%

classnames = [1,2,3,4,5,6,7,8,9,10];
classes = vec2ind(y);
netROC = rocmetrics(vec2ind(t), y', classnames);
sum(netROC.AUC)/10






