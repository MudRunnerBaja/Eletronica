"use strict";

import { DatabaseInitialization } from "./setup/database-setup";
import { InformacaoSchema } from "./repository/Informacao";

import * as ComPortSetup from "./setup/com-port-setup"
import * as FrontendSocketSetup from "./setup/frontend-socket-setup"

// ExpressJs -> Lidar principalmente com requests http (Server-side)
// Docs: https://expressjs.com/
const express = require("express");
const server = express();
const serverPort = 3030;

export const dataSheet = DatabaseInitialization();
ComPortSetup.ComPortInitialization(dataSheet);



// Essa função é chamada sempre que o programa receber dados enviados do arduino.
// No caso, ela lê o serial até encontrar o delimitador '\n'.


// Iniciando o servidor
server.listen(serverPort, () => {
  console.log(`Servidor escutando a porta ${serverPort}`);
  console.log(`Aguardando comunicação serial:`);

  // ComPortSetup.retryOpeningComPort();
});

/*
 * Sempre que uma nova linha for recebida, ela deve ser salva no banco de dados. É necessário que
 * seja criada uma relação entre essa linha recebida e o dataset criado no início da comunicação.
 *
 * A linha, a princípio irá conter:
 * RPM,TempCVT,Vel,Comb,rpmMovida
 *
 * Obs: Talvez adicionar o tempo desde o início da comunicação possa ser interessante.
 */

/*
 * Outras tarefas:
 *    Criar um endpoint para consultar os datasets:
 *        Há um servidor aberto na porta localhost:3030. É legal que haja um endpoint que receba parâmetros,
 *        como o object ID ou uma data, e o servidor retorne o conjunto.
 *
 *
 *    Para fins de teste, buscar como realizar uma comunicação virtual (ou mockada):
 *        Para testar sem arduino, pode ser possível simular uma comunicação serial mockada que envie dados
 *        de teste. Dessa forma, não é necessário um pico/arduino/pcis para testar o backend da aplicação.
 *        Interessante de desenvolver separadamente do backend (Ou, se junto do backend, usar scripts e
 *        variáveis de ambiente).
 */
