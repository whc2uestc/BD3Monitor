%% 版权声明
% 第三代北斗B1信号质量评估平台接收机仿真代码
% 数据通道: BOC(1,1)  导频通道：TMBOC(6,1,4/33)
% 采样率: 16MHz   中频：5MHz
% 作者: Hancheng Wang
% 日期:   2014.9
% 版权所有, 欢迎拷贝, 拷贝请注明出处!
%% B1信号

function BD_B1_trk
clc;
GAME_OVER = 1000;
ACCPHS = 2^32;
%% initial condition
Channel(1).fs = 16e6;
Channel(1).f_car = 5e6;
Channel(1).f_prn = 1.023e6;
Channel(1).f_sub = 1.023e6;


Channel(1).car_par.fo = Channel(1).f_car;
Channel(1).car_par.fcw = Channel(1).car_par.fo*ACCPHS/Channel(1).fs;
Channel(1).car_par.phs = 0;

Channel(1).sub_par.fo = Channel(1).f_sub;
Channel(1).sub_par.fcw = Channel(1).sub_par.fo*ACCPHS/Channel(1).fs;
Channel(1).sub_par.phs = 0;

Channel(1).prn_par.fo = Channel(1).f_prn;
Channel(1).prn_par.fcw = Channel(1).prn_par.fo*ACCPHS/Channel(1).fs;
Channel(1).prn_par.phs = 0;

Channel(1).pkg_par.fo = 4*1.024e6;
Channel(1).pkg_par.phs = 0;
Channel(1).pkg_par.fcw = Channel(1).pkg_par.fo*ACCPHS/Channel(1).fs;
Channel(1).pkg_par.N_FFT = Channel(1).pkg_par.fo*0.001;
Channel(1).pkg_par.pid = 1;
Channel(1).pkg_par.bag.re = 0*ones(1,Channel(1).pkg_par.N_FFT);
Channel(1).pkg_par.bag.im = 0*ones(1,Channel(1).pkg_par.N_FFT);
Channel(1).pkg_par.did = 1;


Channel(1).acq.rec = 0;
Channel(1).acq.flg = 0;

Channel(1).trk.prn_loop.Bl = 0.8;
Channel(1).trk.prn_loop.wnd = Channel(1).trk.prn_loop.Bl/0.53;
Channel(1).trk.prn_loop.dll_a = 1.0*Channel(1).trk.prn_loop.wnd^2;
Channel(1).trk.prn_loop.dll_b = 1.414*Channel(1).trk.prn_loop.wnd;
reg = 0;
Channel(1).trk.prn_loop.reg = reg;
reg0 = 0;
reg1 = 0;
Channel(1).trk.car_loop.reg0 = reg0;
Channel(1).trk.car_loop.reg1 = reg1;
Channel(1).trk.car_loop.Bl = 18;
Channel(1).trk.car_loop.wnf = Channel(1).trk.car_loop.Bl/0.53;
Channel(1).trk.car_loop.wnp = Channel(1).trk.car_loop.Bl/0.7845;
Channel(1).trk.car_loop.pll_a = 1.0*Channel(1).trk.car_loop.wnp^3*3;
Channel(1).trk.car_loop.pll_b = 1.1*Channel(1).trk.car_loop.wnp^2*3;
Channel(1).trk.car_loop.pll_c = 2.4*Channel(1).trk.car_loop.wnp*1*3;
Channel(1).trk.car_loop.fll_a = 1.0*Channel(1).trk.car_loop.wnf^2*0.1;
Channel(1).trk.car_loop.fll_b = 1.414*Channel(1).trk.car_loop.wnf*0.1;
Channel(1).trk.tmr = 0;

Channel(1).trk.fll_en = 1;
Channel(1).trk.fll_cnt = 0;
Channel(1).trk.pll_en = 0;

Channel(1).trk.phsE = 2^30;
Channel(1).trk.phsP = 0;
Channel(1).trk.phsL = ACCPHS - 2^30;
Channel(1).trk.cidE = 1;
Channel(1).trk.cidP = 1;
Channel(1).trk.cidL = 1023;
Channel(1).trk.code = codegen(1);
Channel(1).trk.mag.re = 0*ones(1,20);
Channel(1).trk.mag.im = 0*ones(1,20);
Channel(1).trk.pid = 1;
Channel(1).trk.suc = 0;
Channel(1).trk.rdy = 1;
Channel(1).chnltype = 1;

Channel(1).syn.pid = 1;
Channel(1).syn.PID = 20;
Channel(1).syn.non = 1;
Channel(1).syn.NON = 11;
Channel(1).syn.flg = 0;
Channel(1).syn.suc = 0;
Channel(1).syn.win = 0*ones(1,Channel(1).syn.PID);


Channel(2).fs = 16e6;
Channel(2).f_car = 5e6;
Channel(2).f_prn = 1.023e6;
Channel(2).f_sub = 1.023e6;

Channel(2).car_par.fo = 5e6;
Channel(2).car_par.fcw = Channel(2).car_par.fo*2^32/Channel(2).fs;
Channel(2).car_par.phs = 0;

Channel(2).sub_par.fo = 1.023e6;
Channel(2).sub_par.fcw = Channel(2).sub_par.fo*2^32/Channel(2).fs;
Channel(2).sub_par.phs = 0;
Channel(2).sub_6.fo = 6*1.023e6;
Channel(2).sub_6.fcw = Channel(2).sub_6.fo*2^32/Channel(2).fs;
Channel(2).sub_6.phs = 0;

Channel(2).prn_par.fo = 1.023e6;
Channel(2).prn_par.fcw = Channel(2).prn_par.fo*2^32/Channel(2).fs;
Channel(2).prn_par.phs = 0;

Channel(2).pkg_par.fo = 4*1.024e6;
Channel(2).pkg_par.phs = 0;
Channel(2).pkg_par.fcw = Channel(2).pkg_par.fo*2^32/Channel(2).fs;
Channel(2).pkg_par.N_FFT = Channel(2).pkg_par.fo*0.001*2;
Channel(2).pkg_par.pid = 1;
Channel(2).pkg_par.bag.re = 0*ones(1,Channel(2).pkg_par.N_FFT);
Channel(2).pkg_par.bag.im = 0*ones(1,Channel(2).pkg_par.N_FFT);
Channel(2).pkg_par.did = 1;
Channel(2).NH = [-1 -1 -1 -1 -1 1 -1 -1 1 1 -1 1 -1 1 -1 -1 1 1 1 -1];

Channel(2).acq.rec = 0;
Channel(2).acq.flg = 0; 

