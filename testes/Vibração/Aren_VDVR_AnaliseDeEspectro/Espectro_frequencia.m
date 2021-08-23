% Data: 27 setembro 2020
% Rio de janeiro
% Codigo desenvolvido pela equipe MUD RUNNER (CEFET-RJ); MINI BAJA
%
% O codigo vai transformar no dominio de frequencia
% os dados de um aceleromero (MPU6050) via transformada de Fourier,
% monstando o seu espectro de frequencia
% aplicar um filtro passa baixa e no final implementar um filtro digital
% FIR para observar o espectro de frequência do sinal (aceleração vertical e nos eixos X e Y)

close all;
clear all; clc;

vibration;

Fs = 80; % freq
%t = time/1000;
X = AcX;
Y = AcY; 
Z = AcZ;


% tamanho de cada sinal
tam = length(X);
tamm = 2.^nextpow2(tam);
% aplicando a transformada de Fourier 

fyx = fft(X,tamm);
fyx = fyx(1:tamm/2);
ftx = Fs.*(0:tamm/2-1)/tamm;

fyy = fft(Y,tamm);
fyy = fyy(1:tamm/2);
fty = Fs.*(0:tamm/2-1)/tamm;

fyz = fft(Z,tamm);
fyz = fyz(1:tamm/2);
ftz =Fs.*(0:tamm/2-1)/tamm;

% definindo a frequência de corte
cut_freq = 10/Fs/2;

ordem = 20;

hx = fir1(ordem,cut_freq);
hy = fir1(ordem,cut_freq);
hz = fir1(ordem, cut_freq);

fhx = fft(hx,tamm);
fhx = fhx(1:tamm/2);

fhy = fft(hy,tamm);
fhy = fhx(1:tamm/2);

fhz = fft(hz,tamm);
fhz = fhz(1:tamm/2);

mulx = fhx.*fyx;
muly = fhy.*fyy;
mulz = fhz.*fyz;


hold on
subplot(3,1,1);
plot(abs(mulx),'b');
xlabel('Frequência (HZ)');
ylabel('Amplitude');
title('Espectro de vibração em X');

subplot(3,1,2);
plot(abs(muly),'b');
xlabel('Frequência (HZ)');
ylabel('Amplitude');
title('Espectro de vibração em Y');

subplot(3,1,3);
plot(abs(mulz),'b');
xlabel('Frequência (HZ)');
ylabel('Amplitude');
title('Espectro de vibração em Z');



% convolution_X = conv(X,hx);
% convolution_Y = conv(Y,hy);
% convolution_Z = conv(Z,hz);
% 
% subplot(3,1,1);
% plot(convolution_X);
% xlabel('Time()');
% title('Sinal filtrado no X');
% 
% subplot(3,1,2);
% plot(convolution_Y);
% title('Sinal filtrado no Y');
% 
% subplot(3,1,3);
% plot(convolution_Z);
% title('sinal filtado no Z');


% 
% 
% 
% subplot(4,1,1);
% plot(ftx,abs(fy1/max(fy1)));
% xlabel('Frequência (HZ)');
% ylabel('Amplitude');
% title('Eixos X e Y(sem filtro)');
% 
% subplot(4,1,3);
% plot(ftz,abs(fy2/max(fy2)));
% xlabel('Frequência (HZ)');
% ylabel('Amplitude');
% title('Eixo Z(sem filtro)');





