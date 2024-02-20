#include "Player.h"

#include "Engine/Model.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Input.h"

#include "Ore.h"
#include "Engine/Camera.h"

namespace {
    const float sensitivity = 0.5f;// �}�E�X���x
    const float playerCameraDistance = 5.f;
    const float playerHeadHeight = 4.f;
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
        ImGui::Text("Player.position = %f,%f,%f", pPos.x, pPos.y, pPos.z);
	}
	
    // new �ړ�����
    {

        // �A�j���[�V����������Ă��邩�ǂ���
        bool isAnim = false;

        // �v���C���[�̑��x
        float speed = 0.1f;

        // ���K�����������x�N�g�����擾
        XMVECTOR moveDir = XMVector3Normalize(Camera::GetSightline());

        // debug
        {
            XMFLOAT3 mdf = {
                XMVectorGetX(moveDir),
                XMVectorGetY(moveDir),
                XMVectorGetZ(moveDir),
            };
            ImGui::Text("moveDir = %f,%f,%f", mdf.x, mdf.y, mdf.z);
        }

        // Y�����ւ̈ړ��𐧌��������̂ŁAY�v�f���O�ɂ���
        moveDir = XMVectorSetY(moveDir, 0);

        // �X�s�[�h����Z
        moveDir *= speed;


        // �ړ������x�N�g����p��
        XMVECTOR move{ 0,0,0,0 };

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
                /*XMMatrixRotationX(XMConvertToRadians(mouseMove.y * sensitivity)) **/ XMMatrixRotationY(XMConvertToRadians(mouseMove.x * sensitivity));

            // ��]�s����|���āA�����x�N�g������]
            player_To_camPos = XMVector3Transform(player_To_camPos, matRotate);

            // ������ύX
            player_To_camPos *= playerCameraDistance;

            // ���_�O�C�O�����]��̃J�����̈ʒu�ɐL�т�x�N�g�����쐬���A�ʒu�ɑ��
            XMVECTOR origin_To_camPos = player_To_camPos + XMLoadFloat3(&playerHead_position);
            XMStoreFloat3(&camera_position, origin_To_camPos);

        }

        // �J�����̏œ_�̉�]
        XMFLOAT3 camera_target = Camera::GetTarget();
        {

            // ���K���ς݂̌����x�N�g����p��
            XMVECTOR player_To_camPos = XMLoadFloat3(&camera_position) - XMLoadFloat3(&playerHead_position);
            player_To_camPos = XMVector3Normalize(player_To_camPos);

            // ��]�s����}�E�X�̈ړ��ʂ���ɍ쐬
            XMMATRIX matRotate =
                /*XMMatrixRotationX(XMConvertToRadians(mouseMove.y * sensitivity) + 45.f) **/ XMMatrixRotationY(XMConvertToRadians(mouseMove.x * sensitivity) + 45.f);

            // ��]�s����|���āA�����x�N�g������]
            XMVECTOR player_To_camTgt = XMVector3Transform(player_To_camPos, matRotate);

            // ������ύX
            player_To_camTgt *= playerCameraDistance;

            // ���_�O�C�O�����]��̃J�����̈ʒu�ɐL�т�x�N�g�����쐬���A�ʒu�ɑ��
            XMVECTOR origin_To_camTgt = XMLoadFloat3(&playerHead_position)- player_To_camTgt;
            XMStoreFloat3(&camera_target, origin_To_camTgt);

        }

        ImGui::Text("camera_position = %f,%f,%f", camera_position.x, camera_position.y, camera_position.z);
        Camera::SetPosition(camera_position);

        // �œ_�������̎��͂��܂������B
        //Camera::SetTarget(playerHead_position);

        ImGui::Text("camera_target = %f,%f,%f", camera_target.x, camera_target.y, camera_target.z);
        Camera::SetTarget(camera_target);

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
