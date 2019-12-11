#pragma once

struct ActorParam
{
	Vector2F accel;
	float	 speedMax;
	float	 gravityMax;

	float    ladderAccel;
};

class Actor :public MoveAlg
{
//--�����o�ϐ�--//
private:
	char key[KEY_MAX];
	bool keyTrg = false;

private:
	//�v���C���[�p
	void playerMoveY(OBJ2D* obj);			//Player�̏c�����ړ�
	void playerMoveX(OBJ2D* obj);			//Player�̉������ړ�
	void playerJump(OBJ2D* obj);			//Player��Jump����

	//�G�p
	void enemyMoveY(OBJ2D* obj);			//�G�̏c�����ړ�
	void enemyMoveX(OBJ2D* obj);			//�G�̉������ړ�

	//�G���A�`�F�b�N
	void areaCheck(OBJ2D* obj);

protected:
	ActorParam actorParam;					// ���L�̊e�֐������s����ۂɎg�p�����p�����[�^�Q

	//�v���C���[�p
	void playerMove(OBJ2D* obj);			//�v���C���[����
	
	//�G�p
	void enemyTurn(OBJ2D* obj);				//�R�ň����Ԃ��G
	void enemyFall(OBJ2D* obj);				//�R�ŗ�����G
	void enemyNoMove(OBJ2D* obj);			//�����Ȃ��G


	virtual void fixPos(OBJ2D* obj) = 0;	//���ꂼ���pivot�̍X�V(�}�b�v�`�b�v�̓����蔻��ȂǂɎg�p)

public:
	Actor();
};
