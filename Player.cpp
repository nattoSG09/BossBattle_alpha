#include "Player.h"

#include "Engine/Model.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Input.h"

#include "Ore.h"
#include "Engine/Camera.h"

namespace {
    const float sensitivity = 0.5f;// マウス感度
    const float playerCameraDistance = 5.f;
    const float playerHeadHeight = 3.f;

    // 二つのベクトルから角度を求める関数(ラジアン)
    float AngleBetweenVectors(XMVECTOR& _vec1, XMVECTOR& _vec2) {
        // ベクトルを正規化する
        XMVECTOR normVec1 = XMVector3Normalize(_vec1);
        XMVECTOR normVec2 = XMVector3Normalize(_vec2);

        // 内積を計算する
        float dotProduct = XMVectorGetX(XMVector3Dot(normVec1, normVec2));

        // 外積を計算する
        XMVECTOR crossProduct = XMVector3Cross(normVec1, normVec2);
        float crossLength = XMVectorGetX(XMVector3Length(crossProduct));

        // atan2を使用して角度を計算し、返す
        return atan2(crossLength, dotProduct);
    }
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

    hModel_point_ = Model::Load("DebugCollision/Point.fbx");
    //assert(hModel_point_ <= 0);

}

void Player::Update()
{
	// debug情報の表示
	{
		XMFLOAT3 pPos = transform_.position_;
		ImGui::Text("Player.position = { x(%f),y(%f),z(%f) }", pPos.x, pPos.y, pPos.z);
	}
	
	// old 移動処理&アニメーション処理
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

    // new 移動処理
    {

        // アニメーションがされているかどうか
        bool isAnim = false;

        // プレイヤーの速度
        float speed = 0.1f;

        // 正規化した視線ベクトルを取得
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

        // Y方向への移動を制限したいので、Y要素を０にする
        moveDir = XMVectorSetY(moveDir, 0);
        
        // スピードを乗算
        moveDir *= speed;
        
        
        // 移動方向ベクトルを用意
        XMVECTOR move{0,0,0,0};

        ImGui::Begin("input key");
        
        // 「Ｗ」キーが押されたら...
        if (Input::IsKey(DIK_W)) {
            ImGui::Text("W");

            // 画面前方に進む
            move = XMLoadFloat3(&transform_.position_) + moveDir;
            XMStoreFloat3(&transform_.position_, move);

            // アニメーションを動作させる
            isAnim = true;
        }

        // 「Ａ」キーが押されたら...
        if (Input::IsKey(DIK_A)) {
            ImGui::Text("A");

            // 画面右方に進む
            moveDir = XMVector3Transform(moveDir, XMMatrixRotationY(XMConvertToRadians(90)));
            move = XMLoadFloat3(&transform_.position_) - moveDir;
            XMStoreFloat3(&transform_.position_, move);

            // アニメーションを動作させる
            isAnim = true;
        }

        // 「Ｓ」キーが押されたら...
        if (Input::IsKey(DIK_S)) {
            ImGui::Text("S");

            // 画面後方に進む
            move = XMLoadFloat3(&transform_.position_) - moveDir;
            XMStoreFloat3(&transform_.position_, move);

            // アニメーションを動作させる
            isAnim = true;
        }

        // 「Ｄ」キーが押されたら...
        if (Input::IsKey(DIK_D)) {
            ImGui::Text("D");

            // 画面左方に進む
            moveDir = XMVector3Transform(moveDir, XMMatrixRotationY(XMConvertToRadians(90)));
            move = XMLoadFloat3(&transform_.position_) + moveDir;
            XMStoreFloat3(&transform_.position_, move);

            // アニメーションを動作させる
            isAnim = true;
        }

        ImGui::End();

        // アニメーションを行う
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
        Mining();
    }

    // カメラの設定
    {
        // プレイヤーの頭部の位置を設定
        XMFLOAT3 playerHead_position = transform_.position_;
        playerHead_position.y += playerHeadHeight;

        // マウスの情報を取得
        XMFLOAT3 mouseMove = Input::GetMouseMove();

        // ===== カメラの位置の回転 =====
        XMFLOAT3 camera_position = Camera::GetPosition();
            
        // 正規化済みの向きベクトルを用意
        XMVECTOR player_To_camPos = XMLoadFloat3(&camera_position) - XMLoadFloat3(&playerHead_position);
        player_To_camPos = XMVector3Normalize(player_To_camPos);

        // 回転行列をマウスの移動量を基に作成
        XMMATRIX matRotate = 
            XMMatrixRotationX(XMConvertToRadians(mouseMove.y * sensitivity)) * XMMatrixRotationY(XMConvertToRadians(mouseMove.x * sensitivity));

        // 回転行列を掛けて、向きベクトルを回転
        player_To_camPos = XMVector3Transform(player_To_camPos, matRotate);

        // 長さを変更
        //static float dist = playerCameraDistance;
        //if(mouseMove.z > 0)dist = mouseMove.z;
        player_To_camPos *= playerCameraDistance;

        // 原点０，０から回転後のカメラの位置に伸びるベクトルを作成し、位置に代入
        XMVECTOR origin_To_camPos = player_To_camPos + XMLoadFloat3(&playerHead_position);
        XMStoreFloat3(&camera_position, origin_To_camPos);

        // ===== カメラの焦点の回転 =====
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

    // カメラの位置
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
    // 鉱石の情報を取得
    Ore* ore = (Ore*)FindObject("Ore");
    if (ore == nullptr)return;

    // 視線ベクトルを取得
    XMVECTOR sightline = XMVector3Normalize(Camera::GetSightline());

    // レイキャストを発射
    RayCastData sightRay; {
        XMStoreFloat3(&sightRay.dir, sightline);
        sightRay.start = Camera::GetPosition();
        Model::RayCast(ore->GetModelHandle(), &sightRay);

        // debug
        ImGui::Text("sightRay.hit = %s", sightRay.hit ? "true" : "false");
    }

    // 採掘可能かどうか
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
