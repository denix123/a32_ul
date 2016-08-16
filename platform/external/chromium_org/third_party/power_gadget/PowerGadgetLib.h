// Copyright (c) 2014, Intel Corporation
//     * Redistributions of source code must retain the above copyright
// copyright notice, this list of conditions and the following disclaimer
// this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT

#include <Windows.h>
#include <string>

typedef bool (*IPGInitialize) ();
typedef bool (*IPGGetNumNodes) (int *nNodes);
typedef bool (*IPGGetNumMsrs) (int *nMsr);
typedef bool (*IPGGetMsrName) (int iMsr, wchar_t *szName);
typedef bool (*IPGGetMsrFunc) (int iMsr, int *funcID);
typedef bool (*IPGGetIAFrequency) (int iNode, int *freqInMHz);
typedef bool (*IPGGetTDP) (int iNode, double *TDP);
typedef bool (*IPGGetMaxTemperature) (int iNode, int *degreeC);
typedef bool (*IPGGetTemperature) (int iNode, int *degreeC);
typedef bool (*IPGReadSample) ();
typedef bool (*IPGGetSysTime) (SYSTEMTIME *pSysTime);
typedef bool (*IPGGetRDTSC) (UINT64 *TSC);
typedef bool (*IPGGetTimeInterval) (double *offset);
typedef bool (*IPGGetBaseFrequency) (int iNode, double *baseFrequency);
typedef bool (*IPGGetPowerData) (int iNode, int iMSR, double *result, int *nResult);
typedef bool (*IPGStartLog) (wchar_t *szFileName);
typedef bool (*IPGStopLog) ();

class CIntelPowerGadgetLib
{
public:
	CIntelPowerGadgetLib(void);
	~CIntelPowerGadgetLib(void);
	
	bool IntelEnergyLibInitialize(void);
	bool GetNumNodes(int * nNodes);
	bool GetNumMsrs(int *nMsrs);
	bool GetMsrName(int iMsr, wchar_t *szName);
	bool GetMsrFunc(int iMsr, int *funcID);
	bool GetIAFrequency(int iNode, int *freqInMHz);
	bool GetTDP(int iNode, double *TDP);
	bool GetMaxTemperature(int iNode, int *degreeC);
	bool GetTemperature(int iNode, int *degreeC);
	bool ReadSample();
	bool GetSysTime(SYSTEMTIME *sysTime);
	bool GetRDTSC(UINT64 *TSC);
	bool GetTimeInterval(double *offset);
	bool GetBaseFrequency(int iNode, double *baseFrequency);
	bool GetPowerData(int iNode, int iMSR, double *results, int *nResult);
	bool StartLog(wchar_t *szFilename);
	bool StopLog();
	std::string GetLastError();

private:
	IPGInitialize pInitialize;
	IPGGetNumNodes pGetNumNodes;
	IPGGetNumMsrs pGetNumMsrs;
	IPGGetMsrName pGetMsrName;
	IPGGetMsrFunc pGetMsrFunc;
	IPGGetIAFrequency pGetIAFrequency;
	IPGGetTDP pGetTDP;
	IPGGetMaxTemperature pGetMaxTemperature;
	IPGGetTemperature pGetTemperature;
	IPGReadSample pReadSample; 
	IPGGetSysTime pGetSysTime;
	IPGGetRDTSC pGetRDTSC;
	IPGGetTimeInterval pGetTimeInterval;
	IPGGetBaseFrequency pGetBaseFrequency;
	IPGGetPowerData pGetPowerData;
	IPGStartLog pStartLog;
	IPGStopLog pStopLog;
};

