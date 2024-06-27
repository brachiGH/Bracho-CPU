@start:
NOP

# @FF7 <= 32-i
BIN 32
LDC 0xFFF
SUB
STA 0xFF7


# @FF7 <= 32-j
BIN 32
LDC 0xFFE
SUB
STA 0xFF6


# @FF5 <= (32-i)²
LDB 0xFF7
LDC 0xFF7
MULT
STA 0xFF5



# @FF4 <= (32-j)²
LDB 0xFF6
LDC 0xFF6
MULT
STA 0xFF4


# Distance Cubed @FF3 <= (32-i)² + (32-j)²
LDB 0xFF5
LDC 0xFF4
ADD
STA 0xFF3

## Setting the coordinates (i,j)
# @FF2[15:10] <= i
LDB 0xFFF
SHL 6
STA 0xFF2

# @FF2[9:4] <= j
LDB 0xFF2
LDC 0xFFE
ADD
STA 0xFF2
LDB 0xFF2
SHL 4
STA 0xFF2


### if (DistanceCubed < 273)
LDB 0xFF3
CIN 273
SUB
BRN @setthecolortowhite

# set the color to red
LDB 0xFF2
CIN 9 # color red
ADD
OUT
BR @end # JUMP TO THE END OF THE IF STEATMENT 

# set the color to white
@setthecolortowhite:
LDB 0xFF2
CIN 15 # color white
ADD
OUT
### end if


### if (DistanceCubed < 125 && DistanceCubed > 75 && i < 37)
## exit if (DistanceCubed > 75)
@end:
LDB 0xFF3
CIN 75
SUB
BRN @exit

## exit if (DistanceCubed < 125)
BIN 125
LDC 0xFF3
SUB
BRN @exit

## exit if (i < 37)
BIN 37
LDC 0xFFF
SUB
BRN @exit

# set the color to red
LDB 0xFF2
CIN 9 # color red
OR
OUT

@exit:
NOP
### end if


# j++
LDB 0xFFE
CIN 1
ADD
STA 0xFFE

## for j < 64
LDB 0xFFE
CIN 64
SUB
BRN @start

# Rest j = 0
BIN 0
CIN 0
ADD
STA 0xFFE

# i++
LDB 0xFFF
CIN 1
ADD
STA 0xFFF

## for i < 64
LDB 0xFFF
CIN 64
SUB
BRN @start


### END




### drawing the Star in the middle


CIN 0

LDB @ANXBgCxpJD
@ANXBgCxpJD:
0x9589
ADD
OUT

LDB @QsnehmaOsP
@QsnehmaOsP:
0x9599
ADD
OUT

LDB @IXmaZOTnPJ
@IXmaZOTnPJ:
0x99a9
ADD
OUT

LDB @qKWvVmjtTr
@qKWvVmjtTr:
0x99b9
ADD
OUT

LDB @SpLKrzVYsy
@SpLKrzVYsy:
0x9999
ADD
OUT

LDB @MIYCCabmNY
@MIYCCabmNY:
0x9689
ADD
OUT

LDB @pGStogjSgg
@pGStogjSgg:
0x9679
ADD
OUT

LDB @tnmnNlCTPM
@tnmnNlCTPM:
0x9a79
ADD
OUT

LDB @UYRiSVcCxn
@UYRiSVcCxn:
0x9a69
ADD
OUT

LDB @PXHVppcQiB
@PXHVppcQiB:
0x9a59
ADD
OUT

LDB @vTmaDRGIeH
@vTmaDRGIeH:
0x8209
ADD
OUT

LDB @VHABcQQgnE
@VHABcQQgnE:
0x81f9
ADD
OUT

LDB @gIBOmpbIoB
@gIBOmpbIoB:
0x7e09
ADD
OUT

LDB @oSBhPKPkbc
@oSBhPKPkbc:
0x8219
ADD
OUT

LDB @zLgvbzwbGp
@zLgvbzwbGp:
0x8609
ADD
OUT

LDB @uSejlWwcKZ
@uSejlWwcKZ:
0x7df9
ADD
OUT

LDB @UMIrKYPJiz
@UMIrKYPJiz:
0x7e19
ADD
OUT

LDB @PLwxJfAtRI
@PLwxJfAtRI:
0x8619
ADD
OUT

LDB @KBnynjkfAK
@KBnynjkfAK:
0x85f9
ADD
OUT

LDB @ESWmdNhbJF
@ESWmdNhbJF:
0x7a09
ADD
OUT

LDB @hIttDejUSk
@hIttDejUSk:
0x7609
ADD
OUT

LDB @yNwiCdNwRR
@yNwiCdNwRR:
0x81e9
ADD
OUT

LDB @vTWyhIeyVk
@vTWyhIeyVk:
0x81d9
ADD
OUT

LDB @rheiUlCAnE
@rheiUlCAnE:
0x8229
ADD
OUT

LDB @TVvZFxLGIA
@TVvZFxLGIA:
0x8239
ADD
OUT

LDB @lSmXrwamzJ
@lSmXrwamzJ:
0x89f9
ADD
OUT

LDB @FVbIifGluy
@FVbIifGluy:
0x8a09
ADD
OUT

LDB @csnPvakbXv
@csnPvakbXv:
0x8a19
ADD
OUT

LDB @ECpztxCdFK
@ECpztxCdFK:
0x89e9
ADD
OUT

LDB @LAkCMwwhUK
@LAkCMwwhUK:
0x8de9
ADD
OUT

LDB @UBaQziykyf
@UBaQziykyf:
0x8df9
ADD
OUT

LDB @mqcQSrlPTC
@mqcQSrlPTC:
0x8a29
ADD
OUT

LDB @sVSdUxsLAo
@sVSdUxsLAo:
0x8e29
ADD
OUT

LDB @YqwjlsRKqn
@YqwjlsRKqn:
0x8e19
ADD
OUT

HALT