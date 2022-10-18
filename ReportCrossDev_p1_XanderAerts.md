# Qt Hangman

# Omschrijving test case 

Voor de test case maakte ik een versie van hangman. Een speler laat een lijst met woorden in, er wordt 1 woord gekozen. De speler moet het woord raden doormiddel van de letters te gokken. Na 10 foute gokken verliest de speler het spel. 

# Gevolgde stappen 

## Begin

Als eerst moet er een project gemaakt worden dit werd opgesteld met Qt. 

## Docker

Voor het crosscompilen ben ik na het aanraden van klasgenoten een DockerContainer gaan gebruiken. Voor mij was dit de eerste keer dat ik Docker gebruikten. Een docker container beschermt mij van een package overload op mijn eigen systeem. 
 
# Alle nodige requirements instaleren/downloaden

Voor docker te gebruiken moest ik eerste een dockerfile opstellen.
In deze dockefile staat al een groot deel van de commands. Deze worden da uitgevoerd om zo mijn dockerimage te creeën. 

We beginnen met het `apt-get update` en `apt-get` install commando.
Het eerste is nodig om zeker te zijn dat we van alle packages de laatste versie hebben, bij het 2de voegen we de requirements list toe om alle nodige packages te installeren. 

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


Wanneer we onze Dockerfile opgesteld hebben gaan we onze dockerimage builden. Dit doen we met het command `docker build -t qt .` 

