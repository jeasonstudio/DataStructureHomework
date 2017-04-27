function output = D3draw()
%3Ddraw - Description
%
% Syntax: output = D3draw()
%
% Long description
    t = 0:pi/10:20*pi;
    x = t .* sin(t);
    y = t .*cos(t);
    z = t;
    plot3(x,y,z)
end