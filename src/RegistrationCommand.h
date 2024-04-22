// base class for commands that deal with scene registrationa and deregistration 

#ifndef _RegistrationCommand
#define _RegistrationCommand

class RegistrationCommand
{
public:

	RegistrationCommand() = default;
	RegistrationCommand(const RegistrationCommand&) = delete;
	RegistrationCommand& operator =(const RegistrationCommand&) = delete;
	~RegistrationCommand() = default;

	virtual void execute() = 0;

private:

};




#endif _RegistrationCommand

