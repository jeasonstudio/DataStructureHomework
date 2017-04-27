function output = draw()
%draw - Description
%
% Syntax: output = draw()
%
% Long description
    t = 0:pi/50:2*pi;
    plot(cos(t),sin(t),'b*'),grid on,
    hold on,
    plot(sin(t),sin(2*t),'r.')
end