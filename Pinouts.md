# Pinouts

A collection of pinouts and electrical descriptions for connectors.

**NOTE: These were made using a variety of sources, and I have not been able to 100% verify the validity of every pin. Do your own testing.**

---

## 13-pin Acoustimass Connector
<img src="graphics/acoustimass.png" width=300rem>

Source: [0, pg20] [1, pg70]

Note: Cable is one-to-one, so pinout should be identical on Bass Module and Console.

Pin# | Description | Note
--- | --- | ---
1 | Vunreg | Nominal 26v, Max 31.5V
2 | GND |
3 | SPDIF + | 3/11 are twisted pair
4 | Mute | 3v3 = mute, 0v0 = unmute, pulled high in Bass Module
5 | DSP_Shutdown | Not used on production models
6 | AGND | Shield over Audio Right & Left
7 | DGND | Shield for SPDIF +/-
8 | Audio Left - | 8/9 are twisted pair
9 | Audio Left + | 8/9 are twisted pair
10 | Audio Right - | 10/12 are twisted pair
11 | SPDIF - | 3/11 are twisted pair
12 | Audio Right + | 10/12 are twisted pair
13 | SmartSpeaker | Serial data
Shell | SGND | Connected to GND

---

## 9-pin DE9 Satellite Speaker Connector
<img src="graphics/de9.png" width=300rem>

Source: (pending)

Pin# | Description | Note
--- | --- | ---
1 | LeftA | 
2 | LeftA |
3 | GND |
4 | RightA | 
5 | RightA | 
6 | LeftB | 
7 | LeftB | 
8 | RightB | 
9 | RightB | 
Shell | GND | 

---

## 4-pin Satellite Connector
<img src="graphics/satellite.png" width=300rem>

Source: (pending)

Pin# | Description | Note
--- | --- | ---
1 | SpkA | 
2 | SpkA |
3 | SpkB |
4 | SpkB | 


## 9-pin DIN ETAP/Boselink Connector
<img src="graphics/etap.png" width=300rem>

Source: [1, pg69]

Pin# | Description | Note
--- | --- | ---
1 | ? | 
2 | ? |
3 | Left + #1 | 
4 | Right + #1 | 
5 | Right + #2 | 
6 | ? | 
7 | Data | Serial data
8 | ? | 
9 | Left + #2 | 
Shell | GND | 