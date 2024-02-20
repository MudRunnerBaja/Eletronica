const mongoose = require("mongoose")

const informacaoSchema = new mongoose.Schema({
    corrida: mongoose.SchemaTypes.ObjectId,
    rpm: String,
    rpmMovida: String,
    vel: String,
    tempCVT: String,
    comb: String

})

module.exports = mongoose.model("Informacao", informacaoSchema)