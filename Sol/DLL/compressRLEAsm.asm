.code
compressRLEAsm PROC
    ; Argumenty:
    ; rdi = data (wejœciowy bufor)
    ; rsi = size (rozmiar wejœciowego bufora)
    ; rdx = output (bufor wynikowy)
    ; rcx = outputSize (adres na rozmiar danych wyjœciowych)

    xor r8, r8                ; r8 - bie¿¹ca pozycja w wejœciu
    xor r10, r10              ; r10 - licznik powtórzeñ
    xor r9, r9                ; r9 - bie¿¹ca pozycja w wyjœciu

loop_start:
    ; Sprawdzamy, czy przetworzyliœmy ca³y bufor wejœciowy
    cmp r8, rsi
    jge done

    ; £adujemy 16 bajtów z wejœciowego bufora
    movdqu xmm1, [rdi + r8]     ; £aduje 16 bajtów z rdi + r8 do xmm1

    ; Sprawdzamy, czy wszystkie bajty s¹ takie same
    pcmpeqb xmm2, xmm1          ; Porównanie wszystkich bajtów w xmm1
    pmovmskb r11, xmm2          ; Zapisuje wynik porównania (maski bitowe) do r11
    ; Sprawdzamy, czy wszystkie bajty s¹ takie same (czy maska to 0xFFFFFFFF)
    test r11, r11               ; Sprawdzamy, czy maska jest równa 0xFFFFFFFF
    jnz handle_different_values ; Jeœli nie, to bajty s¹ ró¿ne

    ; Jeœli wszystkie bajty s¹ takie same:
    ; Zliczamy liczbê powtórzeñ
    mov r10, 16                 ; Ustawiamy licznik powtórzeñ na 16

    ; Zapisujemy wynik (licznik i wartoœæ)
    mov byte ptr [rdx + r9], r10b ; Zapisuje licznik (r10b to dolny bajt z r10)
    mov al, byte ptr [rdi + r8]   ; Wczytujemy wartoœæ (w tej chwili wszystkie s¹ takie same)
    mov byte ptr [rdx + r9 + 1], al ; Zapisuje wartoœæ
    add r9, 2                    ; Przesuwa wskaŸnik wyjœcia o 2 bajty

    add r8, 16                   ; Przechodzi do nastêpnego bloku danych
    jmp loop_start               ; Kontynuuje przetwarzanie

handle_different_values:
    ; Jeœli bajty s¹ ró¿ne, przechodzimy po ka¿dym z nich
    xor r10, r10              ; Zerowanie licznika powtórzeñ
    mov r12, r8

done:
    ; Zapisuje koñcowy rozmiar wyjœcia
    mov qword ptr [rcx], r9      ; Zapisuje rozmiar wyjœcia do `outputSize`
    ret
compressRLEAsm ENDP
END