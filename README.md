# Toy CPU

An intentionally minimal 8-bit accumulator CPU emulator written in C++ as a C++ and computer architecture reactivation project.

## Instructions

- `0x01` — LDA immediate
- `0x02` — ADD immediate
- `0x03` — STA
- `0xFF` — HLT

The example program loads 2, adds 3, stores the result at memory address `0xF0`, and halts.

## Build

```bash
make run
