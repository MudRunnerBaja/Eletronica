import { Schema, model, SchemaTypes } from "mongoose";

// const mongoose = require("mongoose")

const informacaoSchema = new Schema({
    corrida: SchemaTypes.ObjectId,
    rpm: String,
    rpmMovida: String,
    vel: String,
    tempCVT: String,
    comb: String

})
export const InformacaoSchema = model("Informacao", informacaoSchema)

// module.exports = model("Informacao", informacaoSchema)