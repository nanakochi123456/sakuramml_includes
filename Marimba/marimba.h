///////////////////////////////////////////////////////////////////////////////
// title:        "marimba.h" ver 0.1
// description:  マリンバ記述用インクルードファイル(2015/05/24)
// keywords:     SAKURA Function     by ななこっち★ @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// marimba.h マリンバ記述用関数
///////////////////////////////////////////////////////////////////////////////
// Function MRINIT(len, min, value)
// マリンバの繰り返す速度、乱数値の最小値、最大値を設定する。両方0にすると、同一タイミングで演奏します。
//
// Function MR(mml1, mml2, len)
// mml1 -> mml2 -> mml1-> ... のように、len長さ分だけ演奏する
///////////////////////////////////////////////////////////////////////////////
// Example
// Include(marimba.h)
// MRINIT(53,513)
// l4 MR(ceg)
// l8 MR(<b>fg)
// l8 MR(ceg)
///////////////////////////////////////////////////////////////////////////////
// テストする場合、コメントアウトを消して下さい。
//Int TEST=1
///////////////////////////////////////////////////////////////////////////////

Int MR_LEN=!16
Int MR_Q=85
Int MR_MIN=192
Int MR_MAX=768
Int MR_INITVOL=100
Int MR_VOL=100
Int MR_CRESC=0

// マリンバ初期化
Function MRINIT(Int LEN, Int Q, Int MIN, Int MAX) {
	MR_LEN=LEN
	MR_Q=Q
	MR_MIN=MIN
	MR_MAX=MAX
}

// マリンバの両手別のクレッシェンド
Function MRCresc(Int VOL, Int Offset) {
	MR_INITVOL=VOL
	MR_CRESC=Offset
}

// マリンバの両手同時、rchord.h RCDと同じ関数
Function MCD(Str MML) {
	Str BUF=""
	Str FIRST=""
	Str ML=""
	Str M
	Str R
	Str FM
	Int C=0

	BUF=""
	R=""

	For(Int i=1; MID(MML, i, 1)!=""; i++) {
		M=MID(MML, i, 1)
		IF(M="a"||M="b"||M="c"||M="d"||M="e"||M="f"||M="g") {
		C++
	  	IF(C<2) {
			FIRST=ML
			ML=FM+M
			FM=""
		} ELSE {
				BUF=BUF+"Sub" + CHR(123)+R+ML+CHR(125)
				IF(MR_MAX>0) {
					R=R+"r"+Random(MR_MIN, MR_MAX)
				}
				ML=M
		}
		} ELSE {
		IF(C>0) {
				ML=ML+M
		} ELSE {
			FM=FM+M
		}
		}
	}
	BUF=BUF+"Sub"+CHR(123)+R+ML+CHR(125)+FIRST+"r"
	BUF
}

// マリンバの両手別
Function MR(Str MML1, Str MML2, Int Len) {
	Str MML="Sub"+CHR(123)
	Str BUF1=""
	Str BUF2=""
	Str FIRST1=""
	Str FIRST2=""
	Str ML1=""
	Str ML2=""
	Str M
	Str R
	Str FM1
	Str FM2
	Int C=0

	MR_VOL=MR_INITVOL
	MML=MML+"v"+MR_VOL
	For (Int i=0; i <= (Len / MR_LEN / 2) * MR_Q / 100; i++) {
		BUF1=""
		BUF2=""
		FIRST1=""
		FIRST2=""
		ML1=""
		ML2=""
		
		R=""
		C=0
		For(Int i=1; MID(MML1, i, 1)!=""; i++) {
			M=MID(MML1, i, 1)
			IF(M="a"||M="b"||M="c"||M="d"||M="e"||M="f"||M="g") {
			C++
		  	IF(C<2) {
				FIRST1=ML1
				ML1=FM1+M
				FM1=""
			} ELSE {
					BUF1=BUF1+"Sub" + CHR(123)+R+ML1+CHR(125)
					IF(MR_MAX>0) {
						R=R+"r"+Random(MR_MIN, MR_MAX)
					}
					ML1=M
			}
			} ELSE {
			IF(C>0) {
					ML1=ML1+M
			} ELSE {
				FM1=FM1+M
			}
			}
		}
		BUF1=BUF1+"Sub"+CHR(123)+R+ML1+CHR(125)+FIRST1+"r%"+MR_LEN
		R=""
		C=0
		For(Int i=1; MID(MML2, i, 1)!=""; i++) {
			M=MID(MML2, i, 1)
			IF(M="a"||M="b"||M="c"||M="d"||M="e"||M="f"||M="g") {
				C++
		  		IF(C<2) {
					FIRST2=ML2
					ML2=FM2+M
					FM2=""
				} ELSE {
					BUF2=BUF2+"Sub" + CHR(123)+R+ML1+CHR(125)
					IF(MR_MAX>0) {
						R=R+"r"+Random(MR_MIN, MR_MAX)
					}
					ML2=M
				}
			} ELSE {
				ML2=ML2+M
			}
		}
		BUF2=BUF2+"Sub"+CHR(123)+FIRST2+R+ML2+CHR(125)+"r%"+MR_LEN

		MML=MML+BUF1
		MR_VOL=MR_VOL+MR_CRESC
		MML=MML+"v"+MR_VOL

		MML=MML+BUF2
		MR_VOL=MR_VOL+MR_CRESC
		MML=MML+"v"+MR_VOL

		MML=MML+" "
	}
	MML=MML+CHR(125)+"r%"+Len

	MR_VOL=MR_INITVOL
	MML=MML+"v"+MR_VOL
	MML
}

