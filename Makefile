SPRITEDIR:=/usr/local
SPRITEINCDIR:=$(SPRITEDIR)/include/SPRITE
SPRITELIBDIR:=$(SPRITEDIR)/lib/SPRITE
LUADIR:=/usr/include/lua5.2/

SRC:=tasks/Logger.cpp \
     tasks/SMD.cpp

TEST_SRC:=

TGT:=sprite_main
TGT_TYPE:=application

SP:=./
CFLAGS=-I./ -I$(SPRITEINCDIR) -I$(LUADIR) -DXPRINT_LOCATION #-DPRINT_DEBUG

include $(SP)rules.mk

LDFLAGS+=-L$(SPRITELIBDIR) -lSPRITE_SCALE -lSPRITE_SRTX -lSPRITE_math \
         -lSPRITE_units -lpthread -llua5.2 -lrt -ldl

$(TGT): $(TGT).o $(OBJS)
	$(CPP) -o $@ $^ $(LDFLAGS)

EXTRA_CLEAN+=$(TGT).o $(TGT).d

#tasks/SMD.o: CPPFLAGS+=-DPRINT_DEBUG

release:
	@echo "Enter version number: "; \
	read VERSION; \
	git branch release-$$VERSION; \
	git push origin release-$$VERSION; \
	RELEASENAME=libSPRITE-SMD_demo-$$VERSION; \
	git archive --prefix=$$RELEASENAME/ master | bzip2 > ../$$RELEASENAME.tar.bz2
