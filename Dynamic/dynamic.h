///////////////////////////////////////////////////////////////////////////////
// title:        "dynamic.h" ver 1.0
// description:  音源ごとに差異ある音量コントロールを変数１つでバランスよくできるインクルードファイル(2015/05/24)
// keywords:     SAKURA Function     by ななこっち★ @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// Example
// Include(dynamic.h)
// DynamicInit(80*128+127)
// E(127)
// o5cde
// ET(127,0,!2)
// fgab>c
///////////////////////////////////////////////////////////////////////////////
// Function DynamicInit(value)
// ダイナミック値を指定します。
// 値は、（音量幅）×128 + （ベース音量）になります。
// （音量幅、ベース音量共に0～127までとなります）
// 指定しないと、MSGS用の 80*128+127が指定されます。
///////////////////////////////////////////////////////////////////////////////
// Function E (Expression compatible)
// Usage : EW(vol)
// Example : 
// o5
// E(100)c VV(127)d E(80)e
///////////////////////////////////////////////////////////////////////////////
// Function VV (Velocity compatible)
// Usage : VV(vol)
// Example : 
// o5
// VV(100)c VV(127)d VV(80)e
///////////////////////////////////////////////////////////////////////////////
// Function EW (Expression.onNotewave compatible)
// Usage : EW(vol1, vol2, length, ... ) max 5 parms
// Example : 
// EW(127,0,!16)
// o5l8
// cdefgab>c
///////////////////////////////////////////////////////////////////////////////
// Function ET (Expression.onTime compatible)
// Usage : ET(vol1, vol2, length, ... ) max 5 parms
// Example : 
// ET(127,0,!1)
// o5l8
// cdefgab>c
///////////////////////////////////////////////////////////////////////////////

Int DYNAMIC=80*128+127

Function DynamicInit(Int value) {
	DYNAMIC=value
}

Function Dy(Int value) {
	Int D

	IF(DYNAMIC=0) {
		// for MSGS
		D=80*128+127

		// for TWM2
		IF(TWM2=1) {
			D=100*128+110
		} ELSE {
			// for TiMidity++ Default
			IF(TIMIDITY=1) {
				D=105*128+120
			}
		}
	} ELSE {
		D=DYNAMIC
	}

	Int Base = 127 - (D % 128)
	Int Dynamic = D / 128
	Int V
	Int V2

	V = value - Base
	V = 127 - V
	V = V * 10 * Dynamic
	V = V / 1000
	V = 127 - V
	IF(V<0) {
		V=0
	}
	IF(V>127) {
		V=127
	}
 	Result = V
}

// for verocity
Function VV(value) {
	Str MML="v"
	MML=MML+(ExpVol(value))
	MML
}

Function ExpVol(value) {
	RESULT=Dy(value)
}

Function ExpExp(value) {
	RESULT=Dy(value)
}

// for expression
Function E(value) {
	Expression(ExpExp(value))
}

// for expression.ontime
Function ET(v11, v12, len1, v21, v22, len2, v31, v32, len3, v41, v42, len4, v51, v52, len5) {
	Int	NowTime;
	NowTime = Time;
	Expression.onTime(ExpExp(v11), ExpExp(v12), len1)
	IF(v21<>0) {
		Time=NowTime+len1
		Expression.onTime(ExpExp(v21), ExpExp(v22), len2)
		IF(v31<>0) {
			Time=NowTime+len1+len2
			Expression.onTime(ExpExp(v31), ExpExp(v32), len3)
			IF(v41<>0) {
				Time=NowTime+len1+len2+len3
				Expression.onTime(ExpExp(v41), ExpExp(v42), len4)
				IF(v51<>0) {
					Time=NowTime+len1+len2+len3+len4
					Expression.onTime(ExpExp(v51), ExpExp(v52), len5)
				}
			}
		}
	}
	Time=NowTime
}

// for expression onnotewave
Function EW(v11, v12, len1, v21, v22, len2, v31, v32, len3, v41, v42, len4, v51, v52, len5) {
	IF(len5<>0) {
		Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1, ExpExp(v21), ExpExp(v22), len2, ExpExp(v31), ExpExp(v32), len3, ExpExp(v41), ExpExp(v42), len4, ExpExp(v51), ExpExp(v52), len5)
	} ELSE {
		IF(len4<>0) {
			Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1, ExpExp(v21), ExpExp(v22), len2, ExpExp(v31), ExpExp(v32), len3, ExpExp(v41), ExpExp(v42), len4)
		} ELSE {
			IF(len3<>0) {
				Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1, ExpExp(v21), ExpExp(v22), len2, ExpExp(v31), ExpExp(v32), len3)
			} ELSE {
				IF(len2<>0) {
					Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1, ExpExp(v21), ExpExp(v22), len2
					)
				} ELSE {
					IF(len1<>0) {
						Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1)
					}
				}
			}
		}
	}
}
