#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/ImGui/imgui.h"

const XMFLOAT3 c_modelSize = { 1.f,1.f,1.f };
const float sensitivity = 5.f;

Player::Player(GameObject* _parent)
	:GameObject(_parent,"Player")
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("DebugCollision/Point.fbx");
	transform_.position_.y += c_modelSize.y/2;

	//�J�����̏����ʒu�̐ݒ�
	{
		initCamPos = { transform_.position_.x + 1.f, transform_.position_.y + 1.f, transform_.position_.z - 3.f };
		Camera::SetPosition(initCamPos);
        
		//Camera::SetTarget(transform_.position_.x + 1.f, transform_.position_.y, transform_.position_.z + 3.f);
        Camera::SetTarget(transform_.position_);
	}
}

void Player::Update()
{
	//// �ړ��̐ݒ�
	//{
 //       // �uW�v�L�[�������ꂽ��...
 //       if (Input::IsKey(DIK_W)) {
 //           // ��ʁu���v�����ɐi��
 //           transform_.position_.z += 0.1f;
 //       }
 //       // �uA�v�L�[�������ꂽ��...
 //       if (Input::IsKey(DIK_A)) {
 //           // ��ʁu���v�����ɐi��
 //           transform_.position_.x -= 0.1f;
 //       }
 //       // �uS�v�L�[�������ꂽ��...
 //       if (Input::IsKey(DIK_S)) {
 //           // ��ʁu��O�v�����ɐi��
 //           transform_.position_.z -= 0.1f;
 //       }
 //       // �uD�v�L�[�������ꂽ��...
 //       if (Input::IsKey(DIK_D)) {
 //           // ��ʁu�E�v�����ɐi��
 //           transform_.position_.x += 0.1f;
 //       }
	//}

	// �J�����̐ݒ�
	{
		XMFLOAT3 cameraPosition = Camera::GetPosition();
		ImGui::Begin("Camera");
		ImGui::Text("start_cameraPos = (%f,%f,%f),", initCamPos.x, initCamPos.y, initCamPos.z);
		ImGui::Text("rotated_cameraPos = (%f,%f,%f),", cameraPosition.x, cameraPosition.y, cameraPosition.z);

		XMFLOAT3 mouseMove = Input::GetMouseMove();
		ImGui::Text("mouseMove = (%f,%f,%f),", mouseMove.x, mouseMove.y, mouseMove.z);


		if (mouseMove.x >= 0 || mouseMove.y >= 0) {
			initCamPos = cameraPosition;
			// �P�D�J�����̈ʒu����v���C���[�̈ʒu�����āA�Q�_������playerToCameraVec���쐬����
			XMVECTOR playerToCameraVec = XMLoadFloat3(&cameraPosition) - XMLoadFloat3(&transform_.position_);

			// �Q�D�x�N�g���`�𐳋K�����������P�ɂ��A�����x�N�g���a�Ƃ���
			XMVECTOR nom_playerToCameraVec = XMVector3Normalize(playerToCameraVec);

			// �R�D���K�������x�N�g���a����]�s������Ƃɉ�]������
			// ��jY���ɂX�O�x��]
			XMMATRIX rotateMatrix = XMMatrixRotationX(XMConvertToRadians(mouseMove.y /sensitivity)) * XMMatrixRotationY(XMConvertToRadians(mouseMove.x / sensitivity));
			XMVECTOR rotatedPlayerToCameraVec = XMVector3Transform(nom_playerToCameraVec, rotateMatrix);

			// �S�D��]��Ƀx�N�g���a��playerToCameraVec�̒������|����
			rotatedPlayerToCameraVec *= XMVectorGetX(XMVector3Length(playerToCameraVec));

			// �T�D�v���C���[�̈ʒu�ƃx�N�g���a�𑫂��āA��]��̃J�����̈ʒu�ɐL�т�x�N�g���b���쐬
			rotatedPlayerToCameraVec = rotatedPlayerToCameraVec + XMLoadFloat3(&transform_.position_);

			// �U�D�x�N�g���b��XMStoreFloat3()�ňʒu�ɕϊ�����΃J�����̈ʒu�����߂邱�Ƃ��ł���͂�
			XMStoreFloat3(&cameraPosition, rotatedPlayerToCameraVec);

			Camera::SetPosition(cameraPosition);

		}
		ImGui::End();
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
