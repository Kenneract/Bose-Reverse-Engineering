EESchema Schematic File Version 5
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
NoConn ~ 7950 2550
$Comp
L power:GND #PWR0101
U 1 1 62CF309F
P 8250 2150
F 0 "#PWR0101" H 8250 1900 50  0001 C CNN
F 1 "GND" H 8255 1977 50  0000 C CNN
F 2 "" H 8250 2150 50  0001 C CNN
F 3 "" H 8250 2150 50  0001 C CNN
	1    8250 2150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 62D0CD40
P 6500 1700
F 0 "#PWR0102" H 6500 1450 50  0001 C CNN
F 1 "GND" H 6505 1527 50  0000 C CNN
F 2 "" H 6500 1700 50  0001 C CNN
F 3 "" H 6500 1700 50  0001 C CNN
	1    6500 1700
	1    0    0    -1  
$EndComp
Connection ~ 6500 1700
Wire Wire Line
	7700 1550 7800 1550
Wire Wire Line
	7300 1550 7400 1550
Wire Wire Line
	8250 2150 8250 2250
$Comp
L LED:SK6812 D2
U 1 1 62CED032
P 8250 2550
F 0 "D2" H 8593 2595 50  0000 L CNN
F 1 "SK6812" H 8593 2505 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 8300 2250 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/1138/SK6812+LED+datasheet+.pdf" H 8350 2175 50  0001 L TNN
	1    8250 2550
	-1   0    0    1   
$EndComp
$Comp
L dk_LED-Indication-Discrete:LTL2R3KGKNN D1
U 1 1 62CEE24A
P 7900 1550
F 0 "D1" H 7850 1888 60  0000 C CNN
F 1 "5mm Green LED" H 7850 1781 60  0000 C CNN
F 2 "digikey-footprints:LED_5mm_Radial" H 8100 1750 60  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS20-2000-191/LTL2R3KGKNN.pdf" H 8100 1850 60  0001 L CNN
F 4 "160-1947-ND" H 8100 1950 60  0001 L CNN "Digi-Key_PN"
F 5 "LTL2R3KGKNN" H 8100 2050 60  0001 L CNN "MPN"
F 6 "Optoelectronics" H 8100 2150 60  0001 L CNN "Category"
F 7 "LED Indication - Discrete" H 8100 2250 60  0001 L CNN "Family"
F 8 "http://optoelectronics.liteon.com/upload/download/DS20-2000-191/LTL2R3KGKNN.pdf" H 8100 2350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/lite-on-inc/LTL2R3KGKNN/160-1947-ND/3198465" H 8100 2450 60  0001 L CNN "DK_Detail_Page"
F 10 "LED GREEN CLEAR T-1 3/4 T/H" H 8100 2550 60  0001 L CNN "Description"
F 11 "Lite-On Inc." H 8100 2650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8100 2750 60  0001 L CNN "Status"
	1    7900 1550
	-1   0    0    1   
$EndComp
Wire Wire Line
	5500 2500 5650 2500
Text GLabel 5500 2500 0    50   Input ~ 0
7S_A
Text GLabel 5500 2600 0    50   Input ~ 0
7S_B
Text GLabel 6050 1500 2    50   Output ~ 0
IR_SIG
Wire Wire Line
	6000 1300 6500 1300
Wire Wire Line
	6000 1700 6500 1700
Wire Wire Line
	6000 1500 6050 1500
Wire Wire Line
	6500 1650 6500 1700
Wire Wire Line
	6500 1300 6500 1350
Wire Wire Line
	5500 2800 5650 2800
Wire Wire Line
	5500 2900 5650 2900
NoConn ~ 5650 3300
Wire Wire Line
	5500 3100 5650 3100
Wire Wire Line
	5500 3000 5650 3000
$Comp
L Interface_Optical:TSOP17xx U1
U 1 1 62CDF2EF
P 5600 1500
F 0 "U1" H 5588 1923 50  0000 C CNN
F 1 "TSOP17xx" H 5588 1832 50  0000 C CNN
F 2 "OptoDevice:Vishay_CAST-3Pin" H 5550 1125 50  0001 C CNN
F 3 "http://www.micropik.com/PDF/tsop17xx.pdf" H 6250 1800 50  0001 C CNN
	1    5600 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 62CF1963
