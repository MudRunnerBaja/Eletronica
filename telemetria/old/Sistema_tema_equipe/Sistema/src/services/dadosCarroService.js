const DadosCarro = require("../models/DadosCarro");

function adicionar(dados) {
  try {
    DadosCarro.create(dados);
    return { erro: false };
  } catch (erro) {
    {
      return { erro: true, msg: erro };
    }
  }
}

function pegarTodos() {
  try {
    return DadosCarro.findAll({ raw: true });
  } catch (erro) {
    return { erro: true, msg: erro };
  }
}

module.exports = { adicionar, pegarTodos };
