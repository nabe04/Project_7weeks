#include "load_texture.h"

namespace n_texture
{
	int storePlayer[NO_ANIMATION];				   //�v���C���[
	int storeBG[BG_CHIP_NUM];					   //BG
	int storeTerrain[TERRAIN_CHIP_NUM];			   //�}�b�v�`�b�v
	int sprBlock[BLOCK_CHIP_NUM];				   //�u���b�N
	int sprMyBlock[NO_ANIMATION];				   //���v
	int sprCursorW[NO_ANIMATION];				   //�J�[�\��(��)
	int sprCursorH[NO_ANIMATION];				   //�J�[�\��(�c)
	int sprCursorC[NO_ANIMATION];				   //�J�[�\��(����)
	int sprLine[NO_ANIMATION];					   //�J�[�\�����C��
	int sprCursor[CURSOR_CHIP_NUM];				   //�J�[�\��
	int sprFrame[NO_ANIMATION];					   //�Ֆʂ̘g
	int sprGauge[UI_CHIP_NUM];					   //�Q�[�W
	int sprGaugeFrame[NO_ANIMATION];			   //�Q�[�W�g
	int sprDoorLeft[NO_ANIMATION];				   //�h�A(��)
	int sprDoorRight[NO_ANIMATION];				   //�h�A(�E)
	int sprBG[NO_ANIMATION];					   //BG(�{��)
	int sprBlokenBLock[BLOKEN_BLOCK_CHIP_NUM];	   //�u���b�N�j��(�A�Z�b�g)
	int sprPressMachine[NO_ANIMATION];			   //�v���X�@
	int sprPressEffect[PRESS_EFFECT_CHIP_NUM];	   //�v���X�G�t�F�N�g
	int sprCounterBlock[COUNTER_BLOCK_CHIP_NUM];   //�J�E���^�[�u���b�N
	int sprCounterEffect[COUNTER_EFFECT_CHIP_NUM]; //�J�E���^�[�u���b�N�̃G�t�F�N�g
	int sprArrow[NO_ANIMATION];					   //���
	int sprIndexLine[NO_ANIMATION];				   //�w�W(Tutorial�̋��ރ��C��)
	int sprIndexCursor[NO_ANIMATION];			   //�w�W(Tutorial�̎����̃J�[�\��)

}

namespace n_font
{
	int fontYomogi;

	char* fh_yomogi = "Nu ��������� �W��-��1";
}