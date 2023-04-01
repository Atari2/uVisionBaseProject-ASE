# Progetto base per l'esame di Architetture dei Sistemi di Elaborazione al POLITO

## Descrizione
Questo progetto è stato realizzato per essere usato come "base" per l'esame di Architetture dei Sistemi di Elaborazione al POLITO. Il progetto è stato realizzato con l'IDE uVision con la estensione per la scheda LandTiger ed è pensato per l'utilizzo con quest'ultima. Per utilizzare il progetto è necessario impostare la flag C99 nell'IDE.

Nel caso l'esame si faccia per emulatore invece che direttamente sulla scheda, è necessario definire la macro SIMULATOR nell'IDE.

Non è garantita la correttezza completa del codice, ma è stato testato estensivamente ed usato per vari temi d'esame passati ed è stato anche utilizzato dall'autore ad un esame in sede, passato con 30 nella parte di programmazione. Gran parte del codice è stato anche usato per lo sviluppo del progetto di [ASE Tamagotchi](https://github.com/Atari2/PolitoASE2022-Tamagotchi) e dei laboratori dell'AA 2022/2023.

I temi d'esami passati con cui è stato usato questo progetto possono essere trovati come branch di questo repository:
- [Appello del 2021-06-23](https://github.com/Atari2/uVisionBaseProject-ASE/tree/exam-2021-06-23)
- [Appello del 2023-02-06](https://github.com/Atari2/uVisionBaseProject-ASE/tree/exam-2023-02-06)
- [Appello del 2020-02-03](https://github.com/Atari2/uVisionBaseProject-ASE/tree/exam-2020-02-03)
- [Appello del 2021-02-03](https://github.com/Atari2/uVisionBaseProject-ASE/tree/exam-2021-02-03)
- [Appello del 2019-01-30](https://github.com/Atari2/uVisionBaseProject-ASE/tree/exam-2019-01-30)
- [Appello del 2023-02-23](https://github.com/Atari2/uVisionBaseProject-ASE/tree/exam-2023-02-23)

Questi branch possono essere anche visionati per vedere come questa base deve essere usata.

In ogni caso l'autore non si assume alcuna responsabilità per l'uso che ne verrà fatto e non si assume alcuna responsabilità per eventuali danni (e.g. esami non passati) causati da questo progetto.

I file per l'uso dello speaker e del touchpanel sono inclusi per completezza ma non vi è mai stata necessità d'uso per questi ultimi in alcun esame.

E' consigliato fare molta pratica con questo template prima di andare all'esame per prendere familiarità con le sue funzioni e con le sue librerie. Non è riportata alcuna documentazione sull'uso delle funzioni aggiunte ma il loro utilizzo può essere trovato nei vari temi d'esami svolti.

## Modalità d'utilizzo e note sulla licenza

La modalità di utilizzo che consiglio **solamente per l'esame** è la seguente:
- Cancellare i file .gitignore, LICENSE e README.md
- Cancellare la cartella nascosta .git
- Andare nei file .c e .h e cancellare tutto il codice che non è necessario per il tema d'esame, compresi i commenti con le note riguardo l'autore del codice originale.

La rimozione dei file e delle note è autorizzata dall'autore originale di questo progetto solamente ed esclusivamente in sede d'esame, se si ridistribuisce questo progetto o esso viene usato per altri motivi, è necessario mantenere tutti i file ausiliari e le note riguardo l'autore del codice originale. Fallimento di fare ciò è violazione della licenza e viene considerato plagio.

Tutti i file che non contengono esplicita nota a licenza o autore sono da considerarsi non soggetti ad alcuna restrizione di utilizzo.

## Contribuzione

Se si vuole contribuire al progetto o riparare degli errori, è possibile aprire una pull request. Eventuali issue verranno ignorate.

## Struttura
```
adc \
     adc.h
     IRQ_adc.c
     lib_adc.c
button \
        button.h
        irq_button.c
        button.c
drawing \
         drawing.h
         drawing.c
GLDC \
      AsciiLib.c
      AsciiLib.h
      GLDC.c
      GLDC.h
      HzLib.c
      HzLib.h
joystick \
          funct_joystick.c
          joystick.h
          lib_joystick.c
led \
     funct_led.c
     led.h
     lib_led.c
RIT \
     RIT.h
     IRQ_RIT.c
     lib_RIT.c
sound \
       libsound.c
       libsound.h
timer \
       IRQ_Timer.c
       lib_timer.c
       timer.h
TouchPanel \
            TouchPanel.c
            TouchPanel.h
macros.h
main.c
misc.c
misc.h
source.s
startup_LPC17xx.s
system_LPC17xx.c
```


