#include "Player.h"

#include "Engine/Model.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Input.h"

#include "Ore.h"
#include "Engine/Camera.h"

namespace {
    const float sensitivity = 0.5f;// マウス感度
    const float playerCameraDistance = 5.f;
    const float playerHeadHeight = 4.f;
}

Player::Player(GameObject* _pParent)
	:GameObject(_pParent,"Player"),hModel_(-1)
{
}

void Player::Initialize()
{
	// モデルの読み込み
	hModel_ = Model::Load("Models/Player/Walking.fbx");
	assert(hModel_ <= 0);

}

void Player::Update()
{
	// debug情報の表示
	{
		XMFLOAT3 pPos = transform_.position_;
        ImGui::Text("Player.position = %f,%f,%f", pPos.x, pPos.y, pPos.z);
	}
	
	// 移動処理&アニメーション処理
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

    // 採掘処理
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

    // カメラの設定
    {
        // プレイヤーの頭部の位置を設定
        XMFLOAT3 playerHead_position = transform_.position_;
        playerHead_position.y += playerHeadHeight;

        // マウスの情報を取得
        XMFLOAT3 mouseMove = Input::GetMouseMove();

        // カメラの位置の回転
        XMFLOAT3 camera_position = Camera::GetPosition();
        {
            
            // 正規化済みの向きベクトルを用意
            XMVECTOR player_To_camPos = XMLoadFloat3(&camera_position) - XMLoadFloat3(&playerHead_position);
            player_To_camPos = XMVector3Normalize(player_To_camPos);

            // 回転行列をマウスの移動量を基に作成
            XMMATRIX matRotate = 
                /*XMMatrixRotationX(XMConvertToRadians(mouseMove.y * sensitivity)) **/ XMMatrixRotationY(XMConvertToRadians(mouseMove.x * sensitivity));

            // 回転行列を掛けて、向きベクトルを回転
            player_To_camPos = XMVector3Transform(player_To_camPos, matRotate);

            // 長さを変更
            player_To_camPos *= playerCameraDistance;

            // 原点０，０から回転後のカメラの位置に伸びるベクトルを作成し、位置に代入
            XMVECTOR origin_To_camPos = player_To_camPos + XMLoadFloat3(&playerHead_position);
            XMStoreFloat3(&camera_position, origin_To_camPos);

        }

        // カメラの焦点の回転
        XMFLOAT3 camera_target = Camera::GetTarget();
        {

            // 正規化済みの向きベクトルを用意
            XMVECTOR player_To_camPos = XMLoadFloat3(&camera_position) - XMLoadFloat3(&playerHead_position);
            player_To_camPos = XMVector3Normalize(player_To_camPos);

            // 回転行列をマウスの移動量を基に作成
            XMMATRIX matRotate =
                /*XMMatrixRotationX(XMConvertToRadians(mouseMove.y * sensitivity) + 45.f) **/ XMMatrixRotationY(XMConvertToRadians(mouseMove.x * sensitivity) + 45.f);

            // 回転行列を掛けて、向きベクトルを回転
            XMVECTOR player_To_camTgt = XMVector3Transform(player_To_camPos, matRotate);

            // 長さを変更
            player_To_camTgt *= playerCameraDistance;

            // 原点０，０から回転後のカメラの位置に伸びるベクトルを作成し、位置に代入
            XMVECTOR origin_To_camTgt = XMLoadFloat3(&playerHead_position)- player_To_camTgt;
            XMStoreFloat3(&camera_target, origin_To_camTgt);

        }

        ImGui::Text("camera_position = %f,%f,%f", camera_position.x, camera_position.y, camera_position.z);
        Camera::SetPosition(camera_position);

        // 焦点が頭部の時はうまくいく。
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
