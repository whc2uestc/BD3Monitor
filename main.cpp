/*
 * main.cpp
 * Date   : 11-14-2014
 * Author : HouBiao,WangHanCheng
*/
/*
 * 调试运行该程序，需要注意以下三个问题：
 * 1、为B2B3通道指定正确的扩频码路径
 * 2、设置相位输出时间基准标志outflag，即以某一路信号为基准
 * 3、如果要分别调试B1或者B2B3,最好把另外的通道注释掉
*/
#include<stdio.h>


#include "./pub/inc/cfg.h"
#include "./pub/inc/ioc.h"

#include "./b1/inc/type.h"
#include "./b1/inc/init.h"
#include "./b1/inc/acq.h"
#include "./b1/inc/trk.h"

#include "./b2/inc/type.h"
#include "./b2/inc/init.h"
#include "./b2/inc/acq.h"
#include "./b2/inc/trk.h"


B1ChnlPrms chnlInst0[2];		// B1频点
B2ChnlPrms chnlInst1[4];		// B2、B3频点
int outflag;					// 由于统计正交性，一致性等问题，需要在同一时刻采样不同通道的数据，因此，设置这样一个全局变量，为时间基准
int main(){
	int i;
	int num;
	char dat_src;
	// 初始化B1频点两个通道参数

	B1ChnlInit(chnlInst0);

	// 初始化B2B3频点四个通道参数

	B2ChnlInit(chnlInst1);

	// 打开各观测量输出文件

	openFile();

	// 读取一个样本
	//for (i=0;i<1000;i++)
	num = fread(&dat_src,sizeof(char),1,pFile);

	// 读取样本成功

	while(num != 0){
		
    // B1频点两个通道信号源相位累加

		for (i=0;i<2;i++)
		{
			(chnlInst0[i]).TCAR.phs += (chnlInst0[i]).TCAR.fcw;
			if ((chnlInst0[i]).TCAR.phs >= NCOTOTAL)
				(chnlInst0[i]).TCAR.phs -= NCOTOTAL;
			(chnlInst0[i]).TPRN.phs += (chnlInst0[i]).TPRN.fcw;
			if ((chnlInst0[i]).TPRN.phs >= NCOTOTAL)
			{
				(chnlInst0[i]).TPRN.phs -= NCOTOTAL;
				(chnlInst0[i]).prnIndex += 1;
				if ((chnlInst0[i]).prnIndex == 1023)
				{
					(chnlInst0[i]).prnIndex = 0;

				}
			}
		}

	// B2B3频点四个通道信号源相位累加

		for (i=2;i<4;i++)
		{
			(chnlInst1[i]).TCAR.phs += (chnlInst1[i]).TCAR.fcw;
			if ((chnlInst1[i]).TCAR.phs >= NCOTOTAL)
				(chnlInst1[i]).TCAR.phs -= NCOTOTAL;
			(chnlInst1[i]).TPRN.phs += (chnlInst1[i]).TPRN.fcw;
			if ((chnlInst1[i]).TPRN.phs >= NCOTOTAL)
			{
				(chnlInst1[i]).TPRN.phs -= NCOTOTAL;
				(chnlInst1[i]).prnIndex += 1;
				if ((chnlInst1[i]).prnIndex == 10230)
				{
					(chnlInst1[i]).prnIndex = 0;
					if ( i==2)
					outflag =1;
				}
			}
		}

    // B1频点两个通道处理读取样本


		for(i=0; i<2; i++ )
		{
			switch(chnlInst0[i].chnlPros)
			{
				case ACQ_FLG: B1AcqASPT(chnlInst0+i,dat_src);break;
				case TRK_FLG: B1TrkASPT(chnlInst0+i,dat_src);break;
				default:break;
			}
		}

    // B2B3频点四个通道处理读取样本

		for(i=2; i<4; i++ )
		{
			switch(chnlInst1[i].chnlPros)
			{
				case ACQ_FLG: B2Acq(chnlInst1+i,dat_src);break;
				case TRK_FLG: B2Trk(chnlInst1+i,dat_src);break;
				default:break;
			}
		}

    // 各观测量输出标志清零

		outflag = 0;


	// 读取下一个样本

		num = fread(&dat_src,sizeof(char),1,pFile);


	}


    // 关闭各观测量输出文件

	closeFile();

	return 0;
}