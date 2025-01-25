zadanie.exe < .\doEdycji\testy.txt > .\doEdycji\wynikiTwojegoProgramu.txt
fc /a /w .\doEdycji\janosikOdp.txt .\doEdycji\wynikiTwojegoProgramu.txt > .\doEdycji\wynikiTestu.txt
start notepad ".\doEdycji\wynikiTestu.txt"