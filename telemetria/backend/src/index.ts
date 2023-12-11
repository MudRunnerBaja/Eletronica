"use strict";

const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const ARDUINO_CONFIG = require("../arduino-config.json");

console.log(ARDUINO_CONFIG);

const port = new SerialPort(ARDUINO_CONFIG);
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' })); // Pipes the port data to the parser using a delimiter

port.on("open", () => {
  console.log("serial port open on " + ARDUINO_CONFIG.path + " at a baudrate " + ARDUINO_CONFIG.baudRate);
});

parser.on('data', (data: string) =>{
  console.log('------------------\nRecebido do Pico:\n', data);
});