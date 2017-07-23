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

#include<string>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="csvFile">CSV�t�@�C����</param>
Stage::Stage(/*string csvFile*/)
{
	//this->m_csvFile = csvFile;

	//// �������Ăяo��
	//Initialize();
}

/// <summary>
/// ����������
/// </summary>
void Stage::Initialize()
{
	//// ���f���̓ǂݍ���
	//m_stageObj.resize(1);
	//m_stageObj[0][].LoadModel(L"Resources\\stageBox.cmo");

	//// ���W�̐ݒ�
	//m_stageObj[0][].SetTransform(Vector3(0, 0, 0));
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
void Stage::Draw(vector<string>)
{
	//for (vector<Obj3d>::iterator it = m_stageObj.begin();
	//	it != m_stageObj.end();
	//	it++)
	//{
	//	it->Draw();
	//}
}

/// <summary>
/// csv�t�@�C���̐ݒ�
/// </summary>
/// <param name="csvFile"></param>
void Stage::SetCsvFile(const std::string csvFile)
{
	m_csvFile = csvFile;
}

/// <summary>
/// csv�ǂݍ���
/// </summary>
/// <param name="data">1�s���f�[�^</param>
/// <param name="delim">�f���~�b�^</param>
/// <returns>�}�b�v�f�[�^�̔z��</returns>
vector<string> Stage::GetMapData(const char delim)
{
	// �t�@�C���I�[�v��
	fstream filestream(m_csvFile);

	// �J���Ȃ�������I��
	if (!filestream.is_open())
	{
		exit(1);
	}

	// �t�@�C������ǂݍ���1�s�̕�������f���~�b�^�ŕ����ă��X�g�ɒǉ�
	vector<string> record;				// 1�s���̕����񃊃X�g
	// �t�@�C���̓ǂݍ���
	while (!filestream.eof())
	{

		char c;
		string msg = "";

		while (filestream.get(c)) {
			if (c != '\n') {
				msg += c;
			}
			else {
				msg += ',';
			}
		}
		// 1�s���o�b�t�@
		string tmp;


		istringstream iss(msg);
		while (getline(iss, tmp, delim))
		
		// 1�Z�����̕���������X�g�ɒǉ�
		record.push_back(tmp);

	}
	return record;
}

Stage::~Stage()
{
}
