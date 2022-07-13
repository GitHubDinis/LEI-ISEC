; TRABALHO PRÁTICO DE TECNOLOGIAS E ARQUITETURA DE COMPUTADORES (1º ANO, 2º SEMESTRE)
; 2021/2022
; Dinis Meireles de Sousa Falcão - 2020130403
; David Seco Rodrigues - 2019130152

.8086
.model small
.stack 2048h

dseg    segment para public 'data'

	; BEM-VINDO MENU:

		Bem_Vindo	db "Bem-vindo ao Jogo Sopa de Letras!          ",13,10
					db "Prima qualquer tecla para continuar...     ",13,10,'$'

	; MENU INICIAL:

		MenuOptions db "                                                          ",13,10
					db "                    **************************************",13,10
					db "                    *                                    *",13,10
					db "                    *                                    *",13,10
					db "                    *   ISEC - Trabalho Pratico de TAC   *",13,10
					db "                    *                                    *",13,10
					db "                    *                                    *",13,10
					db "                    *             1. Jogar               *",13,10
					db "                    *             2. Top 10              *",13,10
					db "                    *             3. Ajuda               *",13,10
					db "                    *             4. Teclas              *",13,10
					db "                    *             5. Sair                *",13,10
					db "                    *                                    *",13,10
					db "                    **************************************",13,10
					db "                                                          ",13,10
					db "                                                          ",13,10
					db "                                                          ",13,10,'$'

	; MENU AJUDA:

		Ajuda       db "                                                          ",13,10
					db "                    **************************************",13,10
					db "                    *                                    *",13,10
					db "                    *                Ajuda:              *",13,10
					db "                    *                                    *",13,10
					db "                    *   Neste jogo seras colocado numa   *",13,10
					db "                    *     Sopa de Letras. Vais ter de    *",13,10
					db "                    *  selecionar letras para encontrar  *",13,10
					db "                    *       as palavras solicitadas.     *",13,10
					db "                    *                                    *",13,10
					db "                    *       Seras pontuado com base      *",13,10
					db "                    *     no tempo com que demoraste     *",13,10
					db "                    *       a encontrar as palavras.     *",13,10
					db "                    *                                    *",13,10
					db "                    *              Boa sorte!            *",13,10
					db "                    *                                    *",13,10
					db "                    **************************************",13,10
					db "                                                          ",13,10
					db "                                                          ",13,10,'$'

	; MENU TECLAS:
	
		Teclas      db "                                                           ",13,10
					db "                    ***************************************",13,10
					db "                    *                                     *",13,10
					db "                    *                Teclas:              *",13,10
					db "                    *                                     *",13,10
					db "                    *                                     *",13,10
					db "                    *  Seta esquerda: movimenta esquerda  *",13,10
					db "                    *   Seta direita: movimenta direita   *",13,10
					db "                    *      Seta cima: movimenta cima      *",13,10
					db "                    *     Seta baixo: movimenta baixo     *",13,10
					db "                    *       Enter: selecionar letra       *",13,10
					db "                    *               Esc: sair             *",13,10
					db "                    *                                     *",13,10
					db "                    *                                     *",13,10
					db "                    *          Simples e Eficaz!          *",13,10
					db "                    *                                     *",13,10
					db "                    ***************************************",13,10
					db "                                                           ",13,10
					db "                                                           ",13,10,'$'

	; MENU TOP10:

		CarrTop10	db "Prima qualquer tecla para voltar ao menu!               ",13,10
					db "                                                       	",13,10
					db "                                                       	",13,10
					db " Top 10:												",13,10,'$'
	
		FichTop10	db 'TOP10.TXT',0
	
	; IMPRIME FICHEIRO:

        Erro_Open       db      'Erro ao tentar abrir o ficheiro$'
        Erro_Ler_Msg    db      'Erro ao tentar ler do ficheiro$'
        Erro_Close      db      'Erro ao tentar fechar o ficheiro$'
        Fich         	db      'DADOS.TXT',0
        HandleFich      dw      0
        car_fich        db      ?
	
	; ASSINALA CARÁCTER:

		Car			db	32	; Guarda um caracter do Ecran 
		Cor			db	7	; Guarda os atributos de cor do caracter

	; RELÓGIO:

		STR12	 		DB 		"            "	; String para 12 digitos	
		NUMERO		DB		"                    $", 	; String destinada a guardar o número lido
		
	
		NUM_SP		db		"                    $" 	; PAra apagar zona de ecran
		DDMMAAAA 		db		"                     "

		Horas			dw		0				; Vai guardar a HORA actual
		Minutos		dw		0				; Vai guardar os minutos actuais
		Segundos		dw		0				; Vai guardar os segundos actuais
		Old_seg		dw		0				; Guarda os últimos segundos que foram lidos

	; COORDENADAS:

		POSy		db	1	; a linha pode ir de [1 .. 25]
		POSx		db	2	; POSx pode ir [1..80]
		POSya		db	1	; posiÇÃo anterior de y
		POSxa		db	2	; posiÇÃo anterior de x
		POSxlista   db  ?	; posição na lista de palavras
		POSylista   db  ?	; posição na lista de palavras

	; STRING PALAVRAS:

		StringS 	db "            $" ; STRING PARA GUARDAR O CONJUNTO DE LETRAS SELECIONADAS
		tentativas	db	?

