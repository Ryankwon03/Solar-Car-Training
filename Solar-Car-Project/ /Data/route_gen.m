NUM_SEGS = 250;

%% Route Grade/Altitude Gen Part
rel_alt = 0.5;
% while(std(rel_alt) > 1.0 || max(abs(rel_alt)) < 0.2)
while(max(abs(rel_alt)) > 2.0 || max(abs(rel_alt)) < 1.0...
        && std(rel_alt) < 0.2)
    grade = round(generate_random_pts(NUM_SEGS)', 5);
    rel_alt = cumsum(grade);
    std(rel_alt);
end
x = 1:1:NUM_SEGS;
subplot(411);
plot(x,grade);
hold on
plot(x,rel_alt);
hold off
ylim([-4 4]);
legend(["grade", "route alt."]);


%% Wind Direction and Magnitude Gen
w_mag = round(abs(13 + 7 .* randn([1, NUM_SEGS])'), 5);

w_dir = mod(round(abs(180 + 90 .* randn([1, NUM_SEGS])'), 5), 360);

subplot(412);
plot(x,w_mag);
legend(["wind mag"]);

subplot(413);
plot(x,w_dir);
legend(["wind dir"]);

%% Speed Limit Gen
n = 9;
set_of_lims = [60 80 110 110 110 130 130 130 130 130 130 130 130];
bigseg_len = NUM_SEGS / 10; % 10 equidistant segs
lims_sample = [...
    set_of_lims(randi(n)) set_of_lims(randi(n)) set_of_lims(randi(n)) ...
    set_of_lims(randi(n)) set_of_lims(randi(n)) set_of_lims(randi(n)) ...
    set_of_lims(randi(n)) set_of_lims(randi(n)) set_of_lims(randi(n)) ... 
    set_of_lims(randi(n)) ];
speed_lims = repelem(lims_sample, bigseg_len)';
subplot(414);
plot(x, speed_lims);
ylim([0 100]);
legend(["speed lim"]);



%% Output to CSV
output = array2table(horzcat(w_mag, w_dir, grade, speed_lims));
output.Properties.VariableNames(1:4) = ...
    {'wind_speed','wind_dir','grade','speed_limit'};
writetable(output, 'route.csv');


%% Function to generate random pts in [-0.03, 0.03] in a sane manner
function [y1] = generate_random_pts (NUM_SEGS)

x = 1:1:NUM_SEGS;
y1 = ( 0 ...
    + (-1 ^ randi(2)) * (sin(x * randi([-NUM_SEGS, NUM_SEGS]))) ...
    + (-1 ^ randi(2)) * (cos(x * randi([-NUM_SEGS, NUM_SEGS]))) ...
    + (-1 ^ randi(2)) * (sin(x * randi([-NUM_SEGS, NUM_SEGS]))) ...
    + (-1 ^ randi(2)) * (cos(x * randi([-NUM_SEGS, NUM_SEGS]))) ...
    + (-1 ^ randi(2)) * (sin(x * randi([-NUM_SEGS, NUM_SEGS]))) ...
    + (-1 ^ randi(2)) * (cos(x * randi([-NUM_SEGS, NUM_SEGS]))) ...
    ) / (6 * 33);
% plot(x,y1);
% hold on
% plot(x,cumsum(y1));
% hold off
% ylim([-5 5]);

end
