import os

cxx_flags = ['-std=c++17', '-g', '-Og', '-Wall']
link_flags = ['-std=c++17', '-g', '-Og', '-Wall']
libs = ['SDL2']

# If building on Windows
if os.name == 'nt':
    cxx_flags.append('-Dmain=SDL_main')
    libs = ['mingw32', 'SDL2main', 'SDL2']
    # link_flags.append('-mwindows')  # Uncomment to supress cout on Windows.

VariantDir('build', 'src', duplicate=0)
env = Environment(ENV=os.environ,
                  tools=['g++', 'gnulink'],
                  CXXFLAGS=cxx_flags,
                  CPPPATH=['thirdparty'],
                  LIBS=libs,
                  LINKFLAGS=link_flags)

env.Program('cateye', Glob('build/*.cpp'))

# Used to build a small test program for segments.
#env.Program('segmentTest', ['build/Segment.cpp', 'build/SegmentTest.cpp'])
