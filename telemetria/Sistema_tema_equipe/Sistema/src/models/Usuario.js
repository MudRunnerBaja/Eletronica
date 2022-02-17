const Sequelize = require("sequelize");
const database = require("../db/db");

const Usuario = database.define(
  "usuario",
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

    imagem: {
      type: Sequelize.STRING,
      allowNull: false,
    },
    subsistema: {
      type: Sequelize.STRING,
      allowNull: false,
    },
    cargo: {
      type: Sequelize.STRING,
      allowNull: false,
    },
    curso: {
      type: Sequelize.STRING,
      allowNull: false,
    },
    data: {
      type: Sequelize.DATE,
      allowNull: false,
      defaultValue: Sequelize.NOW(),
    },
  },
  { timestamps: false }
);

module.exports = Usuario;
