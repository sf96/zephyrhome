Opis projektu
=============

W ramach projektu zaimplementowalem aplikacje sterujaca budynkiem w oparciu o system Zephyr RTOS. Do emulacji wykorzystalem Renode. Pracowalem na plytce prototypowej NUCLEO-F103RB.


Funkcjonalnosci aplikacji:
- informowowanie uzytkownika o swoim statusie przez port UART,
- uruchamianie alarmu po wykryciu pozaru przez czujnik dymu,
- sterowanie natezeniem oswietlenia w zaleznosci od natezenia światla na zewnatrz budynku,
- sterowanie roletami w zaleznosci od natezenia swiatla na zewnątrz budynku, 
- pozwala wlaczac/wylaczac system.
