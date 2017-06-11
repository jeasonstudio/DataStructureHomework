% clc
clear

function z= f(x)
    z=exp(x)+3*x^3-x^2-2;
end
function z=f1(x)
    z=exp(x)+9*x^2-2*x;
end

x=0;
k=0;
format long;

x1=x-f(x)/f1(x);
if(abs(x1)<1)
    res=abs(x1-x);
else
    res=abs((x1-x)/x1);
end
while (res>1e-4)
    x=x1;   
    x1=x-f(x)/f1(x);
    if(abs(x1)<1.5)
    res=abs(x1-x);
    k=k+1;
    else
    res=abs((x1-x)/x1);
    k=k+1;
    end
    if f(x1)==0
        k=0;
        break;
    end
end
fprintf('\nx = %f, k = %d\n', x, k);