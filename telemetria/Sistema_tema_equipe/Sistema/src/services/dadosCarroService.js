const db = require("../db/db");
const DadosCarro = require("../models/DadosCarro");

async function adicionar(dados) {
  try {
    DadosCarro.create(dados);
    return { erro: false };
  } catch (erro) {
    {
      return { erro: true, msg: erro };
    }
  }
}

async function pegarTodosOsDados() {
  try {
    return DadosCarro.findAll();
  } catch (erro) {
    return { erro: true, msg: erro };
  }
}

async function pegarDadosPorDia(dia) {
  //
}

module.exports = { adicionar, pegarTodosOsDados };
