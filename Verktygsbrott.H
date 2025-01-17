BEGIN PGM Verktygsbrott MM 
; Program to check if a tool is broken
; Written by Martin Bjoersberg
; Tested in a DMG DMU 60eVo with a PH150
; Controll Heidenhain TNC640
; Value in 'R-OFFS' decides if measured of center
; Value in 'LBREAK' decides tolerance for length


; Move to safe space
L  Z-1 FMAX M91
L  X-596  Y-433 FMAX M91
L  C+0  B+0 FMAX M91


FN 18: SYSREAD Q1 = ID20 NR1 ; What tool is in the spindle?
FN 18: SYSREAD Q2 = ID50 NR19 IDXQ1 ; What is the R-OFFS for the tool?
FN 18: SYSREAD Q3 = ID50 NR36 IDXQ1 ; What typ of tool?
FN 9: IF +Q3 EQU +0 GOTO LBL 1 ; Is it a mill?


TCH PROBE 586 VT-BROTTKONTROLL ~
    Q356=+1    ;MAETRIKTNING ~
    Q357=Q2    ;RADIELL OFFSET ~
    Q359=+0    ;CORR. TO CORE LENGTH      ~
    Q375=+0    ;APPROACH STRATEGY ~
    Q376=+50   ;SAFETY DISTANCE
;
FN 9: IF +1 EQU +1 GOTO LBL 5


LBL 1
22 TCH PROBE 584 VT-LAENGD, VT-RADIE ~
    Q350=-2    ;MAETFORM ~
    Q351=+1    ;MAETOMFANG ~
    Q352=+1    ;SKAERKONTROLL ~
    Q355=-1    ;MEASURING POSITION ~
    Q361=+0    ;DIGILOG/SWITCHED ~
    Q362=+0.005 ;SPRIDNINGSTOLERANS ~
    Q359=+0    ;ADD.LAENGDKORRIGER. ~
    Q360=+0    ;ADD.RADIEKORRIGERING
;
 

LBL 5
FN 9: IF +Q199 EQU +0 GOTO LBL 30 ; Is it broken?

; If broken, quit all
M30

; If OK, return to main
LBL 30

END PGM Verktygsbrott MM 