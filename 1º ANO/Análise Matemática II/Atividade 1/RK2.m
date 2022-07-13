% Atividade 1  
% Dinis Meireles de Sousa Falcão, 2020130403
% David Seco Rodrigues, 2019130152
%
% RK2 -> Método de Runge-Kutta de ordem 2
%   y = RK2(f,a,b,n,y0) -> Método numérico para a resolução de um PVI;
%   y'= f(t,y) , t=[a,b];
%   y(a)=y0 (Condição inicial).
%
% INPUT:
%   f -> função do segundo membro de uma ED;
%   [a,b] -> extremos do intervalo de uma variável independente t;
%   n -> número de iterações do método;
%   t = a -> y = y0(condição inicial).

% OUTPUT: 
%   y -> vetor das aproximações discretas da solução exacta;
%   y(i+1) = y(i)+h*f(t(i),y(i)) , i =0,1,...,n-1 . 
%

function y=RK2(f,a,b,n,y0)
h=(b-a)/n;
t=a:h:b; % Valores de "a" a "b" com compassos de "h" 
y=zeros(1,n+1); % Vetor de zeros onde se armazenam todos os valores de y
y(1)=y0;
for i=1:n % Ciclo "for" que percorre todos os valores de i - de 1 até n - com compassos de 1 a 1.
    k1=h*f(t(i),y(i));
    k2=h*f(t(i+1),y(i)+k1);
    y(i+1)=y(i)+(k1+k2)/2;
end


