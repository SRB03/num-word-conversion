# Num Word Conversion

Small, single-file C program to convert between English words and numeric values.

This repository contains `main.c` which now supports two directions:

- Words -> Number
- Number -> Words

It also supports both Indian and International naming/formatting:

- Indian naming/format: `lakh`, `crore` and Indian comma grouping (e.g. 1,23,456)
- International naming/format: `million`, `billion` and standard grouping (e.g. 1,234,567)

## Features
- Recognizes words for 1–19 (`one`..`nineteen`).
- Recognizes tens (`twenty`, `thirty`, ..., `ninety`).
- Recognizes multipliers: `hundred`, `thousand`, `lakh`, `crore`, `million`, `billion`.
- Converts numbers to words (both Indian and International naming schemes).
- Menu-driven: the program asks whether you want Words→Number or Number→Words and whether to use Indian or International formats.

## Examples

Words → Number (Indian naming allowed)

Input:
```
one crore twenty three lakh forty five thousand six hundred seventy eight
```
Output:
```
Numeric value: 12345678
```

Number → Words

Input: `14256`

Output (International naming):
```
In words: Fourteen thousand two hundred fifty six
```

Input: `12345678` (Indian naming)

Output:
```
In words: One crore twenty three lakh forty five thousand six hundred seventy eight
```

## Notes & Limitations

- The program prints `Unrecognized word: <token>` for any token it doesn't understand and continues parsing.
- Negative numbers are supported for Number→Words (the output is prefixed with "minus").
- Very large numbers may exceed 64-bit range; the program uses `long long` for numeric values — avoid inputs above approx 9e18.
