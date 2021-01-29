import os
import tempfile

from ._ell.lib import *
from ._ell import ffi


class EllSettings:
    def __init__(self, filename=None):
        self.settings = l_settings_new()
        if filename:
            self.filename = os.path.abspath(filename)
            if os.path.exists(self.filename):
                ok = l_settings_load_from_file(self.settings, filename.encode())
                if not ok:
                    raise ValueError(f'l_settings_load_from_file({filename}): failed')
        else:
            self.filename = None

    def save(self, filename=None):
        fn = filename or self.filename
        if not fn:
            raise ValueError(f"save(): no target")
        siz = ffi.new('size_t *')
        cdata = l_settings_to_data(self.settings, siz)
        data = ffi.string(cdata)
        l_free(cdata)
        d = os.path.dirname(fn)
        fd, tn = tempfile.mkstemp(dir=d)
        with os.fdopen(fd, 'wb') as fo:
            fo.write(data)
        os.replace(tn, fn)

    def free(self, obj=None):
        if obj:
            l_free(obj)
        else:
            l_settings_free(self.settings)
            self.settings = None

    # --- GROUP ---

    def get_groups(self):
        cgroups = l_settings_get_groups(self.settings)
        groups = []
        i = 0
        while cgroups[i] != ffi.NULL:
            groups.append(ffi.string(cgroups[i]).decode())
            i += 1
        # print(groups)
        self.free(cgroups)
        return groups

    def has_group(self, grp):
        return l_settings_has_group(self.settings, grp.encode())

    def remove_group(self, grp):
        return l_settings_remove_group(self.settings, grp.encode())

    # --- KEY ---

    def get_keys(self, grp):
        ckeys = l_settings_get_keys(self.settings, grp.encode())
        keys = []
        i = 0
        while ckeys[i] != ffi.NULL:
            keys.append(ffi.string(ckeys[i]).decode())
            i += 1
        # print(keys)
        self.free(ckeys)
        return keys

    def remove_key(self, grp, key):
        return l_settings_remove_key(self.settings, grp.encode(), key.encode())

    def get_string(self, grp, key):
        try:
            cval = l_settings_get_string(self.settings, grp.encode(), key.encode())
            val = ffi.string(cval).decode()
            # print(val)
        except ValueError:
            val = None
        return val

    def set_string(self, grp, key, val):
        ok = l_settings_set_string(self.settings, grp.encode(), key.encode(), val.encode())
        if not ok:
            raise ValueError(f'l_settings_set_string({self.filename}, {grp}, {key}, {val}): failed')
