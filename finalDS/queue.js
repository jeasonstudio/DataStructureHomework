class Queue {
    constructor(head, end) {
        this.head = head;
        this.end = end;
    }
}
class node {
    constructor(data, next) {
        this.data = data;
        this.next = next;
    }
}

let myQueue = new Queue()

function gets(cb) {
    process.stdin.setEncoding('utf8');
    process.stdin.resume();
    process.stdin.on('data', function (chunk) {
        // console.log('start!');
        //去掉下一行可一直监听输入，即保持标准输入流为开启模式
        // process.stdin.pause();
        cb(chunk);
    });
    console.log('Please input string');
}

gets(function (m) {
    let result = m[0]
    if (m.length > 2) {
        console.log('U should input just one char.')
    } else if (result === '0') {
        // console.log(1)
        console.log('deQueue data is:', deQueue())
        // printQueue(myQueue.head, [])
    } else if (result === '@') {
        // console.log(2)
        printQueue(myQueue.head, [])
    } else if (result === '#') {
        console.log('The queue is ending:', printQueue(myQueue.head, []))
        process.stdin.emit('end');
    } else {
        // console.log(3)
        console.log('enqueue', result)
        enQueue(result)
    }
});

function deQueue() {
    if (myQueue.head === undefined) {
        console.log('There is an empty queue!!')
    } else {
        let d = myQueue.head.data
        myQueue.head = myQueue.head.next
        console.log(myQueue)
        return d
    }
}

function enQueue(text) {
    let thisNode = new node(text)

    if (myQueue.head === undefined) {
        myQueue.head = thisNode
        myQueue.end = thisNode
        myQueue.head.next = myQueue.end
    } else {
        myQueue.end.next = thisNode
        myQueue.end = thisNode
    }
    console.log(myQueue.head)
}

function printQueue(node, arr) {
    if (node === undefined) {
        console.log('This is an empty Queue!!')
        return
    }
    arr.push(node.data)
    if (node.next !== undefined) {
        return printQueue(node.next, arr)
    } else {
        console.log('Your Queue is:', arr.join(','))
    }
}