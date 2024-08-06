const mongoose = require('mongoose');

const timerSchema = new mongoose.Schema({
    id: String,
    duration: Number,
    startTime: String,
    endTime: String
});

module.exports = mongoose.model('Timer', timerSchema);