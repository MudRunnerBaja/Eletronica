const UsuarioModel = require("../models/Usuario");

function pegarTodos() {
  return UsuarioModel.findAll({ raw: true }); // raw true para receber apenas os dados
}

function inserirMultiplosDados(dados) {
  try {
    UsuarioModel.bulkCreate(dados);
    return { erro: false };
  } catch (e) {
    return { erro: true, msg: e };
  }
}

module.exports = { pegarTodos, inserirMultiplosDados };
