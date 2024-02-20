require("dotenv").config();
const express = require("express");
const app = express();
const server = require("http").createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);

const router = require("./routes/router");

const inicializarBancoDeDados = require("./services/dbService");
const dadosCarroService = require("./services/dadosCarroService");

inicializarBancoDeDados();

// Configurações servidor
app.use(express.json());
app.use(express.static("web"));
app.use(router);

server.listen(process.env.PORT, () => {
  console.log(`Escutando na Porta: ${server.address().port} ... `);
});

io.on("connection", (socket) => {
  console.log("Uma nova conexão foi feita :P");
  socket.on("atualizaDados", (data) => {
    console.log("dados enviados ---");
    dadosCarroService.adicionar(data);
    socket.broadcast.emit("atualizaDados", data);
  });
});
