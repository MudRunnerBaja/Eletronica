% esse codigo vai calcular a regressão linear dos dados do MPU6050
% iniciando o calculo para achar a aceleração total
% actot vai ser um vetor de [n x 1]; 
% n é o número de colunas do (mpu6050.txt)

function reg_actot = regressao_linear(ac,tem, acx, acy, acz)

tem = tem/1000;    
actot = sqrt(acx.^2 + acy.^2 +acz.^2);
    
% calculando a regressão linear
reg_actot = polyfit(tem, actot,1);
f = polyval(reg_actot, tem);

% cálculo dos coeficientes de determinação
yfit = reg_actot(1)* tem + reg_actot(2);
yresid = actot - yfit; 
SQresid = sum(yresid.^2);
SQtotal = (length(actot)-1) * var(actot);
R2_1 = 1 - SQresid/SQtotal;

hold on
plot(tem, polyval(reg_actot,tem),'g--');

figure;
plot(tem, actot, 'o', tem,f,'-');
legend('data','linear fit');

end




