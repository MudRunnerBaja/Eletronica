//socket io
import { Socket } from "socket.io";

//backend front end
export const cors = require("cors");

export const io = require("socket.io")(3000, {
  //ponha o local host que você esta usando para o front end entre as aspas
  //botei um html pq eu estava testando
  cors: ["http://localhost:4200"],
});


//importa fs
import * as fs from "fs";
import { InformacaoSchema } from "../repository/Informacao";

const editJsonFile = require("edit-json-file");

//server.use(cors())
io.on("connection", (socket: any) => {
  console.log("\nUm usuário se conectou");

  // Evento personalizado para receber mensagens do frontend
  socket.on("mensagemDoCliente", (mensagem: any) => {
    console.log(`Mensagem do Cliente: ${mensagem}`);

    // Enviar a mensagem de volta para o frontend
    // no front end crie um um io.on para cada tipo de evento nesse caso 'mensagemDoServidor'
    io.emit("mensagemDoServidor", "Mensagem recebida pelo servidor");
  });

  socket.on("comChange", (comChange: any) => {
    console.log(comChange);

    let file = editJsonFile(`../foo.json`);
    file.set("path", comChange);
    //edita data
    // ARDUINO_CONFIG.path = comChange
    // escreve JSON file
    file.save();
    console.log(file.toObject());

    /*
      fs.writeFile("../arduino-config.json", JSON.stringify(ARDUINO_CONFIG), function writeJSON(err) {
        if (err) return console.log(err);
        console.log("\n"+JSON.stringify(ARDUINO_CONFIG));
        console.log('\n escrevendo em ' + "../arduino-config.json");
      });


      */
  });

  socket.on("disconnect", () => {
    console.log("Usuário desconectado");
  });
});


  

