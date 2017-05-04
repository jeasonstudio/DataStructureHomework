function output = que7()
    t = -10:.1:10;
    [x,y] = meshgrid(t);
    z = (x .^ 2) + (3 .* (y .^ 2));
    subplot(1,2,1),mesh(x,y,z),title('mesh');shading faceted
    subplot(1,2,2),surf(x,y,z),title('surf');shading flat,light('position',[0,0,200],'style','local')
end