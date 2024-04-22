// factory with recycling for creating bullets 

#include "BulletFactory.h"
#include "Bullet.h"

void BulletFactory::CreateBullet(Matrix _RotTrans)
{
	Bullet* newBullet = bulletPool.GetBullet();
	newBullet->SetFactory(this);
	newBullet->Initialize(_RotTrans);
}

void BulletFactory::RecycleBullet(Bullet* bullet)
{
	bulletPool.ReturnBullet(bullet);
}