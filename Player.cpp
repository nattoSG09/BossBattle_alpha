#include "Player.h"

#include "Engine/Model.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Input.h"

#include "Ore.h"
#include "Engine/Camera.h"

namespace {
    const float sensitivity = 5.f;
}

Player::Player(GameObject* _pParent)
	:GameObject(_pParent,"Player"),hModel_(-1)
{
}

void Player::Initialize()
{
	// ���f���̓ǂݍ���
	hModel_ = Model::Load("Models/Player/Walking.fbx");
	assert(hModel_ <= 0);

}

void Player::Update()
{
	// debug���̕\��
	{
		XMFLOAT3 pPos = transform_.position_;
		ImGui::Text("Player.position = { x(%f),y(%f),z(%f) }", pPos.x, pPos.y, pPos.z);
	}
	
	// �ړ�����&�A�j���[�V��������
	{
		bool isAnim = false;
        if (Input::IsKey(DIK_W)) {
            transform_.rotate_.y = 0;
            transform_.position_.z += 0.1f;
            isAnim = true;
        }

        if (Input::IsKey(DIK_A)) {
            transform_.rotate_.y = -90;
            transform_.position_.x -= 0.1f;
            isAnim = true;
        }

        if (Input::IsKey(DIK_S)) {
            transform_.rotate_.y = 180;
            transform_.position_.z -= 0.1f;
            isAnim = true;
        }

        if (Input::IsKey(DIK_D)) {
            transform_.rotate_.y = 90;
            transform_.position_.x += 0.1f;
            isAnim = true;
        }


        static bool prevAnim = false;
        if (isAnim == true) {
            if (prevAnim == false)Model::SetAnimFrame(hModel_, 0, 60, 1);
            prevAnim = true;
        }
        else {
            Model::SetAnimFrame(hModel_, 0, 0, 0);
            prevAnim = false;
        }
	}

    // �̌@����
    {
        bool isMining = false;
        Ore* ore = (Ore*)FindObject("Ore");
        if (ore != nullptr) {
            if (ore->GetCircle().ContainsPoint(transform_.position_.x, transform_.position_.z)) {
                
                isMining = true;
                if (Input::IsKeyDown(DIK_SPACE)) {
                    ore->KillMe();
                    isMining = false;
                }
            }
        }
        ImGui::Text("isMining = %s", isMining ? "true" : "false");
    }

    // �J�����̐ݒ�
    {
        XMFLOAT3 cameraPosition = Camera::GetPosition();
        ImGui::Begin("Camera");
        ImGui::Text("start_cameraPos = (%f,%f,%f),", initCamPos.x, initCamPos.y, initCamPos.z);
        ImGui::Text("rotated_cameraPos = (%f,%f,%f),", cameraPosition.x, cameraPosition.y, cameraPosition.z);

        XMFLOAT3 mouseMove = Input::GetMouseMove();
        ImGui::Text("mouseMove = (%f,%f,%f),", mouseMove.x, mouseMove.y, mouseMove.z);

        XMFLOAT3 cameraTarget = transform_.position_;
        cameraTarget.y += 5.0f;

        if (mouseMove.x >= 0 || mouseMove.y >= 0) {

            initCamPos = cameraPosition;
            // �P�D�J�����̈ʒu����v���C���[�̈ʒu�����āA�Q�_������playerToCameraVec���쐬����
            XMVECTOR playerToCameraVec = XMLoadFloat3(&cameraPosition) - XMLoadFloat3(&cameraTarget);

            // �Q�D�x�N�g���`�𐳋K�����������P�ɂ��A�����x�N�g���a�Ƃ���
            XMVECTOR nom_playerToCameraVec = XMVector3Normalize(playerToCameraVec);

            // �R�D���K�������x�N�g���a����]�s������Ƃɉ�]������
            // ��jY���ɂX�O�x��]
            XMMATRIX rotateMatrix = XMMatrixRotationX(-XMConvertToRadians(mouseMove.y / sensitivity)) * XMMatrixRotationY(XMConvertToRadians(mouseMove.x / sensitivity));
            XMVECTOR rotatedPlayerToCameraVec = XMVector3Transform(nom_playerToCameraVec, rotateMatrix);

            // �S�D��]��Ƀx�N�g���a��playerToCameraVec�̒������|����
            rotatedPlayerToCameraVec *= 10.f;

            // �T�D�v���C���[�̈ʒu�ƃx�N�g���a�𑫂��āA��]��̃J�����̈ʒu�ɐL�т�x�N�g���b���쐬
            rotatedPlayerToCameraVec = rotatedPlayerToCameraVec + XMLoadFloat3(&cameraTarget);

            // �U�D�x�N�g���b��XMStoreFloat3()�ňʒu�ɕϊ�����΃J�����̈ʒu�����߂邱�Ƃ��ł���͂�
            XMStoreFloat3(&cameraPosition, rotatedPlayerToCameraVec);

        }
        Camera::SetPosition(cameraPosition);
        Camera::SetTarget(cameraTarget);

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
