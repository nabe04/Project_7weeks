#include "generic.h"
#include "obj2d.h"
#include "algorithm.h"
#include "load_texture.h"

//コンストラクタ
OBJ2D::OBJ2D()
{
	scale = Vector2F{1,1};				//スケールが0のとき何も表示されないため
	color = Color4I{ 255,255,255,255 };	//不透明度が0のとき何も表示されないため
}


//移動
void OBJ2D::move()
{
	if (mvAlg)		mvAlg->move(this);			//移動アルゴリズムが存在すれば、moveメソッドを呼ぶ
	if (eraseAlg)	eraseAlg->erase(this);		//消去アルゴリズムが存在すれば、eraseメソッドを呼ぶ
}

//描画
void OBJ2D::draw()
{
	//--テクスチャ描画--//
	if (this->data != nullptr && category == TEXTURE)
	{
		if (existFrag)
		{
			//負透明度設定
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);
			SetDrawBright(color.r, color.g, color.b);
			
			int sprData = DerivationGraph(clipOrigin.x, clipOrigin.y, clipSize.x, clipSize.y, data[(animeState * chipWidth) + animeTimer]);
			
			//描画
			DrawRotaGraph3(
				pos.x, pos.y,
				texSize.x * 0.5f, texSize.y * 0.5f,
				scale.x, scale.y,
				angle,
				sprData,
				true,
				revFrag.x
				);

			DeleteGraph(sprData);

			//状態を戻す(この処理をしないと全体に負透明度が影響するため)
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, color.a);

#ifdef DEBUG_
			//デバック用文字列描画
			DrawFormatString(pos.x, pos.y, GetColor(255, 0, 0), "・", 3);
			DrawFormatString(pivot.x, pivot.y, GetColor(0, 255, 0), "・", 3);

			if (data == n_texture::sprCursorW)
			{
				DrawFormatString(0, 20, GetColor(0, 255, 0), "arrNo.y : %d", arrNo.y, 3);
			}
			if (data == n_texture::sprCursorH)
			{
				DrawFormatString(0, 0, GetColor(0, 255, 0), "arrNo.x : %d", arrNo.x, 3);
			}
				
#endif // DEBUG_

			}
	}

	//--フォント描画--//
	if (this->data != nullptr && category == FONT)
	{
		if (existFrag)
		{
			//負透明度設定
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);

			int fontData = CreateFontToHandle(loadData, fontSize, fontThick, DX_FONTTYPE_NORMAL);

			//描画
			DrawFormatStringToHandle(
				static_cast<int>(pos.x), static_cast<int>(pos.y),
				GetColor(color.r, color.g, color.b),
				fontData,
				text,
				dispNum
				);

			DeleteFontToHandle(fontData);

			//状態を戻す(この処理をしないと全体に負透明度が影響するため)
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>(color.a));
		}
	}
}


//--OBJ2DManagerクラス--//

//初期化
void OBJ2DManager::init()
{
	//リストのOBJ2Dをすべてクリアする
	objList.clear();
}

//リストへの追加(1:OBJ2D型のメンバポインタ 2:描画用に格納したデータ 3:OBJのposition)
OBJ2D* OBJ2DManager::add(MoveAlg* mvAlg,int* data, e_Category category, const Vector2F& pos, const Vector2F& size, char* loadData)
{
	OBJ2D obj;											//OBJ2Dを宣言する
	obj.mvAlg	 = mvAlg;								//mvAlgに引数のmvAlgを代入
	obj.pos		 = pos;									//posに引数のposを代入
	obj.texSize  = size;
	obj.size     = { size.x * 0.5f,size.y * 0.5f };		//sizeに引数のsizeの半分を代入(判定などに使うときに使いやすくするため)
	obj.scale	 = Vector2F{ 1, 1 };					//スケールは等倍
	obj.color	 = Color4I{ 255,255,255,255 };			//色は原色(不透明度255 = 不透明度Max)
	obj.data	 = data;								//Data格納
	obj.category = category;							//種類選別(この種類で描画方法が変わる)
	obj.clipSize = { static_cast<int>(size.x),static_cast<int>(size.y) };					//はじめは全体を切り抜くようにする(全体が表示される)
	obj.loadData = loadData;

	objList.push_back(obj);								//リストにobjを追加する
	return &(*objList.rbegin());						//今追加したobjのアドレスを返す(何かで使えるように)
}

//更新
void OBJ2DManager::update()
{
	//移動
	for (auto& it : objList)		//objListのすべての要素をループし、itという名前で各要素にアクセス
	{
		it.move();					//itのmoveメソッドを呼ぶ
	}

	//空ノードの削除
	auto it = objList.begin();
	while (it != objList.end())
	{
		if (it->mvAlg)
		{
			it++;
		}
		else
		{
			it = objList.erase(it);
		}
	}
}

//描画
void OBJ2DManager::draw()
{
	for (auto& it : objList)		//objListの全ての要素をループし、itという名前で各要素にアクセス
	{
		it.draw();					//itのdrawメソッドを呼ぶ
	}
}

//デストラクタ
OBJ2DManager::~OBJ2DManager()
{
	//リストのOBJ2Dを全てクリアする
	objList.clear();
}
