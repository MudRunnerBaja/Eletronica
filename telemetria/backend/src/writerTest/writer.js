const {SerialPort} = require("serialport")

const port = new SerialPort({
    path: 'COM1',
    "baudRate": 9600,
    "dataBits": 8,
    "stopBits": 1,
    "parity": "none"
  })

const data = {}


function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}

for (let index = 0; index < 100; index++) {
  
  const data = {
    rpm: getRandomInt(20),
    rpmMovida: getRandomInt(20),
    vel: getRandomInt(20),
    tempCVT: getRandomInt(20),
    comb: getRandomInt(20)
}

port.write(JSON.stringify(data)+"\n")


}



