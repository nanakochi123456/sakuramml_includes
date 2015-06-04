///////////////////////////////////////////////////////////////////////////////
// title:        "rchord.h" ver 1.01
// description:  和音を下からランダムなタイミングで演奏するインクルードファイル(2015/05/24)
// keywords:     SAKURA Function     by ななこっち★ @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// rchord.h 和音をランダムなタイミングで演奏する
///////////////////////////////////////////////////////////////////////////////
// Function RCDINIT(min, value)
// 乱数値の最小値、最大値を設定する。両方0にすると、同一タイミングで演奏します。
//
// Function RCD(mml)
// ランダムに演奏したい和音のMMLを入力する
///////////////////////////////////////////////////////////////////////////////
// Example
// Include(rchord.h)
// RCDINIT(53,513)
// l4 RCD(ceg)
// l8 RCD(<b>fg)
// l8 RCD(ceg)
///////////////////////////////////////////////////////////////////////////////
// テストする場合、コメントアウトを消して下さい。
//Int TEST=1
///////////////////////////////////////////////////////////////////////////////

Int RCD_MIN=192
Int RCD_MAX=768

Function RCDINIT(Int MIN, Int MAX) {
	RCD_MIN=MIN
	RCD_MAX=MAX
}

Function RCD(Str MML) {
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
		IF(DEBUG=1||TEST=1) {
			Print("Count "+ C + " Str="+M)
		}
		IF(M="a"||M="b"||M="c"||M="d"||M="e"||M="f"||M="g") {
		C++
	  	IF(C<2) {
			FIRST=ML
			ML=FM+M
			FM=""
		} ELSE {
				BUF=BUF+"Sub" + CHR(123)+R+ML+CHR(125)
				IF(RCD_MAX>0) {
					R=R+"r"+Random(RCD_MIN, RCD_MAX)
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
	IF(DEBUG=1 || TEST=1) {
		Print(BUF)
	}
	BUF
}

IF(TEST=1) {
	TR(1)
		Tempo 50
		l4
		RCDINIT(32,40)
		l4 RCD(ceg)
		l8 RCD(<b>fg)
		l8 RCD(ceg)

		RCDINIT(96,425)
		l4 RCD(ceg)
		l8 RCD(<b>fg)
		l8 RCD(ceg)

		RCDINIT(193,765)
		l4 RCD(ceg)
		l8 RCD(<b>fg)
		l8 RCD(ceg)

		RCDINIT(0,0)
		l4 RCD(ceg)
		l8 RCD(<b>fg)
		l8 RCD(ceg)
}
