const mongoose = require("mongoose")

const informacaoSchema = new mongoose.Schema({
    corrida: mongoose.SchemaTypes.ObjectId,
    rpm: Number,
    rpmMovida: Number,
    vel: Number,
    tempCVT: Number,
    comb: Number

})

module.exports = mongoose.model("Informacao", informacaoSchema)