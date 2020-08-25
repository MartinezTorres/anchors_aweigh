NAME := anchors_aweigh


tmp/inc/res/custom_midi/%_a.h: tmp/inc/res/custom_midi/%.h
	@echo $(MSG)
	@touch $@

tmp/inc/res/custom_midi/%_b.h: tmp/inc/res/custom_midi/%.h
	@echo $(MSG)
	@touch $@

tmp/inc/res/custom_midi/%_c.h: tmp/inc/res/custom_midi/%.h
	@echo $(MSG)
	@touch $@


tmp/inc/res/custom_midi/%.h: res/custom_midi/% tmp/util/mkMidiImproved
	@echo $(MSG)
	@mkdir -p tmp/$(<D)
	@mkdir -p tmp/inc/$(<D)
	@tmp/util/mkMidiImproved -fps=34 $<

BINARIES_SRC +=  $(patsubst %, %_a, $(call rwildcard, res/custom_midi/, *.mid))
BINARIES_SRC +=  $(patsubst %, %_b, $(call rwildcard, res/custom_midi/, *.mid))
BINARIES_SRC +=  $(patsubst %, %_c, $(call rwildcard, res/custom_midi/, *.mid))
HEADERS_GEN  +=  $(patsubst %, tmp/inc/%.h, $(call rwildcard, res/custom_midi/, *.mid))


tmp/inc/res/midi_improved/%_a.h: tmp/inc/res/midi_improved/%.h
	@echo $(MSG)
	@touch $@

tmp/inc/res/midi_improved/%_b.h: tmp/inc/res/midi_improved/%.h
	@echo $(MSG)
	@touch $@

tmp/inc/res/midi_improved/%_c.h: tmp/inc/res/midi_improved/%.h
	@echo $(MSG)
	@touch $@

tmp/inc/res/midi_improved/%.h: res/midi_improved/% tmp/util/mkMidiImproved
	@echo $(MSG)
	@mkdir -p tmp/$(<D)
	@mkdir -p tmp/inc/$(<D)
	@tmp/util/mkMidiImproved -fps=50 $<

BINARIES_SRC +=  $(patsubst %, %,   $(call rwildcard, res/midi_improved/, *.mid))
BINARIES_SRC +=  $(patsubst %, %_a, $(call rwildcard, res/midi_improved/, *.mid))
BINARIES_SRC +=  $(patsubst %, %_b, $(call rwildcard, res/midi_improved/, *.mid))
BINARIES_SRC +=  $(patsubst %, %_c, $(call rwildcard, res/midi_improved/, *.mid))
HEADERS_GEN  +=  $(patsubst %, tmp/inc/%.h, $(call rwildcard, res/midi_improved/, *.mid))

include sdcc_msx/Makefile.in

CCFLAGS_MSX   += -DKONAMI5
CCFLAGS_MSX   += --all-callee-saves --opt-code-speed
#CCFLAGS_MSX   += --reserve-regs-iy --callee-saves-bc

CCFLAGS_MSX   += -DID=1012002253UL -DPSEED=27633UL
CCFLAGS_LINUX += -DID=1012002253UL -DPSEED=27633UL


#OPENMSX_BIN = /opt/openMSX/bin/openmsx
#OPENMSX_PARAM = -command "profile::section_scope_bp frame 0xFD9F; profile_osd p;" 
#OPENMSX_PARAM = -command "profile::enable_z80_interface;" 
#OPENMSX_PARAM = -command "profiler::auto_scan::enable; catch {profiler::gui::start};"

ADDR_DATA = 0xC000

CCZ80 = sdcc_msx/bin/sdcc-3.9.0/bin/sdcc
ASM = sdcc_msx/bin/sdcc-3.9.0/bin/sdasz80

MAX_ALLOCS = 20000


