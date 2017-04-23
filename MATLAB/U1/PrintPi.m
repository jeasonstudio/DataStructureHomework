function Pi = PrintPi()
%PrintPi - Description
%
% Syntax: Pi = PrintPi()
%
% Long description
    Pi = 0;
    a = 0;
    b = 1;
    i = 1;
    
    while b >= 1e-6
        b = 1 / i;
        i = i + 2;
        Pi = Pi + b * ((-1) ^ ((i + 1) / 2));
    end

    Pi = Pi * 4;
end