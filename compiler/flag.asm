@start NOP

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
HALT
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
HALT
OUT
BR @end # JUMP TO THE END OF THE IF STEATMENT 

# set the color to white
@setthecolortowhite BIN 0xFF2
LDC 1111 # color white
ADD
OUT
### end if


### if (DistanceCubed < 125 && DistanceCubed > 75 && i < 37)
## exit if (DistanceCubed > 75)
@end BIN 0xFF3
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
ADD
OUT

@exit NOP
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
HALT