// DataTypeConverter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Zigbee.h"
#include "DataTypeConverter.h"


// CDataTypeConverter

IMPLEMENT_DYNAMIC(CDataTypeConverter, CWnd)

CDataTypeConverter::CDataTypeConverter()
{

}

CDataTypeConverter::~CDataTypeConverter()
{
}


BEGIN_MESSAGE_MAP(CDataTypeConverter, CWnd)
END_MESSAGE_MAP()



// CDataTypeConverter ��Ϣ�������




unsigned int CDataTypeConverter::Hex2Dec(CString strHex)
{
	const char hexLowerCase[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	const char hexCapital[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	const short int dec[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	CString strH,strL;
	unsigned short int intH,intL,intDec;
	strH=strHex.Left(1);
	strL=strHex.Right(1);
	for(short int i=0;i<16;i++)
	{
		if( (strH==hexLowerCase[i]) || (strH==hexCapital[i]) )
			intH=dec[i];
		if( (strL==hexLowerCase[i]) || (strL==hexCapital[i]) )
			intL=dec[i];
	}
	intDec=intH*16+intL;
	return intDec;
}


COleVariant CDataTypeConverter::HexM2OleVariant(CString strHexM)
{
	BYTE bt[255];
	short int len=strHexM.GetLength();
	short int length=0;
	short int intDec;
	for(int n=0,i=0;n<len-1;n+=2,i++)
	{		
		intDec=Hex2Dec(strHexM.Mid(n,2));
		bt[i]=char(intDec);
		length=i+1;
	}
	CByteArray m_Array;
	m_Array.RemoveAll();
	m_Array.SetSize(length);
	for(int i=0;i<length;i++)
		m_Array.SetAt(i,bt[i]);
	return COleVariant(m_Array);
}


CString CDataTypeConverter::Dec2Hex(unsigned int intDec)
{
	CString strHex;
	char charHex[255];
	//sprintf(charHex,"%x",intDec);
	sprintf_s(charHex,"%X",intDec);
	strHex=charHex;
	if(strHex.GetLength()==1)
		strHex=_T("0")+strHex;
	return strHex;
}


int CDataTypeConverter::CString2Int(CString strDex)
{
	//CString ת��Ϊ int ���ͣ�atoi()��ansi�汾�ģ�_tstoi()�Ǽ���ansi�汾��unicode�汾��
	int intDec=_tstoi(strDex);
	return intDec;
}


const char* CDataTypeConverter::CString2ConstCharPointer(CString str)
{
	//CStringת����const char*��GetBuffer()
	return (const char*)(str.GetBuffer(str.GetLength()));	
}
