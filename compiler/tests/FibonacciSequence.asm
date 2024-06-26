@nbofsequence:
20
@nthsequence:
1
@n-1thsequence:
1
@n-1thsequencetemp:
0
@i:
1

@startofloop:
    BIN @nbofsequence
    CIN @i
    SUB
    BRN @returnsequence

    BIN @nthsequence
    LDC 0
    ADD
    STA @n-1thsequencetemp

    BIN @nthsequence
    CIN @n-1thsequence
    ADD
    STA @nthsequence

    BIN @n-1thsequencetemp
    LDC 0
    ADD
    STA @n-1thsequence

    BIN @i
    LDC 1
    ADD
    STA @i

    BR @startofloop


@returnsequence:
    BIN @n-1thsequence
    CIN @nthsequence
    HALT


## The B register should show (2AC2)h = 10946 the 19th fibonacci sequence
## The C register should show (452F)h = 17711 the 20th fibonacci sequence