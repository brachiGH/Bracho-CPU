export const flag_asm = `####################################### 
#
#   demo tunisian flag:
#   https://brachigh.github.io/Bracho-CPU/docs/bracho-cpu/demos.html
#   Usage & Documentation:
#   https://brachigh.github.io/Bracho-CPU/bracho-cpu/components/alu/usage-&-documentation.html
#
#######################################

@start:

# @FF7 <= 32-i
BIN 32
LDC 0xFFF
SUB
STA 0xFF7 # 4087


# @FF7 <= 32-j
BIN 32
LDC 0xFFE
SUB
STA 0xFF6 # 4086


# @FF5 <= (32-i)²
LDB 0xFF7 # 4087
LDC 0xFF7 # 4087
MULT
STA 0xFF5



# @FF4 <= (32-j)²
LDB 0xFF6 # 4086
LDC 0xFF6 # 4086
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
ADD
OUT

LDB @QsnehmaOsP
ADD
OUT

LDB @IXmaZOTnPJ
ADD
OUT

LDB @qKWvVmjtTr
ADD
OUT

LDB @SpLKrzVYsy
ADD
OUT

LDB @MIYCCabmNY
ADD
OUT

LDB @pGStogjSgg
ADD
OUT

LDB @tnmnNlCTPM
ADD
OUT

LDB @UYRiSVcCxn
ADD
OUT

LDB @PXHVppcQiB
ADD
OUT

LDB @vTmaDRGIeH
ADD
OUT

LDB @VHABcQQgnE
ADD
OUT

LDB @gIBOmpbIoB
ADD
OUT

LDB @oSBhPKPkbc
ADD
OUT

LDB @zLgvbzwbGp
ADD
OUT

LDB @uSejlWwcKZ
ADD
OUT

LDB @UMIrKYPJiz
ADD
OUT

LDB @PLwxJfAtRI
ADD
OUT

LDB @KBnynjkfAK
ADD
OUT

LDB @ESWmdNhbJF
ADD
OUT

LDB @hIttDejUSk
ADD
OUT

LDB @yNwiCdNwRR
ADD
OUT

LDB @vTWyhIeyVk
ADD
OUT

LDB @rheiUlCAnE
ADD
OUT

LDB @TVvZFxLGIA
ADD
OUT

LDB @lSmXrwamzJ
ADD
OUT

LDB @FVbIifGluy
ADD
OUT

LDB @csnPvakbXv
ADD
OUT

LDB @ECpztxCdFK
ADD
OUT

LDB @LAkCMwwhUK
ADD
OUT

LDB @UBaQziykyf
ADD
OUT

LDB @mqcQSrlPTC
ADD
OUT

LDB @sVSdUxsLAo
ADD
OUT

LDB @YqwjlsRKqn
ADD
OUT


HALT

@UMIrKYPJiz:
0x7e19
@PLwxJfAtRI:
0x8619
@zLgvbzwbGp:
0x8609
@oSBhPKPkbc:
0x8219
@uSejlWwcKZ:
0x7df9
@VHABcQQgnE:
0x81f9
@KBnynjkfAK:
0x85f9
@yNwiCdNwRR:
0x81e9
@vTWyhIeyVk:
0x81d9
@rheiUlCAnE:
0x8229
@TVvZFxLGIA:
0x8239
@FVbIifGluy:
0x8a09
@ECpztxCdFK:
0x89e9
@LAkCMwwhUK:
0x8de9
@UBaQziykyf:
0x8df9
@mqcQSrlPTC:
0x8a29
@sVSdUxsLAo:
0x8e29
@ANXBgCxpJD:
0x9589
@QsnehmaOsP:
0x9599
@IXmaZOTnPJ:
0x99a9
@qKWvVmjtTr:
0x99b9
@pGStogjSgg:
0x9679
@SpLKrzVYsy:
0x9999
@MIYCCabmNY:
0x9689
@tnmnNlCTPM:
0x9a79
@UYRiSVcCxn:
0x9a69
@PXHVppcQiB:
0x9a59
@ESWmdNhbJF:
0x7a09
@csnPvakbXv:
0x8a19
@gIBOmpbIoB:
0x7e09
@vTmaDRGIeH:
0x8209
@YqwjlsRKqn:
0x8e19
@hIttDejUSk:
0x7609
@lSmXrwamzJ:
0x89f9

HALT`