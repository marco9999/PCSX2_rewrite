#include "stdafx.h"

#include "FIFOQueue_t.h"

FIFOQueue_t::FIFOQueue_t(const size_t& maxSize) :
	mMnemonic(""),
	mMaxSize(maxSize)
{
}

FIFOQueue_t::FIFOQueue_t(const char* mnemonic, const size_t& maxSize) :
	mMnemonic(mnemonic),
	mMaxSize(maxSize)
{
}

FIFOQueue_t::~FIFOQueue_t()
{
}

u128 FIFOQueue_t::read()
{
	auto temp = mFIFOQueue.front();
	mFIFOQueue.pop();
	return temp;
}

void FIFOQueue_t::write(const u128 & data)
{
	if (getCurrentSize() >= mMaxSize)
		throw std::runtime_error("FIFO Queue overloaded. Please fix.");

	mFIFOQueue.push(data);
}

bool FIFOQueue_t::isEmpty() const
{
	return getCurrentSize() == 0;
}

bool FIFOQueue_t::isFull() const
{
	return !(getCurrentSize() < getMaxSize());
}

size_t FIFOQueue_t::getCurrentSize() const
{
	return mFIFOQueue.size();
}

size_t FIFOQueue_t::getMaxSize() const
{
	return mMaxSize;
}

const char* FIFOQueue_t::getMnemonic() const
{
	return mMnemonic.c_str();
}