Channel(2).trk.prn_loop.Bl = 0.8;
Channel(2).trk.prn_loop.wnd = Channel(2).trk.prn_loop.Bl/0.53;
Channel(2).trk.prn_loop.dll_a = 1.0*Channel(2).trk.prn_loop.wnd^2;
Channel(2).trk.prn_loop.dll_b = 1.414*Channel(2).trk.prn_loop.wnd;
reg = 0;
Channel(2).trk.prn_loop.reg = reg;
reg0 = 0;
reg1 = 0;
Channel(2).trk.car_loop.reg0 = reg0;
Channel(2).trk.car_loop.reg1 = reg1;
Channel(2).trk.car_loop.Bl = 18;
Channel(2).trk.car_loop.wnf = Channel(2).trk.car_loop.Bl/0.53;
Channel(2).trk.car_loop.wnp = Channel(2).trk.car_loop.Bl/0.7845;
Channel(2).trk.car_loop.pll_a = 1.0*Channel(2).trk.car_loop.wnp^3*3;
Channel(2).trk.car_loop.pll_b = 1.1*Channel(2).trk.car_loop.wnp^2*3;
Channel(2).trk.car_loop.pll_c = 2.4*Channel(2).trk.car_loop.wnp*1*3;
Channel(2).trk.car_loop.fll_a = 1.0*Channel(2).trk.car_loop.wnf^2*0.1;
Channel(2).trk.car_loop.fll_b = 1.414*Channel(2).trk.car_loop.wnf*0.1;
Channel(2).trk.tmr = 0;

Channel(2).trk.phsE = 2^30;
Channel(2).trk.phsP = 0;
Channel(2).trk.phsL = 2^32 - 2^30;
Channel(2).trk.subE = 2^31;
Channel(2).trk.subP = 0;
Channel(2).trk.subL = 2^32 - 2^31;
Channel(2).trk.cidE = 1;
Channel(2).trk.cidP = 1;
Channel(2).trk.cidL = 1023;
Channel(2).trk.code = codegen(2);
Channel(2).trk.rdy = 1;
Channel(2).chnltype = 2;

[Channel(2).pkg_par.fft_boc,Channel(2).pkg_par.fft_prn] = Pilot_fftgen(Channel(2));%本地BOC信号以及码的FFT
[Channel(1).pkg_par.fft_boc,Channel(1).pkg_par.fft_prn] = Data_fftgen(Channel(1));%本地BOC信号以及码的FFT
Fid = fopen('BD_B1_5M_50s_60dB.bin','r');


% data_src = fread(Fid,5,'int8');


