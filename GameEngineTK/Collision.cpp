/// <summary>
/// 衝突判定ライブラリ
/// </summary>
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 球と球の当たり判定
/// </summary>
/// <param name="_sphereA">球A</param>
/// <param name="_sphereB">球B</param>
/// <returns>true:ヒット	false:ヒットせず</returns>
bool CheckSphere2Sphere(const Sphere& _sphereA, const Sphere& _sphereB)
{
	// 球AとBの中心座標の差を計算する
	Vector3 sub = _sphereB._center - _sphereA._center;

	float distanceSquare;

	// 三平方の定理
	distanceSquare = sqrt(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);

	float radiusSquare;

	radiusSquare = _sphereA._radius + _sphereB._radius;

	radiusSquare = radiusSquare * radiusSquare;

	// 距離が半径の和より大きければ当たっていない
	if (distanceSquare > radiusSquare)
	{
		return false;
	}
	return true;
}

/// <summary>
/// 三点の座標から三角形を計算(反時計回りに頂点をして地)
/// </summary>
/// <param name="_p0">点0</param>
/// <param name="_p1">点1</param>
/// <param name="_p2">点2</param>
/// <param name="_triangle">三角形(結果出力用)</param>
void ComputeTriangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, Triangle* _triangle)
{
	// 座標をコピー
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	// 法線ベクトルを計算
	Vector3 P0_P1 = _p1 - _p0;
	Vector3 P1_P2 = _p2 - _p1;

	// 外積で2ベクトルに垂直なベクトルを算出
	_triangle->Normal = P0_P1.Cross(P1_P2);
	_triangle->Normal.Normalize();
}

/// <summary>
/// 点と法線付き三角形の最近接点
/// </summary>
/// <param name="_point">点</param>
/// <param name="_tri">三角形</param>
/// <param name="_closest">最近接点(出力)</param>
void ClosestPtPoint2Triangle(const Vector3& _point, const Triangle& _tri, Vector3* _closest)
{
	// _pointがP0の外側の頂点領域の中にあるかチェック
	Vector3 P0_P1 = _tri.P1 - _tri.P0;
	Vector3 P0_P2 = _tri.P2 - _tri.P0;
	Vector3 P0_PT = _point - _tri.P0;

	float d1 = P0_P1.Dot(P0_PT);
	float d2 = P0_P2.Dot(P0_PT);

	if (d1 <= 0.0f && d2 <=0.0f)
	{
		// P0が一番近い
		*_closest = _tri.P0;
		return;
	}

	// _pointがP1の外側の頂点領域の中にあるかチェック
	Vector3 P1_PT = _point - _tri.P1;

	float d3 = P0_P1.Dot(P1_PT);
	float d4 = P0_P2.Dot(P1_PT);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// P1が一番近い
		*_closest = _tri.P1;
		return;
	}

	// _pointがP0_P1の辺領域の中にあるかどうかチェックし、あれば_pointのP0_P1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*_closest = _tri.P0 + v * P0_P1;
		return;
	}

	// _pointがP2の外側の頂点領域の中にあるかどうかチェック
	Vector3 P2_PT = _point - _tri.P2;

	float d5 = P0_P1.Dot(P2_PT);
	float d6 = P0_P2.Dot(P2_PT);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*_closest = _tri.P2;
		return;
	}

	// _pointがP0_P2の辺領域の中にあるかどうかチェックし、あれば_pointのP0_P2上に対する射影を返す
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*_closest = _tri.P0 + w * P0_P2;
		return;
	}

	// _pointがP1_P2の辺領域の中にあるかどうかチェックし、あれば_pointのP1_P2上に対する射影を返す
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*_closest = _tri.P1 + w * (_tri.P2 - _tri.P1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*_closest = _tri.P0 + P0_P1 * v + P0_P2 * w;
}

// 三角形と点の当たり判定
bool CheckPoint2Triangle(const Vector3& _point, const Triangle& _triangle)
{
	//点と三角形は同一平面上にあるものとしています。同一平面上に無い場合は正しい結果になりません
	//線上は外とみなします。
	//ABCが三角形かどうかのチェックは省略...

	// 点0→1、 1→2、 2→0 のベクトルをそれぞれ計算
	Vector3 v01 = _triangle.P1 - _triangle.P0;
	Vector3 v12 = _triangle.P2 - _triangle.P1;
	Vector3 v20 = _triangle.P0 - _triangle.P2;
	// 三角形の各頂点から点へのベクトルをそれぞれ計算
	Vector3 v0p = _point - _triangle.P0;
	Vector3 v1p = _point - _triangle.P1;
	Vector3 v2p = _point - _triangle.P2;
	// 各辺ベクトルと、点へのベクトルの外積を計算
	Vector3 c0 = v01.Cross(v0p);
	Vector3 c1 = v12.Cross(v1p);
	Vector3 c2 = v20.Cross(v2p);
	// 内積で同じ方向かどうか調べる
	float dot01 = c0.Dot(c1);
	float dot02 = c0.Dot(c2);
	// 外積ベクトルが全て同じ方向なら、三角形の内側に点がある
	if (dot01 > 0 && dot02 > 0)
	{
		return true;
	}

	//三角形の外側に点がある
	return false;

}

