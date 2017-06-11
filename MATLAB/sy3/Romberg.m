function y = f(x)
    y = (3 * x - x ^ 2 + x ^ 3 + exp(x)) ^ 0.5;
end

function [quad,R]  =  Romberg(f)
    a = 0;
    b = 2;
    eps = 1e-5;
    h = b-a;
    R(1,1) = h*(feval('f',a)+feval('f',b))/2;
    M = 1;J = 0;err = 1;
    while err>eps
        J = J+1;
        h = h/2;
        S = 0;
        for p = 1:M
            x = a+h*(2*p-1);
            S = S+feval('f',x);
        end
        R(J+1,1) = R(J,1)/2+h*S;
        M = 2*M;
        for k = 1:J
            R(J+1,k+1) = R(J+1,k)+(R(J+1,k)-R(J,k))/(4^k-1);
        end
        err = abs(R(J+1,J)-R(J+1,J+1));
    end
    quad = R(J+1,J+1); 
    J
    h
end
