const express = require("express");
const router = express.Router();
const dadosCarroService = require("../services/dadosCarroService");

router.get("/carro", async (req, res) => {
  let dadosCarro = await dadosCarroService.pegarTodos();
  return res.send(dadosCarro);
});

module.exports = router;
