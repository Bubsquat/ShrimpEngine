// attribute that allows a game object to be updatable 

#ifndef _Updatable
#define _Updatable

class Updatable
{
public:

	Updatable() = default;
	Updatable(const Updatable&) = delete;
	Updatable& operator =(const Updatable&) = delete;
	~Updatable() = default;

	virtual void Update();

private:
};



#endif _Updateable
