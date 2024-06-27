BR @firstjump
@secondjump:
    STA @variable
    LDB @variable
    LDC @variable
    HALT




@firstjump:
    BIN 0x111
    CIN 0x222

    SUB
    BRN @secondjump


@variable:
    0