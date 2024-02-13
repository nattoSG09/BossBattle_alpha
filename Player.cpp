#include "Player.h"
#include "Engine/Model.h"

// 状態インスタンス
#include "Waiting.h"
#include "Engine/Input.h"

Player::Player(GameObject* _pParent)
	:GameObject(_pParent,"Player"),currentState_(nullptr),states_()
{
}

void Player::Initialize()
{
	// すべての状態インスタンスを配列に確保
	states_[S_WAIT] = new Waiting;

	// 最初の状態を「待機」に変更
	ChangeState(S_WAIT);
}

void Player::Update()
{
	// 各状態ごとの更新
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
