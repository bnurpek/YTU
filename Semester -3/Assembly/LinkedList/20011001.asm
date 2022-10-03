STSG SEGMENT PARA STACK 'STSGM'
	DW 32 DUP (?)
STSG ENDS

DTSG SEGMENT PARA 'DTSGM'
	dizi 	DB 	32 DUP (?)			;dump ettiğimde rahat görmek için maks eleman sayısını
	linkler DB 	32 DUP (?)			;32 olarak aldım. Değiştirirseniz de çalışır.
	head	DW	-1
	n 	DW 	?
	CR	EQU 13
	LF	EQU 10
	bilgi	DB CR, LF, 'Buse Nur Pekmezci - 20011001 ',0
	menu	DB CR, LF, 'MENU', CR, LF, '1 - Dizi olusturma', CR, LF, '2 - Diziyi ekrana bastirma', CR, LF, '3 - Diziye eleman ekleme',0
	menu2	DB CR, LF, 'CIKIS ICIN BU DEGERLER DISINDA BIR SAYI GIREBILIRSINIZ', CR, LF, 'Islemi giriniz: ', 0
	secim	DB ?
	HATA	DB CR, LF, 'Dikkat !!! Sayi vermediniz yeniden giris yapiniz.!!!  ', 0
	DIZIYOK	DB CR, LF, 'Dikkat !!! Dizi olusturulmadi.!!! ',0
	girES   DB CR, LF, 'Dizinin eleman sayisi: ',0
	girD	DB CR, LF, 'Dizi elemanlarini giriniz. ',0	
	girE	DB CR, LF, 'Eklemek istediginiz sayiyi giriniz. ',0	
DTSG ENDS

CDSG SEGMENT PARA 'CDSGM'
	ASSUME CS:CDSG, DS:DTSG, SS:STSG
	ANA 	PROC FAR
	        PUSH DS
        	XOR AX,AX
        	PUSH AX
        	MOV AX, DTSG 
        	MOV DS, AX

BASLANGIC:	MOV AX, OFFSET bilgi
        	CALL PUT_STR			        ;bilgi'yi göster 
		MOV AX, OFFSET menu			;menüyü bastırıyor
		CALL PUT_STR
		MOV AX, OFFSET menu2
		CALL PUT_STR				
		CALL GETN				;seçimi alıyor
		MOV secim, AL
		CMP secim, 1
		JNE COMP2
		CALL ILK				;dizi oluşturma fonksiyonunu çağırıyor
		JMP BASLANGIC
COMP2:		CMP secim, 2
		JNE COMP3
		CMP head, -1
		JNE DIZIVAR
		MOV AX, OFFSET DIZIYOK			
		CALL PUT_STR	
		JMP BASLANGIC				;dizi yoksa başlangıca dönüyor
DIZIVAR:	CALL IKI				;dizi varsa ekrana bastırma fonksiyonunu çağırıyor
		JMP BASLANGIC
COMP3:		CMP secim, 3
		JNE SON
		CALL UC					;eleman ekleme fonksiyonunu çağırıyor
		JMP BASLANGIC
SON:		
        	RETF 
	ANA 	ENDP

ILK	PROC NEAR
        ;------------------------------------------------------------------------
        ; Dizi oluşturma işlemini yapıyor. AX, SI ve DX değerlerini korumak için
	; PUSH/POP yapıyor.
        ;------------------------------------------------------------------------
	PUSH AX
	PUSH CX
	PUSH SI
	MOV AX, OFFSET girES		
	CALL PUT_STR
	CALL GETN				;eleman sayısını AL'ye alıyor
	XOR AH, AH
	MOV n, AX
	MOV CX, n
	XOR SI, SI
	MOV AX, OFFSET girD
	CALL PUT_STR
L1:	CALL GETN				;dizi elemanlarını AL'ye alıyor
	MOV dizi[SI], AL
	CMP head, -1
	JE AYNI
	CALL EKLE				;head varsa ekle fonksiyonunu çağırıyor
	JMP DEVAM
AYNI:	MOV head, SI				;eğer head yoksa yani null gösteriyorsa ilk girilen elemanın indexini head olarak gösteriyor
	MOV linkler[SI], -1			;ilk elemanın işaret ettiği yeri null yapıyor
DEVAM:	INC SI
	LOOP L1
	POP SI
	POP CX
	POP AX
	RET
ILK ENDP

EKLE	PROC NEAR
	;-----------------------------------------------------------------------
	; Eğer head -1 değilse yani belliyse yeni eklenecek elemanın başa mı 
	; ortaya mı sona mı ekleneceğini bulan fonksiyon.
	;-----------------------------------------------------------------------
	PUSH AX				;cmp ile label ile çalışmayacağından karşılaştırmalar için kullanıldı
	PUSH BX				;BX current data değeri gibi iş görüyor
	PUSH DI				;DI prev data değeri gibi iş görüyor
	MOV BX, head
	MOV DI, 0FFFFH
	MOV AL, dizi[SI]
