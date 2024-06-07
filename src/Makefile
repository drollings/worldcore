# Generated automatically from Makefile.in by configure.
# CircleMUD 3.0 Makefile.in - Makefile template used by 'configure'
#

# C compiler to use
CC = ccache clang++

# Any special flags you want to pass to the compiler
MYFLAGS = -Wall -Wno-unused -Wno-sign-compare -Wno-switch -std=c++11
#-fno-inline

#flags for profiling (see hacker.doc for more information)
PROFILE = 
#PROFILE = -pg

# LIBS = -lz -lpcre -lpcrecpp -L/opt/local/lib
LIBS = -L/opt/local/lib


##############################################################################
# Do Not Modify Anything Below This Line (unless you know what you're doing) #
##############################################################################

BINDIR = ../bin
DEPDIR = .deps

CFLAGS = -g3 $(MYFLAGS) $(PROFILE)
OPTCFLAGS = -O0 $(MYFLAGS) $(PROFILE)
# INCLUDE = -I/opt/local/include -Iann_1.1.1/include
# INCLUDE = -I/opt/local/include -I/opt/local/include/thrift
INCLUDE = -I/opt/include -I/opt/include/thrift
MODULES = 

# CONFIGTYPE = -DGURPS
CONFIGTYPE = -DUNITTEST

# ACTFILES = act.comm.o act.informative.o act.movement.o act.item.o \
# 	act.offensive.o act.other.o act.social.o act.wizard.o
# CUSTOMFILES = elevators.o newfight.o vehicles.o events.o ident.o
# OLC = aedit.o cedit.o hedit.o medit.o oedit.o redit.o sedit.o zedit.o \
# 	scriptedit.o olc.o
# SCRIPTENGINE = scriptengine.o triggers.o scriptcmd.o scriptcompiler.o
# CPPFILES = affects.o characters.o clans.o descriptors.o event.o objects.o \
# 	files.o index.o rooms.o scripts.o sstring.o parser.o help.o opinion.o \
# 	queue.o entity.o zones.o idmap.o
# IMC = imc-config.o imc-events.o imc-interp.o imc-mail.o imc-mercbase.o \
# 	imc-util.o imc-version.o imc.o ice.o icec-mercbase.o icec.o iced.o \
# 	minilzo.o
# LEXI = lexifile.o lexiparser.o
# #PCRE = pcre/pcre_chartables.o pcre/pcrecpp.o pcre/pcre_compile.o \
# 	pcre/pcre_exec.o pcre/pcre_fullinfo.o pcre/pcre_globals.o \
# 	pcre/pcre_tables.o pcre/pcre_try_flipped.o
# OPTIMIZEDCPP = utils.opt.o buffer.opt.o lexistring.opt.o
# OBJFILES = comm.o $(ACTFILES) ban.o boards.o config.o constants.o db.o \
# 	fight.o find.o graph.o handler.o house.o interpreter.o limits.o mail.o \
# 	mobact.o modify.o objsave.o shop.o spec_assign.o spec_procs.o \
# 	weather.o races.o random.o log.o track.o space.o \
# 	$(OPTIMIZEDCPP) $(OLC) $(CUSTOMFILES) $(SCRIPTENGINE) \
# 	$(CPPFILES) $(IMC) $(LEXI)

OBJFILES = base.o constraints.o coord.o editing.o events.o \
	find.o functions.o gurpsskills.o mixins.o permissions.o \
	properties.o queue.o things.o worlds.o

THRIFTFILES = \
	gen-cpp/base_types.h \
	gen-cpp/errorcodes_types.h \
	gen-cpp/genus_types.h \
	gen-cpp/materials_types.h \
	gen-cpp/permissions_types.h \
	gen-cpp/pronouns_types.h \
	gen-cpp/propertytypes_types.h \
	gen-cpp/proximities_types.h \
	gen-cpp/signals_types.h \
	gen-cpp/skills_types.h \
	gen-cpp/things_types.h \
	gen-cpp/typedefs_types.h




# OBJFILES = leximud.o


# the modules we have installed -- mandatory modules go here
# MODULES := bodytypes

# optional modules go on this line
# MODULES += time socials alias help2


default: 
	$(MAKE) unittest.bin

all:
	$(MAKE) unittest.bin
	
mudcore.bin:
	$(MAKE) $(BINDIR)/mudcore.bin

$(BINDIR)/mudcore.bin : $(OBJFILES) engine.o
	@echo ""
	$(CC) -v -o $(BINDIR)/mudcore.bin $(PROFILE) engine.o $(OBJFILES) $(LIBS)

unittest.bin : $(THRIFTFILES) $(OBJFILES) unittest.o
	@echo ""
	@echo $(OBJFILES)
	$(CC) -v -o unittest.bin $(PROFILE) unittest.o $(OBJFILES) $(LIBS)

# remove all the compiled objects for a clean compile
clean:
	rm -rf $(DEPDIR)
	rm -f *.o */*.o unittest.bin mudcore.bin
	mkdir $(DEPDIR)

cleancache:
	rm -rf ~/.ccache
	
test:
	$(MAKE) unittest.bin
	./unittest.bin
	
# include the description for each module. These will add to SRC
# C_FLAGS, LIBS, etc...
include $(patsubst %,%/module.mk, $(MODULES))

# default rule to make all of the .c files
# 	@echo -n "$< "
%.opt.o: %.cpp
	@echo "$< "
	@$(CC) $(INCLUDE) $(CONFIGTYPE) -c $(OPTCFLAGS) $< -o $@

# default rule to make all of the .c files
%.o: %.cpp
	@echo "$< "
	@$(CC) $(INCLUDE) $(CONFIGTYPE) -c $(CFLAGS) $< -o $@

%.verbose: %.cpp
	@echo "$< "
	@$(CC) $(INCLUDE) $(CONFIGTYPE) -c $(CFLAGS) $< -E $@

src-worldcore.tar.gz:
	tar -zcvf src-worldcore.tar.gz Makefile TODO-DR *.hpp *.cpp *.thrift Templates/*

src-worldcore.zip:
	zip src-worldcore.zip Makefile TODO-DR *.hpp *.cpp *.thrift Templates/*

thrift:  $(THRIFTFILES)
	@echo

gen-cpp/%_types.h: %.thrift
	thrift --gen cpp:pure_enums $<

gen-py/%/ttypes.py: %.thrift
	thrift --gen py $<
	
# Dependencies for the object files (automagically generated with gcc -MM)

$(DEPDIR)/%.opt.d $(DEPDIR)/%.d: %.cpp
	@echo Generating dependencies for $<
	@mkdir -p $(@D)
	@$(CC) -std=c++11 -MM $(INCLUDE) $< | \
	  sed 's@\(.*\).o:@$(<D)/\1.o $@:@' > $@; \
	  [ -s $@ ] || rm -f $@

# Uncomment this to regenerate dependencies automatically
-include $(OBJFILES:%.o=$(DEPDIR)/%.d)

