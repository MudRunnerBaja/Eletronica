
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
class Dados
{
public:
    static short nivelComb;
    static int nivelFreio;
    static double pressaoFreio;
    static double pedal;
    static double tensaoBat;
    static float tmpCvt;
    static float tmpAmb;
    static double rpm;
    static double vel;

    static String formatarDados()
    {
        String dadosString = "";
        dadosString = dadosString + String(tmpCvt) + " ";
        dadosString = dadosString + String(nivelComb) + " ";
        dadosString = dadosString + String(vel) + " ";
        dadosString = dadosString + String(rpm) + " ";
        dadosString = dadosString + String(nivelFreio) + " ";
        dadosString = dadosString + String(pressaoFreio);
        return dadosString;
    };

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
    static void atualizarDados(short nivelComb, int nivelFreio, double pressaoFreio, double pedal, double tensaoBat, float tmpCvt, float tmpAmb, double rpm, double vel)
    {
        nivelComb = nivelComb;
        nivelFreio = nivelFreio;
        pressaoFreio = pressaoFreio;
        pedal = pedal;
        tensaoBat = tensaoBat;
        tmpCvt = tmpCvt;
        tmpAmb = tmpAmb;
        rpm = rpm;
        vel = vel;

        // Ponderar se os novos dados que forem adicionados precisam ser
        // também adicionados à StructDados
    }

    static StructDados getStructDados()
    {
        // A definicao da struct se encontra em Constantes.h
        StructDados data = StructDados();
        data.nivelComb = nivelComb;
        data.nivelFreio = nivelFreio;
        data.pressaoFreio = pressaoFreio;
        data.pedal = pedal;
        data.tensaoBat = tensaoBat;
        data.tmpCvt = tmpCvt;
        data.tmpAmb = tmpAmb;
        data.rpm = rpm;
        data.vel = vel;

        return data;
    }
};

short Dados::nivelComb = 0;
int Dados::nivelFreio = 0;
double Dados::pedal = 0;
double Dados::pressaoFreio = 0;
double Dados::tensaoBat = 0;
float Dados::tmpCvt = 0;
float Dados::tmpAmb = 0;
double Dados::rpm = 0;
double Dados::vel = 0;