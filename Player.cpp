#include "Player.h"

#include "Engine/Model.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Input.h"

#include "Ore.h"
#include "Engine/Camera.h"

namespace {
    const float sensitivity = 0.5f;// �}�E�X���x
    const float playerCameraDistance = 5.f;
    const float playerHeadHeight = 3.f;

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

    hModel_point_ = Model::Load("DebugCollision/Point.fbx");
    //assert(hModel_point_ <= 0);

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
        Mining();
    }

    // �J�����̐ݒ�
    {
        // �v���C���[�̓����̈ʒu��ݒ�
        XMFLOAT3 playerHead_position = transform_.position_;
        playerHead_position.y += playerHeadHeight;

        // �}�E�X�̏����擾
        XMFLOAT3 mouseMove = Input::GetMouseMove();

        // ===== �J�����̈ʒu�̉�] =====
        XMFLOAT3 camera_position = Camera::GetPosition();
            
        // ���K���ς݂̌����x�N�g����p��
        XMVECTOR player_To_camPos = XMLoadFloat3(&camera_position) - XMLoadFloat3(&playerHead_position);
        player_To_camPos = XMVector3Normalize(player_To_camPos);

        // ��]�s����}�E�X�̈ړ��ʂ���ɍ쐬
        XMMATRIX matRotate = 
            XMMatrixRotationX(XMConvertToRadians(mouseMove.y * sensitivity)) * XMMatrixRotationY(XMConvertToRadians(mouseMove.x * sensitivity));

        // ��]�s����|���āA�����x�N�g������]
        player_To_camPos = XMVector3Transform(player_To_camPos, matRotate);

        // ������ύX
        //static float dist = playerCameraDistance;
        //if(mouseMove.z > 0)dist = mouseMove.z;
        player_To_camPos *= playerCameraDistance;

        // ���_�O�C�O�����]��̃J�����̈ʒu�ɐL�т�x�N�g�����쐬���A�ʒu�ɑ��
        XMVECTOR origin_To_camPos = player_To_camPos + XMLoadFloat3(&playerHead_position);
        XMStoreFloat3(&camera_position, origin_To_camPos);

        // ===== �J�����̏œ_�̉�] =====
        XMFLOAT3 camera_target = Camera::GetPosition();

        XMVECTOR origin_To_camTarget = XMLoadFloat3(&playerHead_position) - player_To_camPos;
        XMStoreFloat3(&camera_target, origin_To_camTarget);

        ImGui::Text("camera_position = %f,%f,%f", camera_position.x, camera_position.y, camera_position.z);
        ImGui::Text("camera_target = %f,%f,%f", camera_target.x, camera_target.y, camera_target.z);
       
        Camera::SetPosition(camera_position);
        Camera::SetTarget(camera_target);
    }

}

void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    // �J�����̈ʒu
    Transform cam;
    cam.position_ = Camera::GetPosition();
    Model::SetTransform(hModel_point_, cam);
    Model::Draw(hModel_point_);

    cam.position_ = Camera::GetTarget();
    Model::SetTransform(hModel_point_, cam);
    Model::Draw(hModel_point_);
}

void Player::Release()
{
}

void Player::Mining()
{
    // �z�΂̏����擾
    Ore* ore = (Ore*)FindObject("Ore");
    if (ore == nullptr)return;

    // �����x�N�g�����擾
    XMVECTOR sightline = XMVector3Normalize(Camera::GetSightline());

    // ���C�L���X�g�𔭎�
    RayCastData sightRay; {
        XMStoreFloat3(&sightRay.dir, sightline);
        sightRay.start = Camera::GetPosition();
        Model::RayCast(ore->GetModelHandle(), &sightRay);

        // debug
        ImGui::Text("sightRay.hit = %s", sightRay.hit ? "true" : "false");
    }

    // �̌@�\���ǂ���
    bool isMining = false;
    if (ore->GetCircle().ContainsPoint(transform_.position_.x, transform_.position_.z)
        && sightRay.hit) {

        isMining = true;
        if (Input::IsMouseButtonDown(0)) {
            ore->KillMe();
            isMining = false;
        }
    }
    ImGui::Text("isMining = %s", isMining ? "true" : "false");

}
