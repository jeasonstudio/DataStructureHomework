function output = test()
%test - Description
%
% Syntax: output = test()
%
% Long description
    x = 0:6;
    y = cos(x);
    xi = 0:.25:6;
    yi1 = interp1(x,y,xi,'*nearest');
    yi2 = interp1(x,y,xi,'*linear');
    yi3 = interp1(x,y,xi,'*spline');
    yi4 = interp1(x,y,xi,'*cubic');
    plot(x, y, 'ro', xi, yi1, '--', xi, yi2, '-', xi, yi3, 'k.-', xi, yi4, 'm:')
    
end