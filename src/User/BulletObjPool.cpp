// obj pool for bullets

#include "BulletObjPool.h"
#include "Bullet.h"

BulletObjPool::~BulletObjPool()
{
	while (!allBullets.empty())
	{
		delete allBullets.front();
		allBullets.pop();
	}
}

Bullet* BulletObjPool::GetBullet()
{
	Bullet* bullet;
	if (recycledBullets.empty())
	{
		bullet = new Bullet();
		allBullets.push(bullet);
	}
	else
	{
		bullet = recycledBullets.top();
		recycledBullets.pop();

	}

	bullet->SubmitEntry();
	return bullet;
}

void BulletObjPool::ReturnBullet(Bullet* bullet)
{
	recycledBullets.push(bullet);
}