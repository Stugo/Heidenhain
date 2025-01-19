BEGIN PGM TOOL-TABLE-CLEANUP MM 
; Program to clean up the tool table after taking out the tools from the magazine
; Written by Martin Bjoersberg
; Tested in a DMG DMU 60eVo with a PH150
; Controll Heidenhain TNC640
;
; Take out the tool from the magazine
; Set the tool range to empty and run this script 
;
FN 0 : Q1 = +10 ; Set first tool to be reset
FN 0: Q2 = +20 ; Last tool to reset
FN 0: Q8 = Q1

LBL 1 ; Start over

FN 17: SYSWRITE ID50 NR0 IDXQ8 = "" ; NAME, untested!
FN 17: SYSWRITE ID50 NR1 IDXQ8 = +0 ; L
FN 17: SYSWRITE ID50 NR2 IDXQ8 = +0 ; R
FN 17: SYSWRITE ID50 NR3 IDXQ8 = +0 ; R2
FN 17: SYSWRITE ID50 NR4 IDXQ8 = +0 ; DL
FN 17: SYSWRITE ID50 NR5 IDXQ8 = +0 ; DR
FN 17: SYSWRITE ID50 NR9 IDXQ8 = +0 ; TIME1
FN 17: SYSWRITE ID50 NR10 IDXQ8 = +0 ; TIME2
FN 17: SYSWRITE ID50 NR11 IDXQ8 = +0 ; CUR_TIME
FN 17: SYSWRITE ID50 NR15 IDXQ8 = +2 ; CUT
FN 17: SYSWRITE ID50 NR16 IDXQ8 = +0.1 ; LTOL
FN 17: SYSWRITE ID50 NR17 IDXQ8 = +0.1 ; RTOL
FN 17: SYSWRITE ID50 NR19 IDXQ8 = +0 ; R-OFFS
FN 17: SYSWRITE ID50 NR20 IDXQ8 = +0 ; L-OFFS
FN 17: SYSWRITE ID50 NR21 IDXQ8 = +0 ; LBREAK
FN 17: SYSWRITE ID50 NR22 IDXQ8 = +0 ; RBREAK
FN 17: SYSWRITE ID50 NR36 IDXQ8 = +0 ; Tool type

LBL 3; Counting logic
FN 1: Q8 = +Q8 + +1 ; Increment the tool number
FN 11: IF +Q8 GT +Q2 GOTO LBL 5 
FN 9: IF +1 EQU +1 GOTO LBL 1

LBL 5 ; End
M30

END PGM TOOL-TABLE-CLEANUP MM