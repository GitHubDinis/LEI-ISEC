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
function y = RK4(f, a, b, n, y0)
h = (b-a)/n;
t(1) = a;
y(1) = y0;
for i=1:n % Ciclo "for" que percorre todos os valores de i - de 1 até n - com compassos de 1 a 1.
    t(i+1) = t(i) + h;
    K1 = h * f(t(i),y(i));
    K2 = h * f(t(i) + (h/2),y(i) + (1/2) * K1);
    K3 = h * f(t(i) + (h/2),y(i) + (1/2) * K2);
    K4 = h * f(t(i) + h,y(i) + K3);
    y(i+1) = y(i) + ((1/6) * (K1 + (2*K2) + (2*K3) + K4));
end 


