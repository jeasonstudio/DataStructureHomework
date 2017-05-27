/**
 * 计算逆波兰表达式的值
 */
function calculate(RPolishArray) {
    var result = 0;
    var tempArray = new Array(100);
    var tempNum = -1;
    for (i = 0; i < RPolishArray.length; i++) {
        if (RPolishArray[i].match(/\d/)) {
            tempNum++;
            tempArray[tempNum] = RPolishArray[i];
        } else {
            switch (RPolishArray[i]) {
                case '+':
                    result = (tempArray[tempNum - 1] * 1) + (tempArray[tempNum] * 1);
                    tempNum--;
                    tempArray[tempNum] = result;
                    break;
                case '-':
                    result = (tempArray[tempNum - 1] * 1) - (tempArray[tempNum] * 1);
                    tempNum--;
                    tempArray[tempNum] = result;
                    break;
                case '*':
                    result = (tempArray[tempNum - 1] * 1) * (tempArray[tempNum] * 1);
                    tempNum--;
                    tempArray[tempNum] = result;
                    break;
                case '/':
                    result = (tempArray[tempNum - 1] * 1) / (tempArray[tempNum] * 1);
                    tempNum--;
                    tempArray[tempNum] = result;
                    break;
            }
        }
    }
    result = tempArray[tempNum];
    return result;
}

/**
 * 把普通算术表达式转换为逆波兰表达式
 */
function toRPolish(input) {
    var regex = /(\(|\)|\+|\-|\*|\/)+/;
    var array = input.split(regex);
    var RPolish = ""
    var isI = false;
    num = 0;
    var SymbolArray = new Array(100);
    var SymbolNum = -1;
    for (j = 0; j < input.length; j++) {
        if (input.charAt(j).match(/\d/)) {
            if (isI == false) {
                RPolish += ','
                RPolish += array[num];
                num++;
                isI = true;
            }
        } else {
            if (SymbolNum == -1) {
                SymbolNum++;
                SymbolArray[SymbolNum] = input.charAt(j);
            } else {
                if (input.charAt(j).match(/\(/) || SymbolArray[SymbolNum].match(/\(/)) {
                    SymbolNum++;
                    SymbolArray[SymbolNum] = input.charAt(j);
                } else if (input.charAt(j).match(/\)/)) {
                    while (!SymbolArray[SymbolNum].match(/\(/)) {
                        RPolish += ',';
                        RPolish += SymbolArray[SymbolNum];
                        SymbolNum--;
                    }
                    SymbolNum--;
                } else if (compare(input.charAt(j), SymbolArray[SymbolNum])) {
                    SymbolNum++;
                    SymbolArray[SymbolNum] = input.charAt(j);
                } else if (!compare(input.charAt(j), SymbolArray[SymbolNum])) {
                    RPolish += ',';
                    RPolish += SymbolArray[SymbolNum];
                    SymbolNum--;
                    if (SymbolNum >= 0) {
                        if (SymbolArray[SymbolNum].match(/\(/)) {
                            SymbolNum++;
                            SymbolArray[SymbolNum] = input.charAt(j);
                        } else if (!compare(input.charAt(j), SymbolArray[SymbolNum])) {
                            RPolish += ',';
                            RPolish += SymbolArray[SymbolNum];
                            SymbolArray[SymbolNum] = input.charAt(j);
                        } else {
                            SymbolNum++;
                            SymbolArray[SymbolNum] = input.charAt(j);
                        }
                    } else {
                        SymbolNum++;
                        SymbolArray[SymbolNum] = input.charAt(j);
                    }
                }
            }
            isI = false;
        }
    }
    while (SymbolNum >= 0) {
        RPolish += ',';
        RPolish += SymbolArray[SymbolNum];
        SymbolNum--;
    }
    regex = /,/;
    var RPolishArray = RPolish.split(regex);
    return RPolishArray;
}

function compare(a, b) {
    if ((a.match(/\*/) || a.match(/\//)) && (b.match(/\+/) || b.match(/\-/))) {
        return true;
    } else {
        return false;
    }
}

console.log(toRPolish('1  asd+f (a(^%$2$@+#3)*4)-5').join(' '))