L3:	CMP AL, dizi[BX]
	JNG KUCUK
	CMP linkler[BX], -1
	JE ESIT				;curr datanın gösterdiği -1 olursa sona eklenecek demektir
	MOV DI, BX
	MOV BL, linkler[BX]
	JMP L3
ESIT:	MOV AL, linkler[BX]
	MOV linkler[SI], AL
	MOV AX, SI
	MOV linkler[BX], AL
	JMP ENDE
KUCUK:	CMP DI, -1			;eğer DI hiç değişmemişse başa eklenecek head değişecek
	JE ESIT2
	MOV AX, SI			;eğer araya eklenecekse bu kısma geliyo
					;dizi ve linkleri byte kabul ettiğim için SI indexini AX'e atayım least meaning kısmını linklere atıyorum
	MOV linkler[DI], AL
	MOV linkler[SI], BL		;önceki node eklenen node indexini gösteriyor
					;eklenen node şimdiki node indexini gösteriyor
	JMP ENDE
ESIT2:	MOV linkler[SI], BL
	MOV head, SI
ENDE:
	POP DI
	POP BX
	POP AX
	RET
EKLE ENDP

IKI	PROC NEAR
        ;------------------------------------------------------------------------
        ; Diziyi sırayla (yanına linkleri ekleyerek) bastırma işlemini yapıyor.
	; CX, BX ve AX değerlerini korumak için PUSH/POP yapıyor.
        ;------------------------------------------------------------------------
	PUSH CX				;eleman sayısı için
	PUSH BX				;index olarak
	PUSH AX				;bastırma fonksiyonları için
	MOV CX, n
	MOV BX, head
L2:	XOR AX, AX
	MOV AL, dizi[BX]
	CALL PUTN
	MOV AX, 32			;boşluk
	CALL PUTC
	MOV BL, linkler[BX]
	MOV AL, BL
	CALL PUTN
	MOV AX, LF
	CALL PUTC			;alt satır
	LOOP L2
	POP AX
	POP BX
	POP CX
	RET
IKI ENDP

UC	PROC NEAR
        ;------------------------------------------------------------------------
        ; Dizi yeni eleman ekleme işlemini yapıyor. AX ve SI değerlerini korumak
	; için PUSH/POP yapıyor.
        ;------------------------------------------------------------------------
	PUSH AX
	PUSH SI				;index
	MOV SI, n			;aslında linksiz olarak sona ekleneceği için eleman sayısını SI'ya atıyorum
	MOV AX, OFFSET girE
	CALL PUT_STR
	CALL GETN
	MOV dizi[SI], AL		;alınan karakteri en sona ekliyor
	CMP head, -1			;head -1'se başa ekleyecek (hiç dizi oluşturulmamışsa)
	JE A1
	CALL EKLE			;dizi oluşturulmuşsa ekle fonksiyonunu çağırıyor
	JMP A2
A1:	MOV head, SI
	MOV linkler[SI], -1
A2:	INC n				;ekleme tamamlanınca eleman sayısını 1 arttırıyor
	POP SI
	POP AX
	RET
UC ENDP

PUTC	PROC NEAR
        ;------------------------------------------------------------------------
        ; AL yazmacındaki değeri ekranda gösterir. DL ve AH değişiyor. AX ve DX 
        ; yazmaçlarının değerleri korumak için PUSH/POP yapılır. 
        ;------------------------------------------------------------------------
        PUSH AX
        PUSH DX
        MOV DL, AL
        MOV AH,2
        INT 21H
        POP DX
        POP AX
        RET 
PUTC 	ENDP 

PUT_STR	PROC NEAR
	PUSH BX 
        MOV BX,	AX			         
        MOV AL, BYTE PTR [BX]	                
PUT_LOOP:   
        CMP AL,0		
        JE  PUT_FIN 			        ;0 geldi ise dizge sona erdi demek
        CALL PUTC 			        
        INC BX 				        ;Bir sonraki karaktere geç
        MOV AL, BYTE PTR [BX]
        JMP PUT_LOOP			        ;Yazdırmaya devam 
PUT_FIN:
	POP BX
	RET 
PUT_STR	ENDP

GETC	PROC NEAR
        MOV AH, 1h
        INT 21H
        RET 
GETC	ENDP 

GETN 	PROC NEAR
        ;------------------------------------------------------------------------
        ; Klavyeden basılan sayiyi okur, sonucu AX yazmacı üzerinden dondurur. 
        ; DX: sayının işaretli olup/olmadığını belirler. 1 (+), -1 (-) demek 
        ; BL: hane bilgisini tutar 
        ; CX: okunan sayının islenmesi sırasındaki ara değeri tutar. 
        ; AL: klavyeden okunan karakteri tutar (ASCII)
        ; AX zaten dönüş değeri olarak değişmek durumundadır. Ancak diğer 
        ; yazmaçların önceki değerleri korunmalıdır. 
        ;------------------------------------------------------------------------
        PUSH BX
        PUSH CX
        PUSH DX