/// <summary>
/// 球と法線付き三角形の当たりチェック
/// </summary>
/// <param name="_sphere">球</param>
/// <param name="_tri">三角形</param>
/// <param name="_inter">交点座標(出力)</param>
/// <returns></returns>
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _tri, Vector3* _inter)
{
	Vector3 p;

	// 球の中心に一番近い点である三角形にある点pを見つける
	ClosestPtPoint2Triangle(_sphere._center, _tri, &p);

	Vector3 v = p - _sphere._center;

	// 球と三角形が交差するのは、球の中心から点pまでの距離が球の半径よりも小さい場合
	if (v.Dot(v) <= _sphere._radius * _sphere._radius)
	{
		if (_inter)
		{
			*_inter = p;
		}

		return true;
	}

	return false;

	// 球と平面（三角形が乗っている平面）の当たり判定
	// 球と平面の距離を計算
	float ds = _sphere._center.Dot(_tri.Normal);
	float dt = _tri.P0.Dot(_tri.Normal);
	float dist = ds - dt;
	// 距離が半径以上なら、当たらない
	if (fabsf(dist) > _sphere._radius)	return false;
	// 中心点を平面に射影したとき、三角形の内側にあれば、当たっている
	// 射影した座標
	Vector3 center = -dist * _tri.Normal + _sphere._center;

	// 三角形の外側になければ、当たっていない
	if (!CheckPoint2Triangle(center, _tri))	return false;

	if (_inter)
	{
		*_inter = center;	// 交点をコピー
	}

	return true;
}
bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, Vector3 *_inter)
{
	const float epsilon = -1.0e-5f;	// 誤差吸収用の微小な値
	Vector3 	LayV;		// 線分の終点→始点
	Vector3 	tls;		// 三角形の頂点0→線分の始点
	Vector3 	tle;		// 三角形の頂点0→線分の終点
	float 	distl0;
	float 	distl1;
	float 	dp;
	float 	denom;
	float 	t;
	Vector3	s;			// 直線と平面との交点
	Vector3 	st0;		// 交点→三角形の頂点0
	Vector3 	st1;		// 交点→三角形の頂点1
	Vector3 	st2;		// 交点→三角形の頂点2
	Vector3 	t01;		// 三角形の頂点0→頂点1
	Vector3 	t12;		// 三角形の頂点1→頂点2
	Vector3 	t20;		// 三角形の頂点2→頂点0
	Vector3	m;

	// 線分の始点が三角系の裏側にあれば、当たらない
	tls = _segment.Start - _triangle.P0;
	distl0 = tls.Dot(_triangle.Normal);	// 線分の始点と平面の距離
	if (distl0 <= epsilon) return false;

	// 線分の終点が三角系の表側にあれば、当たらない
	tle = _segment.End - _triangle.P0;
	distl1 = tle.Dot(_triangle.Normal);	// 線分の終点と平面の距離
	if (distl1 >= -epsilon) return false;

	// 直線と平面との交点sを取る
	denom = distl0 - distl1;
	t = distl0 / denom;
	LayV = _segment.End - _segment.Start;	// 線分の方向ベクトルを取得
	s = t * LayV + _segment.Start;

	// 交点が三角形の内側にあるかどうかを調べる。
	// 三角形の内側にある場合、交点から各頂点へのベクトルと各辺ベクトルの外積（三組）が、全て法線と同じ方向を向く
	// 一つでも方向が一致しなければ、当たらない。
	st0 = _triangle.P0 - s;
	t01 = _triangle.P1 - _triangle.P0;
	m = st0.Cross(t01);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	st1 = _triangle.P1 - s;
	t12 = _triangle.P2 - _triangle.P1;
	m = st1.Cross(t12);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	st2 = _triangle.P2 - s;
	t20 = _triangle.P0 - _triangle.P2;
	m = st2.Cross(t20);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	if (_inter)
	{
		*_inter = s;	// 交点をコピー
	}

	return true;
}