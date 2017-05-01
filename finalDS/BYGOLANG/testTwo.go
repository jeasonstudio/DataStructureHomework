package main

import "fmt"
import "strings"

// Stack struct as stack
type Stack struct {
	quenu map[int]string
}

// New init stack
func New() *Stack {
	s := new(Stack)
	s.quenu = make(map[int]string)
	return s
}

// Push Push to stack
func (s *Stack) Push(i string) {
	s.quenu[len(s.quenu)] = i
}

// Pop pop a num
func (s *Stack) Pop() string {
	item := s.CheckTop()
	delete(s.quenu, len(s.quenu)-1)
	return item
}

// CheckTop check the top
func (s *Stack) CheckTop() string {
	return s.quenu[len(s.quenu)-1]
}

func (s *Stack) String() []string {
	var info []string
	for i := 0; i < len(s.quenu); i++ {
		info = append(info, s.quenu[i])
	}
	return info
}

func (s *Stack) checkFirst(a string) bool {
	if (a == "(" || a == ")") || ((a == "*" || a == "/") && (s.CheckTop() == "+") || (s.CheckTop() == "-")) {
		return true
	}
	return false

}

func dealInput(s string) []string {
	midresult := New()
	operator := New()
	strArr := strings.Split(s, "")
	fmt.Println(strArr)

	for i := range strArr {
		if strArr[i] >= "0" && strArr[i] <= "9" {
			// 遇到操作数时，将其压入midresult
			midresult.Push(strArr[i])
		} else if strArr[i] == "+" || strArr[i] == "-" || strArr[i] == "*" || strArr[i] == "/" {
			//  遇到运算符时，比较其与operator栈顶运算符的优先级：
		TAG:
			if operator.CheckTop() == "" || operator.CheckTop() == "(" || operator.checkFirst(strArr[i]) {
				// 如果operator为空，或栈顶运算符为左括号“(”，则直接将此运算符入栈,否则，若优先级比栈顶运算符的高，也将运算符压入operator
				operator.Push(strArr[i])
			} else {
				//  否则，将operator栈顶的运算符弹出并压入到midresult中，再次转到(4-1)与operator中新的栈顶运算符相比
				midresult.Push(operator.Pop())
				goto TAG
			}
		} else if strArr[i] == "(" {
			// 如果是左括号“(”，则直接压入operator
			operator.Push("(")
		} else if strArr[i] == ")" {
			// 如果是右括号“)”，则依次弹出operator栈顶的运算符，并压入midresult，直到遇到左括号为止，此时将这一对括号丢弃；
		TAGT:
			optop := operator.Pop()
			// fmt.Println(optop)
			if optop != "(" {
				midresult.Push(optop)
				goto TAGT
			}
		} else {
			continue
		}
		// fmt.Println("MID:---", midresult)
		// fmt.Println("OPT:---", operator)
	}

	for {
		thisTemp := operator.Pop()
		if thisTemp != "" {
			midresult.Push(thisTemp)
		} else {
			break
		}
	}

	return midresult.String()
}

func main() {
	fmt.Println("The result is :", dealInput("1  asd+f (a(^%$2$@+#3)*4)-5"))
}
