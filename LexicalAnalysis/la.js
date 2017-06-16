let fs = require("fs");
const keyWord = /auto|short|int|long|float|double|char|struct|union|enum|typedef|const|unsigned|signed|extern|register|static|volatile|void|if|else|switch|case|for|do|while|goto|continue|break|default|sizeof|return/
const numberWord = /[0-9]+/
const identfierWord = /[A-Za-z]([A-Za-z][0-9])*/
const operatorWord = /\+|-|\*|\/|:=|>=|<=|#|=/
const delimiterWord = /[,\.;]/

function readLines(input, func) {
    let remaining = ''
    input.on('data', function (data) {
        remaining += data
        let index = remaining.indexOf('\n')
        while (index > -1) {
            let line = remaining.substring(0, index)
            remaining = remaining.substring(index + 1)
            func(line)
            index = remaining.indexOf('\n')
        }
    })

    input.on('end', function () {
        if (remaining.length > 0) {
            func(remaining)
        }
    })
}

console.log(`Usage for help
    -- key : 关键字
    -- number : 常数
    -- identfier : 标识符
    -- operator : 运算符
    -- delimiter : 分界符
`)

let input = fs.createReadStream(__dirname + '/main.c')
readLines(input, startAnalysis)

function startAnalysis(data) {
    console.log(data)
}