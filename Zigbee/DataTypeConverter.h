#pragma once

#include "afxcoll.h"
// CDataTypeConverter

class CDataTypeConverter : public CWnd
{
	DECLARE_DYNAMIC(CDataTypeConverter)

public:
	CDataTypeConverter();
	virtual ~CDataTypeConverter();

protected:
	DECLARE_MESSAGE_MAP()
public:
	unsigned int Hex2Dec(CString strHex);
	COleVariant HexM2OleVariant(CString strHexM);
	CString Dec2Hex(unsigned int intDec);
	int CString2Int(CString strDex);
	const char* CString2ConstCharPointer(CString str);
};


