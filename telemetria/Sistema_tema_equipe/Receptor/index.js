const { io } = require("socket.io-client");
const socket = io("http://localhost:3000");
const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");
const fs = require("fs");

const CONFIG = JSON.parse(fs.readFileSync("config.json"));
const DESCRICAO_DADO = [
  { nome: "nome", tipo: "string" },
  { nome: "velocidade", tipo: "float" },
  { nome: "rpm", tipo: "float" },
  { nome: "temperaturaCvt", tipo: "float" },
  { nome: "combustivel", tipo: "int" },
];

const porta = new SerialPort({ path: CONFIG.porta, baudRate: CONFIG.baudrate });
const parser = porta.pipe(new ReadlineParser({ delimiter: "\r\n" }));

parser.on("data", (data) => {
  let dadosParaEnvio = filtrarDados(data);
  if (dadosParaEnvio.erro) return;

  parser._flush(() => {}); // limpando buffer
  console.log("DADOS ENVIADOS ------------");
  socket.emit("atualizaDados", dadosParaEnvio);
});

// Funções auxiliares
function filtrarDados(data) {
  try {
    let listData = data.split(",");
    if (listData.length != DESCRICAO_DADO.length) return printarErro(data);

    let dadosFiltrados = new Object();
    listData.forEach((valor, index) => {
      let resposta = validarDado(valor, index);
      if (resposta.erro) throw "erro";

      dadosFiltrados[DESCRICAO_DADO[index].nome] = resposta.valor;
    });

    return dadosFiltrados;
  } catch (erro) {
    return printarErro(data);
  }
}
function validarDado(valor, index) {
  if (DESCRICAO_DADO[index].tipo == "int") {
    if (!isNaN(valor)) return { erro: false, valor: parseInt(valor) };
    else return { erro: true };
  }

  if (DESCRICAO_DADO[index].tipo == "float") {
    if (!isNaN(valor)) return { erro: false, valor: parseFloat(valor) };
    else return { erro: true };
  }

  if (DESCRICAO_DADO[index].tipo == "string") {
    return { erro: false, valor: valor };
  }
}
function printarErro(data) {
  console.log("Erro na recepção de dados: " + data);
  return { erro: true };
}

// TESTE
//filtrarDados("MR-22,21.4,3100,89.3,1");

// const data = {
//   nome: "MR-22",
//   velocidade: 21.4,
//   rpm: 3100,
//   temperaturaCvt: 89.3,
//   combustivel: 1,
// };
// socket.emit("atualizaDados", data);
