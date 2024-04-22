// factory with recycling for creating bullets 

#ifndef _BulletFactory
#define _BulletFactory

class Bullet;
#include "BulletObjPool.h"
#include "AzulCore.h"

class BulletFactory
{
public:

	BulletFactory() = default;
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator = (const BulletFactory&) = delete;
	~BulletFactory() = default;

	void CreateBullet(Matrix _RotTrans);
	void RecycleBullet(Bullet* bullet);

private:

	BulletObjPool bulletPool;

};


#endif _BulletFactory
