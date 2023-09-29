PROJECT=baslib.lib
OBJS=\
	abs16.prg \
	abs32.prg \
	absfp.prg \
	add16.prg \
	add32.prg \
	add32i.prg \
	addfp.prg \
	addfpi.prg \
	addtows.prg \
	alloc.prg \
	and16.prg \
	and32.prg \
	assignstring.prg \
	atoi16.prg \
	atoi32.prg \
	atof.prg \
	checkeom.prg \
	cmp32.prg \
	comp32.prg \
	concat.prg \
	copystring.prg \
	dealloc.prg \
	div16.prg \
	div32.prg \
	div32i.prg \
	divfp.prg \
	divfpi.prg \
	eof16.prg \
	eof32.prg \
	eq16.prg \
	eq32.prg \
	eqfp.prg \
	false.prg \
	false32.prg \
	fpacos.prg \
	fpargs.prg \
	fpasin.prg \
	fpatan.prg \
	fpcomp2.prg \
	fpcopy.prg \
	fpcos.prg \
	fpdata.prg \
	fpexp.prg \
	fpln.prg \
	fpnorm.prg \
	fppow.prg \
	fpret0.prg \
	fpreta.prg \
	fpretb.prg \
	fpsin.prg \
	fpsqrt.prg \
	fptan.prg \
	ftoa.prg \
	ftoi.prg \
	getargs.prg \
	gt16.prg \
	gt32.prg \
	gtfp.prg \
	gte16.prg \
	gte32.prg \
	gtefp.prg \
	hfree.prg \
	icomp32.prg \
	itoa16.prg \
	itoa32.prg \
	itof.prg \
	left.prg \
	lfsrlp.prg \
	lower.prg \
	lt16.prg \
	lt32.prg \
	ltfp.prg \
	lte16.prg \
	lte32.prg \
	ltefp.prg \
	mdnorm.prg \
	mid.prg \
	mod16.prg \
	mod32.prg \
	mul16.prg \
	mul32.prg \
	mul32i.prg \
	mulfp.prg \
	mulfpi.prg \
	ne16.prg \
	ne32.prg \
	nefp.prg \
	neg32.prg \
	next16.prg \
	next32.prg \
	nextvar32.prg \
	null32.prg \
	or16.prg \
	or32.prg \
	printstring.prg \
	right.prg \
	rnd16.prg \
	rnd32.prg \
	setstring.prg \
	sgn16.prg \
	sgn32.prg \
	sgnfp.prg \
	shl32.prg \
	shr32.prg \
	strcat.prg \
	strcmp.prg \
	strcpy.prg \
	strcpyin.prg \
	strlen.prg \
	sub16.prg \
	sub32.prg \
	sub32i.prg \
	subfp.prg \
	subfpi.prg \
	tobcd16.prg \
	tobcd32.prg \
	true.prg \
	true32.prg \
	upper.prg \
	xor16.prg \
	xor32.prg \
	zero32.prg

.SUFFIXES: .asm .prg

$(PROJECT): $(OBJS)
	-rm $(PROJECT)
	cat $(OBJS) > $(PROJECT)

.asm.prg:
	asm02 -l -L $<

clean:
	-rm *.prg
	-rm $(PROJECT)

install:
	cp baslib.lib /usr/local/lib

