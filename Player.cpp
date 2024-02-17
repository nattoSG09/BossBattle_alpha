#include "Player.h"

#include "Engine/Model.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Input.h"

#include "Ore.h"
#include "Engine/Camera.h"

namespace {
    const float sensitivity = 0.5f;// �}�E�X���x
    const float playerCameraDistance = 10.f;
    const float playerHeadHeight = 4.f;

    // ��̃x�N�g������p�x�����߂�֐�(���W�A��)
    float AngleBetweenVectors(XMVECTOR& _vec1, XMVECTOR& _vec2) {
        // �x�N�g���𐳋K������
        XMVECTOR normVec1 = XMVector3Normalize(_vec1);
        XMVECTOR normVec2 = XMVector3Normalize(_vec2);

        // ���ς��v�Z����
        float dotProduct = XMVectorGetX(XMVector3Dot(normVec1, normVec2));

        // �O�ς��v�Z����
        XMVECTOR crossProduct = XMVector3Cross(normVec1, normVec2);
        float crossLength = XMVectorGetX(XMVector3Length(crossProduct));

        // atan2���g�p���Ċp�x���v�Z���A�Ԃ�
        return atan2(crossLength, dotProduct);
    }
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
	
	// old �ړ�����&�A�j���[�V��������
	{
		/*bool isAnim = false;
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
        }*/
	}

    // new �ړ�����
    {

        // �A�j���[�V����������Ă��邩�ǂ���
        bool isAnim = false;

        // �v���C���[�̑��x
        float speed = 0.1f;

        // ���K�����������x�N�g�����擾
        XMVECTOR moveDir = XMVector3Normalize(Camera::GetSightline());

        // Y�����ւ̈ړ��𐧌��������̂ŁAY�v�f���O�ɂ���
        moveDir = XMVectorSetY(moveDir, 0);
        
        // �X�s�[�h����Z
        moveDir *= speed;
        
        // debug
        {
            XMFLOAT3 mdf = {
                XMVectorGetX(moveDir),
                XMVectorGetY(moveDir),
                XMVectorGetZ(moveDir),
            };
            ImGui::Text("moveDir = %f,%f,%f", mdf.x, mdf.y, mdf.z);
        }
        
        // �ړ������x�N�g����p��
        XMVECTOR move{0,0,0,0};

        ImGui::Begin("input key");
        
        // �u�v�v�L�[�������ꂽ��...
        if (Input::IsKey(DIK_W)) {
            ImGui::Text("W");

            // ��ʑO���ɐi��
            move = XMLoadFloat3(&transform_.position_) + moveDir;
            XMStoreFloat3(&transform_.position_, move);

            // �A�j���[�V�����𓮍삳����
            isAnim = true;
        }

        // �u�`�v�L�[�������ꂽ��...
        if (Input::IsKey(DIK_A)) {
            ImGui::Text("A");

            // ��ʉE���ɐi��
            moveDir = XMVector3Transform(moveDir, XMMatrixRotationY(XMConvertToRadians(90)));
            move = XMLoadFloat3(&transform_.position_) - moveDir;
            XMStoreFloat3(&transform_.position_, move);

            // �A�j���[�V�����𓮍삳����
            isAnim = true;
        }

        // �u�r�v�L�[�������ꂽ��...
        if (Input::IsKey(DIK_S)) {
            ImGui::Text("S");

            // ��ʌ���ɐi��
            move = XMLoadFloat3(&transform_.position_) - moveDir;
            XMStoreFloat3(&transform_.position_, move);

            // �A�j���[�V�����𓮍삳����
            isAnim = true;
        }

        // �u�c�v�L�[�������ꂽ��...
        if (Input::IsKey(DIK_D)) {
            ImGui::Text("D");

            // ��ʍ����ɐi��
            moveDir = XMVector3Transform(moveDir, XMMatrixRotationY(XMConvertToRadians(90)));
            move = XMLoadFloat3(&transform_.position_) + moveDir;
            XMStoreFloat3(&transform_.position_, move);

            // �A�j���[�V�����𓮍삳����
            isAnim = true;
        }

        ImGui::End();

        // �A�j���[�V�������s��
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
        // �v���C���[�̓����̈ʒu��ݒ�
        XMFLOAT3 playerHead_position = transform_.position_;
        playerHead_position.y += playerHeadHeight;

        // �}�E�X�̏����擾
        XMFLOAT3 mouseMove = Input::GetMouseMove();

        // �J�����̈ʒu�̉�]
        XMFLOAT3 camera_position = Camera::GetPosition();
        {
            
            // ���K���ς݂̌����x�N�g����p��
            XMVECTOR player_To_camPos = XMLoadFloat3(&camera_position) - XMLoadFloat3(&playerHead_position);
            player_To_camPos = XMVector3Normalize(player_To_camPos);

            // ��]�s����}�E�X�̈ړ��ʂ���ɍ쐬
            XMMATRIX matRotate = 
                XMMatrixRotationX(XMConvertToRadians(mouseMove.y * sensitivity)) * XMMatrixRotationY(XMConvertToRadians(mouseMove.x * sensitivity));

            // ��]�s����|���āA�����x�N�g������]
            player_To_camPos = XMVector3Transform(player_To_camPos, matRotate);

            // ������ύX
            player_To_camPos *= playerCameraDistance;

            // ���_�O�C�O�����]��̃J�����̈ʒu�ɐL�т�x�N�g�����쐬���A�ʒu�ɑ��
            XMVECTOR origin_To_camPos = player_To_camPos + XMLoadFloat3(&playerHead_position);
            XMStoreFloat3(&camera_position, origin_To_camPos);

        }
        Camera::SetPosition(camera_position);
        Camera::SetTarget(playerHead_position);
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
