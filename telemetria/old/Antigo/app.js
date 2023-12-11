// server
let express = require("express");
let app = require('express')();
let http = require('http').createServer(app);
let io = require('socket.io')(http);
const path = require("path");

// serial
//const SerialPort = require("serialport");
//const Readline = require('@serialport/parser-readline');

// variaveis globais
//const s = new SerialPort("COM5", {baudRate: 9600});
//let parser = s.pipe(new Readline({delimiter: '\n'}));
//parser.on("data", async (data) => {
//    try {
//      let newData = data.trim().replace(/, */g, ",").split(","); //  lendo porta serial
//    }catch{
//        console.log("Error on getting serial data");
//    }
//})


app.use("/",express.static(path.join(__dirname ,'public')));

http.listen(3000, () => {
    console.log("Listening on port 3000...");
})

let vel = 0;
let rpm = 0;

io.on("connection", (socket) => {
    console.log("Novo usuário conectado: ",socket.id);
   
    setInterval(()=>{
        vel += 10;
        rpm += 10;
        
        let data_array = {
            vel:vel,
            rpm:rpm,
            comb:0,
            temp_cvt:23
        }

        //io.emit("data",data_array)
    },1000)
   
})