dseg    ends

cseg    segment para public 'code'
		assume  cs:cseg, ds:dseg

; POSIÇÃO DO CURSOR (MACRO):

goto_xy	macro	POSx,POSy	; coloca o cursor na posição (POSx,POSy)
		mov		ah,02h
		mov		bh,0		; número da página
		mov		dl,POSx
		mov		dh,POSy
		int		10h
endm

; MOSTRA - Faz o display de uma string terminada em $:

MOSTRA MACRO STR 

	MOV AH,09H			; Print string

	LEA DX,STR 

	INT 21H

ENDM

; HORAS  - LÊ HORA DO SISTEMA E COLOCA EM TRÊS VARIÁVEIS (Horas, Minutos, Segundos):
; CH - Horas, CL - Minutos, DH - Segundos.

Ler_TEMPO PROC	
 
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
	
		PUSHF
		
		MOV AH, 2CH             ; Buscar a hORAS
		INT 21H                 
		
		XOR AX,AX
		MOV AL, DH              ; segundos para al
		mov Segundos, AX		; guarda segundos na variavel correspondente
		
		XOR AX,AX
		MOV AL, CL              ; Minutos para al
		mov Minutos, AX         ; guarda MINUTOS na variavel correspondente
		
		XOR AX,AX
		MOV AL, CH              ; Horas para al
		mov Horas,AX			; guarda HORAS na variavel correspondente
 
		POPF
		POP DX
		POP CX
		POP BX
		POP AX
 		RET 
Ler_TEMPO   ENDP

; HOJE - LÊ DATA DO SISTEMA E COLOCA NUMA STRING NA FORMA DD/MM/AAAA:
; CX - ANO, DH - MES, DL - DIA.

HOJE PROC	

		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		PUSH SI
		PUSHF
		
		MOV AH, 2AH             ; Buscar a data
		INT 21H                 
		PUSH CX                 ; Ano-> PILHA
		XOR CX,CX              	; limpa CX
		MOV CL, DH              ; Mes para CL
		PUSH CX                 ; Mes-> PILHA
		MOV CL, DL				; Dia para CL
		PUSH CX                 ; Dia -> PILHA
		XOR DH,DH                    
		XOR	SI,SI
; DIA ------------------ 
; DX=DX/AX --- RESTO DX   
		XOR DX,DX               ; Limpa DX
		POP AX                  ; Tira dia da pilha
		MOV CX, 0               ; CX = 0 
		MOV BX, 10              ; Divisor
		MOV	CX,2
DD_DIV:                         
		DIV BX                  ; Divide por 10
		PUSH DX                 ; Resto para pilha
		MOV DX, 0               ; Limpa resto
		loop dd_div
		MOV	CX,2
