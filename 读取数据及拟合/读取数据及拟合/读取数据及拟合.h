// dlltest.h   ͷ�ļ���ʹ�ö�̬���ӿ�ʱ��Ҫ����ͷ�ļ�
#include "pch.h"
#include"LeastSquare.h"
#include"OBCal.h"

#pragma once
#ifdef __DLLEXPORT
#define __DLL_EXP _declspec(dllexport)    // �������� - ����dll�ļ�ʱʹ��
#else
#define __DLL_EXP _declspec(dllimport)    // ���뺯�� -ʹ��dll��ʹ��
#endif // __DLLEXPORT

// �ж��Ƿ���c++
#if defined(__cplusplus)||defined(c_plusplus)
extern "C"
{
#endif

	__DLL_EXP void run(SOriginalDatas inputOriginalDatas, SRadarCoordinate inputRadarCoordinate);
#if defined(__cplusplus)||defined(c_plusplus)
}
#endif