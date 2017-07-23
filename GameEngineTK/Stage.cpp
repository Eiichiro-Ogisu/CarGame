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
void Stage::Draw(vector<string> mapData)
{
	for (vector<vector<Obj3d>>::iterator it = m_stageObj.begin();
		it != m_stageObj.end();
		it++)
	{
		
	}
}

/// <summary>
/// csv�t�@�C���̃Z�b�g
/// </summary>
/// <param name="csvFile">csv�t�@�C��</param>
void Stage::SetCsvFile(const std::string csvFile)
{
	m_csvFile = csvFile;
}

/// <summary>
/// �}�b�v�f�[�^���Z�b�g
/// </summary>
/// <param name="delim">��؂蕶��</param>
void Stage::SetMapData(const char delim)
{
	// �t�@�C���I�[�v��
	ifstream ifs(m_csvFile);

	// �J���Ȃ�������I��
	if (!ifs)
	{
		exit(1);
	}

	// �t�@�C������ǂݍ���1�s�̕�������f���~�b�^�ŕ����ă��X�g�ɒǉ�
	
	// ���������f�[�^�z��
	vector<vector<int>> record;

	// 1�s���̕����񃊃X�g
	vector<int> rowRecord;

	// �t�@�C���̏I���܂œǂݍ��񂾂��`�F�b�N
	while (!ifs.eof())
	{
		// 1�s���̃f�[�^
		string tmp;

		// 1�s�ǂݍ���
		while (getline(ifs,tmp))
		{
			// 1�������̃f�[�^�ێ��p
			string token;

			// ������X�g���[��
			istringstream stream(tmp);

			// �J���}��������1�������z��Ɋi�[
			while (getline(stream,token,delim))
			{
				// string�^��float �^�ɕϊ�
				int temp = stof(token);

				// 1�s���̃f�[�^�z��̒���1�������i�[
				rowRecord.push_back(temp);
			}
			// �񎟌��z���1�s���̃f�[�^���i�[
			record.push_back(rowRecord);

			// 1�s���̃f�[�^���N���A
			rowRecord.clear();

		}
	}

	// �}�b�v�f�[�^�ɓ񎟌��z�����
	m_data = record;
}

Stage::~Stage()
{
}
