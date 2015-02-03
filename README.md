#wavengine

###A library for editing WAV audio files.

Useful information on WAV file format:
http://en.wikipedia.org/wiki/WAV

##Getting Started

Once you have the source code,
while in the wavengine directory

###__Compilation__ (Makefile's parameters)

```
$make
```

###__Run__

```
$./wavengine
```

###__Commands__

**Display a menu with the available commands**
```
$./wavengine --help
```

**List the metadata of the chosen WAV file(s)**
```
$./wavengine -list sound1.wav sound2.wav ... soundn.wav
```

**Reverse the selected WAV audio file(s)**
```
$./wavengine -reverse sound1.wav sound2.wav ... soundn.wav
```

**Convert to mono format the selected WAV audio filee(s)**
```
$./wavengine -mono sound1.wav sound2.wav ... soundn.wav
```

**Exract a specific time range from the selected WAV audio file**
```
$./wavengine -chop sound.wav [from second] [to second]
```

###__Remove object files and executables__
```
$make clean
```
