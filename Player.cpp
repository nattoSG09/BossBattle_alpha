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
	// モデルの読み込み
	hModel_ = Model::Load("Models/Player/Walking.fbx");
	assert(hModel_ <= 0);

}

void Player::Update()
{
	// debug情報の表示
	{
		XMFLOAT3 pPos = transform_.position_;
		ImGui::Text("Player.position = { x(%f),y(%f),z(%f) }", pPos.x, pPos.y, pPos.z);
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
            // １．カメラの位置からプレイヤーの位置引いて、２点を結ぶplayerToCameraVecを作成する
            XMVECTOR playerToCameraVec = XMLoadFloat3(&cameraPosition) - XMLoadFloat3(&cameraTarget);

            // ２．ベクトルＡを正規化し長さを１にし、向きベクトルＢとする
            XMVECTOR nom_playerToCameraVec = XMVector3Normalize(playerToCameraVec);

            // ３．正規化したベクトルＢを回転行列をもとに回転させる
            // 例）Y軸に９０度回転
            XMMATRIX rotateMatrix = XMMatrixRotationX(-XMConvertToRadians(mouseMove.y / sensitivity)) * XMMatrixRotationY(XMConvertToRadians(mouseMove.x / sensitivity));
            XMVECTOR rotatedPlayerToCameraVec = XMVector3Transform(nom_playerToCameraVec, rotateMatrix);

            // ４．回転後にベクトルＢにplayerToCameraVecの長さを掛ける
            rotatedPlayerToCameraVec *= 10.f;

            // ５．プレイヤーの位置とベクトルＢを足して、回転後のカメラの位置に伸びるベクトルＣを作成
            rotatedPlayerToCameraVec = rotatedPlayerToCameraVec + XMLoadFloat3(&cameraTarget);

            // ６．ベクトルＣをXMStoreFloat3()で位置に変換すればカメラの位置を求めることができるはず
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
