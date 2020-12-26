# Eletronica
Repositório a ser usado apenas pelos membros de eletrônica da equipe baja do Cefet-RJ <br />
Por favor, ao fazer uma alteração no código, indicar o que foi alterado e colocar no READ.ME <br />

## Microcontroladores
(Atualizar com estudo sobre microcontroladores...) <br />

## Projetos
No momento foram implementadas as seguintes funcionalidades no carro:<br />

<ul>
  <li>Medição da temperatura da CVT</li>
  <li>GPS para localização e mapeamento do carro</li>
  <li>Medidor de combustível</li>
  <li>Leitura do RPM e da Velocidade</li>
  <li>Exibição dos valores no display</li>
  <li>Telemetria do carro</li>
  <li>Chamada para o box</li>
</ul><br />

### Medição da temperatura da CVT
Atualmente, muitas equipes sofrem com superaquecimento gerado não só pelo atrito dos componentes presentes na CVT, como também pela falta de ventilação do local. Para resolver essa situação, a equipe decidiu desenvolver um sistema capaz de coletar a temperatura relativa à caixa interna da proteção da CVT, e enviar esses dados pela telemetria para o box. Dessa forma, podemos evitar o rompimento da correia ao detectar um sinal de aquecimento dentro do local. <br />

Após uma análise dos módulos a serem utilizados, o escolhido foi o módulo max6675 junto ao termopar tipo K, pois: <br />

<ul>
  <li>Atende a faixa de temperatura esperada (300 ºC)</li>
  <li>Possui o cabo revestido para não afetar no dado </li>
  <li>Possui uma boa precisão </li>
  <li>Facilidade de implementação no código </li>
  <li>Comunicação rápida (SPI) </li>
  <li>Ótimo custo benefício </li>
  <li>Possui na biblioteca do PROTEUS </li>
</ul><br />

![max6675](https://user-images.githubusercontent.com/57758959/103159764-2d9ad180-47ac-11eb-93e6-ab4ec3b03b7b.jpg)<br />
Fig 1 - Termopar max6675<br />

### GPS para localização e mapeamento do carro
O mapeamento de percurso é uma informação de suma importância para nossa equipe, visto que, com ela, é possível analisarmos possíveis falhas de direção, analisar as maiores dificuldades de nossos pilotos, saber se e onde o carro parou, e entre outros dados. O módulo GPS serve para transmitir em tempo real a localização do baja, a partir de dados como a longitude e a latitude. Esses dados podem posteriormente serem processados para mapear os locais visitados pelo carro, bem como sua atual posição. <br />

O módulo escolhido pela equipe foi o  GPS GY-NEO6MV2, por ser mais barato e de fácil utilização: <br />

![gps](https://user-images.githubusercontent.com/57758959/103160082-a2233f80-47af-11eb-986d-ffa3a41f8a7b.png)<br />
Fig 2 - GPS GY-NEO6MV2<br />

### Medidor de combustível
O sistema de controle de nível de combustível é um dos circuitos mais importantes no carro, visto que com a noção do volume de gasolina presente no tanque, é possível prevenir a pane seca, que elimina a equipe da prova. Portanto, visando obter um maior tempo de carro na pista sem precisar reabastecer, é imprescindível que tenhamos um bom funcionamento nesse sistema.<br /> 

O módulo escolhido pela equipe foi o  LJC18A3,pois possui uma boa sensibilidade e é ajustável, permitindo uma melhor calibração. Já possuímos esses sensores na oficina e tivemos bons resultados com ele.<br />

![capacitivo](https://user-images.githubusercontent.com/57758959/103160265-70ab7380-47b1-11eb-94c5-ec99e95b99e8.jpg)<br />
Fig 3 - Sensor capacitivo LJC18A3<br />
### Leitura do RPM e da Velocidade

#### Velocidade
A velocidade do carro é um dado muito importante de se adquirir, visto que dá dados ao piloto para testar as melhores condições para fazer uma curva ou passar um obstáculo e é utilizada em diversos testes para a equipe. Com isso em mente, faz-se necessário a construção de um sistema para adquirir esse dado e o sub de eletrônica projetou esse modelo. O sistema conta um sensor de efeito hall (campo magnético) fixado no [local de fixação do sensor], com 4 imas, para serem a referência, instalados no [locais onde estão instaladas] da [roda em que estão instalados].<br />

Para reduzir os erros causados pela derrapagem do carro, foi escolhido obter a média de velocidade nas rodas do veículo. Para isso, será necessário instalar sensores nas rodas dianteiras do veículo podendo, assim, obter a média de velocidades para que o dado apresentado pelo velocímetro não seja tão distante do comportamento real. E o sensor escolhido foi o NJk-5002C pelo fato dele ser robusto e a saída dele podo ser do tipo NPN ou PNP.<br />

![njc](https://user-images.githubusercontent.com/57758959/103160388-3ba02080-47b3-11eb-9bde-0c09426b4a26.jpg)<br />
Fig 4 - Sensor de efeito hall Njk-5002C<br />

#### RPM
O motor de um baja é seu coração, portanto, controlar seu ‘batimento’ (RPM) é de suma importância para o time como um todo. É um dado imprescindível para análise de comportamento do motor, setagem de motor para TF, esforço do motor, quando mostrado ao piloto e entre outras situações.<br />

O motor utilizado possui 4 tempos que são: a admissão, a compressão, a explosão e a exaustão. Ao efetuar um ciclo completo (admissão, compressão, explosão e exaustão), uma indução eletromagnética da corrente é gerada pela bobina da vela.Para conseguir um bom valor de RPM, o sinal do motor precisa ser tratado antes dele ser transmitido para a entidade que é responsável pelo cálculo do RPM. Esse tratamento de sinal se faz por filtros elétricos; com esse procedimento se espera ter um sinal na forma de onda quadrática com amplitude máxima de 5V.<br />

![sinais](https://user-images.githubusercontent.com/57758959/103160502-d5b49880-47b4-11eb-8fbe-14b9c349f4ab.PNG)<br />
Fig 5 - Sinal da bobina primária do motor sem o filtro e com o filtro<br /> 

![filtroantigo](https://user-images.githubusercontent.com/57758959/103160515-f7ae1b00-47b4-11eb-8956-71e126adb942.PNG)<br />
Fig 6 - Filtro atual implementado pela equipe<br />

![filtronovo](https://user-images.githubusercontent.com/57758959/103160513-f4b32a80-47b4-11eb-8550-59f0dd2b4f46.PNG)<br />
Fig 7 - Filtro que pretendemos implementar no futuro<br />

### Exibição dos valores no display

### Telemetria

### Chamada para o box


## Testes
Os seguintes testes estão em desenvolvimento para auxíliar a equipe quanto a otimização dos componentes do carro<:br />

<ul>
  <li>Teste de Strain Gauge</li>
  <li>Teste de retomada e aceleração</li>
  <li>Teste da variação do coeficiente de atrito da pastilha e do disco</li>
  <li>Teste de vibração</li>
</ul><br />
  
![PIC](https://luizbitencourt.files.wordpress.com/2016/09/pic18f4550.gif?w=630&zoom=2)<br />


### Teste de Strain Gauge

### Teste de retomada e aceleração

### Teste da variação do coeficiente de atrito da pastilha e do disco

### Teste de vibração








