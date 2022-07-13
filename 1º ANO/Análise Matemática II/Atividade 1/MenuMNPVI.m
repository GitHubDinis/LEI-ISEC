% Atividade 1  
% Dinis Meireles de Sousa Falcão, 2020130403
% David Seco Rodrigues, 2019130152
%
% MENUMNPVI  Menu de Métodos Numéricos para um PVI
%   y = MenuMNPVI(f,a,b,n,y0)
%   y'= f(t,y) com t=[a, b] e y(a)=y0 condição inicial  
%
% INPUT:
%   f - função do 2.º membro da Equação Diferencial
%   [a, b] - extremos do intervalo da variável independente t
%   n - número de subintervalos ou iterações do método
%   y0 - condição inicial t=a -> y=y0
% OUTPUT: 
%   y - vector das soluções aproximações
% 

function y=MenuMNPVI(f,a,b,n,y0)
y=[];
menuMNPVI = 1;
while menuMNPVI~=9
    clc
    disp('--------------------------------------------------')
    disp('           Métodos Numéricos para PVI             ')
    disp('--------------------------------------------------')
    menuMNPVI=menu('Métodos Numéricos para PVI', ...
                   'Método de Euler',...
                   'Método de Euler Melhorado',...
                   'Método RK2',...
                   'Método RK4',...
                   'Método RK3',...
                   'Método ODE45',...
                   'Todos',...
                   'Saír');
    switch menuMNPVI
        case 1
              y=NEuler(f,a,b,n,y0);
        case 2  
              y=EulerM(f,a,b,n,y0);                
        case 3
              y=RK2(f,a,b,n,y0);
        case 4
              y=RK4(f,a,b,n,y0);
        case 5
              y=RK3(f,a,b,n,y0);
        case 6
              y=ODE45(f,a,b,n,y0);  
        case 7
             y = MetodosNum(f,a,b,n,y0);
             hold off
            legend('Euler','EulerM','RK2','RK4','ODE45','RK3','Exata'); %Legenda
            grid on;
            shg; 
    end
    disp('-----------Solução aproximada do PVI---------')
    disp(y)
    input('Prima numa tecla para continuar »')
end
            