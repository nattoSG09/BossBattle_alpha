#include "Player.h"
#include "Engine/Model.h"

// ��ԃC���X�^���X
#include "Waiting.h"
#include "Engine/Input.h"

Player::Player(GameObject* _pParent)
	:GameObject(_pParent,"Player"),currentState_(nullptr),states_()
{
}

void Player::Initialize()
{
	// ���ׂĂ̏�ԃC���X�^���X��z��Ɋm��
	states_[S_WAIT] = new Waiting;

	// �ŏ��̏�Ԃ��u�ҋ@�v�ɕύX
	ChangeState(S_WAIT);
}

void Player::Update()
{
	// �e��Ԃ��Ƃ̍X�V
	currentState_->Update(this);
}

void Player::Draw()
{
}

void Player::Release()
{
}

bool Player::IsStateChange(STATE_HANDLE _hState)
{
	switch (_hState)
	{
	case S_WAIT:return true;
	case S_MOVE:return Input::IsKeyDown(DIK_W) || Input::IsKeyDown(DIK_A) || Input::IsKeyDown(DIK_S) || Input::IsKeyDown(DIK_D);

	}
	return false;
}

void Player::ChangeState(STATE_HANDLE _hState)
{
	currentState_ = states_[_hState];
	currentState_->Start(this);
}
