///////////////////////////////////////////////////////////////////////////////
// title:        "loop.h" ver 1.0
// description:  Loopインクルードファイル(2015/06/02)
// keywords:     SAKURA Function     by ななこっち★ @nanakochi123456
// HP:           http://nano.daiba.cx/
///////////////////////////////////////////////////////////////////////////////
// loop.h 可変回数のループ
///////////////////////////////////////////////////////////////////////////////
// Function LoopPlay
// LoopPlay(mml string value[, loop count offset]) max 5 parms.
//
// Example
// Int LOOP=4
// Include(loop.h)
// #mml={
//    cde
// }
// LoopPlay(#mml)
// LoopPlay(#mml,0)
///////////////////////////////////////////////////////////////////////////////
// テストする時は、以下のコメントを外してください。
//Int TEST=1
//Int LOOP=5
///////////////////////////////////////////////////////////////////////////////

Function LoopPlay(Str Mml, Int count) {
	Str _MML
	For (Int i = 1; i <= LOOP + count; i++) {
		_MML=_MML + Mml
	}
	_MML
}

IF(TEST=1) {
	曲名{"かえるの歌(test)"}
	作者{"ドイツ民謡"}
	#mmla={
		l4
		cdef
		edc4.r8
	}
	#mmlb={
		l4
		efga
		gfe4.r8
	}

	#mmlc={
		crcr
		crcr
		l8ccddeeff
		l4
		edc2
	}
	
	TR(1)
		o5
		@(Clarinet)
		q95
		#mmla
		LoopPlay(#mmlb,3)
		#mmlc

	TR(2)
		o6
		@(Violin)
		q95
		[2 r1]
		#mmla
		LoopPlay(#mmlb,2)
		#mmlc

	TR(3)
		o4
		q95
		@(FrenchHorn)
		[4 r1]
		#mmla
		LoopPlay(#mmlb,1)
		#mmlc

	TR(4)
		o3
		q95
		@(Contrabass)
		[6 r1]
		#mmla
		LoopPlay(#mmlb,0)
		#mmlc

	TR(5)
		o3
		q95
		@(Timpani)
		[8 r1]
		#mmla
		LoopPlay(#mmlb,-1)
		#mmlc

}
