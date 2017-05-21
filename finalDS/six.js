(function () {
    let resultObj = new Object()
    require('./eng.js').match(/[a-z]+[\-\']?[a-z]*/ig).map(r => resultObj[r] ? resultObj[r]++ : resultObj[r] = 1)
    let resu = quickSort(Object.keys(resultObj))
    new Array(10).fill(0).map((a, m) => console.log('第' + (m + 1) + '个 : ', resu[m], resultObj[resu[m]]))
    function quickSort(arr) {
        if (arr.length <= 1) return arr
        let [pivot, left, equal, right] = [parseInt(arr.length / 2), [], [], []]
        arr.map(key => {
            resultObj[key] > resultObj[arr[pivot]] ? left.push(key) : (resultObj[key] == resultObj[arr[pivot]] ? equal.push(key) : right.push(key))
        })
        return quickSort(left).concat(equal).concat(quickSort(right))
    }
})()
