"use strict";

import { Socket } from "socket.io";

// ExpressJs -> Lidar principalmente com requests http (Server-side)
// Docs: https://expressjs.com/
const express = require("express");
const server = express();
const serverPort = 3030;

const ARDUINO_CONFIG = require("../arduino-config.json");


// SerialPort e Parser são os responsável pela comunicação Serial com
// o Pico.
// Docs: https://serialport.io/docs/
const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");
const comPort = new SerialPort(ARDUINO_CONFIG);
const parser = comPort.pipe(new ReadlineParser({ delimiter: "\n" })); // Pipes the port data to the parser using a delimiter

//  MONGOOSE e MONGODB
// cria o datasheet assim que o programa começa e quando recebe informações elas referenciam ele
// não botei callback para verificar o erro, estava dando e erro e aparentemente o moondoose "decrepitou" callbacks no.connect()
// ele confirma a conexâo quando cria o datasheet que sera referenciado pelas informações

const mongoose = require("mongoose");

const DataSheet = require("./schematas/DataSheet");
const Informacao = require("./schematas/Informacao");

mongoose.connect("mongodb://127.0.0.1/teste_r_w");

//cria um datasheet com as informações
const now = new Date();
const identificador = now.toLocaleDateString("pt-br", {
  hour: "2-digit",
  minute: "2-digit",
  second: "2-digit",
});
//cria o datasheet e mostra no console
const dataSheet = new DataSheet({
  nome: "dataSheetTeste",
  horarioinicio: Date(),
  identificador: identificador,
});
dataSheet.save().then(() => console.log(dataSheet, " [", Date(), " ]"));

/*
mongoose.connect("mongodb://localhost/telemetria", () => {
  console.log("Conectado ao db telemetria")
},
  e => console.error(e));

  Sobre a estrutura do projeto (não obrigatório, mas uma orientação geral)

  Uma das formas mais comuns de estruturar projetos é a partir de camadas.
    Podemos chamar de controladoria, integração e repositório. 
    (existem alternativas bem mais complexas do que essa)
  
  Controladoria é a portaria das requisições. Ela confere se a requisição está nos conformes e dá continuidade ao fluxo
    caso esteja tudo certo. Ela também é responsável por responder à requisição, devolvendo seus status (404 not found
    ou 400 bad request, por exemplo).

  Integração é a camada que recebe o sinal da controladoria e envia para a camada de repositório. Eventualmente, o repositório
    vai devolver à integração as listas dos dados que ela encontrar no banco de dados. A integração tem como função tratar
    esses dados e garantir que sejam formatados de acordo com a necessidade da requisição.

  Repositório é a camada que envia para o SGBD (MongoDB, no nosso caso) as informações e requisições de query no banco de dados.
    Essa camada recebe as informações do SGBD e devolve à camada de integração os resultados da query.
*/

// Timer para tentar abrir a porta repetidamente quando falhar.

// comentei p trecho abaixo para poder emular o port serial
// abrir a porta via código causa conflito
/*
const comIntervalId = setInterval(openComPort, 2000);

function openComPort() {
  comPort.open(function (error: any) {
    if (error) {
      console.log(error);
    } else {
      console.log("Opened");
      clearInterval(comIntervalId);
    }
  });
}
*/

// Iniciando o servidor
server.listen(serverPort, () => {
  console.log(`Servidor escutando a porta ${serverPort}`);
  console.log(`Aguardando comunicação serial:`);
  console.log(ARDUINO_CONFIG);
});

// Essa função é chamada quando a comunicação com a porta serial (COM - USB) é aberta.
comPort.on("open", () => {
  console.log(
    "serial port open on " +
      ARDUINO_CONFIG.path +
      " at a baudrate " +
      ARDUINO_CONFIG.baudRate
  );
  console.log(`Escrevendo na porta serial`);

  

  /*
   * Sempre que aberta uma nova comunicação, deve ser criado um "dataset"
   * Em um primeiro momento, o dataset deve conter, pelo menos:
   *   A data, as horas e os minutos em que foi criado.
   *
   * Essa informação deve ser buscável no banco de dados. Uma das formas mais simples é
   * incluir três campos distintos. Por exemplo, o data, horarioInicio e identificadorDataset.
   *   Supondo strings:
   *   data: AAAAMMDD
   *   horarioinicio: HHMMSS
   *   identificador: AAAAMMDDHHMMSS
   *
   * Alternativamente, há meios de se adquirir o mesmo resultado salvando apenas o identificador.
   *
   * O dataset é um Schema do mongodb/mongoose; uma tabela com um conjunto de datasets.
   * Atente-se à necessidade de salvar o id ou o identificador do dataset criado para a próxima função
   *
   */
});

//socket io
//backend front end
const cors = require("cors")


const io = require('socket.io')(3000, {
  //ponha o local host que você esta usando para o front end entre as aspas
  //botei um html pq eu estava testando
  cors: ["http://localhost:4200"]
})



//importa fs
import * as fs from 'fs'

const editJsonFile = require("edit-json-file");

//server.use(cors())
io.on('connection', (socket:any) =>{
  console.log('\nUm usuário se conectou');

  // Evento personalizado para receber mensagens do frontend
  socket.on('mensagemDoCliente', (mensagem:any) => {
    console.log(`Mensagem do Cliente: ${mensagem}`);

    // Enviar a mensagem de volta para o frontend
    // no front end crie um um io.on para cada tipo de evento nesse caso 'mensagemDoServidor'
    io.emit('mensagemDoServidor', 'Mensagem recebida pelo servidor');
  });
  
  

  socket.on("comChange",(comChange:any) =>{
    console.log(comChange)
    
      let file = editJsonFile(`../foo.json`);
      file.set("path", comChange);
      //edita data 
     // ARDUINO_CONFIG.path = comChange
      // escreve JSON file 
      file.save();
      console.log(file.toObject())
/*
      fs.writeFile("../arduino-config.json", JSON.stringify(ARDUINO_CONFIG), function writeJSON(err) {
        if (err) return console.log(err);
        console.log("\n"+JSON.stringify(ARDUINO_CONFIG));
        console.log('\n escrevendo em ' + "../arduino-config.json");
      });


      */
  })

  socket.on('disconnect', () => {
    console.log('Usuário desconectado');
  });
})

//
// Essa função é chamada sempre que o programa receber dados enviados do arduino.
// No caso, ela lê o serial até encontrar o delimitador '\n'.
parser.on("data", (data: string) => {
  // considero que data dentro da função é um objeto ja que usa o parser
  console.log(data);
  let arrayData: any[] = data.split(",");
  const info = new Informacao({
    corrida: dataSheet._id,
    rpm: arrayData[0],
    tempCVT: arrayData[1],
    vel: arrayData[2],
    comb: arrayData[3],
    rpmMovida: arrayData[4],
  });
  
  console.log("info");
// manda ao frontend
// no front end crie um um io.on para cada tipo de evento nesse caso "dataArduino"
  
  io.emit("dataArduino",data);

  // como save é async deu pra usar o .then()
  info.save().then(() => {
    console.log("\n [enviado ao db e ao frontend] \n");
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
});



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
