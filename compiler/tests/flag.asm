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
@setthecolortowhite BIN 0xFF2
LDC 15 # color white
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
OR
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




### drawing the Star in the middle


LDC 0
BIN @TXidyLLtMy
@TXidyLLtMy 0x9589
ADD
OUT

BIN @rdwZeksmIj
@rdwZeksmIj 0x9599
ADD
OUT

BIN @ffLZkBxfWT
@ffLZkBxfWT 0x99a9
ADD
OUT

BIN @IvcheiSnmp
@IvcheiSnmp 0x99b9
ADD
OUT

BIN @LNfIlnLzpc
@LNfIlnLzpc 0x9999
ADD
OUT

BIN @bPkxvhadgk
@bPkxvhadgk 0x9689
ADD
OUT

BIN @daSUsVKvBc
@daSUsVKvBc 0x9679
ADD
OUT

BIN @cNVKCOKiNA
@cNVKCOKiNA 0x9a79
ADD
OUT

BIN @fzBjdMFxYp
@fzBjdMFxYp 0x9a69
ADD
OUT

BIN @tDbMxyXLqN
@tDbMxyXLqN 0x9a59
ADD
OUT

BIN @TkTnROyQDs
@TkTnROyQDs 0x8209
ADD
OUT

BIN @ysAxWkESZo
@ysAxWkESZo 0x81f9
ADD
OUT

BIN @ByJdezUXLM
@ByJdezUXLM 0x7e09
ADD
OUT

BIN @EneSknCQRz
@EneSknCQRz 0x8219
ADD
OUT

BIN @UDmrgSduEP
@UDmrgSduEP 0x8609
ADD
OUT

BIN @eHZGSQmiLL
@eHZGSQmiLL 0x7df9
ADD
OUT

BIN @aehtxheLtg
@aehtxheLtg 0x7e19
ADD
OUT

BIN @cmLPwpYXQt
@cmLPwpYXQt 0x8619
ADD
OUT

BIN @reoiQxDuNH
@reoiQxDuNH 0x85f9
ADD
OUT

BIN @SSPKpuRanV
@SSPKpuRanV 0x7a09
ADD
OUT

BIN @mDSFWiqZsc
@mDSFWiqZsc 0x7609
ADD
OUT

BIN @MQzMCzrnRW
@MQzMCzrnRW 0x81e9
ADD
OUT

BIN @zFAcNlyMCW
@zFAcNlyMCW 0x81d9
ADD
OUT

BIN @zLcijTctdb
@zLcijTctdb 0x8229
ADD
OUT

BIN @HMXYqIjioX
@HMXYqIjioX 0x8239
ADD
OUT

BIN @fJrGjLhQaL
@fJrGjLhQaL 0x89f9
ADD
OUT

BIN @KbpDyiKAms
@KbpDyiKAms 0x8a09
ADD
OUT

BIN @oijBGqPHqd
@oijBGqPHqd 0x8a19
ADD
OUT

BIN @deoHgARKqa
@deoHgARKqa 0x89e9
ADD
OUT

BIN @EqyfzfDziN
@EqyfzfDziN 0x8de9
ADD
OUT

BIN @yMPlduwWTf
@yMPlduwWTf 0x8df9
ADD
OUT

BIN @vDAifuAHok
@vDAifuAHok 0x8a29
ADD
OUT

BIN @uDWZxxxfdN
@uDWZxxxfdN 0x8e29
ADD
OUT

BIN @hwMONgzfNH
@hwMONgzfNH 0x8e19
ADD
OUT



###end
HALT