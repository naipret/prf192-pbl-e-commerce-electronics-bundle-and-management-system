#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Prompts the user and reads a safe integer value.
 * @param prompt The string prompt to show to the user.
 * @param out_value Pointer to integer where the parsed value will be stored.
 * @return 1 if successfully parsed a valid integer, 0 if canceled by typing
 * '0'.
 */
int get_safe_int(const char *prompt, int *out_value);

/**
 * @brief Prompts the user and reads a safe floating-point value.
 * @param prompt The string prompt to show to the user.
 * @param out_value Pointer to float where the parsed value will be stored.
 * @return 1 if successfully parsed a valid float, 0 if canceled by typing '0'.
 */
int get_safe_float(const char *prompt, float *out_value);

/**
 * @brief Prompts the user and reads a safe string up to max_len - 1 characters.
 * @param prompt The string prompt to show to the user.
 * @param out_str Character buffer where the string will be stored.
 * @param max_len Size of the output buffer.
 */
void get_safe_string(const char *prompt, char *out_str, int max_len);

/**
 * @brief Clears the standard input buffer up to newline or EOF.
 */
void clear_input_buffer(void);

/**
 * @brief Converts a string in-place to all lowercase letters.
 * @param str The string to convert.
 */
void to_lowercase(char *str);

/**
 * @brief Reads a string of characters from stdin up to a given size limit.
 * @param str Character buffer where the string will be stored.
 * @param size Size of the output buffer.
 */
void input_string(char *str, int size);

/**
 * @brief Halts program execution until the user presses Enter.
 */
void cont(void);

/**
 * @brief Prompts the user for a confirmation and returns their choice.
 * @param message The confirmation message to display.
 * @return 1 if the user confirmed (Y/y), 0 otherwise.
 */
int confirm_action(const char *message);

#endif /* UTILS_H */
