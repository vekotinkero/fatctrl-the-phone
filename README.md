# fatctrl-the-phone :
## FΔT MIDI Controller: The Phone !

This project demonstrates a basic MIDI controller done with
Arduino UNO clone.

--

Darran has made a basic USB MIDI driver for atmega8u2 which works fantastically. 
The driver sends MIDI messages serially over USB at 115200 baud.

The MIDI messages can be modified and created in midi_messages.h file. The basic message that's sent via serial is four bytes long.

Byte 0: MIDI command
```
  e.g Note Off: 1000nnnn, e.g. 0x80
  Note On: 1001nnnn, e.g. 0x90
```

Byte 1: MIDI channel from 1 to 16
Byte 2: MIDI data byte 2
Byte 3: MIDI data byte 3

These data bytes depend on the command. For Note On/Off they're pitch and velocity values.
And for Control Change they're Control Number and Control Value.

The serial message might look something like this:
1001000 00000001 00001100 01000000 
= 0x90 0x01 0x0c 0x40
= Note On, Channel 1, Note 12 (C1), velocity 64

Got it? So you can develop your own messages by checking the MIDI specification.
Find more about MIDI messages here: http://www.midi.org/techspecs/midimessages.php

Original Uno firmware is flipped with Arduino-usbmidi-0.1.hex, which can be found here. Just scroll down and look for the post:
http://hunt.net.nz/users/darran/
I did the flippin' with Atmels FLIP progammer:
http://www.atmel.com/tools/flip.aspx?tab=overview

--
# So what did I do?

My controller has 12 pushbuttons. Notes are in chromatic scale, since 
this is inteded to be used as a drum pad. Obviously you can play some melodies
or even chords as well. There are also two buttons to change octave and a pot 
that is used for control changes (CC48).

I installed the UNO to an old office telephone. I used old PCB inside and made use of
the neat pushbutton pad. Just had to solder few old components away and make new connections.

At first I kept UNO separate from The Phone. My idea was to use it as a part of a bigger
controller family that would be controlled by only one UNO. I made a hole into the back 
and screwed a 10 pin ribbon connector in it. 

The result looked hideous and finally fitted the whole UNO inside the chassis. At least it's
now simple and neat, but I feel like I'm wasting a lot of UNO's potential with this few controls. 

I'm still planning to make a bigger controller hub some of these days.
