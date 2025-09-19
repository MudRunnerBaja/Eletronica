#include "TemperaturaCVT.h"
#include "Combustivel.h"
#include "RPM_Motor.h"
#include "GPS.h"
#include "Freio.h"
#include "Instancia.h"
#include "Constantes.h"

/**
 * Struct de dados para uso temporario dos dados de forma
 * organizada se encontra na classe Constantes.h
 */
class DadosSincronizados
{
public:
    bool dadosEmAtualizacao = false;

    String formatarDados()
    {
        String dadosString = "";
        dadosString = dadosString + "vel " + String(vel) + " / ";
        dadosString = dadosString + "rpm " + String(rpm) + " / ";
        dadosString = dadosString + "tmpCVT " + String(tmpCvt) + " / ";
        dadosString = dadosString + "nivelComb " + String(nivelComb) + " / ";
        dadosString = dadosString + "nivelFreio " + String(nivelFreio) + " / ";
        dadosString = dadosString + "pressaoFreio " + String(pressaoFreio) + " / ";
        dadosString = dadosString + "tensaoBat" + String(tensaoBat);
        return dadosString;
    };

    String formatarDadosSD()
    {
        String dadosString = "";
        dadosString = dadosString + String(vel) + ",";
        dadosString = dadosString + String(rpm) + ",";
        dadosString = dadosString + String(tmpCvt) + ",";
        dadosString = dadosString + String(nivelComb) + ",";
        dadosString = dadosString + String(nivelFreio) + ",";
        dadosString = dadosString + String(pressaoFreio) + ",";
        dadosString = dadosString + String(tensaoBat);
        return dadosString;
    }

    /**
     * @brief
     *
     * @param nivelComb
     * @param nivelFreio
     * @param pressaoFreio
     * @param pedal
     * @param tensaoBat
     * @param tmpCvt
     * @param tmpAmb
     * @param rpm
     * @param vel
     */
    void atualizarDados(short nivelComb1, int nivelFreio1, double pressaoFreio1, double pedal1, double tensaoBat1, float tmpCvt1, float tmpAmb1, double rpm1, double vel1)
    {
        dadosEmAtualizacao = true;

        nivelComb = nivelComb1;
        nivelFreio = nivelFreio1;
        pressaoFreio = pressaoFreio1;
        pedal = pedal1;
        tensaoBat = tensaoBat1;
        tmpCvt = tmpCvt1;
        tmpAmb = tmpAmb1;
        rpm = rpm1;
        vel = vel1;

        atualizaDadosCompartilhamento();
        dadosEmAtualizacao = false;

        // Ponderar se os novos dados que forem adicionados precisam ser
        // também adicionados à StructDados
    }

    DadosCompartilhamento getStructDados()
    {
        return dadosCompartilhamento;
    }

    bool getDadosEmAtualizacao()
    {
        return dadosEmAtualizacao;
    }

private:
    short nivelComb = 0;
    int nivelFreio = 0;
    double pedal = 0;
    double pressaoFreio = 0;
    double tensaoBat = 0;
    float tmpCvt = 0;
    float tmpAmb = 0;
    double rpm = 0;
    double vel = 0;

    DadosCompartilhamento dadosCompartilhamento = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    void atualizaDadosCompartilhamento()
    {
        dadosCompartilhamento.nivelComb = nivelComb;
        dadosCompartilhamento.nivelFreio = nivelFreio;
        dadosCompartilhamento.pressaoFreio = pressaoFreio;
        dadosCompartilhamento.pedal = pedal;
        dadosCompartilhamento.tensaoBat = tensaoBat;
        dadosCompartilhamento.tmpCvt = tmpCvt;
        dadosCompartilhamento.tmpAmb = tmpAmb;
        dadosCompartilhamento.rpm = rpm;
        dadosCompartilhamento.vel = vel;
    }
};