DD_RESTO:
		POP DX                  ; Resto da divisao
		ADD DL, 30h             ; ADD 30h (2) to DL
		MOV DDMMAAAA[SI],DL
		INC	SI
		LOOP DD_RESTO            
		MOV DL, '/'             ; Separador
		MOV DDMMAAAA[SI],DL
		INC SI
; MES -------------------
; DX=DX/AX --- RESTO DX
		MOV DX, 0               ; Limpar DX
		POP AX                  ; Tira mes da pilha
		XOR CX,CX               
		MOV BX, 10				; Divisor
		MOV CX,2
MM_DIV:                         
		DIV BX                  ; Divisao or 10
		PUSH DX                 ; Resto para pilha
		MOV DX, 0               ; Limpa resto
		LOOP MM_DIV
		MOV CX,2 
MM_RESTO:
		POP DX                  ; Resto
		ADD DL, 30h             ; SOMA 30h
		MOV DDMMAAAA[SI],DL
		INC SI		
		LOOP MM_RESTO
		
		MOV DL, '/'             ; Character to display goes in DL
		MOV DDMMAAAA[SI],DL
		INC SI
 
;  ANO ----------------------
		MOV DX, 0               
		POP AX                  ; mes para AX
		MOV CX, 0               ; 
		MOV BX, 10              ; 
 AA_DIV:                         
		DIV BX                   
		PUSH DX                 ; Guarda resto
		ADD CX, 1               ; Soma 1 contador
		MOV DX, 0               ; Limpa resto
		CMP AX, 0               ; Compara quotient com zero
		JNE AA_DIV              ; Se nao zero
AA_RESTO:
		POP DX                  
		ADD DL, 30h             ; ADD 30h (2) to DL
		MOV DDMMAAAA[SI],DL
		INC SI
		LOOP AA_RESTO
		POPF
		POP SI
		POP DX
		POP CX
		POP BX
		POP AX
 		RET 
HOJE   ENDP

; LÊ UMA TECLA:	 
; Parâmetros de saída: (al, ah);
; al - código da tecla premida;
; ah=0 => caracter normal ; ah=1 => Tecla Extendida (cursor, F1, F2, etc.)

LE_TECLA	PROC
sem_tecla:
	call Trata_Horas
	MOV	AH,0BH				; Check standard input status
	INT 21h
	cmp AL,0
	je	sem_tecla
	
	MOV	AH,08H				; Wait for console input without echo
	INT	21H
	MOV	AH,0
	CMP	AL,0
	JNE	SAI_TECLA

	MOV	AH, 08H				; Wait for console input without echo
	INT	21H
	MOV	AH,1				; Keyboard input with echo
SAI_TECLA:	
	RET
LE_TECLA	endp

; ROTINA PARA APAGAR ECRÃ - Escreve o carecter SPACE em todas as posições do Ecrã:

apaga_ecran	proc
		mov		ax,0B800h
		mov		es,ax

		xor		bx,bx
		mov		cx,25*80
		
apaga:	mov		byte ptr es:[bx],' '	; Caracter SPACE
		mov		byte ptr es:[bx+1],7	; Caracteristicas de COR
		inc		bx
		inc 	bx
		loop	apaga
		ret
apaga_ecran	endp

; IMPRIME O TEMPO E DATA NO MONITOR:

