% esse código vai calcular o Valor da Dose de Vibração Resultante - VDVR
% fs a frequencia de amostragem
% T periodo

ac = load('mpu6050.txt');
% extraindo as colunas da matrix "ac"

tem = ac(:,1);
acx = ac(:,2);
acy = ac(:,3);
acz = ac(:,4);

fs = 100;
T = 1/fs;
fon =  (regressao_linear(ac, tem, acx, acy, acz)).^4;
fonct = @(x) fon(1)*x + fon(2); % criando uma função handle para facilitar a integração

integral_reg_actot = integral(fonct,0,T, 'ArrayValued', true);
VDVR = (integral_reg_actot)^(1/4)
% figure;
% hold on
% fplot(VDVR,[0,T]);
% title('Valor da dose de vibração');
% grid on






