PROJECT = sbc
CC = gcc
DEFS =
INCS =
INCDIR =
LIBS =
LIBDIR =
OBJS = \
	asm.o \
	casm.o \
	ccls.o \
	cdata.o \
	cdealloc.o \
	cdma.o \
	cdpoke.o \
	cend.o \
	cfor.o \
	cexpr.o \
	cgosub.o \
	cgoto.o \
	cidle.o \
	cif.o \
	cinput.o \
	cintr.o \
	cioff.o \
	cion.o \
	clet.o \
	clocate.o \
	cnext.o \
	compileline.o \
	congoto.o \
	cout.o \
	cpoke.o \
	cprint.o \
	cq.o \
	cread.o \
	crem.o \
	crestore.o \
	creturn.o \
	findline.o \
	gethex.o \
	getnumber.o \
	getvariable.o \
	library.o \
	main.o \
	match.o \
	optionfile.o \
	pass.o \
	prepass.o \
	processoption.o \
	showerror.o \
	trim.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm $(PROJECT)

asm.o:           header.h asm.c
casm.o:          header.h casm.c
ccls.o:          header.h ccls.c
cdata.o:         header.h cdata.c
cdealloc.o:      header.h cdealloc.c
cdma.o:          header.h cdma.c
cdpoke.o:        header.h cdpoke.c
cend.o:          header.h cend.c
cexpr.o:         header.h cexpr.c
cfor.o:          header.h cfor.c
cgosub.o:        header.h cgosub.c
cgoto.o:         header.h cgoto.c
cidle.o:         header.h cidle.c
cif.o:           header.h cif.c
cinput.o:        header.h cinput.c
cintr.o:         header.h cintr.c
cioff.o:         header.h cioff.c
cion.o:          header.h cion.c
clet.o:          header.h clet.c
clocate.o:       header.h clocate.c
cnext.o:         header.h cnext.c
compileline.o:   header.h compileline.c
congoto.o:       header.h congoto.c
cout.o:          header.h cout.c
cpoke.o:         header.h cpoke.c
cprint.o:        header.h cprint.c
cq.o:            header.h cq.c
cread.o:         header.h cread.c
crem.o:          header.h crem.c
crestore.o:      header.h crestore.c
creturn.o:       header.h creturn.c
findline.o:      header.h findline.c
gethex.o:        header.h gethex.c
getnumber.o:     header.h getnumber.c
getvariable.o:   header.h getvariable.c
library.o:       header.h library.c
main.o:          header.h main.c
match.o:         header.h match.c
optionfile.o:    header.h optionfile.c
pass.o:          header.h pass.c
prepass.o:       header.h prepass.c
processoption.o: header.h processoption.c
showerror.o:     header.h showerror.c
trim.o:        header.h trim.c
