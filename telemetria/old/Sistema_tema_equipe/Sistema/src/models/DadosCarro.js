const Sequelize = require("sequelize");
const database = require("../db/db");

const DadosCarro = database.define(
  "dadosCarro",
  {
    id: {
      type: Sequelize.INTEGER,
      autoIncrement: true,
      allowNull: false,
      primaryKey: true,
    },
    nome: {
      type: Sequelize.STRING,
      allowNull: false,
    },
    data: {
      type: Sequelize.DATE,
      allowNull: false,
      defaultValue: Sequelize.NOW(),
    },
    competicao: {
      type: Sequelize.INTEGER, // 1 se for competição | 0 se for teste
      defaultValue: 0, // discutir
    },
    velocidade: {
      type: Sequelize.FLOAT,
    },
    rpm: {
      type: Sequelize.FLOAT,
    },
    combustivel: {
      type: Sequelize.FLOAT,
    },
    temperaturaCvt: {
      type: Sequelize.FLOAT,
    },
    latitude: {
      type: Sequelize.FLOAT,
    },
    longitude: {
      type: Sequelize.FLOAT,
    },
  },
  { timestamps: false }
);

module.exports = DadosCarro;
