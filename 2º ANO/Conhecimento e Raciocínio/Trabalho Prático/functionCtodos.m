function functionCtodos(rede)

load(rede);

% Redimensionamento das imagens fornecidas (25*25):

Start = dir('.\start\*.png');
nTotalStart = length(Start);
nStart = nTotalStart/ 6;

Train = dir('.\train\*.png');
nTotalTrain = length(Train);
nTrain = nTotalTrain / 6;

Test = dir('.\test\*.png');
nTotalTest = length(Test);
nTest = nTotalTest / 6;

nTotal= nTotalTest + nTotalStart + nTotalTrain;

n = nTotal/6;
tam = 25;

forma_triangle = zeros(tam*tam*3,n);
forma_trapezoid = zeros(tam*tam*3,n);
forma_square = zeros(tam*tam*3,n);
forma_kite = zeros(tam*tam*3,n);
forma_parallelogram = zeros(tam*tam*3,n);
forma_circle = zeros(tam*tam*3,n);

j = 1;

% Conversão das imagens fornecidas em matrizes binárias:

for i = 1 : nTotalStart
  filename = strcat('.\start\', Start(i).name);
  x = imread(filename);
  b = imresize(x,[tam tam]);
  
  if i <= nStart
      forma_circle(:,j) = imbinarize(b(:));
  elseif i <= (nStart*2)
      forma_kite(:,j) = imbinarize(b(:));
  elseif i <= (nStart*3)
      forma_parallelogram(:,j) = imbinarize(b(:));
  elseif i <= (nStart*4)
      forma_square(:,j) = imbinarize(b(:));
  elseif i <= (nStart*5)
      forma_trapezoid(:,j) = imbinarize(b(:));  
  else
      forma_triangle(:,j) = imbinarize(b(:));
  end
  
  j = j + 1;
  
  if j == n + 1
    j = 1;
  end
end
 
j = nStart + 1;

for i = 1:nTotalTrain
  filename = strcat('.\train\',Train(i).name);
  x = imread(filename);
  b=imresize(x,[tam tam]);
  
  if i <= nTrain
      forma_circle(:,j) = imbinarize(b(:));
  elseif i <= (nTrain*2)
      forma_kite(:,j) = imbinarize(b(:));
  elseif i <= (nTrain*3)
      forma_parallelogram(:,j) = imbinarize(b(:));
  elseif i <= (nTrain*4)
      forma_square(:,j) = imbinarize(b(:));
  elseif i <= (nTrain*5)
      forma_trapezoid(:,j) = imbinarize(b(:));  
  else
      forma_triangle(:,j) = imbinarize(b(:));
  end
  
  j = j + 1;
  
  if j == nStart + nTrain + 1
    j = nStart + 1;
  end
end

j = nStart + nTrain + 1;

for i = 1:nTotalTest
  filename = strcat('.\test\',Test(i).name);
  x = imread(filename);
  b = imresize(x,[tam tam]);
  
  if i <= nTest
      forma_circle(:,j) = imbinarize(b(:));
  elseif i <= (nTest*2)
      forma_kite(:,j) = imbinarize(b(:));
  elseif i <= (nTest*3)
      forma_parallelogram(:,j) = imbinarize(b(:));
  elseif i <= (nTest*4)
      forma_square(:,j) = imbinarize(b(:));
  elseif i <= (nTest*5)
      forma_trapezoid(:,j) = imbinarize(b(:));  
  else
      forma_triangle(:,j) = imbinarize(b(:));
  end
  
  j = j + 1;
  
  if j == n + 1
    j = nStart + nTrain + 1;
  end
end

inputs = zeros(tam*tam*3, nTotal); % Matriz a Zeros

% Para colocar todas as imagens numa só matriz de inputs: 

Targets = zeros(1,nTotal);

for i = 1:nTotal
    if i <=n 
        Targets(1,i)=1;
    elseif i <= (n*2)
        Targets(2,i)=1;
    elseif i <= (n*3)
        Targets(3,i)=1;
    elseif i <= (n*4)
        Targets(4,i)=1;
    elseif i <= (n*5)
        Targets(5,i)=1;
    else
        Targets(6,i)=1;
    end
end

j = 1;

for i = 1:nTotal
    Targets(j,i)=1;
    
    if i == j*n
        j = j+1;
    end
end
 
% Treinar a Rede:

[net,tr] = train(net, inputs, Targets);
view(net);

disp(tr);

out = sim(net, inputs);

% Visualizar Desempenho (Matriz de Confusão):

plotconfusion(Targets, out);

% Grafico com o Desempenho da Rede nos 3 Conjuntos (Train, Validation, Test):         

plotperf(tr);

% Calcula e Mostra a percentagem de Classificações Corretas no Total dos Exemplos:

r=0;

for i=1:size(out,2)               % Para cada Classificação.  
   [a b] = max(out(:,i));         % Em que b guarda a linha onde encontrou o Valor mais alto da Saída Obtida.
   [c d] = max(Targets(:,i));     % Em que d guarda a linha onde encontrou o Valor mais alto da Saída Desejada.
   if b == d                      % Se estão na mesma linha, a Classificação foi Correta (incrementa 1)
       r = r + 1;
   end
 end

accuracyTreino = r/size(out,2)*100;
fprintf('Precisao Total %f\n', accuracyTreino)

% Simular a Rede apenas no conjunto de Teste:

TInput = inputs(:, tr.testInd);
TTargets = Targets(:, tr.testInd);

out = sim(net, TInput);

% Calcula e Mostra a percentagem de Classificações Corretas no Conjunto de Teste:

r=0;

for i=1:size(out,2)               % Para cada Classificação.  
  [a b] = max(out(:,i));          % Em que b guarda a linha onde encontrou o Valor mais alto da Saída Obtida.
  [c d] = max(TTargets(:,i));     % Em que d guarda a linha onde encontrou o Valor mais alto da Saída Desejada.
  if b == d                       % Se estão na mesma linha, a Classificação foi Correta (incrementa 1).
       r = r + 1;
  end
end

accuracyTeste = r/size(tr.testInd,2)*100;
fprintf('Precisao Teste %f\n', accuracyTeste)

end