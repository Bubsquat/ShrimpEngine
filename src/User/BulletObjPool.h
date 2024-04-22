// obj pool for bullets

#ifndef _BulletObjPool
#define _BulletObjPool

#include <stack>
#include <queue>

class Bullet;

class BulletObjPool
{
public:

	BulletObjPool() = default;
	BulletObjPool(const BulletObjPool&) = delete;
	BulletObjPool& operator =(const BulletObjPool&) = delete;
	~BulletObjPool();

	Bullet* GetBullet();
	void ReturnBullet(Bullet* b);

private:
	std::stack<Bullet*> recycledBullets;
	std::queue<Bullet*> allBullets;
};


#endif _BulletObjPool
