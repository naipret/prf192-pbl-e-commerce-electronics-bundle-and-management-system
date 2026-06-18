#ifndef UTILS_H
#define UTILS_H

int get_safe_int(const char *prompt, int *out_value);
int get_safe_float(const char *prompt, float *out_value);
void get_safe_string(const char *prompt, char *out_str, int max_len);
void clear_input_buffer(void);
void to_lowercase(char *str);

#endif /* UTILS_H */
