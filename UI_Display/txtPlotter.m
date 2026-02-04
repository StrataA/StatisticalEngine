%% Text to table to scatter plots
% Intent for this code is to recieve grand time-scale data points (eg. daily
% avarages over multiple weeks) and display that relation on plots.

% Currently hard coded for temperature-humidity-time relationships

% Input .txt should be formatted with 1 header line at the top, as follows:
% HEADING LINE: item_1|item_2|item_3|...
% Data Lines  : data_1|data_2|data_3|...


T = readtable('testNumbers.txt', 'Delimiter' ,'|');

%% 'Temperature vs Sample Number'
figure;
scatter(T, "num", "temperature")
title('Temperature vs Time');


%% 'Humidity vs Sample Number'
figure;
scatter(T, "num", "humidity");
title('Humidity vs Time');


%% 'Humidity vs Temperature'
figure;
scatter(T, "temperature", "humidity");
title('Humidity vs Temperature');