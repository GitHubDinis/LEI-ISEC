% IC 22-23
% Projeto - Fase I (Treino)

% Dinis Meireles de Sousa Falcão | 2020130403
% Kevin Fernando Pereira Rodrigues | 2013010749

%% Inicializar uma seed 

%rng(1);

%% Carregar os Dados de Treino do ficheiro .csv

clearvars
close all

DataTable = readtable("train.csv");

%% Extração de variáveis para 2 vetores

image_name = DataTable.image_name;
label = DataTable.label;

%% Redimensionamento das imagens

label = label + 1;

nimages = length(label);

images = zeros([[28, 28], nimages]);

for i = 1:nimages
    image_name = DataTable.image_name{i};
    image_path = fullfile('images', image_name);
    img = imread(image_path);
    if size(img, 3) == 3
        img = rgb2gray(img);
    end
    img = imresize(img, [28, 28]);
    images(:, :, i) = img;
    %imwrite(img, fullfile('resized_images', DataTable.image_name{i}));
end

%% Matriz de 3D para 2D

images_reshaped = reshape(images, [], size(images, 3)); % Transforma em um vetor coluna
images_transposed = images_reshaped';
%label_transposed = label';

%% Converter os label para formato one-hot

num_classes = 6;
num_samples = length(label);
one_hot_labels = zeros(num_classes, num_samples);

for i = 1:num_samples
    class = label(i);
    one_hot_labels(class, i) = 1;
end

%% Definir a estrutura da rede MLP

net = patternnet(500);
net.layers{end}.size = 6;

%% Treinar a rede

net = train(net, images_reshaped, one_hot_labels);

%% Ver a rede

view(net);

%% Desempenho da rede

y = net(images_reshaped);
perf = perform(net, one_hot_labels, y);
classes = vec2ind(y);
classes = classes';

%% Matriz de confusão

%plotconfusion(one_hot_labels, classes);
classes_vector = classes;
[~, one_hot_labels_vector] = max(one_hot_labels);
C = confusionmat(one_hot_labels_vector, classes_vector);
confusionchart(C);

%% Guardar a rede

save myNet net

%% Calcular sucesso

accuracy = sum(diag(C)) / sum(C(:));
fprintf('Accuracy: %.2f%%\n', accuracy * 100);