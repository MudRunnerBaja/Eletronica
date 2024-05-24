import { SerialPort } from "serialport";
// const { SerialPort } = require("serialport")

export const virtualPort = new SerialPort({
    path: 'COM2',
    "baudRate": 9600,
    "dataBits": 8,
    "stopBits": 1,
    "parity": "none"
  });


function getRandomInt(max: number) {
  return Math.floor(Math.random() * max);
}

let i: number = 0;
let interval: any;

export function WriteToVirtualPort() {
  i = 0;
  interval = setInterval(WriteStringToVirtualPort, 200);
}

  function WriteStringToVirtualPort() {
    const data = {
      rpm: getRandomInt(4000),
      rpmMovida: getRandomInt(1200),
      vel: getRandomInt(30),
      tempCVT: getRandomInt(180),
      comb: getRandomInt(2)
  }

  i++;
  let s: string = `${data.rpm},${data.rpmMovida},${data.vel},${data.tempCVT},${data.comb}\n`
  if (virtualPort) {
    virtualPort.write(s);
  }

    if (i >= 10000) {
    clearInterval(interval);
    }
  }





