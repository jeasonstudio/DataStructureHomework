% clc
clear

a=0;
b=1;
k=0;
f=@(x)exp(x)+3*x^3-x^2-2;
c=(a+b)./2;
while abs(b-a)>1e-4
    if f(c)*f(b)<0
        a=c;
    else
        b=c;        
    end
    c=(a+b)./2;
    x=c;
    k=k+1;
end
fprintf('\nx = %f, k = %d\n', x, k);
