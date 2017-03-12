#include "stdafx.h"

#include "Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"
#include "Resources/IOP/Timers/IOPTimers_t.h"

IOPTimersTimerRegister_COUNT_t::IOPTimersTimerRegister_COUNT_t(const char * mnemonic) :
	Register32_t(mnemonic, false, false),
	mIsOverflowed(false),
	mPrescale(1),
	mPrescaleCount(0)
{
}

bool IOPTimersTimerRegister_COUNT_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void IOPTimersTimerRegister_COUNT_t::reset()
{
	writeWord(RAW, 0);
}

void IOPTimersTimerRegister_COUNT_t::setPrescale(const int prescale)
{
	// Prescale can only be 1 (no prescale) or above.
	if (prescale > 0)
		mPrescale = prescale;
	else
		mPrescale = 1;

	mPrescaleCount = 0;
}

IOPTimersTimerRegister_HWORD_COUNT_t::IOPTimersTimerRegister_HWORD_COUNT_t(const char* mnemonic) :
	IOPTimersTimerRegister_COUNT_t(mnemonic)
{
}

void IOPTimersTimerRegister_HWORD_COUNT_t::increment(u16 value)
{
	u32 temp = readWord(RAW);

	// Update only if the prescale threshold has been reached.
	mPrescaleCount += value;
	if (mPrescaleCount >= mPrescale)
	{
		while (mPrescaleCount >= mPrescale)
		{
			temp += 1;
			mPrescaleCount -= mPrescale;
		}

		if (temp > Constants::VALUE_U16_MAX)
		{
			temp = temp % Constants::VALUE_U16_MAX;
			mIsOverflowed = true;
		}

		writeWord(RAW, temp);
	}
}

IOPTimersTimerRegister_WORD_COUNT_t::IOPTimersTimerRegister_WORD_COUNT_t(const char* mnemonic) : 
	IOPTimersTimerRegister_COUNT_t(mnemonic)
{
}

void IOPTimersTimerRegister_WORD_COUNT_t::increment(u16 value)
{
	u64 temp = static_cast<u64>(readWord(RAW));

	// Update only if the prescale threshold has been reached.
	mPrescaleCount += value;
	if (mPrescaleCount >= mPrescale)
	{
		while (mPrescaleCount >= mPrescale)
		{
			temp += 1;
			mPrescaleCount -= mPrescale;
		}

		if (temp > Constants::VALUE_U32_MAX)
		{
			temp = temp % Constants::VALUE_U32_MAX;
			mIsOverflowed = true;
		}

		writeWord(RAW, static_cast<u32>(temp));
	}
}

IOPTimersTimerRegister_MODE_t::IOPTimersTimerRegister_MODE_t(const char * mnemonic, const int timerIndex, const std::shared_ptr<IOPTimersTimerRegister_COUNT_t> & count) :
	BitfieldRegister32_t(mnemonic, false, false),
	mTimerIndex(timerIndex),
	mIsEnabled(false),
	mClockSource(ClockSource_t::IOPBusClock),
	mCount(count)
{
	registerField(Fields::SyncEnable, "SyncEnable", 0, 1, 0);
	registerField(Fields::SyncMode, "SyncMode", 1, 2, 0);
	registerField(Fields::ResetMode, "ResetMode", 3, 1, 0);
	registerField(Fields::IrqOnTarget, "IrqOnTarget", 4, 1, 0);
	registerField(Fields::IrqOnOF, "IrqOnOF", 5, 1, 0);
	registerField(Fields::IrqRepeat, "IrqRepeat", 6, 1, 0);
	registerField(Fields::IrqToggle, "IrqToggle", 7, 1, 0);
	registerField(Fields::ClockSrc, "ClockSrc", 8, 1, 0);
	registerField(Fields::Prescale0, "Prescale0", 9, 1, 0);
	registerField(Fields::IrqRequest, "IrqRequest", 10, 1, 0);
	registerField(Fields::ReachTarget, "ReachTarget", 11, 1, 0);
	registerField(Fields::ReachOF, "ReachOF", 12, 1, 0);
	registerField(Fields::Prescale1, "Prescale1", 13, 2, 0);
}

void IOPTimersTimerRegister_MODE_t::writeHword(const Context_t& context, size_t arrayIndex, u16 value)
{
	BitfieldRegister32_t::writeHword(context, arrayIndex, value);

	if (context != RAW)
	{
		mCount->reset();
		handleClockSourceUpdate();

		// Check through either of the interrupt bits for "enabled".
		mIsEnabled = (getFieldValue(Fields::IrqOnOF) || getFieldValue(Fields::IrqOnTarget));
	}
}

void IOPTimersTimerRegister_MODE_t::writeWord(const Context_t& context, u32 value)
{
	BitfieldRegister32_t::writeWord(context, value);

	if (context != RAW)
	{
		mCount->reset();
		handleClockSourceUpdate();

		// Check through either of the interrupt bits for "enabled".
		mIsEnabled = (getFieldValue(Fields::IrqOnOF) || getFieldValue(Fields::IrqOnTarget));
	}
}

bool IOPTimersTimerRegister_MODE_t::isEnabled() const
{
	return mIsEnabled;
}

ClockSource_t IOPTimersTimerRegister_MODE_t::getClockSource() const
{
	return mClockSource;
}

void IOPTimersTimerRegister_MODE_t::handleClockSourceUpdate()
{
	if (mTimerIndex > 5)
		throw std::runtime_error("Invalid IOP timer index to determine clock source!");
	
	// Sources are majorly different for each type of timer... no easy way of doing this... time for spaghetti code! 
	// Prescale is handled by the Count register, but we need to set its mode through here.
	if (mTimerIndex < 3)
	{
		// Check for Prescale8 (bit 9).
		if (getFieldValue(Fields::Prescale0) > 0)
		{
			throw std::runtime_error("handleClockSourceUpdate() not fully implemented.");
		}
		else
		{
			if (getFieldValue(Fields::ClockSrc) == 0)
			{
				mCount->setPrescale(1);
				mClockSource = ClockSource_t::IOPBusClock;
			}
			else
			{
				throw std::runtime_error("handleClockSourceUpdate() not fully implemented.");
			}
		}
	}
	else
	{
		// Check for Prescale8/16/256 (bits 13 and 14).
		if (getFieldValue(Fields::Prescale1) > 0)
		{
			throw std::runtime_error("handleClockSourceUpdate() not fully implemented.");
		}
		else
		{
			if (getFieldValue(Fields::ClockSrc) == 0)
			{
				mCount->setPrescale(1);
				mClockSource = ClockSource_t::IOPBusClock;
			}
			else
			{
				throw std::runtime_error("handleClockSourceUpdate() not fully implemented.");
			}
		}
	}
}