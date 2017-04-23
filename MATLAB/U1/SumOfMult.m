function res = SumOfMult(n)
%SumOfMult -  阶乘和
%
% Syntax: res = SumOfMult(n)
%
% Long description
    res = 0;
    mySum = 1;
    for i = 1:n
        mySum = mySum * i;
        res = res + mySum;
    end
end