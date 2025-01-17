BEGIN PGM Tool-check MM
; Program to check if a tool has a tool length
; Written by Martin Bjoersberg
; Tested in a DMG DMU 60eVo with a PH150
; Controll Heidenhain TNC640

FN 18: SYSREAD Q1 = ID20 NR1 ; What tool is in the spindle?
FN 18: SYSREAD Q2 = ID50 NR19 IDXQ1 ; What is the R-OFFS for the tool?
FN 18: SYSREAD Q3 = ID50 NR36 IDXQ1 ; What typ of tool?
FN 18: SYSREAD Q4 = ID50 NR1 IDXQ1 ; What is the length for the tool?


Q5 = INT Q4 
FN 9: IF +Q4 EQU +Q5 GOTO LBL 1 ; Is the tool length set?
FN 9: IF +1 EQU +1 GOTO LBL 30


LBL 1 ; Measure the tool
FN 9: IF +Q3 EQU +0 GOTO LBL 2 ; Is it a mill?

; Length
TCH PROBE 584 VT-LAENGD, VT-RADIE ~
    Q350=+3    ;MAETFORM ~
    Q351=+1    ;MAETOMFANG ~
    Q352=+0    ;SKAERKONTROLL ~
    Q355=-1    ;MEASURING POSITION ~
    Q361=+3    ;DIGILOG/SWITCHED ~
    Q362=+0.01 ;SPRIDNINGSTOLERANS ~
    Q359=+0    ;ADD.LAENGDKORRIGER. ~
    Q360=+0    ;ADD.RADIEKORRIGERING
M28
FN 9: IF +1 EQU +1 GOTO LBL 30


LBL 2
; Offset length
TCH PROBE 584 VT-LAENGD, VT-RADIE ~
    Q350=+0    ;MAETFORM ~
    Q351=+1    ;MAETOMFANG ~
    Q352=+0    ;SKAERKONTROLL ~
    Q355=-1    ;MEASURING POSITION ~
    Q361=+3    ;DIGILOG/SWITCHED ~
    Q362=+0.01 ;SPRIDNINGSTOLERANS ~
    Q359=+0    ;ADD.LAENGDKORRIGER. ~
    Q360=+0    ;ADD.RADIEKORRIGERING
M28

LBL 30 ; Return to main
END PGM Tool-check MM