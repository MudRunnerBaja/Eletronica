% Data: 27 setembro 2020
% Rio de janeiro
% Codigo desenvolvido pela equipe MUD RUNNER (CEFET-RJ); MINI BAJA
%
% O codigo vai transformar no dominio de frequencia
% os dados de um aceleromero (MPU6050) via transformada de Fourier
% monstando o seu espectro de frequencia
% e no final, aplicar um filtro passa baixa
% para eliminar o ruido


clc
clear all

% Fazendo o update dos dados
data = load('mpu6050.txt');

 x = data(:,2); % extracting the first column
 y = data(:,3); % just the second
 z = data(:,4); % and the third
 
X_y = [x; y];
%s1 = data;

fs = 80; % Teorema de Nyquist 
            % A frequencia de amostragem dee ser pelo memos o dobro
            % da frequência máxima do sinal
            
fa = fs; 
fp = 23; %frequencia de passagem
f_stop = 38; %frequencia de corte

% Normalização das frequencias
wp = (fp/(fs/2))*pi;
ws = (f_stop/(fs/2))*pi; 

wt = ws - wp; % frequencia de transição

M = ceil((6.6*pi/wt) + 1);
wc =(ws + wp)/2; % frequencia de corte intermediaria


hd = passa_baixa(wc,M);

w_hamm = hamming(M)';

h = hd.*w_hamm;
sig_filtrado_Z = conv(h,z); % convolução entre os sinais
sig_filtrado_X_Y = conv(h,X_y);

figure;
my_fft(sig_filtrado_Z, fs);
title('Filtro FIR no Eixo Z');

my_fft(sig_filtrado_X_Y, fs);
title('Sinal filtro no Eixo X e Y');
