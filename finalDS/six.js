console.time('run')
let hhh = {},
    eng = require('./f.js').match(/[a-z]+[\-\']?[a-z]*/ig);
eng.map(r => hhh[r] ? hhh[r]++ : hhh[r] = 1)
console.timeEnd('run')
console.log(hhh)