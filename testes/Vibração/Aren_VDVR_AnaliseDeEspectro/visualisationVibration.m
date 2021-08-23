% essa função plota as aceleração nos treis eixos num grafico

function [X, Y, Z] = visualisationVibration(AcX, AcY, AcZ, time)
k = time/1000;
X = AcX;
Y = AcY;
Z = AcZ;

hold on
subplot(3,1,1)
plot(k,X);
xlabel('Time (s)');
ylabel('aceleração (m/s^2)');
grid minor
title('Aceleração no eixo X')

hold on
subplot(3,1,2)
plot(k,Y);
xlabel('Time (s)');
ylabel('aceleração (m/s^2)');
grid minor 
title('Aceleração no eixo Y')

hold on
subplot(3,1,3)
plot(k,Z);
xlabel('Time (s)');
ylabel('aceleração (m/s^2)');
grid minor
title('Aceleração no eixo Z')

end