IF(TEST=1) {
	曲名{"輝き"}
	作者{"きょういちｗ　Arranged by ななこっち★"}

	// メロディー
	TR(1)
		v110
		音色(Marimba)
		MRINIT(!24, 70, 250,460)
		MRCresc(110,-5)
		l8
		[
			MCD(e>e<) MCD(g>g<) MCD(f>f<) MCD(e>e<)
			MCD(d>d<) MCD(f>f<) MCD(e>e<) MCD(d>d<)
			MR("ce",">c<",!4) MR("df",">d<",!4)
			MR("eg",">e<",!4.) r8

			MCD(e>e<) MCD(g>g<) MCD(f>f<) MCD(e>e<)
			MCD(d>d<) MCD(f>f<) MCD(e>e<) MCD(d>d<)
			MR("ce",">e<",!4) MR("fa",">a<",!4)
			MR("eg",">g<",!4.) r8
		]

		MRINIT(!24, 80, 250,460)
		r MCD(g>g<) > MCD(c>c<) < MCD(b>b<)
		MR("fa",">fa<",!4.) r8

		r MCD(f>f<) MCD(b>b<) MCD(a>a<)
		MR("eg",">eg<",!4.) r8

		r MCD(e>e<) MCD(a>a<) MCD(g>g<)
		MR("df",">df<",!4.) r8

		r MCD(d>d<) MCD(g>g<) MCD(f>f<)
		MR("ce",">ce<",!4.) r8

		[
			r MCD(g>g<) > MCD(c>c<) < MCD(b>b<)
			MR("fa",">fa<",!4.) r8
		]

		r MCD(g>g<) > MCD(c>c<) < MCD(b>b<)
		MR("fa",">fa<",!4) MCD(g>g<) MCD(f>f<)
		MR("e",">e<",!4) MR("d",">d<",!4)
		[3
			MR("ce",">c<",!2)
		]

	// チェロピチカート
	TR(8)
		音色(PizzicatoStrings)
		l8
		o4v70
		[
			rg MCD(>ce<)g
			rg MCD(b>f<)g
			rg MCD(b>f<)g
			rg MCD(>ce<)g

			rg MCD(>ce<)g
			rg MCD(b>f<)g
			rg MCD(>cf<)a
			rg MCD(>ce<)g
		]

		rg MCD(>ce<)g
		ra MCD(>cf<)a
		rb MCD(>df<)b
		rg MCD(b>e<)g
		ra MCD(>ce<)a
		ra MCD(>df<)a
		rg MCD(b>f<)g
		rg MCD(>ce<)g

		[3
			rg MCD(>ce<)g
			ra MCD(>cf<)a
		]
		rg MCD(b>f<)g
		音色(Cello)
		v60
		q90
		Expression.onNoteWave(127,30,!1)
		[2 l2 MCD(g>ce<)]
		l1 MCD(g>ce<)

	// コントラバス
	TR(9)
		音色(Strings1)
		q30v95
		o3
		l4
		[
			crgr
			c4g4c2
			crgr
			c4f4cr
		]

		cr
		fr<
		br>
		er<
		ar>
		dr<
		gr>
		cr

		cr
		fr
		cr
		fr
		cr
		fr
		g<g>
		q90
		Expression.onNoteWave(127,60,!2.)
		c2c2c1

	// 以下オリジナル

	IF(0){
	音色(GrandPiano)　
	テンポ１１０
	音量１１０　
	音階５　
	音符４

	ミソファミ
	ッファミレ
	ドーレー
	ミーーッ
	ミソファミ
	ッファミレ
	ミーラー
	ソーーッ

	ミソファミ
	ッファミレ
	ドーレー
	ミーーッ
	ミソファミ
	ッファミレ
	ミーラー
	ソーーッ

	ッソ↑ド↓シ
	ラーーッ
	ッソ↑ド↓シ
	ラーーッ
	ッソ↑ド↓シ
	ラーソファ
	ミーファー
	ソーーッ

	ッソ↑ド↓シ
	ラーーッ
	ッソ↑ド↓シ
	ラーーッ
	ッソ↑ド↓シ
	ラーソファ
	ミーファー
	ソーーッ

	}
}

