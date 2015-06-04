///////////////////////////////////////////////////////////////////////////////
// title:        "vibrate.h" ver 1.0
// description:  Modulation.onNoteWate wrapperインクルードファイル(2015/05/24)
// keywords:     SAKURA Function     by ななこっち★ @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// vibrate.h ディレイビブラート
///////////////////////////////////////////////////////////////////////////////
// Function Vibrate (onnotewave)
// Vibrate(delay time, depth, ...) max 5 parms.
//
// Example
// Vibrate(!16,100)
// Vibrate(0,100,!80,!8,100)
// Vibrate(!32,20,!8,100,!4,80,!4,60,!2,50)
///////////////////////////////////////////////////////////////////////////////
// テストする時は、以下のコメントを外してください。
// Int TEST=1
///////////////////////////////////////////////////////////////////////////////

Function Vibrate(delay1, depth1, delay2, depth2, delay3, depth3, delay4, depth4, delay5, depth5) {
	Int	NowTime;
	NowTime = Time;
	IF(delay5<>0) {
		Modulation.onNoteWave(0, depth1, delay1, depth1, depth2, delay2, depth2, depth3, delay3, depth3, depth4, delay4, depth4, depth5, delay5)
	} ELSE {
		IF(delay4<>0) {
			Modulation.onNoteWave(0, depth1, delay1, depth1, depth2, delay2, depth2, depth3, delay3, depth3, depth4, delay4)
		} ELSE {
			IF(delay3<>0) {
				Modulation.onNoteWave(0, depth1, delay1, depth1, depth2, delay2, depth2, depth3, delay3)
			} ELSE {
				IF(delay2<>0) {
					Modulation.onNoteWave(0, depth1, delay1, depth1, depth2, delay2)
				} ELSE {
					IF(delay1<>0) {
						Modulation.onNoteWave(0, depth1, delay1)
					}
				}
			}
		}
	}
}


IF(TEST=1) {
	Tempo 100
	@(Violin)
	o5l2q100
	Vibrate(!8,40,!16,70,!4,30)
	cdefgab>c1
	c<bagfedc1
}


