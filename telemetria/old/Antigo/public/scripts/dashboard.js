let socket = io();

// valores baja
let vel_max = document.getElementById("vel_max");
let vel_media = document.getElementById("vel_media");
let rpm_max = document.getElementById("rpm_max");
let rpm_medio = document.getElementById("rpm_medio");
let temp_cvt = document.getElementById("temp_cvt");
let temp_cvt_medio =document.getElementById("temp_cvt_medio");
let cvt_max_temp = document.getElementById("temp_cvt_max");

// valores
let vel = document.getElementById("vel");
let rpm = document.getElementById("rpm");

// comunicação
let con_status = document.getElementById("con_status");
let box = document.getElementsByClassName("box")[0];
let piloto = document.getElementById("piloto");

// combustivel
let comb_vermelho = document.getElementsByClassName("red_comb")[0];
let comb_amarelo = document.getElementsByClassName("yellow_comb")[0];
let comb_verde = document.getElementsByClassName("green_comb")[0];

//  tempo
let tempo_integral = document.getElementById("tempo_integral");
let tempo_parado = document.getElementById("tempo_parado");
let tempo_andando = document.getElementById("tempo_andando");
let tempo_medio = document.getElementById("tempo_medio");
let tempo_ultima_volta = document.getElementById("tempo_ultima_volta");
let tempo_melhor_volta = document.getElementById("tempo_melhor_volta");
let voltas_doc = document.getElementById("voltas");

//  botao
let parar_carro_botao = document.getElementById("parar_carro");
let comecar_botao = document.getElementById("comecar_corrida");
let volta_botao = document.getElementById("volta_botao");

// Variaveis globais
let andando = false;
let corrida_comecou = false;
let timer;
let voltas = 0;
let tempo_total = 0;
let tempo_voltas = [];
let max_values = {vel:0,rpm:0,temp_cvt:0}
let max_sum = {vel:0,rpm:0,temp_cvt:0}
let data_counter = 0;

eventSetup()

function timeHandler(){
    let s = 1;
    let min = 0;
    let hour = 0;
    let segundos_andando = 0;
    let segundos_parado = 0;

    timer = window.setInterval(() => {
        tempo_total += 1
        if(s == 60){s = 0; min++;}
        if(min == 60){min = 0; hour++}

        if(andando){
            segundos_andando += 1;
        }

        else{
            segundos_parado += 1;
        }

        tempo_integral.textContent = `${zeroFill(hour,2)}:${zeroFill(min,2)}:${zeroFill(s,2)}`;
        tempo_andando.textContent = `${zeroFill(Math.trunc(segundos_andando/3600),2)}:${zeroFill(Math.trunc(segundos_andando%3600/60),2)}:${zeroFill(segundos_andando%3600%60,2)}`;
        tempo_parado.textContent = `${zeroFill(Math.trunc(segundos_parado/3600),2)}:${zeroFill(Math.trunc(segundos_parado%3600/60),2)}:${zeroFill(Math.trunc(segundos_parado%3600%60),2)}`;
        s += 1;
    },1000)
}

function eventSetup(){
    box.addEventListener("click",()=>{
        box.style.backgroundColor  = "green";
        console.log("clicked");
    })

    comecar_botao.addEventListener("click",()=>{
        if(!corrida_comecou){
           
            timeHandler();
            start_setup = true;
            corrida_comecou = true;
            comecar_botao.textContent = "Terminar Corrida";
        }

        else{
            corrida_comecou = false;
            comecar_botao.textContent = "Comecar Corrida";
            finishRun();
        }   
    });

    parar_carro_botao.addEventListener("click",()=>{
        if(andando){
            andando = false;
            parar_carro_botao.textContent = "Andar Carro";
        }

        else{
            andando = true;
            parar_carro_botao.textContent = "Parar Carro"
        }
    });

    volta_botao.addEventListener("click",()=>{
        if(corrida_comecou){
            voltas += 1;
            voltas_doc.textContent = voltas;
            voltasHandler();
        }
    })
}

