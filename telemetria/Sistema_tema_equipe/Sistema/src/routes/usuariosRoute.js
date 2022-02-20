const express = require("express");
const router = express.Router();
const usuarioService = require("../services/usuarioService");

router.get("/usuarios", async (req, res) => {
  let users = await usuarioService.pegarTodos();
  return res.send(users);
});

router.post("/usuarios", (req, res) => {
  return res.send(usuarioService.inserirMultiplosDados(req.body));
});

module.exports = router;
