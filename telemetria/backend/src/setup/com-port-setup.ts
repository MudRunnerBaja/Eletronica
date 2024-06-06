// SerialPort e Parser são os responsável pela comunicação Serial com o Pico.
// Docs: https://serialport.io/docs/

// const { SerialPort } = require("serialport");
// const { ReadlineParser } = require("@serialport/parser-readline");
import { SerialPort } from "serialport";
import { ReadlineParser } from "@serialport/parser-readline";
import { WriteToVirtualPort } from "../testing/virtual-serial-port";

import { InformacaoSchema } from "../repository/Informacao";

import * as FrontendSocketSetup from "./frontend-socket-setup"

export const ARDUINO_CONFIG = require("../../arduino-config.json");
// export const comPort = new SerialPort(ARDUINO_CONFIG);
export const comPort = new SerialPort(ARDUINO_CONFIG);
export const parser = comPort.pipe(new ReadlineParser({ delimiter: "\n" })); // Pipes the port data to the parser using a delimiter

export function ComPortInitialization(dataSheet: any) {

// Timer para tentar abrir a porta repetidamente quando falhar.
// const comIntervalId = setInterval(comPort.open, 2000);

//   comPort.open(function (error: any) {
//     if (error) {
//       console.log(error);
//     } else {
//       console.log("Opened");
//       clearInterval(comIntervalId);
//     }
//   });

// Essa função é chamada quando a comunicação com a porta serial (COM - USB) é aberta.
  comPort.on("open", () => {
    console.log(
      "serial port open on " +
        comPort.path +
        " at a baudrate " +
        comPort.baudRate
    );
    console.log(`Escrevendo na porta serial`);
  });

  parser.on("data", (data: string) => {
    // considero que data dentro da função é um objeto ja que usa o parser
    console.log(data);
    let arrayData: any[] = data.split(",");
    const info = new InformacaoSchema({
      corrida: dataSheet._id,
      rpm: arrayData[0],
      rpmMovida: arrayData[1],
      vel: arrayData[2],
      tempCVT: arrayData[3],
      comb: arrayData[4],
    });
    console.log(info);
    
    info.save().then(() => { console.log("\n [enviado ao db e ao frontend] \n");
  
    // manda ao frontend
    // no front end crie um um io.on para cada tipo de evento nesse caso "dataArduino"
    FrontendSocketSetup.io.emit("dataArduino", JSON.stringify(info));
    });
  
  });

  WriteToVirtualPort();
}