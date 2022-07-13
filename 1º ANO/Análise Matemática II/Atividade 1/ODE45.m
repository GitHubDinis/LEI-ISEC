% Atividade 01  
% Dinis Meireles de Sousa Falcão, 2020130403
% David Seco Rodrigues, 2019130152
%
% ODE45 Método de ODE45 para PVI:
%     y = mn_ode(f, a, b, n, y0)->Método numérico para a resolução de um
%   PVI;
%     y' = f(t,y) , t=[a,b];
%     y(a)=y0 (Condição inicial).
%   
% INPUT:
%     f -> função do segundo membro da ED;
%     [a,b] -> extremos do intervalo da variável independente t;
%     n -> número de iterações do método;
%     y0 -> condição inicial.
%
% OUTPUT:
%     y -> vetor das aproximações discretas da solução exata;
%     [t,y] = ode45(f,t,y0).
%

function y = ODE45(f,a,b,n,y0)
h = (b-a)/n;
t = a:h:b; 
y=zeros(1,n+1); 
[t,y] = ode45(f,t,y0);
end
