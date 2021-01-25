typedef long int ptrdiff_t;
typedef long unsigned int size_t;
typedef int wchar_t;



/* ----- FROM /usr/include/ell/util.h ----- */
void *l_malloc(size_t size);
void *l_memdup(const void *mem, size_t size);
void l_free(void *ptr);

void *l_realloc(void *mem, size_t size);
char *l_strdup(const char *str);
char *l_strndup(const char *str, size_t max);
//char *l_strdup_printf(const char *format, ...);
//char *l_strdup_vprintf(const char *format, va_list args);

size_t l_strlcpy(char* dst, const char *src, size_t len);

bool l_str_has_prefix(const char *str, const char *prefix);
bool l_str_has_suffix(const char *str, const char *suffix);

char *l_util_hexstring(const unsigned char *buf, size_t len);
char *l_util_hexstring_upper(const unsigned char *buf, size_t len);
unsigned char *l_util_from_hexstring(const char *str, size_t *out_len);

typedef void (*l_util_hexdump_func_t) (const char *str, void *user_data);

void l_util_hexdump(bool in, const void *buf, size_t len, l_util_hexdump_func_t function, void *user_data);
void l_util_hexdump_two(bool in, const void *buf1, size_t len1, const void *buf2, size_t len2, l_util_hexdump_func_t function, void *user_data);
void l_util_hexdumpv(bool in, const struct iovec *iov, size_t n_iov, l_util_hexdump_func_t function, void *user_data);



/* ----- FROM /usr/include/ell/base64.h ----- */
uint8_t *l_base64_decode(const char *in, size_t in_len, size_t *n_written);
char *l_base64_encode(const uint8_t *in, size_t in_len, int columns, size_t *n_written);



/* ----- FROM /usr/include/ell/settings.h ----- */
struct l_settings;

typedef void (*l_settings_debug_cb_t) (const char *str, void *user_data);
typedef void (*l_settings_destroy_cb_t) (void *user_data);

struct l_settings *l_settings_new(void);
void l_settings_free(struct l_settings *settings);


_Bool
    l_settings_load_from_data(struct l_settings *settings,
      const char *data, size_t len);
char *l_settings_to_data(const struct l_settings *settings, size_t *len);


_Bool
    l_settings_load_from_file(struct l_settings *settings,
     const char *filename);


_Bool
    l_settings_set_debug(struct l_settings *settings,
    l_settings_debug_cb_t callback,
    void *user_data,
    l_settings_destroy_cb_t destroy);

char **l_settings_get_groups(const struct l_settings *settings);
char **l_settings_get_keys(const struct l_settings *settings,
       const char *group_name);


_Bool
    l_settings_has_group(const struct l_settings *settings,
       const char *group_name);

_Bool
    l_settings_has_key(const struct l_settings *settings,
    const char *group_name, const char *key);

const char *l_settings_get_value(const struct l_settings *settings,
     const char *group_name,
     const char *key);

_Bool
    l_settings_set_value(struct l_settings *settings, const char *group_name,
    const char *key, const char *value);


_Bool
    l_settings_get_bool(const struct l_settings *settings,
    const char *group_name,
    const char *key, 
                    _Bool
                         *out);

_Bool
    l_settings_set_bool(struct l_settings *settings, const char *group_name,
    const char *key, 
                    _Bool
                         in);


_Bool
    l_settings_get_int(const struct l_settings *settings,
   const char *group_name, const char *key, int *out);

_Bool
    l_settings_set_int(struct l_settings *settings, const char *group_name,
    const char *key, int in);


_Bool
    l_settings_get_uint(const struct l_settings *settings,
    const char *group_name,
    const char *key, unsigned int *out);

_Bool
    l_settings_set_uint(struct l_settings *settings, const char *group_name,
    const char *key, unsigned int in);


_Bool
    l_settings_get_int64(const struct l_settings *settings,
    const char *group_name,
    const char *key, int64_t *out);

_Bool
    l_settings_set_int64(struct l_settings *settings, const char *group_name,
    const char *key, int64_t in);


_Bool
    l_settings_get_uint64(const struct l_settings *settings,
    const char *group_name,
    const char *key, uint64_t *out);

_Bool
    l_settings_set_uint64(struct l_settings *settings, const char *group_name,
    const char *key, uint64_t in);

char *l_settings_get_string(const struct l_settings *settings,
    const char *group_name, const char *key);

_Bool
    l_settings_set_string(struct l_settings *settings, const char *group_name,
    const char *key, const char *value);

char **l_settings_get_string_list(const struct l_settings *settings,
     const char *group_name,
     const char *key, char delimiter);

_Bool
    l_settings_set_string_list(struct l_settings *settings,
     const char *group_name,
     const char *key, char **list,
     char delimiter);


_Bool
    l_settings_get_double(const struct l_settings *settings,
    const char *group_name,
    const char *key, double *out);

_Bool
    l_settings_set_double(struct l_settings *settings, const char *group_name,
    const char *key, double in);


_Bool
    l_settings_get_float(const struct l_settings *settings,
    const char *group_name,
    const char *key, float *out);

_Bool
    l_settings_set_float(struct l_settings *settings, const char *group_name,
    const char *key, float in);


_Bool
    l_settings_remove_key(struct l_settings *settings, const char *group_name,
    const char *key);

_Bool
    l_settings_remove_group(struct l_settings *settings,
    const char *group_name);

char **l_settings_get_embedded_groups(struct l_settings *settings);

_Bool
    l_settings_has_embedded_group(struct l_settings *settings,
     const char *group);
const char *l_settings_get_embedded_value(struct l_settings *settings,
      const char *group_name,
      const char **out_type);
