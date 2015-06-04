///////////////////////////////////////////////////////////////////////////////
// title:        "tempo.h" ver 1.1
// description:  TempoChange��݊����@�\�e���|�`�F���W�@�\�C���N���[�h�t�@�C��(2015/05/28)
// keywords:     SAKURA Function     by �ȂȂ������� @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// tempo.h �f�o�b�O�@�\�t���e���|�`�F���W
// �i�T�N���� TempoChange ������܂����A���̍��@�\�łł��j
//
// Include�O�ɁA�ȉ��̕ϐ����`���ĉ������B
//
// �EInt DEBUG=0 // 1 �Ń��g���m�[�����Ȃ�܂��A2 �Ńe���|�`�F���W���ɂ��邳���G������܂�
// �@�i���g���m�[����10000���߂ŏI�����܂��A4/4 ��O��ɍ쐬����Ă��܂��B�j
//
// �EInt TEMPORATIO
// �@�x�[�X�e���|�̊��������Őݒ肵�܂��B�i100���f�t�H���g�B�j
//
// �EInt TEMPODIFF
// �@�x�[�X�e���|��ݒ肵�āA�O�����e���|�𐧌䂵�����ꍇ�ATEMPODIFF �� �����l (-�`+)��ݒ肵�܂��B
//
// �EInt IGNORETEMPO
// �@IGNORETEMPO=1 �ɂ���ƁA�e���|�`�F���W�𖳌��ɂ��܂��B
//
// #METORONOMEMML
// �@���g���m�[���̃��Y��MML��ݒ�ł��܂��B3���q�ɂ��鎞���g�p���܂��B
// �@(M=�\���Am=����)
//
//  ���e���|�`�F���W�́A��p�̃g���b�N���쐬���邱�Ƃ������߂��܂��B
///////////////////////////////////////////////////////////////////////////////
// Function TmpChange(tempo, len)
// �e���|���`�F���W���܂��B
// �O�̃e���|�͎����I�ɓǂݍ��܂�܂�
// �����`�F���W����ꍇ�ɂ́Alen�� 0 �ɂ��܂��B
// ����ȊO�́A!2 !4. �����w�肵�܂��B
//
// Function TmpChangeR(tempo, len)
// �e���|���`�F���W���āAlen���̋x����u���܂��B
///////////////////////////////////////////////////////////////////////////////
// �e�X�g����Ƃ��́A�ȉ��̃R�����g��S�ĊO���Ă��������B
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
