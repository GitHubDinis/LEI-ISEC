function functionCstart(rede)

load(rede);

% Redimensionamento das imagens fornecidas (25*25):

Start = dir('.\start\*.png');
n = length(Start);
tam = 25;
inputs = zeros(tam*tam*3, length(Start)); % Matriz a Zeros

% Conversão das imagens fornecidas em matrizes binárias:

for i = 1 : n
     filename = strcat('.\start\',Start(i).name);
     x = imread(filename);
      
     b = imresize(x,[tam tam]);
     
     inputs(:,i)=imbinarize(b(:));           
end
 
 
Targets = zeros(6,1);

for i = 1:6
     Targets(i,i) = 1;
end

% Treinar a Rede (Sem re-treinar a rede):

out = net(inputs);

% Visualizar Desempenho (Matriz de Confusão):

plotconfusion(Targets, out);

% Gráficos

set(gca,'xticklabel',{'Forma Triangle' 'Forma Trapezoid' 'Forma Square' 'Forma Parallelogram' 'Forma Kite' 'Forma Triangle' 'Total'})
set(gca,'yticklabel',{'Forma Triangle' 'Forma Trapezoid' 'Forma Square' 'Forma Parallelogram' 'Forma Kite' 'Forma Triangle' 'Total'})

end