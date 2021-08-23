% Essa função vai calcular a transformada de Fourier
% do sinal de entrada para analisar 
% o Espectro no dominio de frequencia
% fs é a frequência amostragem (frequency sample)

function [s_freq,frequency] = my_fft(s_temp, fs)

normal = length(s_temp);
T = normal/fs;
aux = (0:normal-1);
frequency = aux/T;  % frequencia de corte para ajustar os dados
s_freq = fftn(s_temp)/normal;
fc = ceil(normal/2);
s_freq = s_freq(1:fc);

figure;
plot(frequency(1:fc),abs(s_freq));
title('Análise de Espectro');
xlabel('Frequência (HZ)');
ylabel('Amplitude');

end
