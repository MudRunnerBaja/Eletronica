/**
 * Em fase de planejamento e desenvolvimento
 * MONGOOSE e MONGODB
 * MONGODB é o gerenciador de banco de dados (SGBD). Mongoose é uma API que facilita a integração entre o nodejs e o mongodb.
 */

import * as Mongoose from "mongoose";

import { DatasheetSchema } from "../repository/DataSheet";
import { InformacaoSchema } from "../repository/Informacao";



export function DatabaseInitialization() {

    Mongoose.connect("mongodb://127.0.0.1/teste_r_w"); // DB de teste
    // Mongoose.connect("mongodb://localhost/telemetria"); // DB de teste

    // Gera o identificador de um datasheet
    const now = new Date();
    const identificador = now.toLocaleDateString("pt-br", {
      hour: "2-digit",
      minute: "2-digit",
      second: "2-digit",
    });

    // Cria e persiste o datasheet a partir do identificador. Imprime no console.
    const dataSheet = new DatasheetSchema({
      nome: "dataSheetTeste",
      horarioinicio: Date(),
      identificador: identificador,
    });
    dataSheet.save().then(() => console.log(dataSheet, " [", Date(), " ]"));

    return dataSheet;
}


  /*
   * Sempre que aberta uma nova comunicação, deve ser criado um "dataset"
   * Em um primeiro momento, o dataset deve conter, pelo menos:
   *   A data, as horas e os minutos em que foi criado.
   *
   * Essa informação deve ser buscável no banco de dados. Uma das formas mais simples é
   * incluir três campos distintos. Por exemplo, o data, horarioInicio e identificadorDataset.
   *   Supondo strings:
   *   data: AAAAMMDD
   *   horarioinicio: HHMMSS
   *   identificador: AAAAMMDDHHMMSS
   *
   * Alternativamente, há meios de se adquirir o mesmo resultado salvando apenas o identificador.
   *
   * O dataset é um Schema do mongodb/mongoose; uma tabela com um conjunto de datasets.
   * Atente-se à necessidade de salvar o id ou o identificador do dataset criado para a próxima função
   *
   */
