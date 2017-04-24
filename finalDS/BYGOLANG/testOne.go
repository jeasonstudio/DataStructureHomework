package main

import (
	"fmt"
)

// Link s
type Link struct {
	ID   int
	Num  int
	Next *Link
}

func createLink() (*Link, int) {
	var id, len = 1, 0
	var DATA int
	// var s *Student = new(Student)
	var thisNode *Link = new(Link)
	resNode := thisNode

	for {
		stopThis, _ := fmt.Scanf("%d", &DATA)

		if stopThis == 0 {
			thisNode.Next = nil
			break
		}

		var nextNode *Link = new(Link)

		thisNode.ID = id
		thisNode.Num = DATA
		thisNode.Next = nextNode

		// fmt.Println(thisNode)

		id++
		len++
		thisNode = nextNode
	}
	// fmt.Println(id)

	return resNode, len
}

func AdjMax(s *Link, k int, len int) *Link {

	var MaxLinkHeadNode, MaxLinkEndNode, myHead *Link = s, new(Link), s
	MaxNum := 0

	// var Z *Link = &Link{0, 0, nil}

	for {
		thisMax := 0

		for m := 0; m < k; m++ {
			if m == 0 {
				MaxLinkEndNode = MaxLinkHeadNode
			} else {
				MaxLinkEndNode = MaxLinkEndNode.Next
			}

			thisMax = thisMax + MaxLinkEndNode.Num
		}

		if MaxLinkEndNode.Next == nil {
			break
		}
		if thisMax > MaxNum {
			MaxNum = thisMax
			myHead = MaxLinkHeadNode
		} else {
			MaxLinkHeadNode = MaxLinkHeadNode.Next
		}

	}

	return myHead
}

func main() {

	fmt.Println("Please input linked line A,type any STRING to end:")
	linkNodes, len := createLink()

	fmt.Printf("Please input k (0 < k < %d):\n", len-1)
	var k int
	for {
		fmt.Scanf("%d", &k)
		if k <= 0 || k >= len {
			fmt.Printf("Please input the right k (0 < k < %d):\n", len)
			continue
		} else {
			break
		}
	}

	// fmt.Println("K", k)

	resNode := AdjMax(linkNodes, k, len)
	fmt.Printf("The Reasult ID is: %d \nThe Result Data is: %d \n", resNode.ID, resNode.Num)
}
