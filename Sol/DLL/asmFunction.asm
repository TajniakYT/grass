.code
compressRLEAsm PROC
    ; Argumenty:
    ; rdi = data (wejœciowy bufor)
    ; rsi = size (rozmiar wejœciowego bufora)
    ; rdx = output (bufor wynikowy)
    ; r9  = outputSize (adres na rozmiar danych wyjœciowych)

    xor r8, r8                ; r8 - bie¿¹ca pozycja w wejœciu
    xor r10, r10              ; r10 - licznik powtórzeñ
    xor r9, r9                ; r9 - bie¿¹ca pozycja w wyjœciu

loop_start:
    ; Sprawdzamy, czy przetworzyliœmy ca³y bufor wejœciowy
    cmp r8, rsi
    jge done

    ; Pobieramy bie¿¹cy bajt
    mov al, byte ptr [rdi + r8]      ; Pobiera wartoœæ bajtu z `rdi + r8`
    mov bl, al                    ; Kopiuje wartoœæ do `bl` rejestru
    xor r10, r10                  ; Zeruje licznik powtórzeñ
    mov rcx, 1                    ; Inicjalizuje licznik w pêtli

count_repeats:
    ; Sprawdzamy kolejny bajt
    inc r10                       ; Zwiêksza licznik powtórzeñ
    inc r8                        ; Przechodzi do kolejnego bajtu

    cmp r8, rsi                   ; Czy jesteœmy na koñcu wejœcia?
    jge write_rle
    cmp r10, 255                  ; Czy licznik powtórzeñ osi¹gn¹³ maksimum?
    jge write_rle

    mov al, byte ptr [rdi + r8]       ; Pobiera nastêpny bajt
    cmp al, bl                    ; Czy bajt jest taki sam?
    je count_repeats

write_rle:
    ; Zapisuje do wyjœcia: licznik i wartoœæ
    mov byte ptr [rdx + r9], r10b   ; Zapisuje licznik (r10b to dolny bajt z r10)
    mov byte ptr [rdx + r9 + 1], bl  ; Zapisuje wartoœæ
    add r9, 2                      ; Przesuwa wskaŸnik wyjœcia o 2 bajty
    jmp loop_start                 ; Kontynuuje przetwarzanie


done:
    ; Zapisuje koñcowy rozmiar wyjœcia
    mov qword ptr [r9], rsi        ; Zapisuje rozmiar wyjœcia
    ret
compressRLEAsm ENDP

END