#include "sceneManager.h"

//�V�[���I�u�W�F�N�g
#include "../TestScene.h"
#include "../LoadScene.h"

#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Texture.h"
#include "ImGui/imgui.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	testTexture_ = new Texture;
	testTexture_->Load("TestScene.png");

	loadTexture_ = new Texture;
	loadTexture_->Load("Miner'sHope_Images/title_color01.png");

	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}


//�X�V
void SceneManager::Update()
{
	ImGui::Begin("Scene");
	ImGui::Text("TestScene");
	if (ImGui::ImageButton(testTexture_->GetSRV(), ImVec2(testTexture_->GetSize().x / 10, testTexture_->GetSize().y / 10))) {
		ChangeScene(SCENE_ID_TEST, TID_BLACKOUT, 1.f);
	}
	ImGui::Text("LoadScene");
	if (ImGui::ImageButton(loadTexture_->GetSRV(), ImVec2(loadTexture_->GetSize().x / 10, loadTexture_->GetSize().y / 10))) {
		ChangeScene(SCENE_ID_LOAD, TID_BLACKOUT, 1.f);

	}
	ImGui::End();

	//�g�����W�V�������s���A�V�[���ؑւ̃^�C�~���O�ŃV�[����ύX����
	if (Transition::IsChangePoint())nextSceneID_ = tmpID_;

	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_LOAD: Instantiate<LoadScene>(this); break;
		}

		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next, TRANSITION_ID _type,float _time)
{
	//�g�����W�V���������쒆�̓V�[���J�ڂ��s��Ȃ�
	if (!Transition::IsActive()) {
		//�g�����W�V�������g��Ȃ��ꍇ�A�V�[��ID���Z�b�g
		if (!Transition::SetTransition(_type))nextSceneID_ = next;
		
		//���Ԃ��Z�b�g
		Transition::SetTime(_time);

		//�g�����W�V�������J�n���A�V�[��ID���Z�b�g
		Transition::Start();tmpID_ = next;
	}
}
void SceneManager::ChangeScene(SCENE_ID next, TRANSITION_ID _type){ChangeScene(next, _type, 2);}
void SceneManager::ChangeScene(SCENE_ID next){ChangeScene(next, TID_NONE);}


