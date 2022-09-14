function [forma] = functionD(simbolo,rede)

load(rede);

% Redimensionamento das imagens fornecidas (25*25):

tam=25;
inputs = zeros(tam*tam*3,1);

filename = strcat('.\paint\', simbolo);
x = imread(filename);

x = rgb2gray(x);    % converts the truecolor image RGB to the grayscale image x

b = imresize(x,[tam tam]);

% Conversão das imagens fornecidas em matrizes binárias:

inputs = imbinarize(b(:));
      
newoutput = sim(net,inputs);

if newoutput(1)>newoutput(2) && newoutput(1)>newoutput(3) && newoutput(1)>newoutput(4) && newoutput(1)>newoutput(5) && newoutput(1)>newoutput(6)
    forma = "Sou a forma -> triangle";
elseif newoutput(2)>newoutput(1) && newoutput(2)>newoutput(3)&& newoutput(2)>newoutput(4) && newoutput(2)>newoutput(5) && newoutput(2)>newoutput(6) 
    forma = "Sou a forma -> trapezoid";
elseif newoutput(3)>newoutput(1) && newoutput(3)>newoutput(2)&& newoutput(3)>newoutput(4) && newoutput(3)>newoutput(5) && newoutput(3)>newoutput(6)             
    forma = "Sou a forma -> square";
elseif newoutput(4)>newoutput(1) && newoutput(4)>newoutput(2)&& newoutput(4)>newoutput(3) && newoutput(4)>newoutput(5) && newoutput(4)>newoutput(6) 
    forma = "Sou a forma -> parallelogram";
elseif newoutput(5)>newoutput(1) && newoutput(5)>newoutput(2)&& newoutput(5)>newoutput(3) && newoutput(5)>newoutput(4) && newoutput(5)>newoutput(6)          
    forma = "Sou a forma -> kite";
elseif newoutput(6)>newoutput(1) && newoutput(6)>newoutput(2)&& newoutput(6)>newoutput(3) && newoutput(6)>newoutput(4) && newoutput(6)>newoutput(5)         
    forma = "Sou a forma -> circle"; 
else
    forma = "Nao encontrou"; 
end
end
