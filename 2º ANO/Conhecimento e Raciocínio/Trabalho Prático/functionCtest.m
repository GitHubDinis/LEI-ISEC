function functionCtest(rede)

load(rede);

% Redimensionamento das imagens fornecidas (25*25):

Teste = dir('.\test\*.png');
nTotal = length(Teste);
tam = 25;
inputs = zeros(tam*tam*3, nTotal); % Matriz a Zeros

n = nTotal/6;

forma_triangle = zeros(tam*tam*3,n);
forma_trapezoid = zeros(tam*tam*3,n);
forma_square = zeros(tam*tam*3,n);
forma_kite = zeros(tam*tam*3,n);
forma_parallelogram = zeros(tam*tam*3,n);
forma_circle = zeros(tam*tam*3,n);

j = 1;

%resize
for i=1:nTotal
  filename = strcat('.\test\',Teste(i).name);
  x = imread(filename);
  b = imresize(x,[tam tam]);
  
  if i <= n
      forma_circle(:,j) = imbinarize(b(:));
  elseif i <= (n*2)
      forma_kite(:,j) = imbinarize(b(:));
  elseif i <= (n*3)
      forma_parallelogram(:,j) = imbinarize(b(:));
  elseif i <= (n*4)
      forma_square(:,j) = imbinarize(b(:));
  elseif i <= (n*5)
      forma_trapezoid(:,j) = imbinarize(b(:));  
  else
      forma_triangle(:,j) = imbinarize(b(:));
  end
  
  j = j + 1;
  
  if j == n + 1
    j = 1;
  end
end

for tot=1:nTotal % Nº Total de Imagens 
  if tot <= n
      for a = 1:n
          inputs(:,tot) = forma_triangle(:,a);
      end
   
  elseif tot <= (n*2)
      for o = 1:n
          inputs(:,tot)=forma_trapezoid(:,o);
      end
   
  elseif tot <= (n*3)
      for o = 1:n
          inputs(:,tot)=forma_square(:,o);
      end
   
  elseif tot <= (n*4)
      for o = 1:n 
          inputs(:,tot)=forma_parallelogram(:,o);
      end
  elseif tot <= (n*5)
      for o = 1:n  
          inputs(:,tot)=forma_kite(:,o);
      end
  else
      for o = 1:n
          inputs(:,tot)=forma_circle(:,o);
      end                            
  end
end

% Colocar Todas as Imagens numa só Matriz de Inputs: 

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


 
% Treinar a Rede:

[net,tr] = train(net, inputs, Targets);
view(net);

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
fprintf('Precisao total %f\n', accuracyTreino);

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