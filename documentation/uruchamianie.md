Jak uruchomic emulator
========

Do emulacji wykorzystywany jest program Renode.  
Zeby uruchomic program nalezy wykonac polecenie  
`make emulator`  
  
Emulator pozwala zdefiniowac makra. Dzieki nim mozna latwiej wywolywac polecenia sterujace systemem.  

`start_reset` - Uruchomienie systemu.  
`switch` - Wlaczenie lub wylaczenie programu.  
`fire_alarm_start` - Wlaczenie alarmu pozarowego.  
`fire_alarm_stop` - Wylaczenie alarmu pozarowego.  
`fire_alarm_status` - Odczytanie wartosci portu informujacego o alarmie.  
`lights_up` - Ustawienie wartosci swiatla na poziom wysoki.  
`lights_down` - Ustawienie wartosci swiatla na poziom niski.  
`lights_status` - Odczytanie wartosci swiatla.  
`blinds_status` - Pozwala odczytac ustawienie rolet.  
  
Makro wywolywane jest poleceniem:  
`runMacro $machine_0.nazwa_makra`  

