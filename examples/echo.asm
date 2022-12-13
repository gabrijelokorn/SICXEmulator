.ker je beseda max 24 bitna je pri num 
.največja pozitivna številka 8388607

echo   START   0

char    WD      #1
        RSUB

nl      LDA     #10
        WD      #1
        RSUB

string  +LDA    #0x4142
        +STA    beseda
        CLEAR   X
        LDS     #1

loop    LDCH    beseda, X
        ADDR    S, X
        COMP    #0
        JEQ     nw
        WD      #69
        J       loop

nw      RSUB

mod     LDA     munn
        LDS     del
        DIVR    S, A
        MULR    S, A
        LDS     munn
        SUBR    A, S
        STS     munn
        J       nad    


num     LDA     numm
        STA     munn
        
lup    
        LDA     munn
        LDS     del

        DIVR    S, A
        ADD     #0x30
        STA     res, X

        LDA     #3
        ADDR    A, X

        J       mod
        LDA     munn

nad     
        LDS     del
        LDA     #10
        DIVR    A, S
        STS     del
        LDA     #0
        COMPR   A, S
        JEQ     konc

        J       lup

konc    
        +LDX     #0
lip     
        LDA     res, X
        WD      #70

        LDA     #3
        ADDR    A, X

        LDA     #19
        COMPR   X, A
        JLT     lip
        RSUB    


first   .LDA     #0x46
        .JSUB    char
        .JSUB    nl
        .JSUB    string
        JSUB    num
        END     first
halt    J       halt


        ORG     200
beseda  RESW    1
numm    WORD    8388607
munn    RESW    1
del     WORD    1000000
res     RESW    7
