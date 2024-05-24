# DOCUMENTAÇÃO DO PROJETO

## Estrutura geral

> Orientações gerais sobre a estrutura de arquivos do projeto

### Arquitetura de Camadas

> Uma das formas mais comuns de estruturar projetos é a partir de camadas.
Podemos chamar de controladoria, integração e repositório. 
(existem alternativas bem mais complexas do que essa)
  
> Controladoria é a portaria das requisições. Ela confere se a requisição está nos conformes e  dá continuidade ao fluxo caso esteja tudo certo. Ela também é responsável por responder à   requisição, devolvendo seus status (404 not found, 400 bad request ou 200 OK, por exemplo).

> Integração, negócios ou serviço é a camada que recebe os dados validados pela controladoria e envia para a camada de repositório. Eventualmente, o repositório vai devolver à integração as listas dos dados que ela encontrar no banco de dados. A integração tem como função tratar esses dados, tanto de entrada quanto saída, e garantir que sejam formatados de acordo com a necessidade da requisição. Também costuma ser responsável por validar regras de negócio.

>Repositório é a camada que envia para o Sistema Gerenciador de Banco de Dados (o SGBD sendo o MongoDB, neste caso) as instruções de modificação e consulta dos bancos de dados. Essa camada mantém cópias lógicas do que é esperado encontrar no banco de dados - como Schemas - e, com auxílio de APIs especializadas (como a Mongoose), interpreta instruções e facilita a comunicação entre o código do projeto e o banco de dados. Essa camada é responsável pela lógica que altera ou consulta o banco de dados a partir das informações ou pedidos que recebe da camada de integração.

## EM DESENVOLVIMENTO