P 7550 1550
F 0 "R2" H 7618 1595 50  0000 L CNN
F 1 "200R" H 7618 1505 50  0000 L CNN
F 2 "" V 7590 1540 50  0001 C CNN
F 3 "~" H 7550 1550 50  0001 C CNN
	1    7550 1550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 62D00BC1
P 7300 1550
F 0 "#PWR0106" H 7300 1300 50  0001 C CNN
F 1 "GND" H 7305 1377 50  0000 C CNN
F 2 "" H 7300 1550 50  0001 C CNN
F 3 "" H 7300 1550 50  0001 C CNN
	1    7300 1550
	1    0    0    -1  
$EndComp
Text GLabel 6500 1300 1    50   Input ~ 0
5V
$Comp
L Device:CP1 C1
U 1 1 62CFACF8
P 6500 1500
F 0 "C1" H 6615 1545 50  0000 L CNN
F 1 "47uF" H 6615 1455 50  0000 L CNN
F 2 "" H 6500 1500 50  0001 C CNN
F 3 "~" H 6500 1500 50  0001 C CNN
	1    6500 1500
	1    0    0    -1  
$EndComp
Text GLabel 10300 2450 2    50   Output ~ 0
SOURCE_CHNG
NoConn ~ 10100 2450
Wire Wire Line
	10200 2300 10350 2300
Wire Wire Line
	10200 2450 10300 2450
Wire Wire Line
	10200 2350 10200 2450
$Comp
L power:GND #PWR0103
U 1 1 62CEFE2F
P 10900 1950
F 0 "#PWR0103" H 10900 1700 50  0001 C CNN
F 1 "GND" H 10905 1777 50  0000 C CNN
F 2 "" H 10900 1950 50  0001 C CNN
F 3 "" H 10900 1950 50  0001 C CNN
	1    10900 1950
	0    -1   -1   0   
$EndComp
$Comp
L dk_Pushbutton-Switches:GPTS203211B S2
U 1 1 62CE48A6
P 10550 1950
F 0 "S2" H 10550 2224 50  0000 C CNN
F 1 "Down/-" H 10550 2133 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 10750 2150 50  0001 L CNN
F 3 "http://switches-connectors-custom.cwind.com/Asset/GPTS203211BR2.pdf" H 10750 2250 60  0001 L CNN
F 4 "CW181-ND" H 10750 2350 60  0001 L CNN "Digi-Key_PN"
F 5 "GPTS203211B" H 10750 2450 60  0001 L CNN "MPN"
F 6 "Switches" H 10750 2550 60  0001 L CNN "Category"
F 7 "Pushbutton Switches" H 10750 2650 60  0001 L CNN "Family"
F 8 "http://switches-connectors-custom.cwind.com/Asset/GPTS203211BR2.pdf" H 10750 2750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/cw-industries/GPTS203211B/CW181-ND/3190590" H 10750 2850 60  0001 L CNN "DK_Detail_Page"
F 10 "SWITCH PUSHBUTTON SPST 1A 30V" H 10750 2950 60  0001 L CNN "Description"
F 11 "CW Industries" H 10750 3050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10750 3150 60  0001 L CNN "Status"
	1    10550 1950
	1    0    0    -1  
$EndComp
$Comp
L dk_Pushbutton-Switches:GPTS203211B S3
U 1 1 62CEBF8C
P 10550 2300
F 0 "S3" H 10550 2574 50  0000 C CNN
F 1 "Power" H 10550 2483 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 10750 2500 50  0001 L CNN
F 3 "http://switches-connectors-custom.cwind.com/Asset/GPTS203211BR2.pdf" H 10750 2600 60  0001 L CNN
F 4 "CW181-ND" H 10750 2700 60  0001 L CNN "Digi-Key_PN"
F 5 "GPTS203211B" H 10750 2800 60  0001 L CNN "MPN"
F 6 "Switches" H 10750 2900 60  0001 L CNN "Category"
F 7 "Pushbutton Switches" H 10750 3000 60  0001 L CNN "Family"
F 8 "http://switches-connectors-custom.cwind.com/Asset/GPTS203211BR2.pdf" H 10750 3100 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/cw-industries/GPTS203211B/CW181-ND/3190590" H 10750 3200 60  0001 L CNN "DK_Detail_Page"
F 10 "SWITCH PUSHBUTTON SPST 1A 30V" H 10750 3300 60  0001 L CNN "Description"
F 11 "CW Industries" H 10750 3400 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10750 3500 60  0001 L CNN "Status"
	1    10550 2300
	1    0    0    -1  
