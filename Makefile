PROJECT = sbc
CC = gcc
DEFS =
INCS =
INCDIR =
LIBS =
LIBDIR =
OBJS = \
	cdma.o \
	cdpoke.o \
	cend.o \
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
	compileline.o \
	congoto.o \
	cout.o \
	cpoke.o \
	cprint.o \
	cq.o \
	crem.o \
	creturn.o \
	findline.o \
	gethex.o \
	getnumber.o \
	getvariable.o \
	library.o \
	main.o \
	pass.o \
	prepass.o \
	showerror.o \
	trim.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm $(PROJECT)

cdma.o:        header.h cdma.c
cdpoke.o:      header.h cdpoke.c
cend.o:        header.h cend.c
cexpr.o:       header.h cexpr.c
cgosub.o:      header.h cgosub.c
cgoto.o:       header.h cgoto.c
cidle.o:       header.h cidle.c
cif.o:         header.h cif.c
cinput.o:      header.h cinput.c
cintr.o:       header.h cintr.c
cioff.o:       header.h cioff.c
cion.o:        header.h cion.c
clet.o:        header.h clet.c
compileline.o: header.h compileline.c
congoto.o:     header.h congoto.c
cout.o:        header.h cout.c
cpoke.o:       header.h cpoke.c
cprint.o:      header.h cprint.c
cq.o:          header.h cq.c
crem.o:        header.h crem.c
creturn.o:     header.h creturn.c
findline.o:    header.h findline.c
gethex.o:      header.h gethex.c
getnumber.o:   header.h getnumber.c
getvariable.o: header.h getvariable.c
library.o:     header.h library.c
main.o:        header.h main.c
pass.o:        header.h pass.c
prepass.o:     header.h prepass.c
showerror.o:   header.h showerror.c
trim.o:        header.h trim.c
