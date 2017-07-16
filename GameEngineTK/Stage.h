//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Stage.h
//!
//! @brief  �X�e�[�W�֘A�̃w�b�_�[�t�@�C��
//!
//! @date   2017/07/17
//!
//! @author E.Ogisu
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#include <string>
#include <vector>

#pragma once
class Stage
{
private:
	// csv�t�@�C����
	std::string m_csvFile;

public:
	// �R���X�g���N�^
	Stage(std::string csvFile);

	// �}�b�v�f�[�^�擾
	bool LoadMapData(std::vector<std::vector<std::string>>& csvFile, const char delim = ',');

	~Stage();
};