$EndComp
$Comp
L dk_Pushbutton-Switches:GPTS203211B S1
U 1 1 62CE498E
P 10550 1600
F 0 "S1" H 10550 1874 50  0000 C CNN
F 1 "Up/+" H 10550 1783 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 10750 1800 50  0001 L CNN
F 3 "http://switches-connectors-custom.cwind.com/Asset/GPTS203211BR2.pdf" H 10750 1900 60  0001 L CNN
F 4 "CW181-ND" H 10750 2000 60  0001 L CNN "Digi-Key_PN"
F 5 "GPTS203211B" H 10750 2100 60  0001 L CNN "MPN"
F 6 "Switches" H 10750 2200 60  0001 L CNN "Category"
F 7 "Pushbutton Switches" H 10750 2300 60  0001 L CNN "Family"
F 8 "http://switches-connectors-custom.cwind.com/Asset/GPTS203211BR2.pdf" H 10750 2400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/cw-industries/GPTS203211B/CW181-ND/3190590" H 10750 2500 60  0001 L CNN "DK_Detail_Page"
F 10 "SWITCH PUSHBUTTON SPST 1A 30V" H 10750 2600 60  0001 L CNN "Description"
F 11 "CW Industries" H 10750 2700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10750 2800 60  0001 L CNN "Status"
	1    10550 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 1600 10900 1950
Wire Wire Line
	10750 1600 10900 1600
$Comp
L dk_Transistors-Bipolar-BJT-Single:2N3904 Q1
U 1 1 62CE4102
P 9750 4750
F 0 "Q1" H 9950 4750 60  0000 L CNN
F 1 "2N3904" H 9950 4650 60  0000 L CNN
F 2 "digikey-footprints:TO-92-3" H 9950 4950 60  0001 L CNN
F 3 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=LSSGP072.PDF" H 9950 5050 60  0001 L CNN
F 4 "2N3904CS-ND" H 9950 5150 60  0001 L CNN "Digi-Key_PN"
F 5 "2N3904" H 9950 5250 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 9950 5350 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 9950 5450 60  0001 L CNN "Family"
F 8 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=LSSGP072.PDF" H 9950 5550 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/central-semiconductor-corp/2N3904/2N3904CS-ND/4806876" H 9950 5650 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V TO-92" H 9950 5750 60  0001 L CNN "Description"
F 11 "Central Semiconductor Corp" H 9950 5850 60  0001 L CNN "Manufacturer"
F 12 "Active" H 9950 5950 60  0001 L CNN "Status"
	1    9750 4750
	1    0    0    -1  
$EndComp
Text GLabel 10550 3550 2    50   Output ~ 0
Right+
Text GLabel 10550 3950 2    50   Output ~ 0
Left+
Wire Wire Line
	10450 4250 10450 4500
Wire Wire Line
	10350 4500 10450 4500
Wire Wire Line
	10100 1850 10200 1850
Wire Wire Line
	10200 1600 10350 1600
Wire Wire Line
	10200 1850 10200 1600
NoConn ~ 10100 1350
NoConn ~ 10100 1650
Text GLabel 5500 2800 0    50   Input ~ 0
7S_D
Text GLabel 5500 2700 0    50   Input ~ 0
7S_C
Text GLabel 5500 2900 0    50   Input ~ 0
7S_E
Text GLabel 5500 3000 0    50   Input ~ 0
7S_F
Text GLabel 5500 3100 0    50   Input ~ 0
7S_G
Text GLabel 5500 4200 0    50   Input ~ 0
V_UNREG
Wire Wire Line
	5500 4200 5600 4200
