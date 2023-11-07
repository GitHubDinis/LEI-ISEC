% IC 22-23
% Projeto - Fase I (Teste)

% Dinis Meireles de Sousa Falcão | 2020130403
% Kevin Fernando Pereira Rodrigues | 2013010749 

%% Load da rede treinada

clearvars
close all

load myNet

%% Carregar os Dados de Teste do ficheiro .csv

DataTable = readtable("test.csv");

%% Extração de variáveis

image_name = DataTable.image_name;

%% Redimensionamento de imagens de teste

num_images = length(image_name);

images = zeros([[28, 28], num_images]);

for i = 1:num_images
    image_name = DataTable.image_name{i};
    image_path = fullfile('images', image_name);
    img = imread(image_path);
    if size(img, 3) == 3
        img = rgb2gray(img);
    end
    img = imresize(img, [28, 28]);
    images(:, :, i) = img;
    %imwrite(img, fullfile('resizedtest_images', DataTable.image_name{i}));
end

%% Matriz de 3D para 2D

images_reshaped = reshape(images, [], size(images, 3));

%% Teste 

y = net(images_reshaped);
classes_pred = vec2ind(y);