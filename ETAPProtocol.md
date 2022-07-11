# ETAP Protocol

A quick and rough investigation surrounding the ETAP protocol.

It appears that the Console uses a 5V, UART, half-duplex data line, but the baud-rate and data format are not as clear.

[1, pg69] suggests 19200 baud, 8N1, [3, pg2] suggests 9600 baud, 8N1.

[1, pg69] also suggests the protocol takes the form of ASCII characters.

Some sources say the Console enters ETAP automatically, otheres say ETAP commands must be sent within the first 10 seconds of power-on to start it.

I did not pursue the ETAP protocol for long as my focus shifted to finding the core required SmartSpeaker commands to get a functioning Arduino prototype.