$Comp
L Device:R_US R1
U 1 1 62CFA3DA
P 6550 3200
F 0 "R1" H 6618 3245 50  0000 L CNN
F 1 "200R" H 6618 3155 50  0000 L CNN
F 2 "" V 6590 3190 50  0001 C CNN
F 3 "~" H 6550 3200 50  0001 C CNN
	1    6550 3200
	0    -1   -1   0   
$EndComp
$Comp
L Display_Character:MAN71A U3
U 1 1 62CE6807
P 5950 2900
F 0 "U3" H 5950 3566 50  0000 C CNN
F 1 "Generic 7seg" H 5950 3475 50  0000 C CNN
F 2 "Display_7Segment:MAN71A" H 5450 2200 50  0001 L CNN
F 3 "https://www.digchip.com/datasheets/parts/datasheet/161/MAN3640A-pdf.php" H 5960 3240 50  0001 L CNN
	1    5950 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2950 8250 2850
Text GLabel 8250 2950 0    50   Input ~ 0
5V
Wire Wire Line
	6200 4200 6300 4200
$Comp
L power:GND #PWR0107
U 1 1 62CDCF5B
P 5900 4500
F 0 "#PWR0107" H 5900 4250 50  0001 C CNN
F 1 "GND" H 5905 4327 50  0000 C CNN
F 2 "" H 5900 4500 50  0001 C CNN
F 3 "" H 5900 4500 50  0001 C CNN
	1    5900 4500
	1    0    0    -1  
$EndComp
$Comp
L Converter_DCDC:OKI-78SR-12_1.0-W36-C U2
U 1 1 62CF8235
P 5900 4200
F 0 "U2" H 5900 4441 50  0000 C CNN
F 1 "12V DC/DC Buck" H 5900 4350 50  0000 C CNN
F 2 "" H 5950 3950 50  0001 L CIN
F 3 "" H 5900 4200 50  0001 C CNN
	1    5900 4200
	1    0    0    -1  
$EndComp
Text GLabel 6300 4200 2    50   Output ~ 0
12V
Text GLabel 7300 4400 0    50   Input ~ 0
Right+
Wire Wire Line
	7300 4350 7300 4400
Text GLabel 7300 4500 0    50   Input ~ 0
Audio_GND
Text GLabel 6700 3200 2    50   Input ~ 0
5V
$Comp
L Connector:RJ45 J1
U 1 1 62CF0C56
P 7600 3950
F 0 "J1" V 7611 4480 50  0000 L CNN
F 1 "RJ45" V 7702 4480 50  0000 L CNN
F 2 "" V 7600 3975 50  0001 C CNN
F 3 "~" V 7600 3975 50  0001 C CNN
	1    7600 3950
	0    1    1    0   
$EndComp
NoConn ~ 7800 4350
Wire Wire Line
	8000 4350 8000 4400
Wire Wire Line
	7400 4350 7400 4500
Text GLabel 7500 4650 0    50   BiDi ~ 0
SmartSpeaker
Wire Wire Line
	7400 4500 7300 4500
Wire Wire Line
	7500 4350 7500 4650
Wire Wire Line
	7900 4500 8000 4500
Text GLabel 7850 4650 2    50   Output ~ 0
V_UNREG
Text GLabel 8000 4400 2    50   Input ~ 0
Left+
Wire Wire Line
	7900 4350 7900 4500
Text GLabel 8000 4500 2    50   Input ~ 0
Audio_GND
$Comp
L power:GND #PWR0108
U 1 1 62CE016A
P 7600 4600
F 0 "#PWR0108" H 7600 4350 50  0001 C CNN
F 1 "GND" H 7605 4427 50  0000 C CNN
F 2 "" H 7600 4600 50  0001 C CNN
F 3 "" H 7600 4600 50  0001 C CNN
	1    7600 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 4650 7850 4650
Wire Wire Line
	7700 4350 7700 4650
Wire Wire Line
	7600 4350 7600 4600
Connection ~ 6250 3200
Wire Wire Line
	6250 3200 6400 3200
Wire Wire Line
	6250 3200 6250 3300
Wire Wire Line
	5500 2700 5650 2700
Wire Wire Line
	5500 2600 5650 2600
