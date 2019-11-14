# Eletronica
Repositório a ser usado apenas pelos membros de eletrônica da equipe baja do Cefet-RJ <br />
Por favor, ao fazer uma alteração no código, indicar o que foi alterado e colocar no READ.ME <br />


## PIC
No momento estão implementadas as seguintes aplicações no PIC:<br />

<ul>
  <li>Medidor de combustível</li>
  <li>Leitura do RPM e da Velocidade</li>
  <li>Exibição dos valores no display</li>
</ul><br />

![PIC](https://luizbitencourt.files.wordpress.com/2016/09/pic18f4550.gif?w=630&zoom=2)<br />

Aplicações a serem implementadas:<br />

<ul>
  <li>Item1</li>
  <li>Item2</li>
  <li>Item3</li>
</ul><br />

### Medidor de combustível




### Leitura do RPM e da Velocidade
A leitura do RPM e da Velocidade é feita utilizando sensores de efeito hall, que funcionam como um detector de campo magnético. No pneu dianteiro e no virabrequim do motor foram colocados 2 ímãs, de forma que, a cada rotação de seus eixos, um sinal será enviado para o PIC pelo sensor. Esse sinal se comporta como uma perna de baixa, pois a tensão presente nos fios pula de 5 para 0 Volts cada vez que o sensor identifica a presença do ímã. Para se contabilizar o RPM do motor basta saber quantas vezes esse processo se repete em 1 segundo e depois multiplicar por 60. Entretanto, para calcular a velocidade do carro, precisamos multiplicar o número de rotações do pneu pelo seu diâmetro. Esses valores são posteriormente enviados ao display para exibição no carro. 

![PIC](https://luizbitencourt.files.wordpress.com/2016/09/pic18f4550.gif?w=630&zoom=2)<br />



### Exibição dos valores no display



### Transmissao dos valores do PIC para o Arduino


## Arduino
No momento a principal função do arduino é transmitir os dados do carro para o computador através da telemetria. Outras aplicações serão desenvolvidas no futuro.<br />


### Telemetria
A telemetria consiste na transmissão dos dados do carro para o computador. O transmissor escolhido foi o XBEE devido a sua praticidade e eficiência. Além disso, os dados transmitidos alcançam até 3km de distância.
![XBEE](https://core-electronics.com.au/media/catalog/product/cache/1/image/fe1bcd18654db18f328c2faaaf3c690a/x/b/xbee_pro_60mw_u.fl_connection_-_series_1__802.15.4___wrl-08710__01.jpg)<br />







