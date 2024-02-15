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

	//カメラの初期位置の設定
	{
		initCamPos = { transform_.position_.x + 1.f, transform_.position_.y + 1.f, transform_.position_.z - 3.f };
		Camera::SetPosition(initCamPos);
        
		//Camera::SetTarget(transform_.position_.x + 1.f, transform_.position_.y, transform_.position_.z + 3.f);
        Camera::SetTarget(transform_.position_);
	}
}

void Player::Update()
{
	//// 移動の設定
	//{
 //       // 「W」キーが押されたら...
 //       if (Input::IsKey(DIK_W)) {
 //           // 画面「奥」方向に進む
 //           transform_.position_.z += 0.1f;
 //       }
 //       // 「A」キーが押されたら...
 //       if (Input::IsKey(DIK_A)) {
 //           // 画面「左」方向に進む
 //           transform_.position_.x -= 0.1f;
 //       }
 //       // 「S」キーが押されたら...
 //       if (Input::IsKey(DIK_S)) {
 //           // 画面「手前」方向に進む
 //           transform_.position_.z -= 0.1f;
 //       }
 //       // 「D」キーが押されたら...
 //       if (Input::IsKey(DIK_D)) {
 //           // 画面「右」方向に進む
 //           transform_.position_.x += 0.1f;
 //       }
	//}

	// カメラの設定
	{
		XMFLOAT3 cameraPosition = Camera::GetPosition();
		ImGui::Begin("Camera");
		ImGui::Text("start_cameraPos = (%f,%f,%f),", initCamPos.x, initCamPos.y, initCamPos.z);
		ImGui::Text("rotated_cameraPos = (%f,%f,%f),", cameraPosition.x, cameraPosition.y, cameraPosition.z);

		XMFLOAT3 mouseMove = Input::GetMouseMove();
		ImGui::Text("mouseMove = (%f,%f,%f),", mouseMove.x, mouseMove.y, mouseMove.z);


		if (mouseMove.x >= 0 || mouseMove.y >= 0) {
			initCamPos = cameraPosition;
			// １．カメラの位置からプレイヤーの位置引いて、２点を結ぶplayerToCameraVecを作成する
			XMVECTOR playerToCameraVec = XMLoadFloat3(&cameraPosition) - XMLoadFloat3(&transform_.position_);

			// ２．ベクトルＡを正規化し長さを１にし、向きベクトルＢとする
			XMVECTOR nom_playerToCameraVec = XMVector3Normalize(playerToCameraVec);

			// ３．正規化したベクトルＢを回転行列をもとに回転させる
			// 例）Y軸に９０度回転
			XMMATRIX rotateMatrix = XMMatrixRotationX(XMConvertToRadians(mouseMove.y /sensitivity)) * XMMatrixRotationY(XMConvertToRadians(mouseMove.x / sensitivity));
			XMVECTOR rotatedPlayerToCameraVec = XMVector3Transform(nom_playerToCameraVec, rotateMatrix);

			// ４．回転後にベクトルＢにplayerToCameraVecの長さを掛ける
			rotatedPlayerToCameraVec *= XMVectorGetX(XMVector3Length(playerToCameraVec));

			// ５．プレイヤーの位置とベクトルＢを足して、回転後のカメラの位置に伸びるベクトルＣを作成
			rotatedPlayerToCameraVec = rotatedPlayerToCameraVec + XMLoadFloat3(&transform_.position_);

			// ６．ベクトルＣをXMStoreFloat3()で位置に変換すればカメラの位置を求めることができるはず
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
