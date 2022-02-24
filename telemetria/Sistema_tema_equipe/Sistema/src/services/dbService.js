const db = require("../db/db");

async function inicializarBancoDeDados() {
  try {
    const resultado = await db.sync();
    console.log("Conexão com banco de dados");
    return resultado;
  } catch (erro) {
    console.log("Erro na conexão com o banco de dados");
    console.log(erro);
    return { erro: erro };
  }
}

module.exports = inicializarBancoDeDados;
