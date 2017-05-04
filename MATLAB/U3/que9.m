function output = que9()
    t = -2:.01:2;
    [x,y] = meshgrid(t);
    z = 5 - x .^ 2 - y .^ 2;
    subplot(1,3,1),mesh(x,y,z),title('mesh');shading flat
    z2 = 3 * ones(size(x));
    subplot(1,3,2),mesh(x,y,z2),title('z = 3');shading flat
    r0 = abs(z-z2) <= 0.05;
    zz = r0 .* z2;
    yy = r0 .* y;
    xx = r0 .* x;
    subplot(1,3,3),plot3(xx(r0 ~= 0),yy(r0 ~= 0),zz(r0 ~= 0),'x'),title('jiaoxian')
end