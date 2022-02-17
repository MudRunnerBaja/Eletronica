const Sequelize = require("sequelize").Sequelize;
const sequelize = new Sequelize("sqlite:src/db/db.db");

module.exports = sequelize;
