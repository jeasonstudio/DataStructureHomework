function[x,n]=jacobi(A,b,x0,eps,varargin)

if nargin==3
    eps=1.0e-4;
    M=200;
    else if nargin<3
          error('')
            return
        else if nargin==5
            M=varargin{1};
            end
        end
end
D=diag(diag(A));
L=-tril(A,-1);
U=-tril(A,1);
B=D\(L+U);
f=D\b;
x=B*x0+f;
n=1;
while norm(x-x0)>=eps
    x0=x;
    x=B*x0+f;
    n=n+1;
    if(n>=M)
        disp('注意:迭代次数过多，可能不收敛');
        return;
    end                                              
end    
end
