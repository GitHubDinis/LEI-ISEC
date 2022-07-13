% Atividade 1  
% Dinis Meireles de Sousa Falcão, 2020130403
% David Seco Rodrigues, 2019130152

% NEULER  Método de Euler para ED/PVI:
%   y = NEuler(f,a,b,n,y0) -> Método numérico para a resolução de um PVI;
%   y'= f(t,y) , t=[a,b];  
%   y(a)=y0 (Condição inicial) .  
%
% INPUT:
%   f -> função do segundo membro de uma ED;
%   [a,b] -> extremos do intervalo de uma variável independente t;
%   n -> número de iterações do método;
%   t = a -> y = y0(condição inicial).
%
% OUTPUT: 
%   y -> vetor das aproximações discretas da solução exacta;
%   y(i+1) = y(i)+h*f(t(i),y(i)) , i =0,1,...,n-1 . 
%

function y = NEuler(f,a,b,n,y0)
h=(b-a)/n;
t=zeros(1,n+1); 
y=zeros(1,n+1); 
t(1)=a;
y(1)=y0;
    for i=1:n  
    y(i+1)=y(i)+h*f(t(i),y(i));
    t(i+1)=a+h*i;
    end
  

end


