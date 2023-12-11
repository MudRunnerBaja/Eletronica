const express = require("express");
const router = express.Router();

const usuariosRoute = require("./usuariosRoute");
const dadosCarroRoute = require("./dadosCarroRoute");

router.use(usuariosRoute);
router.use(dadosCarroRoute);

module.exports = router;
