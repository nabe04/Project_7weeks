#pragma once

#define CURSOR_W			(256)
#define CURSOR_H			(320)
#define CURSOR_CHIP_SIZE	(64)

#define CURSOR_SIZE			(64)
#define CURSOR_CHIP_NUM		(4)
#define CURSOR_CHIP_W		(4)
#define CURSOR_CHIP_H		(1)

#define LINE_WIDTH			(320)
#define LINE_HEIGHT			(64)

//�v���C���[ 1
class Cursor_1 :public MoveAlg
{
private:
	bool keyTrg = false;

public:
			Vector2I cursorNo = {};					//���݂̃J�[�\��������ʒu
	 static Vector2I cursorCenterPos;

public:
	//�J�[�\���p
	void cursorMoveY(OBJ2D* obj);			//�J�[�\���̏c�ړ�
	void cursorMoveX(OBJ2D* obj);			//�J�[�\���̉��ړ�
};

//�v���C���[ 2
class Cursor_2 :public MoveAlg
{
private:
	bool keyTrg = false;

public:
	Vector2I cursorNo = {};					//���݂̃J�[�\��������ʒu
	static Vector2I cursorCenterPos;

public:
	//�J�[�\���p
	void cursorMoveY(OBJ2D* obj);			//�J�[�\���̏c�ړ�
	void cursorMoveX(OBJ2D* obj);			//�J�[�\���̉��ړ�
};


class CursorH :public Cursor_1
{
	void move(OBJ2D* obj);
	void fixPos(OBJ2D* obj);
};

class CursorW :public Cursor_1
{
	void move(OBJ2D* obj);
	void fixPos(OBJ2D* obj);
};

class CursorPivot : public Cursor_1
{
	void move(OBJ2D* obj);
	void fixPos(OBJ2D* obj);
};

class CursorCenter :public Cursor_1
{
	void move(OBJ2D* obj);
	void fixPos(OBJ2D* obj);
};

extern CursorH cursorH;
extern CursorW cursorW;
extern CursorPivot cursorPivot;
extern CursorCenter cursorCenter;

class EraseCursor :public EraseAlg
{
	void erase(OBJ2D* obj);
};

class CursorManager :public OBJ2DManager
{
private:

public:

};