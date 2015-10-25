/*
 * ioc.cpp
 * Date   : 11-14-2014
 * Author : HouBiao,WangHanCheng
*/
#include <stdio.h>
#include <stdlib.h>
#include"../inc/ioc.h"
#include"../inc/type.h"

FILE *pFile;
FILE *FP[FILENUM];
void openFile(){

	pFile = fopen("D:/B3-10dB4-9.bin","rb");
	if (pFile ==NULL)
	{
		printf("无法打开数据源文件，请指定正确的文件路径！\n");
		exit(1);
	}
	FP[B1D_DLL_DIS_OUT] = fopen("./output/B1D_DLL_DIS_OUT.bin","wb");
	if (FP[B1D_DLL_DIS_OUT] ==NULL)
	{
		printf("无法打开输出文件，请指定正确的文件路径！\n");
		exit(1);
	}
	FP[B1D_DLL_LPF_OUT] = fopen("./output/B1D_DLL_LPF_OUT.bin","wb");
	FP[B1D_PLL_DIS_OUT] = fopen("./output/B1D_PLL_DIS_OUT.bin","wb");
	FP[B1D_PLL_LPF_OUT] = fopen("./output/B1D_PLL_LPF_OUT.bin","wb");
	FP[B1D_TRK_I_OUT]   = fopen("./output/B1D_TRK_I_OUT.bin","wb");
	FP[B1D_TRK_Q_OUT]   = fopen("./output/B1D_TRK_Q_OUT.bin","wb");

	FP[B1D_ACQ_OUT]         = fopen("./output/B1D_ACQ_OUT.bin","wb");
	FP[B1D_PRN_PHS_SRC_OUT] = fopen("./output/B1D_PRN_PHS_SRC_OUT.bin","wb");
	FP[B1D_PRN_PHS_LCL_OUT] = fopen("./output/B1D_PRN_PHS_LCL_OUT.bin","wb");
	FP[B1D_CAR_PHS_SRC_OUT] = fopen("./output/B1D_CAR_PHS_SRC_OUT.bin","wb");
	FP[B1D_CAR_PHS_LCL_OUT] = fopen("./output/B1D_CAR_PHS_LCL_OUT.bin","wb");
	
	FP[B1P_DLL_DIS_OUT] = fopen("./output/B1P_DLL_DIS_OUT.bin","wb");
	FP[B1P_DLL_LPF_OUT] = fopen("./output/B1P_DLL_LPF_OUT.bin","wb");
	FP[B1P_PLL_DIS_OUT] = fopen("./output/B1P_PLL_DIS_OUT.bin","wb");
	FP[B1P_PLL_LPF_OUT] = fopen("./output/B1P_PLL_LPF_OUT.bin","wb");
	FP[B1P_TRK_I_OUT]   = fopen("./output/B1P_TRK_I_OUT.bin","wb");
	FP[B1P_TRK_Q_OUT]   = fopen("./output/B1P_TRK_Q_OUT.bin","wb");

	FP[B1P_ACQ_OUT]         = fopen("./output/B1P_ACQ_OUT.bin","wb");
	FP[B1P_PRN_PHS_SRC_OUT] = fopen("./output/B1P_PRN_PHS_SRC_OUT.bin","wb");
	FP[B1P_PRN_PHS_LCL_OUT] = fopen("./output/B1P_PRN_PHS_LCL_OUT.bin","wb");
	FP[B1P_CAR_PHS_SRC_OUT] = fopen("./output/B1P_CAR_PHS_SRC_OUT.bin","wb");
	FP[B1P_CAR_PHS_LCL_OUT] = fopen("./output/B1P_CAR_PHS_LCL_OUT.bin","wb");

	FP[B2D_DLL_DIS_OUT] = fopen("./output/B2D_DLL_DIS_OUT.bin","wb");
	FP[B2D_DLL_LPF_OUT] = fopen("./output/B2D_DLL_LPF_OUT.bin","wb");
	FP[B2D_PLL_DIS_OUT] = fopen("./output/B2D_PLL_DIS_OUT.bin","wb");
	FP[B2D_PLL_LPF_OUT] = fopen("./output/B2D_PLL_LPF_OUT.bin","wb");
	FP[B2D_TRK_I_OUT]   = fopen("./output/B2D_TRK_I_OUT.bin","wb");
	FP[B2D_TRK_Q_OUT]   = fopen("./output/B2D_TRK_Q_OUT.bin","wb");

	FP[B2D_ACQ_OUT]         = fopen("./output/B2D_ACQ_OUT.bin","wb");
	FP[B2D_PRN_PHS_SRC_OUT] = fopen("./output/B2D_PRN_PHS_SRC_OUT.bin","wb");
	FP[B2D_PRN_PHS_LCL_OUT] = fopen("./output/B2D_PRN_PHS_LCL_OUT.bin","wb");
	FP[B2D_CAR_PHS_SRC_OUT] = fopen("./output/B2D_CAR_PHS_SRC_OUT.bin","wb");
	FP[B2D_CAR_PHS_LCL_OUT] = fopen("./output/B2D_CAR_PHS_LCL_OUT.bin","wb");
	
	FP[B2P_DLL_DIS_OUT] = fopen("./output/B2P_DLL_DIS_OUT.bin","wb");
	FP[B2P_DLL_LPF_OUT] = fopen("./output/B2P_DLL_LPF_OUT.bin","wb");
	FP[B2P_PLL_DIS_OUT] = fopen("./output/B2P_PLL_DIS_OUT.bin","wb");
	FP[B2P_PLL_LPF_OUT] = fopen("./output/B2P_PLL_LPF_OUT.bin","wb");
	FP[B2P_TRK_I_OUT]   = fopen("./output/B2P_TRK_I_OUT.bin","wb");
	FP[B2P_TRK_Q_OUT]   = fopen("./output/B2P_TRK_Q_OUT.bin","wb");

	FP[B2P_ACQ_OUT]         = fopen("./output/B2P_ACQ_OUT.bin","wb");
	FP[B2P_PRN_PHS_SRC_OUT] = fopen("./output/B2P_PRN_PHS_SRC_OUT.bin","wb");
	FP[B2P_PRN_PHS_LCL_OUT] = fopen("./output/B2P_PRN_PHS_LCL_OUT.bin","wb");
	FP[B2P_CAR_PHS_SRC_OUT] = fopen("./output/B2P_CAR_PHS_SRC_OUT.bin","wb");
	FP[B2P_CAR_PHS_LCL_OUT] = fopen("./output/B2P_CAR_PHS_LCL_OUT.bin","wb");


	FP[B3D_DLL_DIS_OUT] = fopen("./output/B3D_DLL_DIS_OUT.bin","wb");
	FP[B3D_DLL_LPF_OUT] = fopen("./output/B3D_DLL_LPF_OUT.bin","wb");
	FP[B3D_PLL_DIS_OUT] = fopen("./output/B3D_PLL_DIS_OUT.bin","wb");
	FP[B3D_PLL_LPF_OUT] = fopen("./output/B3D_PLL_LPF_OUT.bin","wb");
	FP[B3D_TRK_I_OUT]   = fopen("./output/B3D_TRK_I_OUT.bin","wb");
	FP[B3D_TRK_Q_OUT]   = fopen("./output/B3D_TRK_Q_OUT.bin","wb");

	FP[B3D_ACQ_OUT]         = fopen("./output/B3D_ACQ_OUT.bin","wb");
	FP[B3D_PRN_PHS_SRC_OUT] = fopen("./output/B3D_PRN_PHS_SRC_OUT.bin","wb");
	FP[B3D_PRN_PHS_LCL_OUT] = fopen("./output/B3D_PRN_PHS_LCL_OUT.bin","wb");
	FP[B3D_CAR_PHS_SRC_OUT] = fopen("./output/B3D_CAR_PHS_SRC_OUT.bin","wb");
	FP[B3D_CAR_PHS_LCL_OUT] = fopen("./output/B3D_CAR_PHS_LCL_OUT.bin","wb");
	
	FP[B3P_DLL_DIS_OUT] = fopen("./output/B3P_DLL_DIS_OUT.bin","wb");
	FP[B3P_DLL_LPF_OUT] = fopen("./output/B3P_DLL_LPF_OUT.bin","wb");
	FP[B3P_PLL_DIS_OUT] = fopen("./output/B3P_PLL_DIS_OUT.bin","wb");
	FP[B3P_PLL_LPF_OUT] = fopen("./output/B3P_PLL_LPF_OUT.bin","wb");
	FP[B3P_TRK_I_OUT]   = fopen("./output/B3P_TRK_I_OUT.bin","wb");
	FP[B3P_TRK_Q_OUT]   = fopen("./output/B3P_TRK_Q_OUT.bin","wb");

	FP[B3P_ACQ_OUT]         = fopen("./output/B3P_ACQ_OUT.bin","wb");
	FP[B3P_PRN_PHS_SRC_OUT] = fopen("./output/B3P_PRN_PHS_SRC_OUT.bin","wb");
	FP[B3P_PRN_PHS_LCL_OUT] = fopen("./output/B3P_PRN_PHS_LCL_OUT.bin","wb");
	FP[B3P_CAR_PHS_SRC_OUT] = fopen("./output/B3P_CAR_PHS_SRC_OUT.bin","wb");
	FP[B3P_CAR_PHS_LCL_OUT] = fopen("./output/B3P_CAR_PHS_LCL_OUT.bin","wb");


}
void writeToFile(FLOAT data_src,int i)
{
	fwrite(&data_src,sizeof(FLOAT),1,FP[i]);	
}




void closeFile()
{
	fclose(pFile);
	fflush(pFile);
	int i;
	for (i=0;i<FILENUM;i++)
		fclose(FP[i]);
}