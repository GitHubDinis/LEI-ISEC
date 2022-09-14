function functionCtrain(rede)

load(rede);

% Redimensionamento das imagens fornecidas (25*25):

Train = dir('.\train\*.png');
nTotal = length(Train);
tam = 25;
inputs = zeros(tam*tam*3, nTotal); % Matriz a Zeros

disp(inputs);

n = nTotal/6;

forma_triangle = zeros(tam*tam*3,n);
forma_trapezoid = zeros(tam*tam*3,n);
forma_square = zeros(tam*tam*3,n);
forma_kite = zeros(tam*tam*3,n);
forma_parallelogram = zeros(tam*tam*3,n);
forma_circle = zeros(tam*tam*3,n);

j = 1;

% Conversão das imagens fornecidas em matrizes binárias:

for i = 1:nTotal
  filename = strcat('.\train\', Train(i).name);
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

% Para colocar todas as imagens numa só matriz de inputs 

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

% Treinar a Rede (Sem re-treinar a rede):

out = net(inputs);

% Visualizar Desempenho (Matriz de Confusão):

plotconfusion(Targets, out);

% Gráficos

set(gca,'xticklabel',{'Forma Triangle' 'Forma Trapezoid' 'Forma Square' 'Forma Parallelogram' 'Forma Kite' 'Forma Triangle' 'Total'})
set(gca,'yticklabel',{'Forma Triangle' 'Forma Trapezoid' 'Forma Square' 'Forma Parallelogram' 'Forma Kite' 'Forma Triangle' 'Total'})

end