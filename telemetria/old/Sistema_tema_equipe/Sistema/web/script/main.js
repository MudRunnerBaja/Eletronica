let tempo = {
  Total: 0,
  Parado: 0,
  Andado: 0,
  UltimaVolta: 0,
  MelhorVolta: 100000,
  MediaVolta: 0,
  UltimaVoltaAuxCalc: 0,
};
let medidas = {
  velocidade: 0.0,
  velocidadeMax: 0.0,
  velocidadeMedia: 0.0,
  velocidadeSoma: 0.0,
  rpm: 0,
  rpmMax: 0,
  rpmMedio: 0.0,
  rpmSoma: 0.0,
  temperaturaCvt: 0.0,
  temperaturaCvtMax: 0.0,
  temperaturaCvtMedia: 0.0,
  temperaturaCvtSoma: 0.0,
  combustivel: 0,
  contador: 0,
};
let carroAndando = false;
let voltas = 0;

function setupEvents() {
  // Chamada pro box
  let chamadaBox = document.getElementById("chamada_box");
  let comunicacaoVisual =
    document.getElementsByClassName("comunicacao_visual")[0];
  comunicacaoVisual.addEventListener("click", () => {
    if (chamadaBox.value == "false") {
      // envia para ligar a chamada pro box
      comunicacaoVisual.style.backgroundColor = "#e2062c";
      chamadaBox.value = "true";
    } else {
      // envia para desligar a chamada pro box
      comunicacaoVisual.style.backgroundColor = "#3f3254";
      chamadaBox.value = "false";
    }
  });
}

// Medidas ----------------------------------------------------------------------------
function mudarCombustivel(nivel) {
  // 0 = vazio 1 = médio 2 = cheio
  if (nivel == 0) {
    document.getElementById("arco_combustivel").style.borderColor = "#e2062c";
    document.getElementById("combustivel").style.color = "#e2062c";
    document.getElementById("combustivel").innerHTML = "Vazio";
  } else if (nivel == 1) {
    document.getElementById("arco_combustivel").style.borderColor = "#F2CD00";
    document.getElementById("combustivel").style.color = "#F2CD00";
    document.getElementById("combustivel").innerHTML = "Médio";
  } else {
    document.getElementById("arco_combustivel").style.borderColor = "#00B125";
    document.getElementById("combustivel").style.color = "#00B125";
    document.getElementById("combustivel").innerHTML = "Cheio";
  }
}

function atualizaDadosMedidas(data) {
  medidas.contador += 1;
  medidas.velocidade = data.velocidade;
  medidas.velocidadeSoma += medidas.velocidade;
  medidas.velocidadeMedia = medidas.velocidadeSoma / medidas.contador;
  medidas.velocidadeMax =
    medidas.velocidade > medidas.velocidadeMax
      ? medidas.velocidade
      : medidas.velocidadeMax;

  document.getElementById("velocidade").innerHTML = medidas.velocidade;
  document.getElementById("velocidade_max").innerHTML = medidas.velocidadeMax;
  document.getElementById("velocidade_media").innerHTML =
    medidas.velocidadeMedia;

  medidas.rpm = data.rpm;
  medidas.rpmSoma += medidas.rpm;
  medidas.rpmMedio = medidas.rpmSoma / medidas.contador;
  medidas.rpmMax = medidas.rpm > medidas.rpmMax ? medidas.rpm : medidas.rpmMax;

  document.getElementById("rpm").innerHTML = medidas.rpm;
  document.getElementById("rpm_max").innerHTML = medidas.rpmMax;
  document.getElementById("rpm_medio").innerHTML = medidas.rpmMedio;

  medidas.temperaturaCvt = data.temperaturaCvt;
  medidas.temperaturaCvtSoma += medidas.temperaturaCvt;
  medidas.temperaturaCvtMedia = medidas.temperaturaCvtSoma / medidas.contador;
  medidas.temperaturaCvtMax =
    medidas.temperaturaCvt > medidas.temperaturaCvtMax
      ? medidas.temperaturaCvt
      : medidas.temperaturaCvtMax;

  document.getElementById("temperatura_cvt").innerHTML = medidas.temperaturaCvt;
  document.getElementById("temperatura_cvt_max").innerHTML =
    medidas.temperaturaCvtMax;
  document.getElementById("temperatura_cvt_media").innerHTML =
    medidas.temperaturaCvtMedia;

  medidas.combustivel = data.combustivel;
  mudarCombustivel(medidas.combustivel);
}

// Tempo ------------------------------------------------------------------------------
let cronometro = setInterval(() => {
  tempo.Total += 1;
  if (carroAndando) tempo.Andado += 1;
  else tempo.Parado += 1;

  document.getElementById("tempo_total").innerHTML = formataTempo(tempo.Total);
  document.getElementById("tempo_andando").innerHTML = formataTempo(
    tempo.Andado
  );
  document.getElementById("tempo_parado").innerHTML = formataTempo(
    tempo.Parado
  );
}, 1000);

function completaVolta() {
  voltas += 1;
  tempo.UltimaVolta = tempo.Total - tempo.UltimaVoltaAuxCalc; // consertar
  tempo.UltimaVoltaAuxCalc = tempo.Total;
  tempo.MediaVolta = tempo.Total / voltas;
  tempo.MelhorVolta =
    tempo.UltimaVolta < tempo.MelhorVolta
      ? tempo.UltimaVolta
      : tempo.MelhorVolta;

  let tempoUltimaVolta = document.getElementById("tempo_ultima_volta");
  tempoUltimaVolta.innerHTML = formataTempo(tempo.UltimaVolta);
  let tempoMediaVolta = document.getElementById("tempo_media_volta");
  tempoMediaVolta.innerHTML = formataTempo(tempo.MediaVolta);
  let tempoMelhorVolta = document.getElementById("tempo_melhor_volta");
  tempoMelhorVolta.innerHTML = formataTempo(tempo.MelhorVolta);
  let voltasHtml = document.getElementById("voltas");
  voltasHtml.innerHTML = voltas;
}

function formataTempo(tempo) {
  // HH:MM:SS
  let horas = preencheZero(Math.floor(tempo / 3600));
  let minutos = preencheZero(Math.floor((tempo % 3600) / 60));
  let segundos = preencheZero(Math.floor((tempo % 3600) % 60));

  return `${horas}:${minutos}:${segundos}`;
}

function preencheZero(numero) {
  if (numero < 10) return "0" + String(numero);
  else return String(numero);
}

// Comunicação ----------------------------------------------------------------------------
var socket = io();

socket.on("atualizaDados", (data) => {
  atualizaDadosMedidas(data);
});

// Teste ----------------------------------------------------------------------------------
let testeTempo = document.getElementById("teste_tempo");
testeTempo.addEventListener("click", () => {
  completaVolta();
});

setupEvents();