Wire Wire Line
	10200 2050 10200 2300
NoConn ~ 10100 2250
NoConn ~ 10100 2150
Wire Wire Line
	10100 2050 10200 2050
Wire Wire Line
	10100 1950 10350 1950
Connection ~ 10900 1950
Wire Wire Line
	10750 1950 10900 1950
Wire Wire Line
	10900 1950 10900 2300
Wire Wire Line
	10750 2300 10900 2300
$Comp
L dk_Signal-Relays-Up-to-2-Amps:G5V-2-DC12 RLY1
U 1 1 62CE2FFF
P 10150 3850
F 0 "RLY1" H 10637 3895 50  0000 L CNN
F 1 "EB2-12" H 10637 3805 50  0000 L CNN
F 2 "digikey-footprints:Relay_THT_G5V-2" H 10350 4050 50  0001 L CNN
F 3 "https://omronfs.omron.com/en_US/ecb/products/pdf/en-g5v_2.pdf" H 10350 4150 60  0001 L CNN
F 4 "Z768-ND" H 10350 4250 60  0001 L CNN "Digi-Key_PN"
F 5 "G5V-2-DC12" H 10350 4350 60  0001 L CNN "MPN"
F 6 "Relays" H 10350 4450 60  0001 L CNN "Category"
F 7 "Signal Relays, Up to 2 Amps" H 10350 4550 60  0001 L CNN "Family"
F 8 "https://omronfs.omron.com/en_US/ecb/products/pdf/en-g5v_2.pdf" H 10350 4650 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/omron-electronics-inc-emc-div/G5V-2-DC12/Z768-ND/87821" H 10350 4750 60  0001 L CNN "DK_Detail_Page"
F 10 "RELAY GEN PURPOSE DPDT 2A 125V" H 10350 4850 60  0001 L CNN "Description"
F 11 "Omron Electronics Inc-EMC Div" H 10350 4950 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10350 5050 60  0001 L CNN "Status"
	1    10150 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10450 3550 10550 3550
Wire Wire Line
	10450 3950 10550 3950
Wire Wire Line
	9850 3750 9850 3850
NoConn ~ 9100 1350
Wire Wire Line
	10100 2350 10200 2350
Connection ~ 9700 2850
NoConn ~ 10100 2550
Wire Wire Line
	9600 2850 9700 2850
$Comp
L power:GND #PWR0105
U 1 1 62CDD640
P 9700 2850
F 0 "#PWR0105" H 9700 2600 50  0001 C CNN
F 1 "GND" H 9705 2677 50  0000 C CNN
F 2 "" H 9700 2850 50  0001 C CNN
F 3 "" H 9700 2850 50  0001 C CNN
	1    9700 2850
	1    0    0    -1  
$EndComp
Text GLabel 9000 2050 0    50   Output ~ 0
7S_C
Text GLabel 9000 1950 0    50   Output ~ 0
7S_B
Text GLabel 9000 1850 0    50   Output ~ 0
7S_A
Text GLabel 9000 1650 0    50   BiDi ~ 0
SmartSpeaker
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 62CDBF80
P 9600 1850
F 0 "A1" H 9300 750 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 9600 600 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 9600 1850 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 9600 1850 50  0001 C CNN
	1    9600 1850
	1    0    0    -1  
$EndComp
Text GLabel 9000 2350 0    50   Output ~ 0
7S_E
Text GLabel 9000 2150 0    50   Output ~ 0
7S_F
Text GLabel 9000 2250 0    50   Output ~ 0
7S_G
Text GLabel 9000 2450 0    50   Output ~ 0
7S_D
Wire Wire Line
	8550 2550 9100 2550
Wire Wire Line
	9000 2450 9100 2450
$Comp
L Diode:1N4007 D3
U 1 1 62CE7C64
P 10200 4500
F 0 "D3" H 10200 4700 50  0000 C CNN
F 1 "1N4007" H 10200 4600 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 10200 4325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 10200 4500 50  0001 C CNN
	1    10200 4500
	-1   0    0    1   
$EndComp
Text GLabel 10550 4250 2    50   Input ~ 0
12V
Wire Wire Line
	9850 4250 9850 4500
