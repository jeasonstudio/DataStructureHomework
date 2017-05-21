let resultObj = {}
require('./eng.js').match(/[a-z]+[\-\']?[a-z]*/ig).map(r => resultObj[r] ? resultObj[r]++ : resultObj[r] = 1)

// console.log('module.exports = ', resultObj)
console.log(...quickSort(Object.keys(resultObj)))
// console.log(quickSort(Object.keys(resultObj)).length)

function quickSort(arr) {
    if (arr.length <= 1) return arr
    let pivot = parseInt(arr.length / 2),
        left = [],
        equal = [],
        right = [];
    arr.map(key => {
        resultObj[key] > resultObj[arr[pivot]] ? left.push(key) : (resultObj[key] == resultObj[arr[pivot]] ? equal.push(key) : right.push(key))
    })
    return quickSort(left).concat(equal).concat(quickSort(right))
}