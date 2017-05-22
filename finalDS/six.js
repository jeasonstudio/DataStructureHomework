const fs = require('fs');

let args = process.argv.splice(2)


let resultObj = new Object()
require(args[0]).match(/[a-z]+[\-\']?[a-z]*/ig).map(r => resultObj[r] ? resultObj[r]++ : resultObj[r] = 1)
if (args[1] && (args[1] == '--save' || args[1] == '-S')) {
    fs.writeFile("data.txt", JSON.stringify(resultObj), function (err) {
        if (err) return console.log(err)
        console.log("The file was saved to './data.txt' successfully!");
    });
    return
} else if (args[1] && (args[1] == '--top' || args[1] == '-T')) {
    let resu = quickSort(Object.keys(resultObj))
    new Array(10).fill(0).map((a, m) => console.log('第' + (m + 1) + '个 : ', resu[m], resultObj[resu[m]]))
    return
} else if (args[1] && (args[1] == '--help' || args[1] == '-H')) {
    printUsege();
    return
} else {
    console.log('Nothing Happend, Please input the right command')
}

function quickSort(arr) {
    if (arr.length <= 1) return arr
    let [pivot, left, equal, right] = [parseInt(arr.length / 2), [],
        [],
        []
    ]
    arr.map(key => {
        resultObj[key] > resultObj[arr[pivot]] ? left.push(key) : (resultObj[key] == resultObj[arr[pivot]] ? equal.push(key) : right.push(key))
    })
    return quickSort(left).concat(equal).concat(quickSort(right))
}

function printUsege() {
    let us = `Usage: node six.js [filePath] [command ...]

optional arguments:
    --help, -H  show this help message and exit
    --save, -S  save details to ./data.txt
    --top,  -T  log the top10 records`
    console.log(us)
}