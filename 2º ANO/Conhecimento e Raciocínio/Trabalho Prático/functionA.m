function [net2,accuracyTreino] = functionA(topologia, neuronios, ftreino, epocas, camadas, fativacao)

% Redimensionamento das imagens fornecidas (25*25):

Start = dir('.\start\*.png');
n = length(Start);
tam = 25;
inputs = zeros(tam*tam*3, length(Start)); % Matriz a Zeros

disp(inputs);

% Conversão das imagens fornecidas em matrizes binárias:

for i = 1 : n
     filename = strcat('.\start\',Start(i).name);  % Concatenate strings horizontally
     x = imread(filename);
      
     b = imresize(x,[tam tam]);
     
     % reshape()
     
     inputs(:,i) = imbinarize(b(:)); % Cria uma imagem binária.          
end
 
% disp(inputs);
% save('inputs', 'inputs');

Targets = zeros(30,1);
 
for i = 1:30
    Targets(i,i) = 1;
end
 
% disp(Targets)

% Criar e Configurar a Rede Neuronal (feedforwardnet, patternnet, perceptron): 
% Indicar a Função de Ativação das Camadas Escondidas e de Saída:

if strcmp(topologia,"feedforwardnet") == 1 
    net = feedforwardnet(neuronios);
    for j = 1:camadas+1
        net.layers{j}.transferFcn = fativacao; % Colocar {j} quando utilizar a App;
    end
elseif strcmp(topologia,"patternnet") == 1
     net = patternnet(neuronios);
     for j = 1:camadas
        net.layers{j}.transferFcn = fativacao;
     end
end  


% Indicar a Função de Treino:

net.trainFcn = ftreino;

% Indicar o número de Épocas de Treino:

net.trainParam.epochs = epocas;
net.divideFcn = '';  
              
% Treinar a Rede:

[net,tr] = train(net, inputs, Targets);
view(net);
 
disp(tr);
 
out = sim(net, inputs);
 
% Visualizar Desempenho (Matriz de Confusão):

plotconfusion(Targets, out);

% Grafico com o Desempenho da Rede nos 3 Conjuntos (Train, Validation, Test):

plotperf(tr);

% Simular a Rede apenas no conjunto de Teste:



% Calcula e Mostra a percentagem de Classificações Corretas no Total dos Exemplos:

 r = 0;
 
 for i=1:size(out,2)               % Para cada Classificação.  
   [a b] = max(out(:,i));          % Em que b guarda a linha onde encontrou o Valor mais alto da Saída Obtida.
   [c d] = max(Targets(:,i));      % Em que d guarda a linha onde encontrou o Valor mais alto da Saída Desejada.
   if b == d                       % Se estão na mesma linha, a Classificação foi Correta (incrementa 1).
       r = r + 1;
   end
 end
 
accuracyTreino = r/size(out,2)*100;
fprintf('Precisao total: %f\n', accuracyTreino);

net2=net;

end