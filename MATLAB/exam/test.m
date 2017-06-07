clear
format long

function y = mu(X)
    n=length(X);
    s=sum(X);
    y=s/n;
end

function y = sigma2(X)
    Y=X-mu(X);
    Y2=Y.*Y;
    n=length(X);
    s=sum(Y2);
    y=s/n;
end

load a.txt
mu=mu(a)
sig=sigma2(a)
[mu,sigma,muci,sigmaci]=normfit(a,0.95)
[mu,sigma,muci,sigmaci]=normfit(a,0.99)