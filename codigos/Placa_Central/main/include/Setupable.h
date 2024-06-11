/**
 * Project Classes Placa Central
 */

#ifndef _SETUPABLE_H
#define _SETUPABLE_H

/**
 * Cada classe é responsável por um pequeno sistema.
 * O que queremos atingir é torná-las o mais independente
 * possível, para que elas funcionem independente da falha
 * de terceiras.
 *
 * Construtores não são exatamente métodos estáticos e isso confunde
 * algumas dinâmicas necessárias, como no caso do RPM_Motor.
 * O que faremos aqui é, após inicializar, chamaremos pelo Setup,
 * que é estático.
 */
class Setupable
{
public:
    /**
     * Responsável pela inicialização da classe para uso
     */
    static Setupable *Setup();

    virtual bool Debug() = 0;
};

#endif //_SETUPABLE_H