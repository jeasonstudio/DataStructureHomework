class Node {
    constructor(num, text, fin, fout) {
        this.num = num;
        this.text = text;
        this.fin = fin;
        this.fout = fout;
    }
}

class Rela {
    constructor(tailvex, headvex, fin, fout) {
        this.tailvex = tailvex;
        this.headvex = headvex;
        this.fin = fin;
        this.fout = fout;
    }
}

(function () {
    let nodes = require('./info').node;
    let relas = require('./info').rela;
    let [nNodes, nRelas] = [new Array(), new Array()]

    nodes.map((r, n) => nNodes[n] = new Node(n, r))
    relas.map((r, n) => {
        let thisRela = new Rela(r.split('->')[0], r.split('->')[1])
        for (var index = 0; index < nNodes.length; index++) {
            if (nNodes[index].text === r.split('->')[0]) {
                let t = nNodes[index]
                while (true) {
                    if (t.fout === undefined) {
                        t.fout = thisRela
                        break
                    } else {
                        t = t.fout
                    }
                }
            } else if (nNodes[index].text === r.split('->')[1]) {
                let t = nNodes[index]
                while (true) {
                    if (t.fin === undefined) {
                        t.fin = thisRela
                        break
                    } else {
                        t = t.fin
                    }
                }
            }
        }
        nRelas.push(thisRela)
    })
    // console.log(nNodes[1])

    Array.prototype.remove = function (dx) {
        if (isNaN(dx) || dx > this.length) {
            return false;
        }
        for (var i = 0, n = 0; i < this.length; i++) {
            if (this[i] != this[dx]) {
                this[n++] = this[i]
            }
        }
        this.length -= 1　
    }

    for (var o = 0; o < 10; o++) {
        nNodes.map((r, n) => {
            if (r.fin === undefined) {
                console.log('Deleted node:', r.text)
                r.fout = undefined
                // TODO
                nNodes.remove(n)
                console.log('Rest nodes num:', nNodes.length)
            }
        })
    }
})()