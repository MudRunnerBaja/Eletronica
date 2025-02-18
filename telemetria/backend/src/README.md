# DOCUMENTAÇÃO DO PROJETO

## Estrutura geral

> Orientações gerais sobre a estrutura de arquivos do projeto

### Arquitetura de Camadas

> Uma das formas mais comuns de estruturar projetos é a partição por camadas.
Podemos dividir em três camadas e as chamar de controladoria, integração e repositório.
  
> Controladoria é a portaria das requisições. Ela confere se a requisição está nos conformes e  dá continuidade ao fluxo caso esteja tudo certo. Ela também é responsável por responder à   requisição, devolvendo seus status (404 not found, 400 bad request ou 200 OK, por exemplo).

> Integração, negócios ou serviço é a camada que integra a camada de controle e o repositório. Essa camada é responsável pelo cumprimento das regras de negócio. Enquanto a controladoria apenas verifica se a requisição está dentro do esperado, a integração processa toda a lógica do negócio necessário para aquela requisição, consultando a camada de repositório quando necessário. A integração deve tratar esses dados, tanto de entrada quanto saída, e garantir que sejam formatados de acordo com a necessidade da requisição.

>Repositório é a camada de mais baixo nível e a que se comunica com o Sistema Gerenciador de Banco de Dados (o SGBD sendo o MongoDB, neste caso). Ela monta e envia as instruções de modificação e consulta dos bancos de dados, podendo ser usada a ajuda de APIs (Mongoose, no nosso caso). Essa camada mantém cópias lógicas das estruturas de dados que se espera encontrar no banco de dados - como Schemas - que, com auxílio das APIs, interpreta dados e instruções, facilitando a comunicação entre o código do projeto e o banco de dados. Essa camada é responsável pela lógica que altera ou consulta o banco de dados a partir das informações ou pedidos que recebe da camada de integração.

## EM DESENVOLVIMENTO
