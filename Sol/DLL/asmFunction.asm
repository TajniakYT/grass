.code
compressRLEAsm PROC
    ; Argumenty:
    ; rdi = data (wej�ciowy bufor)
    ; rsi = size (rozmiar wej�ciowego bufora)
    ; rdx = output (bufor wynikowy)
    ; r9  = outputSize (adres na rozmiar danych wyj�ciowych)

    xor r8, r8                ; r8 - bie��ca pozycja w wej�ciu
    xor r10, r10              ; r10 - licznik powt�rze�
    xor r9, r9                ; r9 - bie��ca pozycja w wyj�ciu

loop_start:
    ; Sprawdzamy, czy przetworzyli�my ca�y bufor wej�ciowy
    cmp r8, rsi
    jge done

    ; Pobieramy bie��cy bajt
    mov al, byte ptr [rdi + r8]      ; Pobiera warto�� bajtu z `rdi + r8`
    mov bl, al                    ; Kopiuje warto�� do `bl` rejestru
    xor r10, r10                  ; Zeruje licznik powt�rze�
    mov rcx, 1                    ; Inicjalizuje licznik w p�tli

count_repeats:
    ; Sprawdzamy kolejny bajt
    inc r10                       ; Zwi�ksza licznik powt�rze�
    inc r8                        ; Przechodzi do kolejnego bajtu

    cmp r8, rsi                   ; Czy jeste�my na ko�cu wej�cia?
    jge write_rle
    cmp r10, 255                  ; Czy licznik powt�rze� osi�gn�� maksimum?
    jge write_rle

    mov al, byte ptr [rdi + r8]       ; Pobiera nast�pny bajt
    cmp al, bl                    ; Czy bajt jest taki sam?
    je count_repeats

write_rle:
    ; Zapisuje do wyj�cia: licznik i warto��
    mov byte ptr [rdx + r9], r10b   ; Zapisuje licznik (r10b to dolny bajt z r10)
    mov byte ptr [rdx + r9 + 1], bl  ; Zapisuje warto��
    add r9, 2                      ; Przesuwa wska�nik wyj�cia o 2 bajty
    jmp loop_start                 ; Kontynuuje przetwarzanie


done:
    ; Zapisuje ko�cowy rozmiar wyj�cia
    mov qword ptr [r9], rsi        ; Zapisuje rozmiar wyj�cia
    ret
compressRLEAsm ENDP

END