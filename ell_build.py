from cffi import FFI

# compile with:
# gcc -lell $(python3.8-config --cflags) $(python3.8-config --ldflags) -Wl,-rpath,. -shared -fPIC ell.c -o ell.so


ffibuilder = FFI()

# ell_settings.h is /usr/include/ell/settings.h with all "strange things" removed
with open('ell_settings.h') as fi:
    ffibuilder.cdef(fi.read())

ffibuilder.set_source(
    'ell._ell',
    """#include <ell/ell.h>""",
    libraries=['ell']
)

if __name__ == '__main__':
    ffibuilder.compile(verbose=True)
