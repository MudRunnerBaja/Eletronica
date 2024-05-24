import { Schema, model } from "mongoose";

// const mongoose = require("mongoose");

const dataSheetSchema = new Schema({
    nome: String,
    horarioinicio: String,
    identificador: String
})

export const DatasheetSchema = model("DataSheet", dataSheetSchema)
// module.exports = model("DataSheet", dataSheetSchema)