function regressao = regressao_linear_por_eixo(tem, ac_eixo)

tem = tem/1000;    
    
% calculando a regressão linear
regressao = polyfit(tem, ac_eixo,1);
f = polyval(regressao, tem);

% cálculo dos coeficientes de determinação
yfit = regressao(1)* tem + regressao(2);
yresid = ac_eixo - yfit; 
SQresid = sum(yresid.^2);
SQtotal = (length(ac_eixo)-1) * var(ac_eixo);
R2_1 = 1 - SQresid/SQtotal;


end