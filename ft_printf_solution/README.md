*This project has been created as part of the 42 curriculum by tgerman.*

# ft_printf

## Description

`ft_printf` is a re-implementation of the libc `printf()` function, packaged as a
static library, `libftprintf.a`. The goal of the project is to learn how
**variadic functions** work in C (`va_start`, `va_arg`, `va_end`) and to write
well-structured, extensible code.

The prototype is the same as the original:

```c
int	ft_printf(const char *format, ...);
```

The function writes to standard output and returns the number of characters
printed, or `-1` on error.

Supported conversions:

| Conversion | Output |
|---|---|
| `%c` | a single character |
| `%s` | a string (`(null)` for a `NULL` pointer) |
| `%p` | a `void *` pointer in hexadecimal, prefixed with `0x` (`(nil)` for `NULL`) |
| `%d` | a signed decimal number |
| `%i` | a signed integer in base 10 |
| `%u` | an unsigned decimal number |
| `%x` | an unsigned number in lowercase hexadecimal |
| `%X` | an unsigned number in uppercase hexadecimal |
| `%%` | a percent sign |

The bonus version (`make bonus`) also handles any combination of these flags,
together with a minimum field width, for every conversion:

| Flag | Effect |
|---|---|
| `-` | left-justify inside the field width |
| `0` | pad numbers with zeros instead of spaces (ignored with `-` or a precision) |
| `.N` | precision: minimum digits for numbers, maximum characters for `%s` |
| `#` | add `0x` / `0X` before a non-zero `%x` / `%X` |
| `+` | always print the sign of `%d` / `%i` |
| ` ` (space) | put a space before positive `%d` / `%i` (ignored with `+`) |

```c
ft_printf("[%-8s|%08.3d|%#x|%+d|% d]\n", "hi", 42, 255, 7, 7);
/* [hi      |     042|0xff|+7| 7] */
```

## Instructions

### Build

```sh
make        # builds libft, then libftprintf.a at the root of the repository
make clean  # removes object files (ft_printf and libft)
make fclean # removes object files and both libraries
make re     # fclean + all
make bonus  # builds libftprintf.a with the bonus version (flags support)
```

The library is compiled with `cc -Wall -Wextra -Werror`. The `libft` folder
contains the sources of the author's libft and its own Makefile. The main
Makefile builds it first, then copies `libft.a` into `libftprintf.a` and adds
the ft_printf objects with `ar`.

### Use

```c
#include "ft_printf.h"

int	main(void)
{
	int	n;

	n = ft_printf("%s is %d years old, %x in hex%%\n", "Bob", 42, 42);
	ft_printf("printed %d characters\n", n);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c libftprintf.a -o demo
./demo
```

## Algorithm and data structure

### File layout

| File | Content |
|---|---|
| `ft_printf.c` | `ft_printf` and three `static` helpers: format check, main loop, dispatcher |
| `ft_print_chars.c` | `ft_putchar_pf`, `ft_putstr_pf` |
| `ft_print_nums.c` | `ft_putnbr_base_pf`, `ft_putnbr_pf`, `ft_putptr_pf` |
| `ft_printf.h` | prototypes and the base strings `DEC`, `HEX_LOW`, `HEX_UP` |

### How it works

1. **Validation.** `ft_printf` returns `-1` right away if `format` is `NULL`,
   or if it ends with a single unpaired `%`. glibc does the same, and nothing
   is printed.
2. **Single pass over the format.** `ft_process` reads the format string one
   character at a time:
   - a normal character is written as is;
   - a `%` moves to the next character, and `ft_dispatch` handles the conversion.
3. **Dispatch.** `ft_dispatch` is a chain of `if` statements, one per
   conversion. It takes the matching argument with `va_arg` and calls the right
   printer. An unknown conversion such as `%y` is printed literally (`%y`),
   like glibc does.
4. **One number printer for every base.** `ft_putnbr_base_pf(n, base, len)`
   prints any unsigned number recursively: it first prints `n / len`, then the
   digit `base[n % len]`. The same function handles `%u` (`DEC`), `%x`
   (`HEX_LOW`), `%X` (`HEX_UP`) and `%p`.
   - `%d`/`%i` copies the `int` into a `long` before changing the sign, so
     `INT_MIN` does not overflow.
   - `%p` uses `unsigned long long`, so a 64-bit address always fits.
5. **Counting and errors.** Every printer returns the number of characters it
   wrote, or `-1` if `write` failed. The main loop adds up these values and
   stops at the first `-1`. This matches `printf`, which returns `-1` on an
   output error.

