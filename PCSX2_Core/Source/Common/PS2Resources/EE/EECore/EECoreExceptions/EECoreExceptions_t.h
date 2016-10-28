#pragma once

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/Types/EECoreException_t.h"

using ExType = EECoreException_t::ExType;
class PS2Resources_t;

/*
EE Core exception state functionality.
*/
class EECoreExceptions_t : public PS2ResourcesSubobject
{
public:
	explicit EECoreExceptions_t(const PS2Resources_t* const PS2Resources);

	/*
	TODO: Check thread safety (std::atomic?). Also, add in prioritisation through the setException() function.
	The EE Core exception functionality.
	Use setException() to indicate that an exception occurred. It will check that the appropriate COP0 bits are set before reflecting the exception.
	If the exception is masked, it is silently discarded.

	Within the EE Core, a call should be made to hasExceptionOccurred(), and if true, details can be retrieved by getException().
	A call to hasExceptionOccurred() will reset the exception state (ie: returns false on next call, if no other exception occurred during the calls).
	*/
	bool hasExceptionOccurred();
	const EECoreException_t & getException() const;
	void setException(const EECoreException_t & exception);

private:
	/*
	EE Core Exception state, see above.
	*/
	bool ExceptionOccurred;
	EECoreException_t Exception;
};