Trata_Horas PROC

		PUSHF
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX		

		CALL 	Ler_TEMPO				; Horas MINUTOS e segundos do Sistema
		
		MOV		AX, Segundos
		cmp		AX, Old_seg			; VErifica se os segundos mudaram desde a ultima leitura
		je		fim_horas			; Se a hora não mudou desde a última leitura sai.
		mov		Old_seg, AX			; Se segundos são diferentes actualiza informação do tempo 
		
		mov 	ax,Horas
		MOV		bl, 10     
		div 	bl
		add 	al, 30h				; Caracter Correspondente às dezenas
		add		ah,	30h				; Caracter Correspondente às unidades
		MOV 	STR12[0],al			
		MOV 	STR12[1],ah
		MOV 	STR12[2],'h'		
		MOV 	STR12[3],'$'
		GOTO_XY 1,24
		MOSTRA STR12 		
        
		mov 	ax,Minutos
		MOV 	bl, 10     
		div 	bl
		add 	al, 30h				; Caracter Correspondente às dezenas
		add		ah,	30h				; Caracter Correspondente às unidades
		MOV 	STR12[0],al			; 
		MOV 	STR12[1],ah
		MOV 	STR12[2],'m'		
		MOV 	STR12[3],'$'
		GOTO_XY	6,24
		MOSTRA	STR12 		
		
		mov 	ax,Segundos
		MOV 	bl, 10     
		div 	bl
		add 	al, 30h				; Caracter Correspondente às dezenas
		add		ah,	30h				; Caracter Correspondente às unidades
		MOV 	STR12[0],al			; 
		MOV 	STR12[1],ah
		MOV 	STR12[2],'s'		
		MOV 	STR12[3],'$'
		GOTO_XY	10,24
		MOSTRA	STR12 		
        
		CALL 	HOJE				; Data de HOJE
		MOV 	al ,DDMMAAAA[0]	
		MOV 	STR12[0], al	
		MOV 	al ,DDMMAAAA[1]	
		MOV 	STR12[1], al	
		MOV 	al ,DDMMAAAA[2]	
		MOV 	STR12[2], al	
		MOV 	al ,DDMMAAAA[3]	
		MOV 	STR12[3], al	
		MOV 	al ,DDMMAAAA[4]	
		MOV 	STR12[4], al	
		MOV 	al ,DDMMAAAA[5]	
		MOV 	STR12[5], al	
		MOV 	al ,DDMMAAAA[6]	
		MOV 	STR12[6], al	
		MOV 	al ,DDMMAAAA[7]	
		MOV 	STR12[7], al	
		MOV 	al ,DDMMAAAA[8]	
		MOV 	STR12[8], al
		MOV 	al ,DDMMAAAA[9]	
		MOV 	STR12[9], al		
		MOV 	STR12[10],'$'
		GOTO_XY	68,24
		MOSTRA	STR12 	
		
fim_horas:		
		goto_xy	POSx,POSy			; Volta a colocar o cursor onde estava antes de actualizar as horas
		
		POPF
		POP DX		
		POP CX
		POP BX
		POP AX
		RET		
			
Trata_Horas ENDP

; IMPRIME FICHEIRO:

imp_Ficheiro	proc		

;abre ficheiro
        mov     ah,3dh			; Open file using handle
        mov     al,0
        lea     dx,Fich
        int     21h
        jc      erro_abrir
        mov     HandleFich,ax
        jmp     ler_ciclo

erro_abrir:
        mov     ah,09h			; Print string
        lea     dx,Erro_Open
        int     21h
        jmp     sai

ler_ciclo:
        mov     ah,3fh			; Read file or device using handle
        mov     bx,HandleFich
        mov     cx,1
        lea     dx,car_fich
        int     21h
		jc		erro_ler
		cmp		ax,0		;EOF?
		je		fecha_ficheiro
        mov     ah,02h			; Display output
		mov		dl,car_fich
		int		21h
		jmp		ler_ciclo

erro_ler:
        mov     ah,09h			; Print string
        lea     dx,Erro_Ler_Msg
        int     21h

fecha_ficheiro:
        mov     ah,3eh			; Close file using handle
        mov     bx,HandleFich
        int     21h
        jnc     sai

        mov     ah,09h			; Print string
        lea     dx,Erro_Close
        Int     21h
sai:
		ret
imp_Ficheiro	endp

; ASSINALA CARÁCTER NO ECRÃ:

assinala_P	PROC
CICLO:	
		goto_xy	POSx,POSy	; Vai para nova posição
		mov 	ah, 08h
		mov		bh,0		; numero da página
		int		10h		
		mov		Car, al		; Guarda o Caracter que está na posição do Cursor
		mov		Cor, ah		; Guarda a cor que está na posição do Cursor
		
		goto_xy	35,10		; Mostra o caracter que estava na posição do Cursor
		mov		ah, 02h		; IMPRIME caracter da posição no canto
		mov		dl, Car	
		int		21H			

		goto_xy	POSx,POSy

	; COMPARA COM O CARACTER DA PAREDE:

		cmp		al, 177
		je		PAREDE
	
