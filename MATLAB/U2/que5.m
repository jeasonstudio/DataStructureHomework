function output = que5()
%que5 - Description
%
% Syntax: output = que5()
%
% Long description
    t = 0:pi/50:pi*20;

    x = t .* cos(t .* (pi/6));
    y = t .* sin(t .* (pi/6));
    z = t .* 2;

    plot3(x,y,z),grid on
    title('Question5')
    xlabel('x')
    ylabel('y')
    zlabel('z')
    legend('line')
end