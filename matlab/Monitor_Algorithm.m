%% 版权声明
% 第三代北斗B1信号质量评估平台监测指标算法仿真代码
% 数据通道: BOC(1,1)  导频通道：TMBOC(6,1,4/33)
% 采样率: 16MHz   中频：5MHz
% 作者: Hancheng Wang
% 日期:   2014.9
% 版权所有, 欢迎拷贝, 拷贝请注明出处!

clear;
%% Initialization Parameter
BGN = 10001;
END = 49000;
K = 50;
M = 20;
LEN = (END - BGN + 1)/1000;

%% load data
load('BD_DATA_60dB_50s_0_8.mat')
figure
subplot(2,1,1)
plot(Channel.syn.pkg_PB.I),title('I路')
subplot(2,1,2) 
plot(Channel.syn.pkg_PB.Q),title('Q路')
Ik = reshape(Channel.syn.pkg_PB.I(BGN:END),K,length(Channel.syn.pkg_PB.I(BGN:END))/K);
Qk = reshape(Channel.syn.pkg_PB.Q(BGN:END),K,length(Channel.syn.pkg_PB.Q(BGN:END))/K);
format long;
%% 伪距监测精度
PrnPhs = mean(reshape(dll_out(BGN:END),1000,length(dll_out(BGN:END))/1000));
figure;
subplot(2,1,1)
plot(dll_out(BGN:END));title('伪距监测 平均前');
subplot(2,1,2)
plot(PrnPhs);title('伪距监测 平均后');
StdPrnPhs = std(PrnPhs);


%% 载波相位监测精度
CarPhs = pll_out;
StdCarPhs = std(CarPhs(BGN:END)); 


%% 频率监测精确度
CarFrq = mean(reshape(car_filter_out(BGN:END),1000,length(car_filter_out(BGN:END))/1000)) - 80;
figure;
subplot(2,1,1)
plot(car_filter_out(BGN:END));title('频率监测 平均前');
subplot(2,1,2)
plot(CarFrq);title('频率监测 平均后');
StdCarFrq = std(CarFrq);


%% 载噪比
WBPm = sum(Ik.^2 + Qk.^2);
NBPm = (sum(abs(Ik))).^2 + (sum((Qk))).^2; 
temp = reshape(NBPm./WBPm,M,length(Channel.syn.pkg_PB.I(BGN:END))/K/M);
Etam = sum(temp)/M;
CN0 = 10*log10(1000*(Etam - 1)./(K - Etam));
std_CN0 = std(CN0);
CNO = mean(CN0);




% NPm = reshape(NBPm./WBPm,M,length(Channel.syn.pkg_PB.I(BGN:END))/K/M);
% uNP = 1/K*sum(NPm);
% CN0 = 10*log10(1000*(uNP-1)/(M-uNP));


















