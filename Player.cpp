#include "Player.h"
#include "Engine/ImGui/imgui.h"

#include "Engine/Model.h"
#include "Engine/Input.h"

#include "State.h"
#include "Standby.h"


Player::Player(GameObject* _pParent)
	:GameObject(_pParent,"Player")
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Models/Player/Walking.fbx");
	// Model::SetAnimFrame(hModel_, 0, 70, 1);


	// �l����ꂤ���Ԃ�ێ�
	InitAllStates();
	ChangeState("Standby");
}

void Player::Update()
{
	// ���݂̏�Ԃ̍X�V����
	if (currentState_ != nullptr)currentState_->Update();

	// �ǂ̏�Ԏ��ł��s������
	{
		
	}

	// debug
	ImGui::Text("Player Position = { x %f,y %f,z %f", transform_.position_.x, transform_.position_.y, transform_.position_.z);

	bool isAnim = false;
	{// �ړ����� // 

		// �uW�v�L�[�������ꂽ��...
		if (Input::IsKey(DIK_W)) {
			// ��ʁu���v�����ɐi��
			transform_.rotate_.y = 0;
			transform_.position_.z += 0.1f;
			isAnim = true;
		}
		// �uA�v�L�[�������ꂽ��...
		if (Input::IsKey(DIK_A)) {
			// ��ʁu���v�����ɐi��
			transform_.rotate_.y = -90;
			transform_.position_.x -= 0.1f;
			isAnim = true;
		}
		// �uS�v�L�[�������ꂽ��...
		if (Input::IsKey(DIK_S)) {
			// ��ʁu��O�v�����ɐi��
			transform_.rotate_.y = 180;
			transform_.position_.z -= 0.1f;
			isAnim = true;
		}
		// �uD�v�L�[�������ꂽ��...
		if (Input::IsKey(DIK_D)) {
			// ��ʁu�E�v�����ɐi��
			transform_.rotate_.y = 90;
			transform_.position_.x += 0.1f;
			isAnim = true;
		}

		static bool prevAnim = false;
		if (isAnim == true) {
			if(prevAnim == false)Model::SetAnimFrame(hModel_, 0, 60, 1);
			prevAnim = true;
		}
		else {
			Model::SetAnimFrame(hModel_, 0, 0, 0);
			prevAnim = false;
		}

	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::InitAllStates()
{
	states_["Standby"] = new Standby;

	for (auto state : states_) {
		state.second->Initialize();
	}
}

void Player::ChangeState(string _key)
{
	currentState_ = states_[_key];
	currentState_->Start();
}
