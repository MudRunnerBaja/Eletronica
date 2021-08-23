% valor da aceleração resultante de exposição normalizada (arean)
% esse código calcula somente o "are" quando Ti = 1 e ni = 1
% Ti: tempo de duração da componente de exposição “i”;
% ni:  número de repetições da componente de exposição “i” ao
% longo da jornada de trabalho

ac = load('mpu6050.txt');

tem = ac(:,1);
acx = ac(:,2);
acy = ac(:,3);
acz = ac(:,4);

n = tem(end); % pegando o último valor da matrix "tem"
T = n/60000; %tempo de exposição diário
To = 480; % duração de 480 minutos ou 8 horas (jornada normal)
ni = 1;
Ti = 1;
fxy = 1.4; %fator de multiplicação em função do eixo x e y
fz = 1.0; %fator de multiplicação em função do eixo z
S = 1; % número de amostras da componente de exposição
       % “i” que foram mensuradas.

% Aceleração média de cada eixos ortogonais (ijk)

% eixo x
ai = (regressao_linear_por_eixo(tem, acx)).^2;
Ai = @(x) ai(1)*x + ai(2);
integralX = integral(Ai,10,T, 'ArrayValued', true);
Ami = (1/(T-10) * integralX)^(1/2);

% eixo y
ai = (regressao_linear_por_eixo(tem, acy)).^2;
Ai = @(x) ai(1)*x + ai(2);
integralX = integral(Ai,10,T, 'ArrayValued', true);
Amj = (1/(T-10) * integralX)^(1/2);

% eixo z
ai = (regressao_linear_por_eixo(tem, acz)).^2;
Ai = @(x) ai(1)*x + ai(2);
integralX = integral(Ai,10,T, 'ArrayValued', true);
Amk = (1/(T-10) * integralX)^(1/2);

amr = (fxy*(Ami)^2 + fxy*(Amj)^2 + fz*(Amk)^2)^(1/2); % aceleração média resultante

arep = 1/S * sum(amr*1);
 
% cálculo do are (m/s^2)
 
are = (1/T * (arep)^2)^(1/2);
 
 % cálculo do aren (m/s^2)
 
aren = are * ((T/To)^(1/2))
