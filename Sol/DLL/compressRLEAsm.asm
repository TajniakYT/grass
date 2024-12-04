.code
compressRLEAsm PROC
    ; Argumenty:
    ; rdi = data (wej�ciowy bufor)
    ; rsi = size (rozmiar wej�ciowego bufora)
    ; rdx = output (bufor wynikowy)
    ; rcx = outputSize (adres na rozmiar danych wyj�ciowych)

    xor r8, r8                ; r8 - bie��ca pozycja w wej�ciu
    xor r10, r10              ; r10 - licznik powt�rze�
    xor r9, r9                ; r9 - bie��ca pozycja w wyj�ciu

loop_start:
    ; Sprawdzamy, czy przetworzyli�my ca�y bufor wej�ciowy
    cmp r8, rsi
    jge done

    ; �adujemy 16 bajt�w z wej�ciowego bufora
    movdqu xmm1, [rdi + r8]     ; �aduje 16 bajt�w z rdi + r8 do xmm1

    ; Sprawdzamy, czy wszystkie bajty s� takie same
    pcmpeqb xmm2, xmm1          ; Por�wnanie wszystkich bajt�w w xmm1
    pmovmskb r11, xmm2          ; Zapisuje wynik por�wnania (maski bitowe) do r11
    ; Sprawdzamy, czy wszystkie bajty s� takie same (czy maska to 0xFFFFFFFF)
    test r11, r11               ; Sprawdzamy, czy maska jest r�wna 0xFFFFFFFF
    jnz handle_different_values ; Je�li nie, to bajty s� r�ne

    ; Je�li wszystkie bajty s� takie same:
    ; Zliczamy liczb� powt�rze�
    mov r10, 16                 ; Ustawiamy licznik powt�rze� na 16

    ; Zapisujemy wynik (licznik i warto��)
    mov byte ptr [rdx + r9], r10b ; Zapisuje licznik (r10b to dolny bajt z r10)
    mov al, byte ptr [rdi + r8]   ; Wczytujemy warto�� (w tej chwili wszystkie s� takie same)
    mov byte ptr [rdx + r9 + 1], al ; Zapisuje warto��
    add r9, 2                    ; Przesuwa wska�nik wyj�cia o 2 bajty

    add r8, 16                   ; Przechodzi do nast�pnego bloku danych
    jmp loop_start               ; Kontynuuje przetwarzanie

handle_different_values:
    ; Je�li bajty s� r�ne, przechodzimy po ka�dym z nich
    xor r10, r10              ; Zerowanie licznika powt�rze�
    mov r12, r8

done:
    ; Zapisuje ko�cowy rozmiar wyj�cia
    mov qword ptr [rcx], r9      ; Zapisuje rozmiar wyj�cia do `outputSize`
    ret
compressRLEAsm ENDP
END