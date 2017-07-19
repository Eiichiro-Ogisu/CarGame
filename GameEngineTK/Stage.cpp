//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Stage.cpp
//!
//! @brief  �X�e�[�W�֘A�̃\�[�X�t�@�C��
//!
//! @date   2017/07/18
//!
//! @author E.Ogisu
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#include "pch.h"
#include "Stage.h"

#include<iostream>
#include<string>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="csvFile">CSV�t�@�C����</param>
Stage::Stage(string csvFile)
{
	this->m_csvFile = csvFile;
}

/// <summary>
/// ����������
/// </summary>
void Stage::Initialize()
{
	// ���f���̓ǂݍ���
	m_stageObj.resize(1);
	m_stageObj[0].LoadModel(L"Resources\\stageBox.cmo");

	// ���W�̐ݒ�
	m_stageObj[0].SetTransform(Vector3(0, 0, 0));
}
/// <summary>
/// �X�V����
/// </summary>
void Stage::Update()
{
}
/// <summary>
/// �`�揈��
/// </summary>
void Stage::Draw()
{
	for (vector<Obj3d>::iterator it = m_stageObj.begin();
		it != m_stageObj.end();
		it++)
	{
		it->Draw();
	}
}

/// <summary>
/// CSV�Ǎ�
/// </summary>
/// <param name=""></param>
/// <param name="delim">�f���~�b�^</param>
/// <returns>true:����,false:���s</returns>
bool Stage::LoadMapData(vector<vector<string>>& data, const char delim)
{
	// �t�@�C���I�[�v��
	fstream filestream(m_csvFile);

	// �J���Ȃ�������I��
	if (!filestream.is_open())
	{
		return false;
	}

	// �t�@�C���̓ǂݍ���
	while (!filestream.eof())
	{
		// 1�s���o�b�t�@
		string buffer;

		// 1�s�ǂݍ���
		filestream >> buffer;

		// �t�@�C������ǂݍ���1�s�̕�������f���~�b�^�ŕ����ă��X�g�ɒǉ�
		vector<string> record;				// 1�s���̕����񃊃X�g

		istringstream streambuffer(buffer);	// ������X�g���[��

		string token;

		while (getline(streambuffer,token,delim))
		{
			// 1�Z�����̕���������X�g�ɒǉ�
			record.push_back(token);
		}
		data.push_back(record);
	}
	return true;
}


Stage::~Stage()
{
}
