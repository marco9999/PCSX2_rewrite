#include "stdafx.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

IOPCoreException_t::IOPCoreException_t() :
	mExType(ExType::EX_RESET)
{
}

IOPCoreException_t::IOPCoreException_t(const ExType & type) : 
	mExType(type),
	mTLBExceptionInfo(),
	mIntExceptionInfo(),
	mCOPExceptionInfo()
{
}

IOPCoreException_t::IOPCoreException_t(const ExType & type, const TLBExceptionInfo_t * TLBExceptionInfo, const IntExceptionInfo_t * IntExceptionInfo, const COPExceptionInfo_t * COPExceptionInfo) :
	mExType(type)
{
	if (TLBExceptionInfo != nullptr)
		mTLBExceptionInfo = *TLBExceptionInfo;
	if (IntExceptionInfo != nullptr)
		mIntExceptionInfo = *IntExceptionInfo;
	if (COPExceptionInfo != nullptr)
		mCOPExceptionInfo = *COPExceptionInfo;
}