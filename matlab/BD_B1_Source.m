%% 版权声明
% 第三代北斗B1信号质量评估平台信号源仿真代码
% 数据通道: BOC(1,1)  导频通道：TMBOC(6,1,4/33)
% 采样率: 16MHz   中频：5MHz
% 作者: Hancheng Wang
% 日期:   2014.9
% 版权所有, 欢迎拷贝, 拷贝请注明出处!

%% Source
function BD_B1_source
%% Initialize system parameters ===========================================
clc
TIMELEN = 1000;%bit
Channel.fs = 16e6;
Channel.tmr = 0;
Channel.smp_cnt = 1 ;
ms_cnt = 0;
ACCPHS = 2^32;
% Channel.wgn_cnt = 1;
Channel.DataChnl.car_par.fo = 5e6 - 80;
Channel.DataChnl.car_par.fcw = Channel.DataChnl.car_par.fo*ACCPHS/Channel.fs;
Channel.DataChnl.car_par.phs = 0;

Channel.DataChnl.prn_par.fo = 1.023e6 - 80/1540;
Channel.DataChnl.prn_par.fcw = Channel.DataChnl.prn_par.fo*ACCPHS/Channel.fs;
Channel.DataChnl.prn_par.phs = 0;
Channel.DataChnl.prn_cnt  = 1;
Channel.DataChnl.ms_cnt  = 1;
Channel.DataChnl.nv_cnt  = 1;

Channel.DataChnl.sub_par.fo = 1*1.023e6 - 80/1540;
Channel.DataChnl.sub_par.fcw = Channel.DataChnl.sub_par.fo*ACCPHS/Channel.fs;
Channel.DataChnl.sub_par.phs = 0;

Channel.PilotChnl.car_par.fo = 5e6 - 80;
Channel.PilotChnl.car_par.fcw = Channel.PilotChnl.car_par.fo*ACCPHS/Channel.fs;
Channel.PilotChnl.car_par.phs = 0;

Channel.PilotChnl.prn_par.fo = 1.023e6 - 80/1540;
Channel.PilotChnl.prn_par.fcw = Channel.PilotChnl.prn_par.fo*ACCPHS/Channel.fs;
Channel.PilotChnl.prn_par.phs = 0;
Channel.PilotChnl.prn_cnt  = 1;
Channel.PilotChnl.ms_cnt  = 1;

Channel.PilotChnl.sub_1.fo = 1*1.023e6 - 80/1540;
Channel.PilotChnl.sub_1.fcw = Channel.PilotChnl.sub_1.fo*ACCPHS/Channel.fs;
Channel.PilotChnl.sub_1.phs = 0;

Channel.PilotChnl.sub_6.fo = 6*1.023e6 - 6*80/1540;
Channel.PilotChnl.sub_6.fcw = Channel.PilotChnl.sub_6.fo*ACCPHS/Channel.fs;
Channel.PilotChnl.sub_6.phs = 0;
Channel.PilotChnl.NH = [-1 -1 -1 -1 -1 1 -1 -1 1 1 -1 1 -1 1 -1 -1 1 1 1 -1];
%% generate CA code
Channel.DataChnl.code  = code_gen(1);
Channel.PilotChnl.code = code_gen(2);
%% generate NV_BIT 
% n_nv = 1:ceil(TIMELEN/20);
% Channel.DataChnl.nvbit = sin(pi*n_nv-pi/2);
Channel.DataChnl.nvbit = [1 1 1 -1 -1 -1 1 -1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1 -1 1];
%% initial parameter
sigPower    = 0.5;
C_N0        = 70;
%% generate noise
L           = Channel.fs*0.001;
SNR         = C_N0 - 10*log10(Channel.fs);%dB
SNR         = 10^(SNR/10);
noisePower  = sigPower/SNR;
Channel.wgn = sqrt(noisePower)*randn(1,L);

