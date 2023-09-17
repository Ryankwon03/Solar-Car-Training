%% A MATLAB script to help visualize csv output from running a simulation
% Use this to visualize changing forces and energy levels and validate results
data = readmatrix('../output.csv');
SEGMENTS = [1:1:size(data, 1)]';

subplot(3, 4, 1);
plot(SEGMENTS, data(:, 1));
xlabel("segment num");
ylabel("aero res force");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 2);
plot(SEGMENTS, data(:, 2));
xlabel("segment num");
ylabel("array power");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 3);
plot(SEGMENTS, data(:, 3));
xlabel("segment num");
ylabel("bearing res force");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 4);
plot(SEGMENTS, data(:, 5));
xlabel("segment num");
ylabel("battery energy remaining");
xlim([1 max(SEGMENTS)]);
ylim([0 max(data(:, 5))]);

subplot(3, 4, 5);
plot(SEGMENTS, data(:, 6));
xlabel("segment num");
ylabel("energy gained");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 6);
plot(SEGMENTS, data(:, 7));
xlabel("segment num");
ylabel("gravitation res force");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 7);
plot(SEGMENTS, data(:, 9));
xlabel("segment num");
ylabel("motor loss");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 8);
plot(SEGMENTS, data(:, 10));
xlabel("segment num");
ylabel("power out");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 9);
plot(SEGMENTS, data(:, 11));
xlabel("segment num");
ylabel("resistive force");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 10);
plot(SEGMENTS, data(:, 12));
xlabel("segment num");
ylabel("speed");
xlim([1 max(SEGMENTS)]);
ylim([0 120]);

subplot(3, 4, 11);
plot(SEGMENTS, data(:, 13));
xlabel("segment num");
ylabel("time (hours since race)");
xlim([1 max(SEGMENTS)]);

subplot(3, 4, 12);
plot(SEGMENTS, data(:, 14));
xlabel("segment num");
ylabel("tire res force");
xlim([1 max(SEGMENTS)]);
