//========================================================================================
//		File        : Object2Dsub.cpp
//		Program     : 2Dオブジェクトベースの拡張
//
//		Description : Updateの実装（主に重力的な）
//			
//
//		History     : 2015/5/6	作成開始
//
//																Author : きんたまズ
//========================================================================================


//――――――――――――――――――――――――――――――――――――――――――――
// インクルード
//――――――――――――――――――――――――――――――――――――――――――――
#include "../../h/System/PreInclude.h"
#
#include <math.h>
#include "../../h/Object/Object2Dsub.h"

//========================================================================================
// public:
//========================================================================================
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : コンストラクタ
//	Arguments   : None.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CObject2Dsub::CObject2Dsub()
{
	m_nPhase = 0;

	m_fGAccel = 0.0f;
	m_fGravity = GRAVITY_ZERO;	// 重力

	m_pTimer = &CTimer::GetInstance();
	m_fLastTime = m_pTimer->GetTime();
	m_bAnimeInit = false;

	m_accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : Update
//	Arguments   : None.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CObject2Dsub::Update()
{
	CObject2D::Update();
	// 重力を付ける(くっそ適当)
	if (m_fGravity != GRAVITY_ZERO){
		m_fGAccel += m_fGravity;		// 落下速度を上げてく
		m_pos.y -= m_fGAccel;
	}
	else{
		m_fGAccel = 0.0f;				// 落下速度を0に
	}

	// 位置を反映
	Translate(m_pos);
	// 拡大率を反映
	Scale(m_scale);
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : SetGravity
//	Arguments   : 重力.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CObject2Dsub::SetGravity(float g)
{
	m_fGravity = g;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : 秒数ごとのアニメ
//	Description : アニメーしょん
//	Arguments   : 最初の参照番号、最後の参照番号、アニメーション間隔（秒）
//	Returns     : ないよ
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CObject2Dsub::TimeAnimation(int minNo, int maxNo,int width,int height, float time)
{
	// 経過フレーム数を取得
	int cnt = m_pTimer->Run();

	// 経過フレーム数分の処理を実行
	for (int i = 0; i < cnt; ++i)
	{
		if (m_pTimer->GetTime() - m_fLastTime >= time)	// 秒ごとに描画
		{
			m_fLastTime = m_pTimer->GetTime();		// タイマ値を更新
			m_nCurrentFrame++;
			if (m_nCurrentFrame > maxNo)
				m_nCurrentFrame = minNo;
		}
	}
	UVDivision(m_nCurrentFrame, width, height);
}
//========================================================================================
//	End of File
//========================================================================================