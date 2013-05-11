
gybe_angles = [142.3, 144.3, 151.8, 164.1, 169.7, 172.1, 173.4];
beat_angles = [44.4, 43.8, 42.0, 40.6, 39.7, 39.3, 39.4];

wind_angle = pi/180*[beat_angles;
    repmat([52,60,75,90,110,120,135,150]',1,7);
    gybe_angles];

ta_run_vmg = [995.4, 793.0, 672.8, 592.3, 541.8, 507.5, 458.6];
ta_run = ta_run_vmg.*cos(pi-pi/180*gybe_angles);

ta_beat_vmg = [1034.6, 884.6, 811.3, 773.5, 751.5, 738.9, 733.0];
ta_beat = ta_beat_vmg.*cos(pi/180*beat_angles);

ta = [ta_beat;
    665.9, 577.5, 546.6, 530.8, 521.1, 515.0, 510.1;
    620.9, 550.5, 525.2, 511.4, 502.5, 496.6, 490.8;
    588.5, 531.1, 503.9, 488.0, 478.5, 471.8, 463.6;
    583.9, 523.4, 499.0, 481.7, 467.0, 456.1, 443.9;
    589.3, 523.8, 491.4, 470.1, 455.3, 445.4, 430.2;
    622.7, 537.4, 498.6, 471.9, 451.9, 436.5, 415.8;
    719.8, 583.4, 525.6, 491.3, 465.0, 443.7, 410.5;
    862.0, 686.8, 583.1, 529.5, 495.8, 469.5, 427.8;
    ta_run];

wind_values = [6:2:16,20];
wind_velocity = repmat(wind_values,size(ta,1),1);

sow = 3600./ta;

figure(1);
polar(wind_angle, sow);
view(-90,90);
%legend(num2str(6:2:20));

x = sow.*cos(wind_angle);
y = sow.*sin(wind_angle);

figure(2);
surf(x,y,wind_velocity);
axis equal;
view(-90,90)

figure(3);
cs = contour(x,y,wind_velocity,wind_values);
clabel(cs)
axis equal
view(-90,90)


ta2 = [ta;flipud(ta)];
wind_velocity2 = repmat(wind_values,size(ta2,1),1);
wind_angle2 = [wind_angle;-flipud(wind_angle)];
sow2 = 3600./ta2;

figure(4);
polar(wind_angle2, sow2);
view(-90,90);


% beat apparent wind
ap_wind_x = wind_values.*sin(pi/180*beat_angles);
ap_wind_y = wind_values.*cos(pi/180*beat_angles) + sow(1,:);
ap_wind_angle = 180/pi*atan2(ap_wind_x,ap_wind_y);

figure(5);
plot(wind_values,ap_wind_angle);


set_mag = 2;
set_dir = 330*pi/180;


