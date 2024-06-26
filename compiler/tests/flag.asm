@start:
NOP

# @FF7 <= 32-i
LDB 32
CIN 0xFFF
SUB
STA 0xFF7


# @FF7 <= 32-j
LDB 32
CIN 0xFFE
SUB
STA 0xFF6


# @FF5 <= (32-i)²
BIN 0xFF7
CIN 0xFF7
MULT
STA 0xFF5



# @FF4 <= (32-j)²
BIN 0xFF6
CIN 0xFF6
MULT
STA 0xFF4


# Distance Cubed @FF3 <= (32-i)² + (32-j)²
BIN 0xFF5
CIN 0xFF4
ADD
STA 0xFF3

## Setting the coordinates (i,j)
# @FF2[15:10] <= i
BIN 0xFFF
SHL 6
STA 0xFF2

# @FF2[9:4] <= j
BIN 0xFF2
CIN 0xFFE
ADD
STA 0xFF2
BIN 0xFF2
SHL 4
STA 0xFF2


### if (DistanceCubed < 273)
BIN 0xFF3
LDC 273
SUB
BRN @setthecolortowhite

# set the color to red
BIN 0xFF2
LDC 9 # color red
ADD
OUT
BR @end # JUMP TO THE END OF THE IF STEATMENT 

# set the color to white
@setthecolortowhite:
BIN 0xFF2
LDC 15 # color white
ADD
OUT
### end if


### if (DistanceCubed < 125 && DistanceCubed > 75 && i < 37)
## exit if (DistanceCubed > 75)
@end:
BIN 0xFF3
LDC 75
SUB
BRN @exit

## exit if (DistanceCubed < 125)
LDB 125
CIN 0xFF3
SUB
BRN @exit

## exit if (i < 37)
LDB 37
CIN 0xFFF
SUB
BRN @exit

# set the color to red
BIN 0xFF2
LDC 9 # color red
OR
OUT

@exit:
NOP
### end if


# j++
BIN 0xFFE
LDC 1
ADD
STA 0xFFE

## for j < 64
BIN 0xFFE
LDC 64
SUB
BRN @start

# Rest j = 0
LDB 0
LDC 0
ADD
STA 0xFFE

# i++
BIN 0xFFF
LDC 1
ADD
STA 0xFFF

## for i < 64
BIN 0xFFF
LDC 64
SUB
BRN @start


### END




### drawing the Star in the middle


LDC 0

BIN @ANXBgCxpJD
@ANXBgCxpJD:
0x9589
ADD
OUT

BIN @QsnehmaOsP
@QsnehmaOsP:
0x9599
ADD
OUT

BIN @IXmaZOTnPJ
@IXmaZOTnPJ:
0x99a9
ADD
OUT

BIN @qKWvVmjtTr
@qKWvVmjtTr:
0x99b9
ADD
OUT

BIN @SpLKrzVYsy
@SpLKrzVYsy:
0x9999
ADD
OUT

BIN @MIYCCabmNY
@MIYCCabmNY:
0x9689
ADD
OUT

BIN @pGStogjSgg
@pGStogjSgg:
0x9679
ADD
OUT

BIN @tnmnNlCTPM
@tnmnNlCTPM:
0x9a79
ADD
OUT

BIN @UYRiSVcCxn
@UYRiSVcCxn:
0x9a69
ADD
OUT

BIN @PXHVppcQiB
@PXHVppcQiB:
0x9a59
ADD
OUT

BIN @vTmaDRGIeH
@vTmaDRGIeH:
0x8209
ADD
OUT

BIN @VHABcQQgnE
@VHABcQQgnE:
0x81f9
ADD
OUT

BIN @gIBOmpbIoB
@gIBOmpbIoB:
0x7e09
ADD
OUT

BIN @oSBhPKPkbc
@oSBhPKPkbc:
0x8219
ADD
OUT

BIN @zLgvbzwbGp
@zLgvbzwbGp:
0x8609
ADD
OUT

BIN @uSejlWwcKZ
@uSejlWwcKZ:
0x7df9
ADD
OUT

BIN @UMIrKYPJiz
@UMIrKYPJiz:
0x7e19
ADD
OUT

BIN @PLwxJfAtRI
@PLwxJfAtRI:
0x8619
ADD
OUT

BIN @KBnynjkfAK
@KBnynjkfAK:
0x85f9
ADD
OUT

BIN @ESWmdNhbJF
@ESWmdNhbJF:
0x7a09
ADD
OUT

BIN @hIttDejUSk
@hIttDejUSk:
0x7609
ADD
OUT

BIN @yNwiCdNwRR
@yNwiCdNwRR:
0x81e9
ADD
OUT

BIN @vTWyhIeyVk
@vTWyhIeyVk:
0x81d9
ADD
OUT

BIN @rheiUlCAnE
@rheiUlCAnE:
0x8229
ADD
OUT

BIN @TVvZFxLGIA
@TVvZFxLGIA:
0x8239
ADD
OUT

BIN @lSmXrwamzJ
@lSmXrwamzJ:
0x89f9
ADD
OUT

BIN @FVbIifGluy
@FVbIifGluy:
0x8a09
ADD
OUT

BIN @csnPvakbXv
@csnPvakbXv:
0x8a19
ADD
OUT

BIN @ECpztxCdFK
@ECpztxCdFK:
0x89e9
ADD
OUT

BIN @LAkCMwwhUK
@LAkCMwwhUK:
0x8de9
ADD
OUT

BIN @UBaQziykyf
@UBaQziykyf:
0x8df9
ADD
OUT

BIN @mqcQSrlPTC
@mqcQSrlPTC:
0x8a29
ADD
OUT

BIN @sVSdUxsLAo
@sVSdUxsLAo:
0x8e29
ADD
OUT

BIN @YqwjlsRKqn
@YqwjlsRKqn:
0x8e19
ADD
OUT

HALT