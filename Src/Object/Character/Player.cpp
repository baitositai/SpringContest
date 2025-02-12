#include "../../Utility/Utility.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Load()
{
}

void Player::Init()
{
	trans_.pos = Utility::VECTOR_ZERO;
}

void Player::Update()
{
}

void Player::Draw()
{
	DrawSphere3D(
	trans_.pos,
		30,
		20,
		0xff0000,
		0xff0000,
		true);
}
