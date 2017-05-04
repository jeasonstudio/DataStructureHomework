function output = dm(input)
    t = -2:.1:2;
    [x,y] = meshgrid(t);
    z = x .* exp(-x .^ 2 - y .^ 2);
    subplot(1,2,1),mesh(x,y,z)
    subplot(1,2,2),surf(x,y,z)
end