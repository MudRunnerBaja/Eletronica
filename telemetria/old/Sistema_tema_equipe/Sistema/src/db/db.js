const Sequelize = require("sequelize").Sequelize;
var sequelize = new Sequelize(process.env.DATABASE_URL, {
  dialectOptions: {
    ssl: {
      require: true,
      rejectUnauthorized: false,
    },
  },
});
//const sequelize = new Sequelize("sqlite:src/db/db.db");

module.exports = sequelize;
