/opt/ps3dev/ppu/bin/powerpc64-ps3-elf-g++  -mcpu=cell -I/opt/ps3dev/ppu/include -I/opt/ps3dev/portlibs/ppu/include   CMakeFiles/clabtest.dir/src/main.cpp.obj  -o clabtest.elf libClab-game-0.a -lClab-0 -lSDL2 -lm -lgcm_sys -lrsx -lsysutil -lio -laudio -lrt -llv2 -lio -laudio
sprxlinker clabtest.elf
make_self clabtest.elf clabtest.self
fself.py clabtest.elf clabtest.fake.self