Fid = fopen('BD_B1_5M_1s_NWGN.bin','wb'); 
%% generate NV_signal
while(Channel.tmr < TIMELEN)
    if mod(Channel.PilotChnl.prn_cnt,33) == 1 || mod(Channel.PilotChnl.prn_cnt,33) == 5 || mod(Channel.PilotChnl.prn_cnt,33) == 7 || mod(Channel.PilotChnl.prn_cnt,33) == 30
        sample_data = (sqrt(0.75)*Channel.PilotChnl.code(Channel.PilotChnl.prn_cnt)*sgn(sin(2*pi*Channel.PilotChnl.sub_6.phs/(ACCPHS)))*Channel.PilotChnl.NH(Channel.PilotChnl.ms_cnt)...
            +sqrt(0.25)*Channel.DataChnl.nvbit(Channel.DataChnl.nv_cnt)*Channel.DataChnl.code(Channel.DataChnl.prn_cnt)*sgn(sin(2*pi*Channel.DataChnl.sub_par.phs/(ACCPHS))))*cos(2*pi*Channel.DataChnl.car_par.phs/(ACCPHS));
    else
        sample_data = (sqrt(0.75)*Channel.PilotChnl.code(Channel.PilotChnl.prn_cnt)*sgn(sin(2*pi*Channel.PilotChnl.sub_1.phs/(ACCPHS)))*Channel.PilotChnl.NH(Channel.PilotChnl.ms_cnt)...
            +sqrt(0.25)*Channel.DataChnl.nvbit(Channel.DataChnl.nv_cnt)*Channel.DataChnl.code(Channel.DataChnl.prn_cnt)*sgn(sin(2*pi*Channel.DataChnl.sub_par.phs/(ACCPHS))))*cos(2*pi*Channel.DataChnl.car_par.phs/(ACCPHS));
    end
    temp_data = sample_data + Channel.wgn(Channel.smp_cnt);
    output_data(Channel.smp_cnt) =  round((temp_data)/13*128);
    if output_data(Channel.smp_cnt) > 127
        output_data(Channel.smp_cnt) = 127;
    else if output_data(Channel.smp_cnt) < -127
            output_data(Channel.smp_cnt) = -127;
        end
    end
    
    
    Channel.DataChnl.car_par.phs = Channel.DataChnl.car_par.phs + Channel.DataChnl.car_par.fcw;
    Channel.DataChnl.sub_par.phs = Channel.DataChnl.sub_par.phs + Channel.DataChnl.sub_par.fcw;
    Channel.DataChnl.prn_par.phs = Channel.DataChnl.prn_par.phs + Channel.DataChnl.prn_par.fcw;
    if Channel.DataChnl.car_par.phs >= ACCPHS
        Channel.DataChnl.car_par.phs = Channel.DataChnl.car_par.phs - ACCPHS;
    end

    if Channel.DataChnl.sub_par.phs >= ACCPHS
        Channel.DataChnl.sub_par.phs = Channel.DataChnl.sub_par.phs - ACCPHS;
    end

    if Channel.DataChnl.prn_par.phs >= ACCPHS
        Channel.DataChnl.prn_par.phs = Channel.DataChnl.prn_par.phs - ACCPHS;
        Channel.DataChnl.prn_cnt = Channel.DataChnl.prn_cnt + 1;

        if Channel.DataChnl.prn_cnt > 1023
            Channel.DataChnl.prn_cnt = 1;
            ms_cnt  = ms_cnt + 1
            Channel.DataChnl.ms_cnt = Channel.DataChnl.ms_cnt + 1;
            if Channel.DataChnl.ms_cnt > 20
                Channel.DataChnl.ms_cnt = 1;
                Channel.DataChnl.nv_cnt = Channel.DataChnl.nv_cnt + 1;
                if Channel.DataChnl.nv_cnt > 50
                    Channel.DataChnl.nv_cnt = 1;
                end
            end
        end
    end
%     Channel.PilotChnl.smp_cnt = Channel.PilotChnl.smp_cnt+1;
    
%     Channel.PilotChnl.car_par.phs = Channel.PilotChnl.car_par.phs + Channel.PilotChnl.car_par.fcw;
    Channel.PilotChnl.prn_par.phs  = Channel.PilotChnl.prn_par.phs + Channel.PilotChnl.prn_par.fcw;
    Channel.PilotChnl.sub_1.phs = Channel.PilotChnl.sub_1.phs + Channel.PilotChnl.sub_1.fcw;
    Channel.PilotChnl.sub_6.phs = Channel.PilotChnl.sub_6.phs + Channel.PilotChnl.sub_6.fcw;
    
    
%     if Channel.PilotChnl.car_par.phs >= ACCPHS
%         Channel.PilotChnl.car_par.phs = Channel.PilotChnl.car_par.phs - ACCPHS;
%     end

    if Channel.PilotChnl.sub_1.phs >= ACCPHS
        Channel.PilotChnl.sub_1.phs = Channel.PilotChnl.sub_1.phs - ACCPHS;
    end
    if Channel.PilotChnl.sub_6.phs >= ACCPHS
        Channel.PilotChnl.sub_6.phs = Channel.PilotChnl.sub_6.phs - ACCPHS;
    end
    
    if Channel.PilotChnl.prn_par.phs >= ACCPHS
        Channel.PilotChnl.prn_par.phs = Channel.PilotChnl.prn_par.phs - ACCPHS;
        Channel.PilotChnl.prn_cnt = Channel.PilotChnl.prn_cnt + 1;
        if Channel.PilotChnl.prn_cnt > 1023 
            Channel.PilotChnl.prn_cnt = 1;
            Channel.PilotChnl.ms_cnt = Channel.PilotChnl.ms_cnt + 1;
            if Channel.PilotChnl.ms_cnt > 20
                Channel.PilotChnl.ms_cnt = 1;
            end
        end
    end
    
    Channel.smp_cnt = Channel.smp_cnt + 1;
%     Channel.wgn_cnt = Channel.wgn_cnt + 1; 
    
    if Channel.smp_cnt > Channel.fs*0.001
        Channel.tmr = Channel.tmr + 1;
        Channel.smp_cnt = 1 ;
        fwrite(Fid,output_data,'int8'); 
        Channel.wgn     = sqrt(noisePower)*randn(1,L);
    end

end

fclose(Fid);







%% 产生扩频码 ===========================================
function [code]=code_gen(sat_num)%ca_ph=211
CA_ph = [2,6; 3,7; 4,8; 5,9; 1,9; 2,10; 1,8; 2,9; 3,10; 2,3; 3,4; 5,6; 6,7; 7,8; 8,9; 9,10; 
          1,4; 2,5; 3,6; 4,7; 5,8; 6,9; 1,3; 4,6; 5,7; 6,8; 7,9; 8,10; 1,6; 2,7; 3,8; 4,9];
%G1
reg = -1*ones(1,10);
for i = 1:1023
    g1(i) = reg(10);
    save1 = reg(3)*reg(10);
    reg(1,2:10) = reg(1,1:9);
    reg(1) = save1;
end

%G2
reg = -1*ones(1,10);
for i = 1:1023
    g2(i) = reg(CA_ph(sat_num,1))*reg(CA_ph(sat_num,2));
    save2 = reg(2)*reg(3)*reg(6)*reg(8)*reg(9)*reg(10);
    reg(1,2:10) = reg(1,1:9);
    reg(1) = save2;
end

code = g1.*g2;


function [y] = sgn(x)
if(x >= 0)
    y =  1;
else
    y = -1;
end
