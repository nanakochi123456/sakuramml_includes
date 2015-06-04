///////////////////////////////////////////////////////////////////////////////
// title:        "tempo.h" ver 1.1
// description:  TempoChange非互換高機能テンポチェンジ機能インクルードファイル(2015/05/28)
// keywords:     SAKURA Function     by ななこっち★ @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// tempo.h デバッグ機能付きテンポチェンジ
// （サクラに TempoChange がありますが、その高機能版です）
//
// Include前に、以下の変数を定義して下さい。
//
// ・Int DEBUG=0 // 1 でメトロノームがなります、2 でテンポチェンジ時にうるさい雑音が鳴ります
// 　（メトロノームは10000小節で終了します、4/4 を前提に作成されています。）
//
// ・Int TEMPORATIO
// 　ベーステンポの割合を％で設定します。（100がデフォルト。）
//
// ・Int TEMPODIFF
// 　ベーステンポを設定して、外部よりテンポを制御したい場合、TEMPODIFF に 整数値 (-～+)を設定します。
//
// ・Int IGNORETEMPO
// 　IGNORETEMPO=1 にすると、テンポチェンジを無効にします。
//
// #METORONOMEMML
// 　メトロノームのリズムMMLを設定できます。3拍子にする時等使用します。
// 　(M=表拍、m=裏拍)
//
//  ※テンポチェンジは、専用のトラックを作成することをお勧めします。
///////////////////////////////////////////////////////////////////////////////
// Function TmpChange(tempo, len)
// テンポをチェンジします。
// 前のテンポは自動的に読み込まれます
// 即時チェンジする場合には、lenを 0 にします。
// それ以外は、!2 !4. 等を指定します。
//
// Function TmpChangeR(tempo, len)
// テンポをチェンジして、len分の休符を置きます。
///////////////////////////////////////////////////////////////////////////////
// テストするときは、以下のコメントを全て外してください。
//Int TEST=1
//Int DEBUG
//Int TEMPORATIO=100
//Int IGNORETEMPO=0
//Int TEMPODIFF=0
///////////////////////////////////////////////////////////////////////////////

//#METORONOMEMML={M4m4m4}

IF(#METORONOMEMML="") {
	#METORONOMEMML={M4m4m4m4}
}

IF(TEST=1) {
	DEBUG=2
	Tempo 200
}

IF(DEBUG>=1) {
	IF(DEBUG=2) {
		#DEBUGMML1={Sub{@1v90V(127)'v90o5do6fo7a#o8d'}}
		#DEBUGMML2={Sub{@1v90V(127)'v90o5co6eo7g#o8c'}}
		#DEBUGMML3={Sub{@1v127V(127)'v127o4cdefgabo6cdefgab'}}
	}
	TR(10)
		$M{n(MetronomeBell),}
		$m{n(MetronomeClick),}
		[10000
			Rythm{#METORONOMEMML}
		]
}
Function TmpChangeR(tempo, len) {
	TmpChange(tempo, len)
	r%(len)
}

Function TmpChange(tempo, len) {
	IF(len=0) {
		IF(DEBUG=2) {
			#DEBUGMML1
		}
	} ELSE {
		IF(DEBUG=2) {
			#DEBUGMML2
		}
	}

	IF(len=0) {
		IF(!(IGNORETEMPO<>1)) {
			IF(TEMPORATIO=0) {
				Tempo=tempo+TEMPODIFF
			} ELSE {
				Tempo=(tempo*TEMPORATIO)/100+TEMPODIFF
			}
		}
	} ELSE {
		IF(!(IGNORETEMPO<>1)) {
			Int TT1=Tempo
			Int TT2
			IF(TEMPORATIO=0) {
				TT2=tempo+TEMPODIFF
			} ELSE {
				TT2=(tempo*TEMPORATIO)/100+TEMPODIFF
			}
			Int TTDIFF=(TT2 - TT1)
			Int TTSTEP=TTDIFF
			IF(TTSTEP < 0) {
				TTSTEP=-TTDIFF
			}
			Int TTR=len / TTSTEP
			For(Int I=1; I < TTSTEP; I++) {
				Sub {
					r%(I*TTR)
					IF(TTDIFF < 0) {
						TT1 = TT1 - 1;
					} ELSE {
						TT1 = TT1 + 1;
					}
					Tempo = TT1;
				}
			}
			Sub{
				r%(len)
				IF(TEMPORATIO=0) {
					Tempo=tempo+TEMPODIFF
				} ELSE {
					Tempo=tempo*TEMPORATIO/100+TEMPODIFF
				}
			}
		}
	}
}

IF(TEST=1) {
	TR(1)
		TmpChange(100,0)
		o5l8cdefgfed
		TmpChange(120,!2)
		o5l8cdefgfed
		TmpChange(160,!2)
		o5l8cdefgfed
		TmpChange(80,!2)
		o5l8cdefgfed
		TmpChange(50,!2)
		o5l8cdefgfed
		TmpChange(160,!4)
		o5l8cdefgfed
		TmpChange(50,!2)
		o5l8cdefgfedc1
}
