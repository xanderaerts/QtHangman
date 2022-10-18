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

Als volgend gaan we de build directory maken, hiervan maken we onze workdir. 

Hie