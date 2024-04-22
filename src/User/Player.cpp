// class that handles constructing and managing the player

#include "Player.h"
#include "TankControllerPlayer.h"
#include "Tank.h"
#include "LevelManager.h"

Player::Player(BulletFactory* pBf, float Xpos, float Zpos)
{
	bulletFactory = pBf;

	// create player 
	playerTank = new Tank(bulletFactory, Xpos, Zpos);
	playerController = new TankControllerPlayer(playerTank);

	LevelManager::UpdatePlayerLocation(Vect(Xpos, 40.0f, Zpos));

	// set to be controlled 
	playerController->setTankToControl(playerTank);

}

Player::~Player()
{
	delete playerTank;
	delete playerController;
}