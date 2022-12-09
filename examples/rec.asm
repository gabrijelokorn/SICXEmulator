fak   START   0

stackinit   +LDA     #stacktop
            SUB     #3
            STA     esp
            STA     ebp
            RSUB

stackpush   LDA     esp
            SUB     #3
            STA     esp
            RSUB

stackpop    LDA     esp
            ADD     #3
            STA     esp
            RSUB

fac         
            STL     @esp
            JSUB    stackpush
            
            LDA     ebp
            STA     @esp
            LDA     esp
            STA     ebp
            JSUB    stackpush

            LDA     ebp
            ADD     #6
            STA     stadr
            LDA     @stadr

            COMP    nic
            JGT     cont

            LDT     #1
            LDA     ebp
            ADD     #3
            STA     rtadr
            LDL     @rtadr

            LDA     ebp
            ADD     #6
            STA     esp
            LDA     @ebp
            STA     ebp
            RSUB

cont        
            SUB     #1
            STA     @esp
            JSUB    stackpush
            JSUB    fac

            LDA     ebp
            ADD     #6
            STA     stadr
            LDA     @stadr

            MULR    A, T

            LDA     ebp
            ADD     #3
            STA     rtadr
            LDL     @rtadr
            
            LDA     ebp
            ADD     #6
            STA     esp
            LDA     @ebp
            STA     ebp

            RSUB

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
        
luup    
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

        J       luup

konc    
        LDX     #0
lip     
        LDA     res, X
        WD      #211

        LDA     #3
        ADDR    A, X

        LDA     #19
        COMPR   X, A
        JLT     lip
        CLEAR   X
        RSUB

first       CLEAR   A
            JSUB    stackinit

lup         
            CLEAR   A
            RD      #0xFA
            STA     stevilo
            LDS     #10
            LDT     #0x20
            COMPR   A, S
            JEQ     lup
            COMPR   A, T
            JEQ     lup
            LDS     #0
            COMPR   A, S
            JEQ     halt

            LDA     stevilo
            SUB     #0x30
            .DIV     #16
            .MUL     #16
            .LDS     stevilo
            .SUBR    A, S
            STA     stevilo

            LDA     stevilo
            STA     @esp
            JSUB    stackpush

            JSUB    fac
            CLEAR   A
            ADDR    T, A
            STA     numm
            JSUB    num
            +LDA    #1000000
            STA     del
            LDA     #10
            WD      #211
            J       lup


halt        J       halt
            END     first



esp         WORD    0x0
ebp         WORD    0
stevilo     WORD    10
nic         WORD    1
stadr       WORD    0
rtadr       WORD    0

numm    WORD    8388607
munn    RESW    1
del     WORD    1000000
res     RESW    7

            ORG     0x400
stack       RESW    4096
stacktop    RESW    1
