function output = que3()
%que3 - Description
%
% Syntax: output = que3()
%
% Long description
    x1 = -1*pi:0.1:pi;
    x2 = pi:0.1:4*pi;
    x3 = 1:0.1:8;

    y1 = x1 .* cos(x1);
    y3 = exp(1./x3) .* sin(x3);
    y2 = x2 .* tan(1./x2) .* sin(x2 .^ 3);

    subplot(3,1,1);
    plot(x1,y1),grid on
    legend('y=xcos(x)')
    title('y=xcos(x)')
    xlabel('x')
    ylabel('y')
    axis auto
    % gtext('POINTER')

    subplot(3,1,2);
    plot(x2,y2),grid on
    legend('y=xtan(1/x)sin(x^3)')
    title('y=xtan(1/x)sin(x^3)')
    xlabel('x')
    ylabel('y')
    % gtext('POINTER')

    subplot(3,1,3);
    plot(x3,y3),grid on
    legend('y=exp(1/x)sin(x)')
    title('y=exp(1/x)sin(x)')
    xlabel('x')
    ylabel('y')
    % gtext('POINTER')

end