clear
format long

load b.txt
figure(1)

[N,X]=hist(b(:),7)
hist(b(:),7) % b(:) 的意思是将矩阵 b 变成一列