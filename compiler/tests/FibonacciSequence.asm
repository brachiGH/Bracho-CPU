@nbofsequence:
20
@nthsequence:
1
@n1thsequence:
1
@n1thsequencetemp:
0
@i:
1

@startofloop:
    HALT
    LDB @nbofsequence
    LDC @i
    SUB
    HALT
    BRN @returnsequence

    LDB @nthsequence
    CIN 0
    ADD
    STA @n1thsequencetemp

    LDB @nthsequence
    LDC @n1thsequence
    ADD
    STA @nthsequence

    LDB @n1thsequencetemp
    CIN 0
    ADD
    STA @n1thsequence

    HALT
    LDB @i
    CIN 1
    ADD
    STA @i

    HALT
    BR @startofloop


@returnsequence:
    LDB @n1thsequence
    LDC @nthsequence
    HALT


## The B register should show (2AC2)h = 10946 the 19th fibonacci sequence
## The C register should show (452F)h = 17711 the 20th fibonacci sequence