### Why this design

- **No buffer and no heap allocation.** The subject forbids re-implementing
  printf's buffer management, so each character goes straight to `write`.
  Without `malloc` there is nothing to free and nothing can leak.
- **`va_list` passed by pointer (`va_list *`).** When a function calls
  `va_arg` on a `va_list` it received by value, the caller's copy becomes
  indeterminate (C standard, 7.16). Passing a pointer keeps a single
  `va_list` that advances correctly on every platform.
- **Return values instead of global state.** Each printer returns its own
  count, so there is no global counter, and errors propagate naturally.
- **Easy to extend.** A new conversion needs one line in `ft_dispatch` and,
  if needed, one printer function. That is the extensibility the subject asks
  for, and it is where the bonus flags would plug in.
- **libft functions.** `ft_strlen` is used to measure strings (and
  `ft_bzero`, `ft_strchr`, `ft_isdigit` in the bonus parser). libft's
  `ft_putchar_fd` and `ft_putstr_fd` return `void`, so a failed `write`
  could not be detected through them. The printers call `write` directly for
  that reason.

### Bonus: flags and field width

The bonus is a separate implementation in `*_bonus.c` / `ft_printf_bonus.h`.
`make bonus` builds it into the same `libftprintf.a`. A `.bonus` stamp file
keeps `make bonus` from relinking when nothing has changed.

| File | Content |
|---|---|
| `ft_printf_bonus.c` | `ft_printf`, format check, dispatcher |
| `ft_parse_bonus.c` | `ft_parse`: reads flags, width and precision into a `t_fmt` |
| `ft_print_chars_bonus.c` | `%c`, `%s` with width / precision |
| `ft_print_nums_bonus.c` | `%d %i %u %x %X %p` with every flag |
| `ft_utils_bonus.c` | `ft_out`, `ft_pad`, `ft_numlen`, `ft_putnbr_base_b` |

**Data structures.**

- `t_fmt` holds one parsed conversion: the five flags, `width`, `prec`
  (`-1` means "no precision") and `conv`. It is filled by `ft_parse`, then
  read by the printers.
- `t_pf` holds the printing state: the `va_list`, the number of characters
  written so far, and an `error` flag. Every write goes through
  `ft_out(pf, ...)`, which updates the count, or sets `error` if `write`
  fails. After an error nothing else is written, and `ft_printf` returns `-1`.
  This keeps error handling in one place instead of checking `-1` after every
  call.

**Number layout.** Every numeric conversion is printed by one function,
`ft_putnum`, as four parts:

```
[spaces][prefix][zeros][digits][spaces]
           │       │       └─ the number in its base (none if precision is 0 and value is 0)
           │       └─ precision - digits, or (with `0` flag) width - prefix - digits
           └─ "-", "+", " ", "0x", "0X" or "" depending on sign and flags
```

Leading spaces are `width - total` when `-` is not set, trailing spaces when it
is. The length of every part is computed first, so nothing is built in memory
and no `malloc` is needed.

## Resources

- `man 3 printf`: the reference behaviour that ft_printf is compared against
- `man 3 stdarg`: `va_start`, `va_arg`, `va_copy`, `va_end`
- [cppreference: Variadic functions](https://en.cppreference.com/w/c/variadic)
- [cppreference: printf format specification](https://en.cppreference.com/w/c/io/fprintf)
- ISO/IEC 9899 (C standard), section 7.16 "Variable arguments" and section 7.21.6.1 "The fprintf function"
- The 42 Norm (norminette) documentation

### Use of AI

An AI assistant (Claude, by Anthropic) was used during this project for these tasks:

- **Code review:** it read the author's own first implementation and explained
  the bugs it found. These included a call to a commented-out function, a
  missing `va_end`, `va_list` passed by value, the return count for `%%` and
  unknown conversions, `NULL` format handling, and Norm violations.
- **Testing:** it wrote a test harness that compares `ft_printf` with the libc
  `printf`, byte for byte, together with the return value (105 cases). It also
  wrote a generator for the bonus that tries every flag / width / precision
  combination on every conversion (48,971 cases). It ran the tests under
  AddressSanitizer and UndefinedBehaviorSanitizer and checked the edge cases:
  closed stdout and `NULL` format.
- **Reference implementation:** it wrote the version of `ft_printf.c`,
  `ft_print_chars.c`, `ft_print_nums.c`, `ft_printf.h` and the `Makefile` in
  this repository, based on the author's design, plus all the `*_bonus` files.
- **Documentation:** it drafted this README.
