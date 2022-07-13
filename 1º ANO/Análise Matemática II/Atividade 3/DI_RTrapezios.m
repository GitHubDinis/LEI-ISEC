%Atividade 3
%Dinis Meireles de Sousa Falcão - 2020130403
%David Seco Rodrigues - 2019130152
%
%DI_RTrapezios Calculo Integração Numérica através da Regra dos Trapézios
%   t = DI_RTrapezios(f,a,b,n)
%   t = h*(f(a)+f(b)+t)/2;
%
%INPUT:
%   f - função real de variável real x
%   [a, b] - extremos do intervalo da variável independente x
%   n - número de subintervalos ou iterações da regra
%OUTPUT: 
%   t - Resultado da área do Integral
%   t = h*(f(a)+f(b)+t)/2 , i=2,...,n-1
%

function t = DI_RTrapezios(f,a,b,n)

h = (b-a)/n;
t = 0;
x=a;

for i=1:n-1
	x=x+h;
	t = t+2*f(x);
end

t = h*(f(a)+f(b)+t)/2;
