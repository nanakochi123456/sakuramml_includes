///////////////////////////////////////////////////////////////////////////////
// title:        "rmelody.h" ver 0.24
// description:  �P���������_���ȉ��ʂƃ^�C�~���O�ŉ��t����C���N���[�h�t�@�C��(2015/05/25)
// keywords:     SAKURA Function     by �ȂȂ������� @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// rmelody.h �����f�B�[���������_���ȃ^�C�~���O�ŉ��t����
///////////////////////////////////////////////////////////////////////////////
// Function RMDINIT(rmin, rmax, vmin, vmax)
// �x�������l�̍ŏ��l�A�ő�l�A�ŏ��A�ő剹�ʐݒ肷��B����0�ɂ���ƁA����^�C�~���O�ŉ��t���܂��B
// 
// Function RMDR(rmin, rmax)
// �x�������l�̍ŏ��l�A�ő�l�̐ݒ�݂̂���
//
// Function RNDV(rmin, rmax)
// ���ʗ����l�̍ŏ��l�A�ő�l�̐ݒ�݂̂���B
// ����̒l��ݒ�𗼕��ɍs���ƁA�Œ艹�ʂƂȂ�B
// rmax���ȗ�����ƁArmin�Armax���ɉ��Z�A�܂��͌��Z���s�Ȃ�
//
// rmin, rmax�͗^����x���l�Avmin, vmax�͗^���鉹�ʒl
// Function RMD(mml)
// �����_���ɉ��t�����������f�B�[��MML����͂���
///////////////////////////////////////////////////////////////////////////////
// Example
// Include(rchord.h)
// RMDINIT(53,513,90,110)
// l4 RMD(ceg)
// RMDV(5)
// l8 RMD(<b>fg)
// RMDV(-5)
// l8 RMD(ceg)
///////////////////////////////////////////////////////////////////////////////
// �e�X�g����ꍇ�A�R�����g�A�E�g�������Ă��������B
//Int TEST=1
///////////////////////////////////////////////////////////////////////////////

Int RMD_RMIN=192
Int RMD_RMAX=768
Int RMD_VMIN=95
Int RMD_VMAX=100
Int RMD_CRESC=0

Function RMDINIT(Int RMIN, Int RMAX, Int VMIN, Int VMAX) {
	RMD_RMIN=RMIN
	RMD_RMAX=RMAX
	RMD_VMIN=VMIN
	RMD_VMAX=VMAX
	RMD_CRESC=0
}

Function RMDCresc(Str STEP) {
	RMD_CRESC=STEP
}

Function RMDR(Int RMIN, Int RMAX) {
	RMD_RMIN=RMIN
	RMD_RMAX=RMAX
}

Function RMDV(Int VMIN, Int VMAX) {
	IF(VMAX=0) {
		Int TMPMIN=RMD_VMIN
		Int TMPMAX=RMD_VMAX
		TMPMIN=TMPMIN+VMIN
		TMPMAX=TMPMAX+VMIN
		IF(TMPMIN < 0) {
			TMPMIN=0
		}
		IF(TMPMIN > 127) {
			TMPMAX=127
		}
		IF(TMPMAX < 0) {
			TMPMAX=0
		}
		IF(TMPMAX > 127) {
			TMPMAX=127
		}
		RMD_VMIN=TMPMIN
		RMD_VMAX=TMPMAX
	} ELSE {
		RMD_VMIN=VMIN
		RMD_VMAX=VMAX
	}
}

Function RMD(Str MML) {
	Str BUF=""
	Str FIRST=""
	Str ML=""
	Str M
	Str R
	Str VL
	Str RRMML
	Str RMML
	Str FM=""
	Int C=0
	Str LenStr
	Int TOKEN=0
	Int TO=0
	BUF=""
	R=""
	For(Int i=1; MID(MML, i, 1)!=""; i++) {
		M=MID(MML, i, 1)
//		Print("Start Str="+M)
		IF((ASC(M)>=48 && ASC(M)<=57) || M="r"||M="."||M="^") {
			IF(TO>=1) {
				LenStr=LenStr+M
//Print("LenADD:"+LenStr)
			}
			ML=ML+M
		} ELSE {
			IF((ASC(M)>=97 && ASC(M)<=103)) {
//Print("Note:"+M)
				TOKEN++
				TO=1
				FM=RRMML+VL+ML+RMML
				IF(TOKEN>1) {
					C++
					IF(FM!="") {
						BUF=BUF+"Sub{"+FM+"}r"+LenStr
					}
//					TO=0
					TOKEN=0
				} ELSE {
					BUF=BUF+ML
				}
				LenStr=""
				ML=M
				IF(RMD_RMAX>0) {
					R=Random(RMD_RMIN, RMD_RMAX)
					IF(Random(0,10)<5) {
						RRMML="r-"+R
						RMML="r"+R
					} ELSE {
						RRMML="r"+R
						RMML="r-"+R
					}
				}
				VL="v"+Random(RMD_VMIN, RMD_VMAX)
				RMDV(RMD_CRESC,0)
			} ELSE {
//Print("Other:"+M)
				ML=ML+M
				IF(TO=1) {
					TO=2
				}
				IF((ASC(M)>=97 && ASC(M)<=103) || M="r" || (ASC(M)>=48 && ASC(M)<=57) || M="." ||M="^"|| M="-") {
				} ELSE {
					TO=0
				}
			}
		}
		IF(DEBUG=1||TEST=1) {
			Print("Token "+ TOKEN + " Count "+ C + " Str="+M+" ML="+ML+" Len="+LenStr+" TO="+TO+" BUF="+BUF)
		}
	}
	FM=RRMML+VL+ML+RMML
	IF(FM!="") {
		BUF=BUF+"Sub{"+FM+"}r"+LenStr
	}

	IF(DEBUG=1 || TEST=1) {
		Print(BUF)
	}
	BUF
}

IF(TEST=1) {
	#basemml={
		l8
		[4 RMD(cdefgfed)  RMDV(-5)]
		RMDV(15)
		RMD(c4g4f4d4)
	}
	TR(1)
		Tempo 120
		o6

		// ����߂����Ђ�Ђ�
		RMDINIT(32,40,70,110)
		#basemml

		// �܂��܂�
		RMDINIT(96,425,70,110)
		#basemml

		// ���
		RMDINIT(193,765,100,110)
		#basemml

		// DTM
		RMDINIT(0,0,110,110)
		#basemml

	TR(2)
		Tempo 120
		o4

		// ����߂����Ђ�Ђ�
		RMDINIT(32,40,70,110)
		#basemml

		// �܂��܂�
		RMDINIT(96,425,70,110)
		#basemml

		// ���
		RMDINIT(193,765,100,110)
		#basemml

		// DTM
		RMDINIT(0,0,110,110)
		#basemml

	TR(10)
		$M{n(MetronomeBell),}
		$m{n(MetronomeClick),}
		[40
			Rythm{M4m4m4m4}
		]

}
