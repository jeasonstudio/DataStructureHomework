function [y]=f(x)  %  自定义函数
    y= (3 * x - x ^ 2 + x ^ 3 + exp(x)) ^ 0.5;
end

clc
clear
format long e; % 精确显示

y=18;        
T=zeros(y,y); % 定义长度为y的矩阵T
for i=0:y-1 
    T(i+1)=i; % 对矩阵T的第一行赋初值
end

a=0;
b=1;
T(1,2)=(b-a)*(1+f(b))/2; % 算出T1

for l=2:y              
    sum=0;
    for j=1:2^(l-1)
        sum=sum+f(a+(2*j-1)*(b-a)/2^l);
    end
    T(l,2)=T(l-1,2)/2+((b-a)/2^l)*sum;  % 算出梯形序列
    if (T(l,2)-T(l-1,2)) < 1e-5;     % 判断是否符合精度
        break;
    end
end
h=1;
for m=1:y-2
    for k=h:(y+h-m-1)
        T(k+1,m+2)=((4^m)*T(k+1,m+1)-T(k,m+1))/(4^m-1);
                                          % 按公式算出接下去的序列
    if (T(k+1,m+2)-T(k,m+2))<0.0000005;
        break;
    end
    end
    h=h+1;
end