const {SerialPort} = require("serialport")

const port = new SerialPort({
    path: 'COM1',
    "baudRate": 9600,
    "dataBits": 8,
    "stopBits": 1,
    "parity": "none"
  })

const data = {
    rpm: 21,
    rpmMovida: 2,
    vel: 2,
    tempCVT: 2,
    comb: 3
}

port.write(JSON.stringify(data)+"\n")

