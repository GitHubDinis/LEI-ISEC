% Atividade 1  
% Dinis Meireles de Sousa Falcão, 2020130403
% David Seco Rodrigues, 2019130152
%
% EulerM -> Método de Euler Melhorado/Modificado para PVI
%   y = Euler(f,a,b,n,y0) -> Método usado para a resolução de PVI;
%   y'= f(t,y);
%   t = [a,b];
%   y(a) = y0 (Condição inicial).

function y=EulerM(f,a,b,n,y0)
h=(b-a)/n;
t=a:h:b; % Valores de "a" a "b" com compassos de "h"
y=zeros(1,n+1); % Vetor de zeros onde se armazenam todos os valores de y
y(1)=y0;
for i=1:n % Ciclo "for" que percorre todos os valores de i - de 1 até n - com compassos de 1 a 1.
    y(i+1)=y(i)+h*f(t(i),y(i));
    y(i+1)=y(i)+((h/2)*(f(t(i),y(i))+h*f(t(i+1),y(i))));
end

