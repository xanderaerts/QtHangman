# Qt Hangman

# Omschrijving test case 

Voor de test case maakte ik een versie van hangman. Een speler laat een lijst met woorden in, er wordt 1 woord gekozen. De speler moet het woord raden doormiddel van de letters te gokken. Na 10 foute gokken verliest de speler het spel. 

# Gevolgde stappen 

## Begin

Als eerst moet er een project gemaakt worden dit werd opgesteld met Qt. 

## Docker

Voor het crosscompilen ben ik na het aanraden van klasgenoten een DockerContainer gaan gebruiken. Voor mij was dit de eerste keer dat ik Docker gebruikten. Een docker container beschermt mij van een package overload op mijn eigen systeem. 
 
## Alle nodige requirements instaleren/downloaden

Voor docker te gebruiken moest ik eerste een dockerfile opstellen.
In deze dockefile staat al een groot deel van de commands. Deze worden da uitgevoerd om zo mijn dockerimage te creeën. 

De eerste lijn geef aan welke image je wilt gebruiken. In dit geval `ubutnu:22.04`

We beginnen met het `apt-get update` en `apt-get` install commando.
Het eerste is nodig om zeker te zijn dat we van alle packages de laatste versie hebben, bij het 2de voegen we de requirements list toe om alle nodige packages te installeren. 

## Setup mxe & make 

Omdat we gebruiken maken van docker hebben we een kleine python error, deze is snel opgelost door een link te leggen met het volgende commando.
`RUN ln -s /usr/bin/python3 /usr/bin/python`

Als volgend gaan we de build directory maken, hiervan maken we onze workdir.

Hierna gaan we in deze directory de mxe git repo clonen. 

Als we de gitrepo hebben kunnen we de mxe en qtbase packages downloaden, hiervoor gaf ik `--jobs=4` zodat het maar op 4 cores van mijn procesor is. 
We gebruiken hier het command `RUN cd mxe && make download-qtbase --jobs=4`

Als volgend moeten we de libaries gaan builden, we downloaden en builden enkel het nootzakelijke anders duurt dit veel te lang, en hebben we veel onnodige packages. 

Voor het builden gebruiken we volgend commando. `RUN cd mxe && make qtbase MXE_TARGETS='x86_64-w64-mingw32.static i686-w64-mingw32.static' MXE_USE_CCACHE= --jobs=12` 

We geven 2 mxe targets mee en de mxe use ccache optie, hierdoor moeten we niet alles opnieuw builden wanneer we een 2de keer ons project willen compilen. 
We geven deze keer wel 12 cores mee om het een beetje sneller te laten lopen. 
Het builden neemt zo al tijd in beslag.

De laatste stap in de Dockerfile is het toevoegen van mxe aan onze path variablen. 

`ENV PATH /build/mxe/usr/bin:$PATH`

## Compilen

Wanneer we onze Dockerfile opgesteld hebben gaan we onze dockerimage builden. Dit doen we met het command `docker build -t qt .` 

Deze gaat alle commando's uit de dockerfile uitvoeren en voor ons een docker imgae maken.

Hierna moeten we zelf nog de makefile genereren en het compilen zelf. 
Om dit te doen moeten we gebruik maken van de dockercontainer en gaan we deze runnen zodat we op de ubuntu image commando's kunnen uitvoeren.

Hiervoor voeren we het volgende commando uit 
`docker run -it --rm -v "$(pwd):/app" a68 bash`

We geven een aantal optie's mee, -it voor een interactive terminal en --rm om de container te verwijderen na gebruik. 

De -v optie is belangrijk, hier geven we het path mee zodat we onze bestanden kunnen gebruiken in de dockercontainer. Let hierbij op dat je dit commando uitvoert van uit je folder met je code, dit maakt het makkelijker wanneer je je bestanden zoekt. 

Als laatste geven we nog het id van de image mee en de shell die we willen in dit geval bash. Om het id te vinden kan deze gevonden worden door `docker ps -a` te doen, (een stuk mee geven is genoeg). 

Eens we in onze docker container zitten kunnen we de laatste 2 commando's gaan uitvoeren 

Eerst moeten we onze makefile genereren, hiervoor doen we het volgende
`/build/mxe/usr/i686-w64-mingw32.static/qt5/bin/qmake`

Het allerlaaste wat we moeten doen is `make`

Als alles goed gaat krijg je dan volgende output en een [naamProject].exe in de gegenereerde release folder. 

![alt output docker + make commando](/screenSuccesCompile.png "output make")

## Opmerkingen
Toen ik het de eerste keer compilde liep niet alles goed, ik had in mijn code nog een variable die soms zonder waarde zat. Wanener ik dit teste in de qt-creator werkte alles. Eens het gecompiled was lukte dit niet. Hieraan kan je zien dat niet alle compilers het zelfde werken!


# Link naar de theorie

We gebruiken een cross-compiling toolchain, we builden op linux voor windows.

qMake zal er voor zorgen dat onze makefile automatisch word gegenereerd.