Wire Wire Line
	10450 4250 10550 4250
Connection ~ 9850 4500
$Comp
L Device:R_US R3
U 1 1 62CE331C
P 9300 4750
F 0 "R3" H 9368 4795 50  0000 L CNN
F 1 "2.2k" H 9368 4705 50  0000 L CNN
F 2 "" V 9340 4740 50  0001 C CNN
F 3 "~" H 9300 4750 50  0001 C CNN
	1    9300 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	9050 4750 9150 4750
Text GLabel 9050 4750 1    50   Input ~ 0
SOURCE_CHNG
Wire Wire Line
	9150 4250 9150 4400
Wire Wire Line
	9150 4250 9450 4250
Wire Wire Line
	9150 4400 9250 4400
$Comp
L power:GND #PWR0104
U 1 1 62D1C071
P 10000 5000
F 0 "#PWR0104" H 10000 4750 50  0001 C CNN
F 1 "GND" H 10005 4827 50  0000 C CNN
F 2 "" H 10000 5000 50  0001 C CNN
F 3 "" H 10000 5000 50  0001 C CNN
	1    10000 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9850 5000 10000 5000
Wire Wire Line
	9450 4750 9550 4750
Wire Wire Line
	9850 4950 9850 5000
Text GLabel 9250 4400 2    50   Output ~ 0
Audio_GND
Wire Wire Line
	9850 4500 9850 4550
Wire Wire Line
	10050 4500 9850 4500
$Comp
L Connector:Conn_Coaxial_x2 J2
U 1 1 62CF924C
P 9150 3550
F 0 "J2" H 9250 3524 50  0000 L CNN
F 1 "2x RCA Female" H 9250 3434 50  0000 L CNN
F 2 "" H 9150 3450 50  0001 C CNN
F 3 " ~" H 9150 3450 50  0001 C CNN
	1    9150 3550
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial_x2 J3
U 1 1 62CF4E4F
P 9450 3950
F 0 "J3" H 9550 3924 50  0000 L CNN
F 1 "2x RCA Female" H 9550 3834 50  0000 L CNN
F 2 "" H 9450 3850 50  0001 C CNN
F 3 " ~" H 9450 3850 50  0001 C CNN
	1    9450 3950
	-1   0    0    -1  
$EndComp
Connection ~ 9150 4250
Wire Wire Line
	9150 3850 9150 4250
Wire Wire Line
	9350 3650 9600 3650
Wire Wire Line
	9350 3450 9850 3450
Wire Wire Line
	9850 3650 9650 3650
Wire Wire Line
	9650 3650 9650 3850
Wire Wire Line
	9600 3650 9600 3750
Wire Wire Line
	9600 3750 9850 3750
Wire Wire Line
	9650 4050 9850 4050
NoConn ~ 9100 1250
$Comp
L Device:Jumper JP1
U 1 1 62CEEE0C
P 9150 750
F 0 "JP1" H 9050 550 50  0000 C CNN
F 1 "Jumper" H 9150 650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9150 750 50  0001 C CNN
F 3 "~" H 9150 750 50  0001 C CNN
	1    9150 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 750  8850 750 
Text GLabel 8750 750  0    50   Input ~ 0
12V
Wire Wire Line
	9500 850  9500 750 
Wire Wire Line
	9450 750  9500 750 
NoConn ~ 10100 1250
Text GLabel 9850 750  2    50   Output ~ 0
5V
Wire Wire Line
	9800 750  9800 850 
NoConn ~ 9700 850 
Wire Wire Line
	9800 750  9850 750 
Wire Wire Line
	9000 2150 9100 2150
Wire Wire Line
	9000 2350 9100 2350
Wire Wire Line
	9000 2250 9100 2250
Wire Wire Line
	9000 2050 9100 2050
Wire Wire Line
	9000 1950 9100 1950
Wire Wire Line
	9000 1850 9100 1850
NoConn ~ 9100 1750
Text GLabel 9000 1450 0    50   Input ~ 0
IR_SIG
Wire Wire Line
	9100 1550 8100 1550
Wire Wire Line
	9000 1450 9100 1450
Wire Wire Line
	9000 1650 9100 1650
$EndSCHEMATC
