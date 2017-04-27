function output = que1()
%que1 - Description
%
% Syntax: output = que1()
%
% Long description
    x = 0:0.05:pi*4;
    y = sin(3*x) .* exp(x/3);
    plot(x,y,'b*'), grid on,
    hold on,
    plot(x,exp(x/3),'r.',x,-exp(x/3),'r.')

    set(get(gca, 'Title'), 'String', '练习一');
end