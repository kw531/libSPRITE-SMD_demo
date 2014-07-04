SPRITEDIR:=/usr/local
SPRITEINCDIR:=$(SPRITEDIR)/include/SPRITE
SPRITELIBDIR:=$(SPRITEDIR)/lib/SPRITE

SRC:=tasks/Logger.cpp \
     tasks/SMD.cpp

TEST_SRC:=

TGT:=sprite_main
TGT_TYPE:=application

SP:=./
CFLAGS=-I./ -I$(SPRITEINCDIR) -DXPRINT_LOCATION #-DPRINT_DEBUG

include $(SP)rules.mk

LDFLAGS+=-L$(SPRITELIBDIR) -lSPRITE_SCALE -lSPRITE_SRTX -lSPRITE_math \
         -lSPRITE_units -lpthread -llua -lrt -ldl

$(TGT): $(TGT).o $(OBJS)
	$(CPP) -o $@ $^ $(LDFLAGS)

EXTRA_CLEAN+=$(TGT).o $(TGT).d

#tasks/SMD.o: CPPFLAGS+=-DPRINT_DEBUG
