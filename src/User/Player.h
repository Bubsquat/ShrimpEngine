// class that handles constructing and managing the player

#ifndef _Player
#define _Player

class BulletFactory;
class TankControllerPlayer;
class Tank;

class Player
{
public:

	Player() = delete;
	Player(BulletFactory* pBF, float Xpos, float Zpos); // pass in pointers to objects a player will need here 
	Player(const Player&) = delete;
	Player& operator =(const Player&) = delete;
	~Player();

private:

	BulletFactory* bulletFactory;
	TankControllerPlayer* playerController;
	Tank* playerTank;
};


#endif _Player

