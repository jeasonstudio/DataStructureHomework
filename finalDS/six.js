let resultObj = {},
    eng = require('./eng.js').match(/[a-z]+[\-\']?[a-z]*/ig);
eng.map(r => resultObj[r] ? resultObj[r]++ : resultObj[r] = 1)

// console.log('module.exports = ', resultObj)
// console.log(resultObj)
