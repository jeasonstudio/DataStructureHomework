clear
format long
A = [14,2,1,5;8,17,2,10;4,18,3,6;12,26,11,20];
b = [1;2;3;4];
eps = 1e-04;
t = 50;

x0=ones(4,1);
GaussSdeidel(A,b,x0,eps,t)
jacobi(A,b,x0)