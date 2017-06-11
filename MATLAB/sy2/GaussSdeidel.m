function [x,n]=GaussSdeidel(A,b,x0,eps,t)
    if nargin==3;
        eps=1e-4;
        m=200;
    elseif nargin<3
        error('');
        return;
    elseif nargin==5
        m=t;
    end
    D=diag(diag(A));
    L=-tril(A,-1);
    U=-triu(A,1);
    B=(D-L)\U;
    f=(D-L)\b;
    x=B*x0+f;
    n=1;
    while norm(x-x0)>=eps
        x0=x;
        x=B*x0+f;
        n=n+1;
        if(n>=m)
            disp('�����������࣬���ܲ�����');
            return;
        end;
end
