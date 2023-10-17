% AULA 1 (IC - 3º ANO)
% ALÍNEA A)

function y = regressao(x, d1, d2)
    [xl, xc] = size(x);
    if nargin == 2
        d2 = d1;
        d1 = 0;
    end

    y = zeros(x1*(d2-d1+1), xc);
    for i = 0:(d2-d1)
        y((1:xl)+xl*i, (i+d1+1):xc) = x(:, 1:(xc-i-d1));
    end
end

% ALÍNEA B)

function [w, b] = inicializa(p, t)
    if nargin < 2, error('unsficient number of arguments')
    end
    
    [R, Q] = size(p);   % p = INPUTS
    if max(R, Q) > 1
        r = R;          % r = number of inputs
    end

    [S, Q] = size(a);   % a = outputs
    if max(S, Q) > 1
        s = S;          % s = number os outputs
    end

    w = rand(s,r);      % weight/bias initialization Matlab function - dimensions = s * r
    b = zeros(1, s);    % initialize all bias to zero (number of bias = number of neurons)

end

% ALÍNEA C)

function [y,e,w,b] = adapta(w, b, p, t, lr)
    nneuronios = size(w, 1);
    npatterns = size(p, 2);
    nsaidas = size(t, 1);

    y = zeros(nsaidas, npatterns);
    e = zeros(nsaidas, npatterns);

    for i = 1:npatterns
        y(:, i) = w*p(:, i) +b;
        e(:, i) = t(:, i) - y(:, i);

        for j = 1:nneuronios
            dw = lr*e(j, i)*p(:, i);
            w(j, :) = w(j, :) +dw;
        end
    end
end

% ALÍNEA D)
function ruido
    clear all;
    clear figure;
    randomnoise = 1;
    
    load handel;
    Sinal = y(1: 30000)';
    sound(Sinal);
    pause
    
    time = 1:1:length(Sinal);
    if randomnoise == 1
        ruido = randn(1, length(time));
    else
        ruido = sin(time);
    end
    
    amplitude = 1;
    sinalcomruido = Sinal + amplitude * ruido;
    sound(sinalcomruido, Fs);
    pause
    
    p = regressao(ruido, 10);
    [w, b] = inicializa(p, ruido);
    t = sinalcomruido;
    lr = 0.01;
    [y, e, w, b] = adapta(w, b, p, t, lr);
    
    sound(e);
    mse = mse(Sinal, e);
end