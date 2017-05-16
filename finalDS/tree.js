class Tree {
    constructor(data, left, right) {
        this.data = data;
        this.left = left;
        this.right = right;
    }
}
let n = require('./txt.js')
let res = []

function insertNode(text, node) {
    if (text < node.data) {
        node.left === undefined && (node.left = new Tree(text))
        node.left !== undefined && (insertNode(text, node.left))
    } else if (text > node.data) {
        node.right === undefined && (node.right = new Tree(text))
        node.right !== undefined && (insertNode(text, node.right))
    }
}

function printTree(node) {
    node.left === undefined ? res.push(node.data) : printTree(node.left)
    node.data !== undefined && res.push(node.data)
    node.right === undefined ? res.push(node.data) : printTree(node.right)
}
(function (str) {
    console.log('Your input is:', str);
    let strArr = str.split(' ')
    let thisTree = new Tree(strArr[0]);
    strArr.map(r => insertNode(r, thisTree))
    console.log(thisTree)
    printTree(thisTree)
    console.log(new Set(res))
})(n)