GETN_START:
        MOV DX, 1	                        ; sayının şimdilik + olduğunu varsayalım 
        XOR BX, BX 	                        ; okuma yapmadı Hane 0 olur. 
        XOR CX,CX	                        ; ara toplam değeri de 0’dır. 
NEW:
        CALL GETC	                        ; klavyeden ilk değeri AL’ye oku. 
        CMP AL,CR 
        JE FIN_READ	                        ; Enter tuşuna basilmiş ise okuma biter
        CMP  AL, '-'	                        ; AL ,'-' mi geldi ? 
        JNE  CTRL_NUM	                        ; gelen 0-9 arasında bir sayı mı?
NEGATIVE:
        MOV DX, -1	                        ; - basıldı ise sayı negatif, DX=-1 olur
        JMP NEW		                        ; yeni haneyi al
CTRL_NUM:
        CMP AL, '0'	                        ; sayının 0-9 arasında olduğunu kontrol et.
        JB error 
        CMP AL, '9'
        JA error		                ; değil ise HATA mesajı verilecek
        SUB AL,'0'	                        ; rakam alındı, haneyi toplama dâhil et 
        MOV BL, AL	                        ; BL’ye okunan haneyi koy 
        MOV AX, 10 	                        ; Haneyi eklerken *10 yapılacak 
        PUSH DX		                        ; MUL komutu DX’i bozar işaret için saklanmalı
        MUL CX		                        ; DX:AX = AX * CX
        POP DX		                        ; işareti geri al 
        MOV CX, AX	                        ; CX deki ara değer *10 yapıldı 
        ADD CX, BX 	                        ; okunan haneyi ara değere ekle 
        JMP NEW 		                ; klavyeden yeni basılan değeri al 
ERROR:
        MOV AX, OFFSET HATA 
        CALL PUT_STR	                        ; HATA mesajını göster 
        JMP GETN_START                          ; o ana kadar okunanları unut yeniden sayı almaya başla 
FIN_READ:
        MOV AX, CX	                        ; sonuç AX üzerinden dönecek 
        CMP DX, 1	                        ; İşarete göre sayıyı ayarlamak lazım 
        JE FIN_GETN
        NEG AX		                        ; AX = -AX
FIN_GETN:
        POP DX
        POP CX
        POP DX
        RET 
GETN 	ENDP 

PUTN 	PROC NEAR
        ;------------------------------------------------------------------------
        ; AL de bulunan sayiyi onluk tabanda hane hane yazdırır. 
        ; CX: haneleri 10’a bölerek bulacağız, CX=10 olacak ve başta yığına 0
	; atmak için
        ;------------------------------------------------------------------------
        PUSH CX
        XOR CX,	CX 	                        
        PUSH CX		                        ; haneleri ASCII karakter olarak yığında saklayacağız.
                                                ; Kaç haneyi alacağımızı bilmediğimiz için yığına 0 
                                                ; değeri koyup onu alana kadar devam edelim.
        MOV CL, 10	                        ; CX = 10
        CMP AL, 0
        JGE CALC_DIGITS	
        NEG AL		                        ; sayı negatif ise AL pozitif yapılır. 
        PUSH AX		                        ; AX'i korumak için push ediyoruz
        MOV AL, '-'	                        ; işareti ekrana yazdırıyor
        CALL PUTC
        POP AX		                        ; AX’i geri alıyoruz
        
CALC_DIGITS:
	XOR AH, AH
        DIV CL  		                ; AH: kalan  AL: bölüm
        ADD AH, '0'	                        ; kalan değerini ASCII olarak bul 
        PUSH AX		                        ; AH'ı doğrudan yığında saklayamayacağımız için AX'i atıyoruz
        CMP AL, 0	                        ; bölen 0 kaldı ise sayının işlenmesi bitti demek
        JNE CALC_DIGITS  
DISP_LOOP:
                                                ; yazılacak tüm haneler yığında sona vardığımızı anlamak için konan 0 değeri var. 
        POP AX		                        ; sırayla değerleri yığından alalım
        CMP AH, 0 	                        ; AH=0 olursa sona geldik demek 
        JE END_DISP_LOOP 
	MOV AL, AH				; yazdırmak için AH'ı AL'ye atıyoruz
        CALL PUTC 	                        ; AL deki ASCII değeri yaz
        JMP DISP_LOOP                           ; işleme devam
END_DISP_LOOP: 
        POP CX
        RET
PUTN 	ENDP 

CDSG 	ENDS 
	END ANA