LER_SETA:	
		call 	LE_TECLA
		cmp		ah, 1
		je		ESTEND
		
		CMP 	AL, 27	; ESCAPE para sair do Programa
		JE		FIM
		CMP		AL, 13	; ENTER para alterar a cor do caracter na posicão do cursor
		je		ASSINALA
		jmp		LER_SETA
		
ESTEND:	cmp 	al,48h
		jne		BAIXO
		dec		POSy		;Cima
		jmp		CICLO

BAIXO:	cmp		al,50h
		jne		ESQUERDA
		inc 	POSy		;Baixo
		jmp		CICLO

ESQUERDA:
		cmp		al,4Bh
		jne		DIREITA
		dec		POSx		;Esquerda
		dec		POSx		;Esquerda
		jmp		CICLO

DIREITA:
		cmp		al,4Dh
		jne		LER_SETA 
		inc		POSx		;Direita
		inc		POSx		;Direita
		jmp		CICLO

ASSINALA:
		mov		bl, cor		; BL = character attribute (text) foreground color (graphics)
		not		bl			; altera a cor
		mov		cor, bl		; altera a cor
		mov 	ah, 09h     ; AH = 09 
		mov		al, car		; AL = ASCII character to write
		mov		bh, 0		; BH = display page  (or mode 13h, background pixel value)
		mov		cx, 1		; CX = count of characters to write (CX >= 1)
		int		10h			; INT 10,9 - Write Character and Attribute at Cursor Position
		jmp		CICLO

; GERENCIADOR DE DETEÇÃO DE PAREDES:

PAREDE:
		mov		al, POSxa	   
		mov		POSx, al
		mov		al, POSya	 
		mov 	POSy, al
		jmp 	CICLO
fim:	
		RET
assinala_P	endp

; ENCONTRAR PALAVRAS:

AssinalaPalavras proc

		cmp POSylista, 0
		;jne ENCONTRADAS
		mov POSylista, 29
		mov POSxlista, 1
		
CICLO:	
		goto_xy	POSxlista,POSylista		; Vai para nova posição
		mov 	ah, 08h
		mov		bh,0				; numero da página
		int		10h		
		cmp 	Car, al
		je 		GUARDA
		inc 	POSylista
		cmp 	POSylista, 9
		ja 		TENTATIVA
		jmp 	CICLO

CICLO2:
		goto_xy	POSxlista,POSylista		; Vai para nova posição
		mov 	ah, 08h
		mov		bh,0				; numero da página
		int		10h		
		cmp 	Car, al
		je 		GUARDA
		inc 	POSxlista
		cmp 	POSxlista, 240
		je 		TENTATIVA
		jmp 	GUARDA

AVANCA:
		

GUARDA:
		mov		StringS[si], al		; Guarda o Caracter que está na posição do Cursor
		inc 	si
		jmp 	SAI

TENTATIVA:
		inc 	tentativas
		xor 	si,si
		mov 	POSxlista, 0
		mov 	POSylista, 0 

SAI:
		RET
		
AssinalaPalavras endp

; MENU TOP10:

TOP10	PROC
	call 	apaga_ecran
	goto_xy	1,1
	mov		ah, 09h			; Print string
	lea     dx,CarrTop10
    int     21h

	lefichtop10:
		;abre ficheiro
        mov     ah,3dh		; Open file using handle
        mov     al,0
        lea     dx,FichTop10 ; TOP10.TXT
        int     21h
        jc      erro_fichtop10
        mov     HandleFich,ax
        jmp     ler_top10

	erro_fichtop10:
        mov     ah,09h		; Print string
        lea     dx,Erro_Open
        int     21h
        jmp     fimtop10

	ler_top10:
        mov     ah,3fh		; Read file or device using handle
        mov     bx,HandleFich
        mov     cx,1
        lea     dx,car_fich
        int     21h
		jc		erro_lertop10
		cmp		ax,0		;EOF?
		je		fecha_top10
        mov     ah,02h		; Display output
		mov		dl,car_fich
		int		21h
		jmp		ler_top10

	erro_lertop10:
        mov     ah,09h		; Print string
        lea     dx,Erro_Ler_Msg
        int     21h

	fecha_top10:
        mov     ah,3eh		; Close file using handle
        mov     bx,HandleFich
        int     21h
        jnc     fimtop10

        mov     ah,09h		; Print string
        lea     dx,Erro_Close
        Int     21h

    fimtop10:
		call	MenuInicial        