function finishRun(){
    tempo_integral.textContent = "00.00";
    tempo_parado.textContent = "00.00";
    tempo_medio.textContent = "00.00";
    tempo_melhor_volta.textContent = "00.00";
    tempo_ultima_volta.textContent = "00.00";
    tempo_andando.textContent = "00.00";
    voltas_doc.textContent = "0";
    clearInterval(timer)
}

socket.on("data",(data)=>{
    handleData(data);
})

function handleData(data){
    //  combustivel
    if (data.comb == 2){
        comb_vermelho.style.backgroundColor = " #646464";
        comb_amarelo.style.backgroundColor = " #646464";
        comb_verde.style.backgroundColor = "green";
    }
    else if (data.comb == 1){
        comb_vermelho.style.backgroundColor = " #646464";
        comb_amarelo.style.backgroundColor = "yellow";
        comb_verde.style.backgroundColor = " #646464";
    } 
    else{
        comb_vermelho.style.backgroundColor = "red";
        comb_amarelo.style.backgroundColor = " #646464"
        comb_verde.style.backgroundColor = " #646464";
    }

    // vel e rpm
    rpm.textContent = data.rpm;
    vel.textContent = data.vel;
    temp_cvt.textContent = data.temp_cvt;

    // chegando máximos
    if(data.rpm > max_values.rpm){
        max_values.rpm = data.rpm;
        rpm_max.innerText = max_values.rpm;
    }

    if(data.vel > max_values.vel){
        max_values.vel = data.vel;
        vel_max.innerText = max_values.vel;
    }

    if(data.temp_cvt > max_values.temp_cvt){
        max_values.temp_cvt = data.temp_cvt;
        cvt_max_temp.innerText = max_values.temp_cvt;
    }

    // médias
    data_counter += 1;
    max_sum.vel += data.vel;
    max_sum.rpm += data.rpm;
    max_sum.temp_cvt += data.temp_cvt;

    rpm_medio.innerText = Math.round(max_sum.rpm / data_counter);
    vel_media.innerText = Math.round(max_sum.vel / data_counter);
    temp_cvt_medio.innerText = Math.round(max_sum.temp_cvt / data_counter);
}

function voltasHandler(){
    
    if(voltas == 1){
        tempo_voltas.push(tempo_total);
    }
    else{
        let timesSum = 0;
        for(let i = 0; i < tempo_voltas.length;i++){
            timesSum += tempo_voltas[i];
        }
        tempo_voltas.push(tempo_total - timesSum);
    }
    let tempoMedioSegundos = tempo_total / voltas;
    let tempoUltimaVoltaSegundos = tempo_voltas[tempo_voltas.length - 1];
    let tempoMelhorVoltaSegundos = tempo_voltas.reduce(function(a, b) {
        return Math.min(a, b);
    });

    // 00:00:00
    tempo_medio.textContent = `${zeroFill(Math.trunc(tempoMedioSegundos/3600),2)}:${zeroFill(Math.trunc(tempoMedioSegundos%3600/60),2)}`+
    `:${zeroFill(Math.trunc(tempoMedioSegundos%3600%60),2)}`;
    tempo_ultima_volta.textContent = `${zeroFill(Math.trunc(tempoUltimaVoltaSegundos/3600),2)}:${zeroFill(Math.trunc(tempoUltimaVoltaSegundos%3600/60),2)}`+
    `:${zeroFill(Math.trunc(tempoUltimaVoltaSegundos%3600%60),2)}`;
    tempo_melhor_volta.textContent = `${zeroFill(Math.trunc(tempoMelhorVoltaSegundos/3600),2)}:${zeroFill(Math.trunc(tempoMelhorVoltaSegundos%3600/60),2)}`+
    `:${zeroFill(Math.trunc(tempoMelhorVoltaSegundos%3600%60),2)}`;

}

function zeroFill( number, width )
{
  width -= number.toString().length;
  if ( width > 0 )
  {
    return new Array( width + (/\./.test( number ) ? 2 : 1) ).join( '0' ) + number;
  }
  return number + ""; // always return a string
}