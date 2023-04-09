# ir-sniffer

Quick and dirty 38kHz IR sniffer

I threw this together because I wanted a braindead simple way to sniff IR data. 
This is pretty much just the receiver dump demos in [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266/tree/master)
except I output to OLED as well as serial port.

I'm currently using this to sniff my air conditioning unit's remote commands so I can control it through Home-Assistant.
Also, who knows maybe I'll need something like this in the future for some other dumb thing I make.

## Circuit

TODO: parts list

TODO: kicad image

TODO: breadboard image

TODO: protoboard image

## Sample Output

### TV Remote

```txt
Protocol  : NEC
Code      : 0x61A030CF (32 Bits)

As Source Code:
uint16_t rawData[67] = {9048, 4446,  620, 524,  618, 1650,  618, 1650,  618, 524,  644, 496,  620, 522,  618, 524,  646, 1622,  
                        618, 1650,  618, 524,  618, 1650,  620, 522,  618, 522,  618, 524,  618, 524,  646, 496,  644, 498,  
                        618, 522,  618, 1650,  618, 1648,  618, 524,  618, 524,  644, 498,  646, 496,  646, 1624,  616, 1650,  
                        646, 496,  618, 522,  646, 1622,  620, 1648,  620, 1648,  618, 1652,  618};  // NEC 61A030CF
uint32_t address = 0x586;
uint32_t command = 0xC;
uint64_t data = 0x61A030CF;
```

TODO: picture

### AC Unit

```txt
Protocol  : WHIRLPOOL_AC
Code      : 0x830601720000C0000000000000B30025008038009D (168 Bits)
Mesg Desc.: Model: 2 (DG11J191), Power Toggle: Off, Mode: 2 (Cool), Temp: 23C, Fan: 1 (High), Swing: Off, Light: On, Clock: 00:00, 
On Timer: Off, Off Timer: Off, Sleep: Off, Super: Off, Command: 37 (UNKNOWN)

As Source Code:
uint16_t rawData[343] = {8970, 4558,  552, 1700,  550, 1702,  550, 582,  550, 586,  598, 542,  598, 544,  550, 598,  550, 1710,  
                        550, 574,  548, 1704,  598, 1658,  598, 536,  552, 590,  550, 594,  600, 548,  550, 586,  550, 1700,  
                        550, 578,  552, 582,  552, 586,  550, 590,  550, 594,  550, 596,  598, 538,  550, 576,  550, 1702,  550, 
                        582,  550, 586,  600, 1664,  552, 1716,  550, 1720,  550, 586,  550, 576,  550, 578,  550, 582,  550, 
                        586,  598, 542,  552, 592,  552, 596,  600, 536,  552, 574,  550, 578,  552, 582,  598, 538,  550, 590,  
                        548, 594,  550, 596,  550, 568,  600, 7960,  598, 528,  550, 580,  550, 582,  600, 538,  550, 590,  550, 
                        594,  550, 1720,  550, 1708,  552, 574,  550, 580,  548, 584,  550, 586,  552, 590,  550, 592,  550, 598,  
                        598, 538,  550, 576,  550, 580,  550, 582,  552, 584,  550, 590,  550, 594,  600, 546,  550, 586,  550, 576,  
                        552, 578,  550, 584,  550, 586,  552, 588,  550, 594,  550, 596,  550, 586,  550, 576,  550, 580,  548, 584,  
                        550, 586,  598, 542,  550, 592,  550, 596,  550, 586,  600, 526,  550, 580,  550, 582,  550, 586,  552, 588,  
                        550, 594,  550, 598,  550, 586,  550, 576,  550, 580,  548, 584,  552, 586,  552, 588,  552, 592,  552, 596,  
                        552, 586,  600, 1650,  600, 1654,  550, 584,  598, 538,  550, 1714,  600, 1668,  550, 598,  550, 1694,  552, 
                        8012,  554, 576,  600, 528,  552, 582,  552, 584,  552, 590,  550, 592,  602, 546,  598, 538,  550, 1700,  
                        550, 580,  552, 1706,  550, 588,  550, 590,  552, 1718,  600, 546,  550, 586,  550, 576,  550, 580,  550, 582,  
                        598, 538,  550, 590,  550, 594,  550, 598,  552, 586,  550, 576,  600, 530,  600, 536,  550, 588,  550, 592,  
                        548, 594,  550, 596,  600, 1660,  598, 528,  598, 532,  598, 534,  550, 1710,  600, 1664,  552, 1716,  600, 546,  
                        600, 536,  600, 526,  550, 580,  598, 534,  552, 586,  550, 590,  550, 594,  550, 596,  550, 586,  550, 1700,  550, 
                        578,  552, 1706,  550, 1710,  550, 1716,  550, 594,  598, 548,  600, 1644,  620};  // WHIRLPOOL_AC
uint8_t state[21] = {0x83, 0x06, 0x01, 0x72, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB3, 0x00, 0x25, 0x00, 0x80, 0x38, 0x00, 0x9D};
```

TODO: picture

### Roku Remote

```txt
Protocol  : NEC
Code      : 0x5743CC33 (32 Bits)

As Source Code:
uint16_t rawData[67] = {9056, 4326,  568, 552,  568, 1676,  594, 528,  594, 1650,  566, 554,  592, 1650,  566, 1676,  568, 1678,  568, 554,  566, 1678,  566, 556,  594, 530,  568, 554,  566, 554,  568, 1676,  594, 1648,  568, 1674,  568, 1676,  568, 556,  596, 524,  568, 1674,  568, 1676,  566, 556,  568, 556,  568, 556,  566, 554,  568, 1674,  566, 1678,  568, 554,  568, 554,  566, 1674,  594, 1638,  566};  // NEC 5743CC33
uint32_t address = 0xC2EA;
uint32_t command = 0x33;
uint64_t data = 0x5743CC33;
```

TODO: picture

## References

- https://github.com/crankyoldgit/IRremoteESP8266/tree/master
