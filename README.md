# **calc** - Commandline Calculator

Commandline calculator. A simple mathematical term evaluation tool.

## Usage

  - `calc --version` displays the version.
  - `calc <term>`
  - `calc <term> <term_continued> ...` evaluates the given term and:
    - prints out the result and returns 0 on success.
    - prints out `nan` and returns 1 on failure.

## Supported operations

  - Addition `+`
  - Subtraction `-`
  - Multiplication `*`
  - Division `/`
  - Modulo `%`
  - Power `^`
  
## Examples
  
  - `calc` = 0.00000
  - `calc 6` = 6.00000
  - `calc -3.141592653` = -3.141592653
  - `calc 5+2` = 7.00000
  - `calc 5+2 * 3` = 11.00000
  - `calc "(5 + 2) * 3"` = 21.00000
  - `calc 5^2 - 3` = 11.00000
  - ...

## NOTES

  - Take note of how the terminal you use expands parameters before feeding it in to calc.
  - On bash you need to surround the parameters with quotes to escape `*`, `(`, `)` and other expansions.
