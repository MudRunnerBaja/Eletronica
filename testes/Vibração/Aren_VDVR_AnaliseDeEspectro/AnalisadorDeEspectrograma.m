% Esse código faz uma análise espectrográfica da aceleração vertical e a
% plota num gráfico 3D.
% O código mostra também o gráfico 2D da aceleração no cada eixo no domínio
% de tempo.

vibration;
Fs = 100;
%%
visualisationVibration(AcX, AcY, AcZ, time);
%%
figure
spectrograma(AcZ,Fs,time);
%%
