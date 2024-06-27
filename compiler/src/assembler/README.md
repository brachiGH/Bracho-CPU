# Usage & Documentation

[Usage and the Instruction Set In Detail](https://brachigh.github.io/Bracho-CPU/bracho-cpu/components/alu/usage-&-documentation.html)

> note:
>
> * This a little-endian system, stores the least-significant byte at the smallest address.
> * The Assembler will add a NOP instruction in the beginning automaticaly. Because the content of the adrress 0x000 is the default for the data bus.
> * The assembler will ignore any characters that are not digits (0-9), lowercase letters (a-z), uppercase letters (A-Z), '#', 'space', '@', ':', '_', '[', ']' or '\n'.
> * Every Variable should be initialed.

# build

```console
make p=assembler
```

# Usage

generate binary code using the assembler.

```console
./assembler file.asm
```

`file.asm` is your assembly file.