TOP10	endp

; CÓDIGO ACRESCENTADO:

JOGAR	PROC

	call apaga_ecran   
	goto_xy 0,0
    call imp_Ficheiro

	call assinala_P

	;call assinalaPalavras

	;call LE_TECLA
	cmp al, 27
	je sair

sair:
	call MenuInicial

JOGAR	ENDP

; MENU TECLAS:

CENA	proc

	goto_xy		0,2
    call		apaga_ecran
    lea         dx, Teclas 	; mostra a teclas
    mov         ah, 9		; Print string
    INT			21H
	
	call		MenuInicial
	ret

CENA	endp

; MENU AJUDA:

INSTRUCOES	PROC

	goto_xy		0,2
    call		apaga_ecran
    lea         dx, Ajuda 	; mostra a ajuda
    mov         ah, 9		; Print string
    INT			21H
	
	call		MenuInicial
	ret

INSTRUCOES	ENDP

; IMPRIME O MENU INICIAL:

MostraMenu	proc

	goto_xy   0,3
	lea  dx,  MenuOptions 	; MENU INICIAL
	mov  ah,  9				; Print string
	int  21h
	ret
	
MostraMenu	endp

; LÊ TECLA NO MENU INICIAL:

Le_Tecla_Menu	PROC

nao_ha:	
	mov		ah,0bh		; Check standard input status
	int		21h
	cmp		al,0
	je		nao_ha 		;LOOP

	mov		ah,08h		; Wait for console input without echo
	int		21h
	mov		ah,0
	cmp		al,0
	jne		sucesso

	mov		ah, 08h		; Wait for console input without echo
	int		21h
	mov		ah,1
			
sucesso:	;sai do loop
	RET

Le_Tecla_Menu	endp

; MENU BEM-VINDO:

BoasVindas proc

	call apaga_ecran
	goto_xy 0,20
	mov		ah, 09h			; Print string
	lea		dx, Bem_Vindo 	; mostra o texto de boas vindas ate ao utilizador clicar em qualquer tecla
	int		21h

BoasVindas endp

; MENU INICIAL DO PROGRAMA:

MenuInicial	proc	

	loopMenu: 

		call	Le_Tecla_Menu

		call	apaga_ecran

		call    MostraMenu

		mov ah, 1h		; Keyboard input with echo
		int 21h	

		; CHAMA O PROCEDIMENTO CONFORME A TECLA PRESSIONADA:
		
		cmp 	al, 49 ; 1
		je		OPCJOGAR
		cmp		al, 50 ; 2
		je		OPCTOP10
		cmp		al, 51 ; 3
		je		OPCINSTRUCOES
		cmp  	al, 52 ; 4
		je 		OPCCENA
		cmp		al, 53 ; 5
		je		OPCSAIR
		cmp		al, 27 ; ESC
		je		OPCSAIR
		jmp     loopMenu ; jump -> volta a tentar
		
		; SWITCH:

		OPCJOGAR:
						
			call    JOGAR
			
		OPCTOP10:

			call    TOP10
			
		OPCINSTRUCOES:

			call    INSTRUCOES 
			
		OPCCENA:

			call 	CENA
		
		OPCSAIR:	
			
			mov  ax, 4c00h		; Terminate process with return code
			int  21h

MenuInicial	endp

; MAIN PRINCIPAL:

Main    Proc

        mov     ax,dseg
        mov     ds,ax

		mov		ax,0B800h
		mov		es,ax

		call apaga_ecran

		call BoasVindas

		call MenuInicial

        mov     ah,4ch			; Terminate process with return code
        int     21h
Main    endp
cseg	ends
end     Main     

; FIM DO PROGRAMA.