while(1)
    data_src = fread(Fid,1,'int8');
    if Channel(1).acq.rec == 0
        if Channel(1).pkg_par.N_FFT > 0         
            Channel(1).pkg_par.bag.re(Channel(1).pkg_par.pid) = Channel(1).pkg_par.bag.re(Channel(1).pkg_par.pid) + data_src*cos(2*pi*Channel(1).car_par.phs/ACCPHS);
            Channel(1).pkg_par.bag.im(Channel(1).pkg_par.pid) = Channel(1).pkg_par.bag.im(Channel(1).pkg_par.pid) + data_src*sin(2*pi*Channel(1).car_par.phs/ACCPHS);
            Channel(1).pkg_par.phs = Channel(1).pkg_par.phs + Channel(1).pkg_par.fcw;
            Channel(1).car_par.phs = Channel(1).car_par.phs + Channel(1).car_par.fcw;
        else
            Channel(1).pkg_par.phs = Channel(1).pkg_par.phs + ACCPHS;
        end

        if Channel(1).car_par.phs >= ACCPHS
            Channel(1).car_par.phs = Channel(1).car_par.phs - ACCPHS;
        end
        if Channel(1).pkg_par.phs >= ACCPHS
            Channel(1).pkg_par.phs = Channel(1).pkg_par.phs - ACCPHS;
            Channel(1).pkg_par.pid = Channel(1).pkg_par.pid + 1;
            if Channel(1).pkg_par.pid > Channel(1).pkg_par.N_FFT
                Channel(1).pkg_par.pid = 1;
            % 捕获================================================================
            
                if Channel(1).acq.flg == 1                                 
                    Channel(1).acq.rec = 1;
                    Channel(1).pkg_par.fo = 4*1.023e6;
                    Channel(1).pkg_par.fcw = Channel(1).pkg_par.fo*ACCPHS/Channel(1).fs;
                    Channel(1).pkg_par.N_FFT = Channel(1).pkg_par.fo * 0.001;
                else      
                    Channel(1).acq.fft_src = fft(Channel(1).pkg_par.bag.re+1i*Channel(1).pkg_par.bag.im,Channel(1).pkg_par.N_FFT);
                                                                                     
                    DATA_fft_boc_src = Channel(1).acq.fft_src.*Channel(1).pkg_par.fft_boc;
                    DATA_fft_prn_src = Channel(1).acq.fft_src.*Channel(1).pkg_par.fft_prn;
                    DATA_Rb  = ifft(DATA_fft_boc_src,Channel(1).pkg_par.N_FFT);
                    DATA_Rbp = ifft(DATA_fft_prn_src,Channel(1).pkg_par.N_FFT);

                    DATA_R_ASPeCT = abs(DATA_Rb.^2 - DATA_Rbp.^2);
                    
                    plot(DATA_R_ASPeCT)
                    % 找出峰值及码相位====================
                    Channel(1).acq.pk = max(DATA_R_ASPeCT);%峰值
                    Channel(1).acq.av = sum(DATA_R_ASPeCT,2)/Channel(1).pkg_par.N_FFT;%均值
                    Channel(1).acq.phs = find(DATA_R_ASPeCT==max(DATA_R_ASPeCT));%码相位
                    DATA_pk = Channel(1).acq.pk;
                    DATA_av = Channel(1).acq.av;
                    DATA_phs0 = Channel(1).acq.phs;
                    DATA_phs = (Channel(1).pkg_par.N_FFT-Channel(1).acq.phs)/2+1;%*Channel(1).prn_par.fo/Channel(1).pkg_par.fo;
                    

               
                    if Channel(1).acq.pk > Channel(1).acq.av*10
                        Channel(1).acq.flg = 1;%捕获成功
                        Channel(1).acq.phs = find(DATA_R_ASPeCT==max(DATA_R_ASPeCT));
                        
                         % 相关函数===========================
                        bag = 1:Channel(1).pkg_par.N_FFT;
                        figure(1)
                        subplot(3,1,1);
                        plot(bag,DATA_Rb);
                        subplot(3,1,2);
                        plot(bag,DATA_Rbp);
                        subplot(3,1,3)
                        plot(bag,DATA_R_ASPeCT)
                        Channel(1).pkg_par.N_FFT = Channel(1).acq.phs-1;
                    end
                    Channel(1).pkg_par.bag.re = 0*ones(1,Channel(1).pkg_par.N_FFT);
                    Channel(1).pkg_par.bag.im = 0*ones(1,Channel(1).pkg_par.N_FFT);
                end
            end
                
        end
                % 跟踪==============================================================
    else
        if Channel(1).trk.rdy == 1
            Channel(1).trk.rdy = 0;
        	DATA_bag = 1;
        end
        
        Channel(1).pkg_par.bag.re(DATA_bag) = data_src*cos(2*pi*Channel(1).car_par.phs/ACCPHS);
        Channel(1).pkg_par.bag.im(DATA_bag) = data_src*sin(2*pi*Channel(1).car_par.phs/ACCPHS);
        Channel(1).car_par.phs = Channel(1).car_par.phs + Channel(1).car_par.fcw;

        if Channel(1).car_par.phs >= ACCPHS
            Channel(1).car_par.phs = Channel(1).car_par.phs - ACCPHS;
        end

        DATA_gen_prnE(DATA_bag) = Channel(1).trk.code(Channel(1).trk.cidE);
        DATA_gen_bocE(DATA_bag) = Channel(1).trk.code(Channel(1).trk.cidE)*sgn(sin(2*pi*Channel(1).trk.phsE/ACCPHS));
        DATA_gen_prnP(DATA_bag) = Channel(1).trk.code(Channel(1).trk.cidP);
        DATA_gen_bocP(DATA_bag) = Channel(1).trk.code(Channel(1).trk.cidP)*sgn(sin(2*pi*Channel(1).trk.phsP/ACCPHS));
        DATA_gen_prnL(DATA_bag) = Channel(1).trk.code(Channel(1).trk.cidL);
        DATA_gen_bocL(DATA_bag) = Channel(1).trk.code(Channel(1).trk.cidL)*sgn(sin(2*pi*Channel(1).trk.phsL/ACCPHS));

        Channel(1).trk.phsE = Channel(1).trk.phsE + Channel(1).prn_par.fcw;
        Channel(1).trk.phsP = Channel(1).trk.phsP + Channel(1).prn_par.fcw;
        Channel(1).trk.phsL = Channel(1).trk.phsL + Channel(1).prn_par.fcw;

        DATA_bag = DATA_bag + 1;
        if Channel(1).trk.phsE >= ACCPHS
            Channel(1).trk.phsE = Channel(1).trk.phsE - ACCPHS;
            Channel(1).trk.cidE = Channel(1).trk.cidE + 1;
            if Channel(1).trk.cidE > 1023
                Channel(1).trk.cidE = Channel(1).trk.cidE - 1023;
            end
        end
        if Channel(1).trk.phsP >= ACCPHS
            Channel(1).trk.phsP = Channel(1).trk.phsP - ACCPHS;
            Channel(1).trk.cidP = Channel(1).trk.cidP + 1;
            if Channel(1).trk.cidP > 1023
                Channel(1).trk.cidP = Channel(1).trk.cidP - 1023;
                Channel(1).trk.rdy = 1;
            end
        end
        if Channel(1).trk.phsL >= ACCPHS
            Channel(1).trk.phsL = Channel(1).trk.phsL - ACCPHS;
            Channel(1).trk.cidL = Channel(1).trk.cidL + 1;
            if Channel(1).trk.cidL > 1023
                Channel(1).trk.cidL = Channel(1).trk.cidL - 1023;
            end
        end     


        %[gen_prnE,gen_bocE,gen_prnP,gen_bocP,gen_prnL,gen_bocL] = gen_NCO(Channel(1),1);
        if Channel(1).trk.rdy == 1
            Channel(1).pkg_par.pkg_EB.re = sum(Channel(1).pkg_par.bag.re(1:DATA_bag-1).*DATA_gen_bocE(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_EB.im = sum(Channel(1).pkg_par.bag.im(1:DATA_bag-1).*DATA_gen_bocE(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_PB.re = sum(Channel(1).pkg_par.bag.re(1:DATA_bag-1).*DATA_gen_bocP(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_PB.im = sum(Channel(1).pkg_par.bag.im(1:DATA_bag-1).*DATA_gen_bocP(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_LB.re = sum(Channel(1).pkg_par.bag.re(1:DATA_bag-1).*DATA_gen_bocL(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_LB.im = sum(Channel(1).pkg_par.bag.im(1:DATA_bag-1).*DATA_gen_bocL(1:DATA_bag-1));

            Channel(1).pkg_par.pkg_EBP.re = sum(Channel(1).pkg_par.bag.re(1:DATA_bag-1).*DATA_gen_prnE(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_EBP.im = sum(Channel(1).pkg_par.bag.im(1:DATA_bag-1).*DATA_gen_prnE(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_PBP.re = sum(Channel(1).pkg_par.bag.re(1:DATA_bag-1).*DATA_gen_prnP(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_PBP.im = sum(Channel(1).pkg_par.bag.im(1:DATA_bag-1).*DATA_gen_prnP(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_LBP.re = sum(Channel(1).pkg_par.bag.re(1:DATA_bag-1).*DATA_gen_prnL(1:DATA_bag-1));
            Channel(1).pkg_par.pkg_LBP.im = sum(Channel(1).pkg_par.bag.im(1:DATA_bag-1).*DATA_gen_prnL(1:DATA_bag-1));


            Channel(1).trk.tmr = Channel(1).trk.tmr + 1;
            tmr_test = Channel(1).trk.tmr
            Channel(1).syn.pkg_PB.I(Channel(1).trk.tmr) = Channel(1).pkg_par.pkg_PB.re;
            Channel(1).syn.pkg_PB.Q(Channel(1).trk.tmr) = Channel(1).pkg_par.pkg_PB.im;
            %% 码环
            % 码环鉴相 ==================================================
            DATA_D_EMIP = ((Channel(1).pkg_par.pkg_EB.re^2+Channel(1).pkg_par.pkg_EB.im^2) - (Channel(1).pkg_par.pkg_LB.re^2+Channel(1).pkg_par.pkg_LB.im^2) - ...
                     ((Channel(1).pkg_par.pkg_EBP.re^2+Channel(1).pkg_par.pkg_EBP.im^2) - (Channel(1).pkg_par.pkg_LBP.re^2+Channel(1).pkg_par.pkg_LBP.im^2)));
    %         N_nor = (Channel(1).pkg_par.pkg_EB.re + Channel(1).pkg_par.pkg_LB.re)^2 + (Channel(1).pkg_par.pkg_EB.im + Channel(1).pkg_par.pkg_LB.im)^2;
    %         dll_out(Channel(1).trk.tmr) = D_EMIP/N_nor*(2-3*0.5)^2/(6-8*0.5); 

            DATA_N_nor = (Channel(1).pkg_par.pkg_PB.re^2 + Channel(1).pkg_par.pkg_PB.im^2);
            DATA_dll_out(Channel(1).trk.tmr) = DATA_D_EMIP/(4*(3*(1-3*0.25)+0.25)*DATA_N_nor); 

            %  改进的鉴相函数
    %                 D_E_Linear = (Channel(1).pkg_par.pkg_EB.re^2 + Channel(1).pkg_par.pkg_EB.im^2) - (Channel(1).pkg_par.pkg_EBP.re^2 + Channel(1).pkg_par.pkg_EBP.im^2);
    %                 D_L_Linear = (Channel(1).pkg_par.pkg_LB.re^2 + Channel(1).pkg_par.pkg_LB.im^2) - (Channel(1).pkg_par.pkg_LBP.re^2 + Channel(1).pkg_par.pkg_LBP.im^2);
    %                 r = D_E_Linear/D_L_Linear;
    %                 dll_out(Channel(1).trk.tmr) = (r - 1)*(2 - 4.5*0.5)/9/(r + 1);


    %                 Channel(1).pkg_par.pkg_E = Channel(1).pkg_par.pkg_EB.re^2 + Channel(1).pkg_par.pkg_EB.im^2;
    %                 Channel(1).pkg_par.pkg_L = Channel(1).pkg_par.pkg_LB.re^2 + Channel(1).pkg_par.pkg_LB.im^2;
    %                 dll_out(Channel(1).trk.tmr) = 1/8*(Channel(1).pkg_par.pkg_E - Channel(1).pkg_par.pkg_L)/(Channel(1).pkg_par.pkg_E + Channel(1).pkg_par.pkg_L);

            % 码环滤波 ===================================================
            DATA_reg = DATA_dll_out(Channel(1).trk.tmr)*Channel(1).trk.prn_loop.dll_a*0.001 + Channel(1).trk.prn_loop.reg;
            DATA_prn_filter_out(Channel(1).trk.tmr) = (DATA_reg+Channel(1).trk.prn_loop.reg)*0.5 + DATA_dll_out(Channel(1).trk.tmr)*Channel(1).trk.prn_loop.dll_b;

            Channel(1).reg(Channel(1).trk.tmr) = DATA_reg;
            Channel(1).trk.prn_loop.reg = DATA_reg;
            % 码环反馈 ===================================================
            Channel(1).prn_par.fo = Channel(1).f_prn + DATA_prn_filter_out(Channel(1).trk.tmr);
            Channel(1).prn_par.fcw = Channel(1).prn_par.fo*ACCPHS/Channel(1).fs;
            Channel(1).sub_par.fo = Channel(1).f_sub + DATA_prn_filter_out(Channel(1).trk.tmr);
            Channel(1).sub_par.fcw = Channel(1).sub_par.fo*ACCPHS/Channel(1).fs;

            %% 载波环
            % 载波环鉴相 =================================================
            if Channel(1).trk.tmr < 100
                if Channel(1).trk.tmr == 1
                    DATA_pkg_I0 = Channel(1).pkg_par.pkg_PB.re;
                    DATA_pkg_I1 = Channel(1).pkg_par.pkg_PB.re;
                    DATA_pkg_Q0 = Channel(1).pkg_par.pkg_PB.im;
                    DATA_pkg_Q1 = Channel(1).pkg_par.pkg_PB.im;
                    DATA_fll_out(Channel(1).trk.tmr) = 0;
                    DATA_pll_out(Channel(1).trk.tmr) = 0;
                else
                    DATA_pkg_I0 = DATA_pkg_I1;
                    DATA_pkg_I1 = Channel(1).pkg_par.pkg_PB.re;
                    DATA_pkg_Q0 = DATA_pkg_Q1;
                    DATA_pkg_Q1 = Channel(1).pkg_par.pkg_PB.im;
                    DATA_P_dot  = DATA_pkg_I0*DATA_pkg_I1 + DATA_pkg_Q0*DATA_pkg_Q1;
                    DATA_P_cor  = DATA_pkg_I0*DATA_pkg_Q1 - DATA_pkg_Q0*DATA_pkg_I1;
                    DATA_fll_out(Channel(1).trk.tmr) = atan2(DATA_P_cor,DATA_P_dot)/(2*pi);
                    DATA_pll_out(Channel(1).trk.tmr) = 0;
                end
            else
                DATA_fll_out(Channel(1).trk.tmr) = 0;
                DATA_pll_out(Channel(1).trk.tmr) = atan(Channel(1).pkg_par.pkg_PB.im/Channel(1).pkg_par.pkg_PB.re)/(2*pi);                    
            end

            % 载波环滤波 =================================================
            DATA_reg0 = (DATA_pll_out(Channel(1).trk.tmr)*Channel(1).trk.car_loop.pll_a + DATA_fll_out(Channel(1).trk.tmr)/0.001*Channel(1).trk.car_loop.fll_a)*0.001 + Channel(1).trk.car_loop.reg0;
            DATA_reg1 = (0.5*(DATA_reg0+Channel(1).trk.car_loop.reg0) + DATA_pll_out(Channel(1).trk.tmr)*Channel(1).trk.car_loop.pll_b + ...
                                        DATA_fll_out(Channel(1).trk.tmr)/0.001*Channel(1).trk.car_loop.fll_b)*0.001 + Channel(1).trk.car_loop.reg1;
            DATA_car_filter_out(Channel(1).trk.tmr) = (0.5*(DATA_reg1+Channel(1).trk.car_loop.reg1) + DATA_pll_out(Channel(1).trk.tmr)*Channel(1).trk.car_loop.pll_c);    


            DATA_dop = [DATA_dll_out(Channel(1).trk.tmr) DATA_prn_filter_out(Channel(1).trk.tmr) DATA_fll_out(Channel(1).trk.tmr) DATA_pll_out(Channel(1).trk.tmr) DATA_car_filter_out(Channel(1).trk.tmr) DATA_reg0 DATA_reg1]

            Channel(1).reg0(Channel(1).trk.tmr) = DATA_reg0;
            Channel(1).reg1(Channel(1).trk.tmr) = DATA_reg1;

            Channel(1).trk.car_loop.reg0 = DATA_reg0;
            Channel(1).trk.car_loop.reg1 = DATA_reg1;

            % 载波环反馈 =================================================
            Channel(1).car_par.fo = Channel(1).f_car  - DATA_car_filter_out(Channel(1).trk.tmr);
            Channel(1).car_par.fcw = Channel(1).car_par.fo*ACCPHS/Channel(1).fs;

    %         if Channel(1).trk.suc == 0
    %             Channel(1).trk.mag.re(Channel(1).trk.pid) = Channel(1).pkg_par.pkg_PB.re;
    %             Channel(1).trk.mag.im(Channel(1).trk.pid) = Channel(1).pkg_par.pkg_PB.im;
    %             Channel(1).trk.pid = Channel(1).trk.pid + 1;
    %             if Channel(1).trk.pid > 20
    %                 Channel(1).trk.pid = 1;
    %                 magI = sum(Channel(1).trk.mag.re.^2);
    %                 magQ = sum(Channel(1).trk.mag.im.^2);
    %                 if magI > 10*magQ
    %                     Channel(1).trk.suc = 1;
    %                 end
    %             end
    %         elseif Channel(1).syn.suc == 0
    %             [Channel(1)] = bitSyn(Channel(1));
    %         end

            if(Channel(1).trk.tmr > GAME_OVER)
                save('E:/Matlab/data/bin文件/BD_DATA_75dB_50s_0_8_NQ.mat')

                GAME_OVER = GAME_OVER + 500;
               % test_dll = mean(reshape(dll_out(1:19000),500,length(dll_out(1:19000))/500));
                bag = 1:Channel(1).trk.tmr;
                % car_loop output
                figure(2)
                subplot(5,1,1)
                plot(bag,DATA_fll_out);title('fll disc输出');
                subplot(5,1,2)
                plot(bag,DATA_pll_out);title('pll disc输出');
                subplot(5,1,3)
                plot(bag,Channel(1).reg0);title('reg0');
                subplot(5,1,4)
                plot(bag,Channel(1).reg1);title('reg1');
                subplot(5,1,5)
                plot(bag,DATA_car_filter_out);title('car loop输出');
                % code_loop output
                figure(3)
                subplot(3,1,1)
                plot(bag,DATA_dll_out);title('dll disc输出');
                subplot(3,1,2)
                plot(bag,Channel(1).reg);title('reg');
                subplot(3,1,3)
                plot(bag,DATA_prn_filter_out);title('code loop输出');        
                % output
                figure(4)
                subplot(4,1,1)
                plot(bag,DATA_prn_filter_out*4);title('code loop输出');
                subplot(4,1,2)
                plot(bag,DATA_car_filter_out);title('car loop输出');
                subplot(4,1,3)
                plot(bag,Channel(1).syn.pkg_PB.I);title('I路输出');
                subplot(4,1,4)
                plot(bag,Channel(1).syn.pkg_PB.Q);title('Q路输出');
                break;

            end
        end
    end
    if Channel(2).acq.rec == 0
        if Channel(2).pkg_par.N_FFT > 0 
            Channel(2).pkg_par.bag.re(Channel(2).pkg_par.pid) = Channel(2).pkg_par.bag.re(Channel(2).pkg_par.pid) + data_src*cos(2*pi*Channel(2).car_par.phs/2^32);
            Channel(2).pkg_par.bag.im(Channel(2).pkg_par.pid) = Channel(2).pkg_par.bag.im(Channel(2).pkg_par.pid) + data_src*sin(2*pi*Channel(2).car_par.phs/2^32);
            Channel(2).pkg_par.phs = Channel(2).pkg_par.phs + Channel(2).pkg_par.fcw;
            Channel(2).car_par.phs = Channel(2).car_par.phs + Channel(2).car_par.fcw;
        else
            Channel(2).pkg_par.phs = Channel(2).pkg_par.phs + 2^32;
        end

        if Channel(2).car_par.phs >= 2^32
            Channel(2).car_par.phs = Channel(2).car_par.phs - 2^32;
        end
        if Channel(2).pkg_par.phs >= 2^32
            Channel(2).pkg_par.phs = Channel(2).pkg_par.phs - 2^32;
            Channel(2).pkg_par.pid = Channel(2).pkg_par.pid + 1;
            if Channel(2).pkg_par.pid > Channel(2).pkg_par.N_FFT
                Channel(2).pkg_par.pid = 1;
            
            % 捕获================================================================
                if Channel(2).acq.flg == 1                                 
                    Channel(2).acq.rec = 1;
                    Channel(2).pkg_par.fo = 12*1.023e6;
                    Channel(2).pkg_par.fcw = Channel(2).pkg_par.fo*2^32/Channel(2).fs;
                    Channel(2).pkg_par.N_FFT = Channel(2).pkg_par.fo * 0.001;
                else      
                    Channel(2).acq.fft_src = fft(Channel(2).pkg_par.bag.re+1i*Channel(2).pkg_par.bag.im,Channel(2).pkg_par.N_FFT);                                  
                    PILOT_fft_boc_src = Channel(2).acq.fft_src.*Channel(2).pkg_par.fft_boc;
                    PILOT_fft_prn_src = Channel(2).acq.fft_src.*Channel(2).pkg_par.fft_prn;
                    PILOT_Rb  = ifft(PILOT_fft_boc_src,Channel(2).pkg_par.N_FFT);
                    PILOT_Rbp = ifft(PILOT_fft_prn_src,Channel(2).pkg_par.N_FFT);

                    PILOT_R_ASPeCT = abs(PILOT_Rb.^2 - 0.9*PILOT_Rbp.^2);

                
                    
                    
                    % 找出峰值及码相位====================
                    Channel(2).acq.pk = max(PILOT_R_ASPeCT);%峰值
                    Channel(2).acq.av = sum(PILOT_R_ASPeCT,2)/Channel(2).pkg_par.N_FFT;%均值
                    Channel(2).acq.phs = find(PILOT_R_ASPeCT==max(PILOT_R_ASPeCT));%码相位
                    PILOT_pk = Channel(2).acq.pk;
                    PILOT_av = Channel(2).acq.av;
                    PILOT_phs0 = Channel(2).acq.phs;
                    PILOT_phs = (Channel(2).pkg_par.N_FFT-Channel(2).acq.phs)/4+1;%*Channel(2).prn_par.fo/Channel(2).pkg_par.fo;

                    if Channel(2).acq.pk > Channel(2).acq.av*20
                        Channel(2).acq.flg = 1;%捕获成功
                        Channel(2).acq.phs = find(PILOT_R_ASPeCT==max(PILOT_R_ASPeCT));
                        
                         % 相关函数===========================
                        bag = 1:Channel(2).pkg_par.N_FFT;
                        subplot(3,1,1);
                        plot(bag,PILOT_Rb);
                        subplot(3,1,2);
                        plot(bag,PILOT_Rbp);
                        subplot(3,1,3)
                        plot(bag,PILOT_R_ASPeCT)
                        Channel(2).pkg_par.N_FFT = mod(Channel(2).acq.phs - 1,Channel(2).pkg_par.N_FFT/2);
                    end

                end
                Channel(2).pkg_par.bag.re = 0*ones(1,Channel(2).pkg_par.N_FFT);
                Channel(2).pkg_par.bag.im = 0*ones(1,Channel(2).pkg_par.N_FFT);
            end
        end
                % 跟踪==============================================================
    else
        %for bag = 1:Channel(2).fs*0.001
        if Channel(2).trk.rdy == 1
            Channel(2).trk.rdy = 0;
            PILOT_bag = 1;
            Channel(2).pkg_par.bag.re = 0*ones(1,2*Channel(2).fs*0.001);
            Channel(2).pkg_par.bag.im = 0*ones(1,2*Channel(2).fs*0.001);
            PILOT_gen_prnE = 0*ones(1,2*Channel(2).fs*0.001);
            PILOT_gen_bocE = 0*ones(1,2*Channel(2).fs*0.001);
            PILOT_gen_prnP = 0*ones(1,2*Channel(2).fs*0.001);
            PILOT_gen_bocP = 0*ones(1,2*Channel(2).fs*0.001);
            PILOT_gen_prnL = 0*ones(1,2*Channel(2).fs*0.001);
            PILOT_gen_bocL = 0*ones(1,2*Channel(2).fs*0.001);
        end
        

        Channel(2).pkg_par.bag.re(PILOT_bag) = data_src*cos(2*pi*Channel(2).car_par.phs/2^32);
        Channel(2).pkg_par.bag.im(PILOT_bag) = data_src*sin(2*pi*Channel(2).car_par.phs/2^32);
        Channel(2).car_par.phs = Channel(2).car_par.phs + Channel(2).car_par.fcw;

        if Channel(2).car_par.phs >= 2^32
            Channel(2).car_par.phs = Channel(2).car_par.phs - 2^32;
        end     

        PILOT_gen_prnE(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidE);

        PILOT_gen_prnP(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidP);

        PILOT_gen_prnL(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidL);


        if mod(Channel(2).trk.cidE,33) == 1 || mod(Channel(2).trk.cidE,33) == 5 || mod(Channel(2).trk.cidE,33) == 7 || mod(Channel(2).trk.cidE,33) == 30
            PILOT_gen_bocE(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidE)*sgn(sin(2*pi*Channel(2).trk.subE/2^32));
        else
            PILOT_gen_bocE(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidE)*sgn(sin(2*pi*Channel(2).trk.phsE/2^32));
        end

        if mod(Channel(2).trk.cidP,33) == 1 || mod(Channel(2).trk.cidP,33) == 5 || mod(Channel(2).trk.cidP,33) == 7 || mod(Channel(2).trk.cidP,33) == 30
            PILOT_gen_bocP(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidP)*sgn(sin(2*pi*Channel(2).trk.subP/2^32));
        else
            PILOT_gen_bocP(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidP)*sgn(sin(2*pi*Channel(2).trk.phsP/2^32));
        end

        if mod(Channel(2).trk.cidL,33) == 1 || mod(Channel(2).trk.cidL,33) == 5 || mod(Channel(2).trk.cidL,33) == 7 || mod(Channel(2).trk.cidL,33) == 30
            PILOT_gen_bocL(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidL)*sgn(sin(2*pi*Channel(2).trk.subL/2^32));
        else
            PILOT_gen_bocL(PILOT_bag) = Channel(2).trk.code(Channel(2).trk.cidL)*sgn(sin(2*pi*Channel(2).trk.phsL/2^32));
        end

        PILOT_bag = PILOT_bag + 1;
        Channel(2).trk.phsE = Channel(2).trk.phsE + Channel(2).prn_par.fcw;
        Channel(2).trk.phsP = Channel(2).trk.phsP + Channel(2).prn_par.fcw;
        Channel(2).trk.phsL = Channel(2).trk.phsL + Channel(2).prn_par.fcw;
        Channel(2).trk.subE = Channel(2).trk.subE + Channel(2).sub_6.fcw;
        Channel(2).trk.subP = Channel(2).trk.subP + Channel(2).sub_6.fcw;
        Channel(2).trk.subL = Channel(2).trk.subL + Channel(2).sub_6.fcw;

        if Channel(2).trk.subE >= 2^32
            Channel(2).trk.subE = Channel(2).trk.subE - 2^32;
        end
        if Channel(2).trk.subP >= 2^32
            Channel(2).trk.subP = Channel(2).trk.subP - 2^32;
        end
        if Channel(2).trk.subL >= 2^32
            Channel(2).trk.subL = Channel(2).trk.subL - 2^32;
        end

        if Channel(2).trk.phsE >= 2^32
            Channel(2).trk.phsE = Channel(2).trk.phsE - 2^32;
            Channel(2).trk.cidE = Channel(2).trk.cidE + 1;
            if Channel(2).trk.cidE > 1023
                Channel(2).trk.cidE = Channel(2).trk.cidE - 1023;
            end
        end
        if Channel(2).trk.phsP >= 2^32
            Channel(2).trk.phsP = Channel(2).trk.phsP - 2^32;
            Channel(2).trk.cidP = Channel(2).trk.cidP + 1;
            if Channel(2).trk.cidP > 1023
                Channel(2).trk.cidP = Channel(2).trk.cidP - 1023;
                Channel(2).trk.rdy = 1;
            end
        end
        if Channel(2).trk.phsL >= 2^32
            Channel(2).trk.phsL = Channel(2).trk.phsL - 2^32;
            Channel(2).trk.cidL = Channel(2).trk.cidL + 1;
            if Channel(2).trk.cidL > 1023
                Channel(2).trk.cidL = Channel(2).trk.cidL - 1023;
            end
        end
        
        if Channel(2).trk.rdy == 1
            Channel(2).pkg_par.pkg_EB.re = sum(Channel(2).pkg_par.bag.re.*PILOT_gen_bocE);
            Channel(2).pkg_par.pkg_EB.im = sum(Channel(2).pkg_par.bag.im.*PILOT_gen_bocE);
            Channel(2).pkg_par.pkg_PB.re = sum(Channel(2).pkg_par.bag.re.*PILOT_gen_bocP);
            Channel(2).pkg_par.pkg_PB.im = sum(Channel(2).pkg_par.bag.im.*PILOT_gen_bocP);
            Channel(2).pkg_par.pkg_LB.re = sum(Channel(2).pkg_par.bag.re.*PILOT_gen_bocL);
            Channel(2).pkg_par.pkg_LB.im = sum(Channel(2).pkg_par.bag.im.*PILOT_gen_bocL);

            Channel(2).pkg_par.pkg_EBP.re = sum(Channel(2).pkg_par.bag.re.*PILOT_gen_prnE);
            Channel(2).pkg_par.pkg_EBP.im = sum(Channel(2).pkg_par.bag.im.*PILOT_gen_prnE);
            Channel(2).pkg_par.pkg_PBP.re = sum(Channel(2).pkg_par.bag.re.*PILOT_gen_prnP);
            Channel(2).pkg_par.pkg_PBP.im = sum(Channel(2).pkg_par.bag.im.*PILOT_gen_prnP);
            Channel(2).pkg_par.pkg_LBP.re = sum(Channel(2).pkg_par.bag.re.*PILOT_gen_prnL);
            Channel(2).pkg_par.pkg_LBP.im = sum(Channel(2).pkg_par.bag.im.*PILOT_gen_prnL);



            Channel(2).trk.tmr = Channel(2).trk.tmr + 1;
            tmr_test = Channel(2).trk.tmr
            Channel(2).syn.pkg_PB.I(Channel(2).trk.tmr) = Channel(2).pkg_par.pkg_PB.re;
            Channel(2).syn.pkg_PB.Q(Channel(2).trk.tmr) = Channel(2).pkg_par.pkg_PB.im;
            %% 码环
            % 码环鉴相 ==================================================
            PILOT_D_EMIP = (Channel(2).pkg_par.pkg_EB.re^2+Channel(2).pkg_par.pkg_EB.im^2) - (Channel(2).pkg_par.pkg_LB.re^2+Channel(2).pkg_par.pkg_LB.im^2) - ...
                     0.9*((Channel(2).pkg_par.pkg_EBP.re^2+Channel(2).pkg_par.pkg_EBP.im^2) - (Channel(2).pkg_par.pkg_LBP.re^2+Channel(2).pkg_par.pkg_LBP.im^2));
             %N_nor = (Channel(2).pkg_par.pkg_EB.re + Channel(2).pkg_par.pkg_LB.re)^2 + (Channel(2).pkg_par.pkg_EB.im + Channel(2).pkg_par.pkg_LB.im)^2;
            % dll_out(Channel(2).trk.tmr) = D_EMIP/N_nor*(2-3*0.5)^2/(6-8*0.5); 
            PILOT_N_nor = (Channel(2).pkg_par.pkg_PB.re^2 + Channel(2).pkg_par.pkg_PB.im^2);
            PILOT_dll_out(Channel(2).trk.tmr) = PILOT_D_EMIP/(4*(3*(1-3*0.25)+0.9*0.25)*PILOT_N_nor); 

    %                 dll_out(Channel(2).trk.tmr) = D_EMIP/N_nor; 
            % 码环滤波 ===================================================
            PILOT_reg = PILOT_dll_out(Channel(2).trk.tmr)*Channel(2).trk.prn_loop.dll_a*0.001 + Channel(2).trk.prn_loop.reg;
            PILOT_prn_filter_out(Channel(2).trk.tmr) = (PILOT_reg+Channel(2).trk.prn_loop.reg)*0.5 + PILOT_dll_out(Channel(2).trk.tmr)*Channel(2).trk.prn_loop.dll_b;

            Channel(2).reg(Channel(2).trk.tmr) = PILOT_reg;
            Channel(2).trk.prn_loop.reg = PILOT_reg;
            % 码环反馈 ===================================================
            Channel(2).prn_par.fo = Channel(2).f_prn + PILOT_prn_filter_out(Channel(2).trk.tmr);
            Channel(2).prn_par.fcw = Channel(2).prn_par.fo*2^32/Channel(2).fs;
            Channel(2).sub_par.fo = Channel(2).f_sub + PILOT_prn_filter_out(Channel(2).trk.tmr);
            Channel(2).sub_par.fcw = Channel(2).sub_par.fo*2^32/Channel(2).fs;
            Channel(2).sub_6.fo = 6*Channel(2).f_sub + 6*PILOT_prn_filter_out(Channel(2).trk.tmr);
            Channel(2).sub_6.fcw = Channel(2).sub_6.fo*2^32/Channel(2).fs;
            %% 载波环
            % 载波环鉴相 =================================================
            if Channel(2).trk.tmr < 100
                if Channel(2).trk.tmr == 1
                    PILOT_pkg_I0 = Channel(2).pkg_par.pkg_PB.re;
                    PILOT_pkg_I1 = Channel(2).pkg_par.pkg_PB.re;
                    PILOT_pkg_Q0 = Channel(2).pkg_par.pkg_PB.im;
                    PILOT_pkg_Q1 = Channel(2).pkg_par.pkg_PB.im;
                    PILOT_fll_out(Channel(2).trk.tmr) = 0;
                    PILOT_pll_out(Channel(2).trk.tmr) = 0;
                else
                    PILOT_pkg_I0 = PILOT_pkg_I1;
                    PILOT_pkg_I1 = Channel(2).pkg_par.pkg_PB.re;
                    PILOT_pkg_Q0 = PILOT_pkg_Q1;
                    PILOT_pkg_Q1 = Channel(2).pkg_par.pkg_PB.im;
                    PILOT_P_dot  = PILOT_pkg_I0*PILOT_pkg_I1 + PILOT_pkg_Q0*PILOT_pkg_Q1;
                    PILOT_P_cor  = PILOT_pkg_I0*PILOT_pkg_Q1 - PILOT_pkg_Q0*PILOT_pkg_I1;
                    PILOT_fll_out(Channel(2).trk.tmr) = -atan2(PILOT_P_cor,PILOT_P_dot)/(2*pi);
                    PILOT_pll_out(Channel(2).trk.tmr) = 0;
                end
            else
                PILOT_fll_out(Channel(2).trk.tmr) = 0;
                PILOT_pll_out(Channel(2).trk.tmr) = atan(Channel(2).pkg_par.pkg_PB.im/Channel(2).pkg_par.pkg_PB.re)/(2*pi);                    
            end
    %          fll_out(Channel(2).trk.tmr) = 0;
    %          pll_out(Channel(2).trk.tmr) = atan(Channel(2).pkg_par.pkg_PB.im/Channel(2).pkg_par.pkg_PB.re)/(2*pi);   
            % 载波环滤波 =================================================
            PILOT_reg0 = (PILOT_pll_out(Channel(2).trk.tmr)*Channel(2).trk.car_loop.pll_a + PILOT_fll_out(Channel(2).trk.tmr)/0.001*Channel(2).trk.car_loop.fll_a)*0.001 + Channel(2).trk.car_loop.reg0;
            PILOT_reg1 = (0.5*(PILOT_reg0+Channel(2).trk.car_loop.reg0) + PILOT_pll_out(Channel(2).trk.tmr)*Channel(2).trk.car_loop.pll_b + ...
                                        PILOT_fll_out(Channel(2).trk.tmr)/0.001*Channel(2).trk.car_loop.fll_b)*0.001 + Channel(2).trk.car_loop.reg1;
            PILOT_car_filter_out(Channel(2).trk.tmr) = (0.5*(PILOT_reg1+Channel(2).trk.car_loop.reg1) + PILOT_pll_out(Channel(2).trk.tmr)*Channel(2).trk.car_loop.pll_c);     

            PILOT_dop = [PILOT_dll_out(Channel(2).trk.tmr) PILOT_prn_filter_out(Channel(2).trk.tmr) PILOT_fll_out(Channel(2).trk.tmr) PILOT_pll_out(Channel(2).trk.tmr) PILOT_car_filter_out(Channel(2).trk.tmr) PILOT_reg0 PILOT_reg1]               


            Channel(2).reg0(Channel(2).trk.tmr) = PILOT_reg0;
            Channel(2).reg1(Channel(2).trk.tmr) = PILOT_reg1;

            Channel(2).trk.car_loop.reg0 = PILOT_reg0;
            Channel(2).trk.car_loop.reg1 = PILOT_reg1;

            % 载波环反馈 =================================================
            Channel(2).car_par.fo = Channel(2).f_car - PILOT_car_filter_out(Channel(2).trk.tmr);
            Channel(2).car_par.fcw = Channel(2).car_par.fo*2^32/Channel(2).fs;



            if(Channel(2).trk.tmr > GAME_OVER)
                save('E:/Matlab/data/TMBOC文件/BD_PILOT_60dB_50s_0_8.mat')
                fclose(fidphs);
                GAME_OVER = GAME_OVER + 500;
                bag = 1:Channel(2).trk.tmr;
                % car_loop output
                figure(2)
                subplot(2,1,1)
                plot(bag,pll_out);title('pll disc输出');
                subplot(2,1,2)
                plot(bag,car_filter_out);title('car loop输出');
                % code_loop output
                figure(3)
                subplot(2,1,1)
                plot(bag,dll_out);title('dll disc输出');
                subplot(2,1,2)
                plot(bag,prn_filter_out);title('code loop输出');        
                % output
                figure(4)
                subplot(2,1,1)
                plot(bag,Channel(2).syn.pkg_PB.I);title('I路输出');
                subplot(2,1,2)
                plot(bag,Channel(2).syn.pkg_PB.Q);title('Q路输出');
            end
        end
    end   
end

function [Channel] = bitSyn(Channel)
Channel.syn.pkgI(Channel.syn.pid) =  Channel.pkg_par.pkg_PB.re;
Channel.syn.pid = Channel.syn.pid + 1;
if Channel.syn.pid > Channel.syn.PID || Channel.syn.wid > 1 && Channel.syn.flg == 0
    Channel.syn.pid = 1;
    Channel.syn.win(Channel.syn.wid) = Channel.syn.win(Channel.syn.wid) + abs(sum(Channel.syn.pkgI));
    Channel.syn.wid = Channel.syn.wid + 1;
    if Channel.syn.wid > 20
        Channel.syn.wid = 1;
        Channel.syn.non = Channel.syn.non + 1;
        if Channel.syn.non > Channel.syn.NON
            Channel.syn.non = 1;
            pk = max(Channel.syn.win);
            Channel.syn.phs = Channel.syn.wid;
        end
    end
end
if Channel.syn.flg == 1
    Channel.syn.pkgI(Channel.syn.pid) =  Channel.pkg_par.pkg_PB.re;
    Channel.syn.pid = Channel.syn.pid + 1;
    if Channel.syn.pid > Channel.syn.phs
        Channel.syn.suc = 1;
    end
end
    


  

function [fft_boc,fft_prn]=Data_fftgen(Channel)
Inst.code = Channel.trk.code;
Inst.boc = 0*ones(1,Channel.pkg_par.N_FFT);
Inst.prn = 0*ones(1,Channel.pkg_par.N_FFT);

Inst.pid = 1;
Inst.cid = 1;
Inst.rdy = 0;

while(Inst.rdy == 0)
    Inst.boc(Inst.pid) = Inst.boc(Inst.pid) + Inst.code(Inst.cid)*sgn(sin(2*pi*Channel.sub_par.phs/2^32));
    Inst.prn(Inst.pid) = Inst.prn(Inst.pid) + Inst.code(Inst.cid);
    
    Channel.pkg_par.phs = Channel.pkg_par.phs + Channel.pkg_par.fcw;
    if Channel.pkg_par.phs >= 2^32
        Channel.pkg_par.phs = Channel.pkg_par.phs - 2^32;
        Inst.pid = Inst.pid + 1;
        if(Inst.pid > Channel.pkg_par.N_FFT)
            Inst.rdy =1;
        end
    end
    
    Channel.prn_par.phs = Channel.prn_par.phs+Channel.prn_par.fcw;
    Channel.sub_par.phs = Channel.sub_par.phs+Channel.sub_par.fcw;
    if Channel.prn_par.phs >= 2^32
        Channel.prn_par.phs = Channel.prn_par.phs-2^32;
        Inst.cid = Inst.cid+1;
        if(Inst.cid >= 1024)
            Inst.cid = 1;
        end
    end

    if Channel.sub_par.phs >= 2^32
        Channel.sub_par.phs = Channel.sub_par.phs-2^32;
    end
    
end  
fft_boc = fft(Inst.boc,Channel.pkg_par.N_FFT);
fft_prn = fft(Inst.prn,Channel.pkg_par.N_FFT);

subplot(2,1,1)

plot(real(fft_prn))
xlabel('相位点');ylabel('FFT同向分量');

grid on;
set(gca,'xTick',0:512:4096);
subplot(2,1,2)
plot(imag(fft_prn))
xlabel('相位点');ylabel('FFT正交分量');
grid on;
set(gca,'xTick',0:512:4096);
fft_boc = conj(fft_boc);
fft_prn = conj(fft_prn);

function [fft_boc,fft_prn]=Pilot_fftgen(Channel)
Inst.code = Channel.trk.code;
Inst.boc = 0*ones(1,Channel.pkg_par.N_FFT);
Inst.prn = 0*ones(1,Channel.pkg_par.N_FFT);

Inst.sub_6.fo = Channel.sub_6.fo;
Inst.sub_6.fcw = Channel.sub_6.fcw;


Inst.pid = 1;
Inst.cid = 1;
Inst.rdy = 0;

while(Inst.rdy == 0)
     if mod(Inst.cid,33) == 1 || mod(Inst.cid,33) == 5 || mod(Inst.cid,33) == 7 || mod(Inst.cid,33) == 30
        Inst.boc(Inst.pid) = Inst.boc(Inst.pid) + Inst.code(Inst.cid)*sgn(sin(2*pi*Channel.sub_6.phs/2^32));
    else
        Inst.boc(Inst.pid) = Inst.boc(Inst.pid) + Inst.code(Inst.cid)*sgn(sin(2*pi*Channel.sub_par.phs/2^32));
    end
    
    Inst.prn(Inst.pid) = Inst.prn(Inst.pid) + Inst.code(Inst.cid);
    
    Channel.pkg_par.phs = Channel.pkg_par.phs + Channel.pkg_par.fcw;
    if Channel.pkg_par.phs >= 2^32
        Channel.pkg_par.phs = Channel.pkg_par.phs - 2^32;
        Inst.pid = Inst.pid + 1;
        if(Inst.pid > Channel.pkg_par.N_FFT/2)
            Inst.rdy =1;
        end
    end
    
    Channel.prn_par.phs = Channel.prn_par.phs+Channel.prn_par.fcw;
    Channel.sub_par.phs = Channel.sub_par.phs + Channel.sub_par.fcw;
    Channel.sub_6.phs = Channel.sub_6.phs + Channel.sub_6.fcw;
   
    if Channel.prn_par.phs >= 2^32
        Channel.prn_par.phs = Channel.prn_par.phs - 2^32;
        Inst.cid = Inst.cid+1;
        if(Inst.cid >= 1024)
            Inst.cid = 1;
        end
    end
    if Channel.sub_6.phs >= 2^32
        Channel.sub_6.phs = Channel.sub_6.phs - 2^32;
    end
    if Channel.sub_par.phs >= 2^32
        Channel.sub_par.phs = Channel.sub_par.phs - 2^32;
    end
    
end  
%Inst.boc = [Inst.boc 0*ones(1,Channel.pkg_par.N_FFT)];
%Inst.prn = [Inst.prn 0*ones(1,Channel.pkg_par.N_FFT)];
fft_boc = fft(Inst.boc,Channel.pkg_par.N_FFT);
fft_prn = fft(Inst.prn,Channel.pkg_par.N_FFT);
fft_boc = conj(fft_boc);
fft_prn = conj(fft_prn);


function [code] = codegen(sat_num)
CA_ph = [2,6; 3,7; 4,8; 5,9; 1,9; 2,10; 1,8; 2,9; 3,10; 2,3; 3,4; 5,6; 6,7; 7,8; 8,9; 9,10; 
          1,4; 2,5; 3,6; 4,7; 5,8; 6,9; 1,3; 4,6; 5,7; 6,8; 7,9; 8,10; 1,6; 2,7; 3,8; 4,9];
%G1
reg = -1*ones(1,10);
for i=1:1023
    g1(i) = reg(10);
    save1 = reg(3)*reg(10);
    reg(1,2:10) = reg(1,1:9);
    reg(1) = save1;
end

%G2
reg = -1*ones(1,10);
for i=1:1023
    g2(i) = reg(CA_ph(sat_num,1))*reg(CA_ph(sat_num,2));
    save2 = reg(2)*reg(3)*reg(6)*reg(8)*reg(9)*reg(10);
    reg(1,2:10) = reg(1,1:9);
    reg(1) = save2;
end
code = g1.*g2;

%% sgn函数
function [y] = sgn(x)
if(x >= 0)
    y =  1;
else
    y = -1;
end