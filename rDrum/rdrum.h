///////////////////////////////////////////////////////////////////////////////
// title:        "rdrum.h" ver 0.0α
// description:  ドラムに演奏感をつける
// keywords:     SAKURA Function     by ななこっち★ @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// rdrum.h ドラムに演奏感をつける
///////////////////////////////////////////////////////////////////////////////

// ロテート
Int BDROTATE=0
Int SDROTATE=0
Int CYMROTATE=0

Int BDINIT=0
Int CYMINIT=0
Int SDINIT=0

Int RANDV=0
Int RANDR=0

Int RDVOL=127

Function RDINIT(Int _RDVOL, Int _RANDV, Int _RANDR, Int _BDROTATE, Int _SDROTATE, Int _CYMROTATE) {
	RDVOL=_RDVOL
	RANDV=_RANDV
	RANDR=_RANDR
	BDROTATE=_BDROTATE
	SDROTATE=_SDROTATE
	CYMROTATE=_CYMROTATE
}

Function BassDrum(Int VO) {
	Int CC
	IF(BDROTATE=0) {
		CC=VO
	} ELSE {
		IF(BDINIT=0) {
			CC=BassDrum1
			BDINIT=1
		} ELSE {
				CC=BassDrum2
			BDINIT=0
		}
	}
	Result=CC
}

Function Snare(Int VO) {
	Int CC
	IF(SDROTATE=0) {
		CC=VO
	} ELSE {
		IF(SDINIT=0) {
			CC=Snare1
			SDINIT=1
		} ELSE {
				CC=Snare2
			SDINIT=0
		}
	}
	Result=CC
}

Function Cymbal(Int VO) {
	Int CC
	IF(CYMROTATE=0) {
		CC=VO
	} ELSE {
		IF(CYMINIT=0) {
			CC=CrashCymbal1
			CYMINIT=1
		} ELSE {
			CC=CrashCymbal2
			CYMINIT=0
		}
	}
	Result=CC
}

Function Splash(Int VO) {
	Int CC
	IF(CYMROTATE=0) {
		CC=VO
	} ELSE {
		IF(CYMINIT=0) {
			CC=SplashCymbal
			CYMINIT=1
		} ELSE {
			CC=SplashCymbal
			CYMINIT=0
		}
	}
	Result=CC
}

Function RDV(Int V) {
	RDVOL=V
}

Function RDCresc(Int V) {
	RDVOL=RDVOL+V
	IF(RDVOL>127) {
		RDVOL=127
	}
	IF(RDVOL<0) {
		RDVOL=0
	}
}

Function _RDV(Int V) {
	Int R=V
	R=R-(127-RDVOL)
	IF(R<0) {
		R=0
	}
	Result=R
}

Function RandV(Int MIN, Int MAX) {
	Str MML="v"
	IF(RANDV=0) {
		MML=MML+#STR(_RDV(MAX)
	} ELSE {
		MML=MML+Random(_RDV(MIN), _RDV(MAX))
	}
	MML
}

Str RMML
Function RandR(Int MIN, Int MAX) {
	Str MML
	IF(RANDR=1) {
		MML=MML+"r"
		RMML=RMML+"r"
		Int VALUE=Random(0,10)
		IF(VALUE<5) {
			MML=MML+"-"
		} ELSE {
			RMML=RMML+"-"
		}
		Str RAND=Random(MIN,MAX)
		MML=MML+RAND
		RMML=RMML+RAND
		MML
	}
}

Function SyncR() {
	Str MML=RMML
	RMML=""
	MML
}


#DRUMSET1={
	// stick
	$k{Sub{RandR(800,1536) RandV(124,127) n(Sticks),16}r} //37

	// Bass Drum
	$B{Sub{RandR(800,1536) RandV(124,127) n(BassDrum(Kick2)),16}r}//35
	$b{Sub{RandR(800,1536) RandV(124,127) n(BassDrum(Kick1)),16}r}//36

	// Snare Drum
	$s{Sub{RandR(800,1536) RandV(120,127) n(Snare(Snare1)),16}r}//38
	$S{Sub{RandR(800,1536) RandV(120,127) n(Snare(Snare2)),16}r}//40

	// Toms
	$L{Sub{RandR(800,1536) RandV(123,127) n(LowTom2),16}r}//41
	$l{Sub{RandR(800,1536) RandV(123,127) n(LowTom1),16}r}//43
	$M{Sub{RandR(800,1536) RandV(123,127) n(MidTom2),16}r}//45
	$m{Sub{RandR(800,1536) RandV(123,127) n(MidTom1),16}r}//47
	$T{Sub{RandR(800,1536) RandV(123,127) n(HighTom2),16}r}//48
	$t{Sub{RandR(800,1536) RandV(123,127) n(HighTom1),16}r}//50

	// Hihat
	$p{Sub{RandR(800,1536) RandV(110,127) n(PedalHiHat),16}r}//44
	$h{Sub{RandR(800,1536) RandV( 65, 80) n(ClosedHiHat),16}r}//42
	$o{Sub{RandR(800,1536) RandV( 90,110) n(OpenHiHat),16}r}//46

	// Ride
	$r{Sub{RandR(800,1536) RandV(100,110) n(RideCymbal1),16}r}//51
	$R{Sub{RandR(800,1536) RandV(120,127) n(RideCymbal2),16}r}//59
	$P{Sub{RandR(800,1536) RandV(120,127) n(RideBell),16}r}//53

	// Cymbal
	$c{Sub{RandR(800,1536) RandV(120,127) n(Cymbal(CrashCymbal1)),16}r}//49
	$c{Sub{RandR(800,1536) RandV(120,127) n(Cymbal(CrashCymbal2)),16}r}//57

	// Splash
	$a{Sub{RandR(800,1536) RandV(120,127) n(Splash(SplashCymbal)),16}r}//55
	$A{Sub{RandR(800,1536) RandV(120,127) n(Splash(ChineseCymbal)),16}r}//52
}
