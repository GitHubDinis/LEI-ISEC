% Atividade 1  
% Dinis Meireles de Sousa Falcão, 2020130403
% David Seco Rodrigues, 2019130152
%
% RK4 -> Método de Runge-Kutta de ordem 4
%   y = RK4(f,a,b,n,y0) -> Método numérico para a resolução de um PVI;
%   y'= f(t,y) , t=[a, b];
%   y(a)=y0 (Condição inicial) .
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
function y=RK3(f,a,b,n,y0)
h=(b-a)/n;
t=a:h:b;
y=zeros(1,n+1);
y(1)=y0;   
for i= 1:n
    k1 = h*f(t(i),y(i));         
    k2 = h*f(t(i)+h*0.5,y(i)+h*k1*0.5);
    k3 = h*f(t(i)+h, y(i)-h*k1 +2*k2*h);
    y(i+1) =y(i)+h*(1/6)*(k1 +4*k2+k3);
end


