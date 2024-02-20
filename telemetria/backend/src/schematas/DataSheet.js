const mongoose = require("mongoose");

const dataSheetSchema = new mongoose.Schema({
    nome: String,
    horarioinicio: String,
    identificador: String
})

module.exports = mongoose.model("DataSheet", dataSheetSchema)