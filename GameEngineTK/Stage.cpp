#include "pch.h"
#include "Stage.h"

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

/// <summary>
/// CSV���
/// </summary>
/// <param name="csvFile">CSV�t�@�C��</param>
Stage::Stage(string csvFile)
{
	this->m_csvFile = csvFile;
}

/// <summary>
/// CSV�Ǎ�
/// </summary>
/// <param name=""></param>
/// <param name="delim">�f���~�b�^</param>
/// <returns>true:����,false:���s</returns>
bool Stage::LoadMapData(vector<vector<string>>& data, const char delim = ',')
{
	// �t�@�C���I�[�v��
	ifstream ifs(m_csvFile);
	if (!ifs.is_open()) return false;	// �Ǎ����s

	// �t�@�C���Ǎ�
	string buf;					// 1�s���̃o�b�t�@

	while (getline(ifs,buf))
	{
		vector<string> rec;		// 1�s���̃x�N�^�[�z��

		istringstream iss(buf);	// ������X�g���[��

		string field;			//1�񕪕�����

		// 1�񕪕������1�s���x�N�^�[�ɒǉ�
		while (getline(iss, field, delim))
		{
			rec.push_back(field);
		}

		// 1�s���x�N�^��data�x�N�^�[�ɒǉ�
		if (rec.size() != 0)
		{
			data.push_back(rec);
		}
	}
	return true;
}


Stage::~Stage()
{
}
