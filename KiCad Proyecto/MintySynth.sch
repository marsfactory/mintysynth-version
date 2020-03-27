EESchema Schematic File Version 4
LIBS:MintySynth-cache
EELAYER 29 0
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
$EndDescr
$Comp
L Device:R R1
U 1 1 5DEEE6BB
P 8400 4800
F 0 "R1" V 8300 4750 50  0000 C CNN
F 1 "220E" V 8400 4800 50  0000 C CNN
F 2 "SeleccionDeComponentes:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8330 4800 50  0001 C CNN
F 3 "~" H 8400 4800 50  0001 C CNN
	1    8400 4800
	0    1    1    0   
$EndComp
$Comp
L Device:LED D1
U 1 1 5DEEEA49
P 8800 4800
F 0 "D1" H 8900 4750 50  0000 C CNN
F 1 "LED RED" H 8800 4650 50  0000 C CNN
F 2 "SeleccionDeComponentes:LED_D5.0mm" H 8800 4800 50  0001 C CNN
F 3 "~" H 8800 4800 50  0001 C CNN
	1    8800 4800
	-1   0    0    1   
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5DEEF275
P 3750 4150
F 0 "A1" H 3200 3250 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 3300 3150 50  0000 C CNN
F 2 "Modules:Arduino_Nano" H 3900 3200 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 3750 3150 50  0001 C CNN
	1    3750 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5DEF0139
P 6150 5650
F 0 "C1" H 6265 5696 50  0000 L CNN
F 1 "100nF" H 6265 5605 50  0000 L CNN
F 2 "SeleccionDeComponentes:C_Disc_D3.8mm_W2.6mm_P2.50mm" H 6188 5500 50  0001 C CNN
F 3 "~" H 6150 5650 50  0001 C CNN
	1    6150 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5DEF0665
P 6400 5400
F 0 "C2" V 6655 5400 50  0000 C CNN
F 1 "100uF" V 6564 5400 50  0000 C CNN
F 2 "SeleccionDeComponentes:CP_Radial_D5.0mm_P2.50mm" H 6438 5250 50  0001 C CNN
F 3 "~" H 6400 5400 50  0001 C CNN
	1    6400 5400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5DEF0D9F
P 5450 3100
F 0 "RV1" H 5381 3146 50  0000 R CNN
F 1 "R_POT" H 5381 3055 50  0000 R CNN
F 2 "Potentiometers:Potentiometer_Omeg_PC16PU_Horizontal_MountLS" H 5450 3100 50  0001 C CNN
F 3 "~" H 5450 3100 50  0001 C CNN
	1    5450 3100
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5DEF1A08
P 5750 4350
F 0 "SW2" H 5750 4635 50  0000 C CNN
F 1 "SW_Push" H 5750 4544 50  0000 C CNN
F 2 "SeleccionDeComponentes:SW_PUSH_6mm" H 5750 4550 50  0001 C CNN
F 3 "~" H 5750 4550 50  0001 C CNN
	1    5750 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV2
U 1 1 5DEF225D
P 5850 3100
F 0 "RV2" H 5781 3146 50  0000 R CNN
F 1 "R_POT" H 5781 3055 50  0000 R CNN
F 2 "Potentiometers:Potentiometer_Omeg_PC16PU_Horizontal_MountLS" H 5850 3100 50  0001 C CNN
F 3 "~" H 5850 3100 50  0001 C CNN
	1    5850 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_POT RV3
U 1 1 5DEF2623
P 6300 3100
F 0 "RV3" H 6231 3146 50  0000 R CNN
F 1 "R_POT" H 6231 3055 50  0000 R CNN
F 2 "Potentiometers:Potentiometer_Omeg_PC16PU_Horizontal_MountLS" H 6300 3100 50  0001 C CNN
F 3 "~" H 6300 3100 50  0001 C CNN
	1    6300 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_POT RV4
U 1 1 5DEF4DA9
P 6700 3100
F 0 "RV4" H 6631 3146 50  0000 R CNN
F 1 "R_POT" H 6631 3055 50  0000 R CNN
F 2 "Potentiometers:Potentiometer_Omeg_PC16PU_Horizontal_MountLS" H 6700 3100 50  0001 C CNN
F 3 "~" H 6700 3100 50  0001 C CNN
	1    6700 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_POT RV5
U 1 1 5DEF5091
P 7150 3100
F 0 "RV5" H 7081 3146 50  0000 R CNN
F 1 "R_POT" H 7081 3055 50  0000 R CNN
F 2 "Potentiometers:Potentiometer_Omeg_PC16PU_Horizontal_MountLS" H 7150 3100 50  0001 C CNN
F 3 "~" H 7150 3100 50  0001 C CNN
	1    7150 3100
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 5DEF6F7F
P 6300 4350
F 0 "SW3" H 6300 4635 50  0000 C CNN
F 1 "SW_Push" H 6300 4544 50  0000 C CNN
F 2 "SeleccionDeComponentes:SW_PUSH_6mm" H 6300 4550 50  0001 C CNN
F 3 "~" H 6300 4550 50  0001 C CNN
	1    6300 4350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 5DEF7520
P 6850 4350
F 0 "SW4" H 6850 4635 50  0000 C CNN
F 1 "SW_Push" H 6850 4544 50  0000 C CNN
F 2 "SeleccionDeComponentes:SW_PUSH_6mm" H 6850 4550 50  0001 C CNN
F 3 "~" H 6850 4550 50  0001 C CNN
	1    6850 4350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 5DEF78CA
P 7400 4350
F 0 "SW5" H 7400 4635 50  0000 C CNN
F 1 "SW_Push" H 7400 4544 50  0000 C CNN
F 2 "SeleccionDeComponentes:SW_PUSH_6mm" H 7400 4550 50  0001 C CNN
F 3 "~" H 7400 4550 50  0001 C CNN
	1    7400 4350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5DEF7CC5
P 5200 4350
F 0 "SW1" H 5200 4635 50  0000 C CNN
F 1 "SW_Push" H 5200 4544 50  0000 C CNN
F 2 "SeleccionDeComponentes:SW_PUSH_6mm" H 5200 4550 50  0001 C CNN
F 3 "~" H 5200 4550 50  0001 C CNN
	1    5200 4350
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:AUDIO_JACK_3.5MM_KIT J5
U 1 1 5DEF9043
P 6900 5600
F 0 "J5" H 6622 5505 45  0000 R CNN
F 1 "AUDIO_JACK_3.5MM_KIT" H 6622 5589 45  0000 R CNN
F 2 "SeleccionDeComponentes:AUDIO-JACK-KIT" H 6900 5950 20  0001 C CNN
F 3 "" H 6900 5600 50  0001 C CNN
F 4 "CONN-08774" H 6622 5684 60  0000 R CNN "Campo4"
	1    6900 5600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 5DEFCCAA
P 5950 5400
F 0 "R3" V 5850 5400 50  0000 C CNN
F 1 "1K" V 5950 5400 50  0000 C CNN
F 2 "SeleccionDeComponentes:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5880 5400 50  0001 C CNN
F 3 "~" H 5950 5400 50  0001 C CNN
	1    5950 5400
	0    1    1    0   
$EndComp
$Comp
L SamacSys_Parts:EG2211A S1
U 1 1 5DF01D32
P 3900 1950
F 0 "S1" H 4350 2215 50  0000 C CNN
F 1 "EG2211A" H 4350 2124 50  0000 C CNN
F 2 "SamacSys_Parts:EG2211A" H 4650 2050 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/EG2211A.pdf" H 4650 1950 50  0001 L CNN
F 4 "Slide Switches DPDT 0.2A 2MM R/A" H 4650 1850 50  0001 L CNN "Description"
F 5 "3.7" H 4650 1750 50  0001 L CNN "Height"
F 6 "612-EG2211A" H 4650 1650 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=612-EG2211A" H 4650 1550 50  0001 L CNN "Mouser Price/Stock"
F 8 "E-Switch" H 4650 1450 50  0001 L CNN "Manufacturer_Name"
F 9 "EG2211A" H 4650 1350 50  0001 L CNN "Manufacturer_Part_Number"
	1    3900 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5DF024F1
P 8800 5000
F 0 "D2" H 8900 5050 50  0000 C CNN
F 1 "LED YELLOW" H 8800 5150 50  0000 C CNN
F 2 "SeleccionDeComponentes:LED_D5.0mm" H 8800 5000 50  0001 C CNN
F 3 "~" H 8800 5000 50  0001 C CNN
	1    8800 5000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 5DF0277B
P 7650 3100
F 0 "R4" V 7443 3100 50  0000 C CNN
F 1 "10K" V 7534 3100 50  0000 C CNN
F 2 "SeleccionDeComponentes:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7580 3100 50  0001 C CNN
F 3 "~" H 7650 3100 50  0001 C CNN
	1    7650 3100
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5DF028DE
P 8400 5000
F 0 "R2" V 8500 4950 50  0000 C CNN
F 1 "220E" V 8400 5000 50  0000 C CNN
F 2 "SeleccionDeComponentes:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8330 5000 50  0001 C CNN
F 3 "~" H 8400 5000 50  0001 C CNN
	1    8400 5000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5DF0476D
P 7500 2600
F 0 "#PWR08" H 7500 2350 50  0001 C CNN
F 1 "GND" H 7505 2427 50  0000 C CNN
F 2 "" H 7500 2600 50  0001 C CNN
F 3 "" H 7500 2600 50  0001 C CNN
	1    7500 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 5DF04E82
P 5050 3450
F 0 "#PWR012" H 5050 3300 50  0001 C CNN
F 1 "+5V" H 5065 3623 50  0000 C CNN
F 2 "" H 5050 3450 50  0001 C CNN
F 3 "" H 5050 3450 50  0001 C CNN
	1    5050 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3100 5200 3100
Wire Wire Line
	5200 3100 5200 3300
Wire Wire Line
	7300 3100 7350 3100
Wire Wire Line
	7350 3100 7350 2700
Wire Wire Line
	5700 3100 5700 3300
Wire Wire Line
	5700 3300 5200 3300
Connection ~ 5200 3300
Wire Wire Line
	6150 3100 6150 3300
Wire Wire Line
	6150 3300 5700 3300
Connection ~ 5700 3300
Wire Wire Line
	6550 3100 6550 3300
Wire Wire Line
	6550 3300 6150 3300
Connection ~ 6150 3300
Wire Wire Line
	7000 3100 7000 3300
Wire Wire Line
	7000 3300 6550 3300
Connection ~ 6550 3300
Wire Wire Line
	5600 3100 5600 2700
Wire Wire Line
	5600 2700 6000 2700
Connection ~ 7350 2700
Wire Wire Line
	6000 3100 6000 2700
Connection ~ 6000 2700
Wire Wire Line
	6000 2700 6450 2700
Wire Wire Line
	6450 3100 6450 2700
Connection ~ 6450 2700
Wire Wire Line
	6450 2700 6850 2700
Wire Wire Line
	6850 3100 6850 2700
Connection ~ 6850 2700
Wire Wire Line
	6850 2700 7350 2700
Wire Wire Line
	7350 2700 7350 2550
Wire Wire Line
	5200 3300 5200 3550
Text Label 5450 2950 0    50   ~ 0
A0
Text Label 5850 2950 0    50   ~ 0
A1
Text Label 6300 2950 0    50   ~ 0
A2
Text Label 6700 2950 0    50   ~ 0
A3
Text Label 7150 2950 0    50   ~ 0
A4
Wire Wire Line
	7800 3100 7850 3100
$Comp
L power:GND #PWR013
U 1 1 5DF0C77D
P 7500 3300
F 0 "#PWR013" H 7500 3050 50  0001 C CNN
F 1 "GND" H 7505 3127 50  0000 C CNN
F 2 "" H 7500 3300 50  0001 C CNN
F 3 "" H 7500 3300 50  0001 C CNN
	1    7500 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3100 7500 3300
$Comp
L power:+5V #PWR014
U 1 1 5DF0D1C0
P 8300 2950
F 0 "#PWR014" H 8300 2800 50  0001 C CNN
F 1 "+5V" H 8315 3123 50  0000 C CNN
F 2 "" H 8300 2950 50  0001 C CNN
F 3 "" H 8300 2950 50  0001 C CNN
	1    8300 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 2950 8300 3100
Wire Wire Line
	8300 3100 8200 3100
Wire Wire Line
	7850 3100 7850 3300
Connection ~ 7850 3100
Wire Wire Line
	7850 3100 7900 3100
Text Label 7850 3300 0    50   ~ 0
A5
Text Label 4250 4150 0    50   ~ 0
A0
Text Label 4250 4250 0    50   ~ 0
A1
Text Label 4250 4350 0    50   ~ 0
A2
Text Label 4250 4450 0    50   ~ 0
A3
Text Label 4250 4550 0    50   ~ 0
A4
Text Label 4250 4650 0    50   ~ 0
A5
$Comp
L power:GND #PWR06
U 1 1 5DF10187
P 3800 5300
F 0 "#PWR06" H 3800 5050 50  0001 C CNN
F 1 "GND" H 3805 5127 50  0000 C CNN
F 2 "" H 3800 5300 50  0001 C CNN
F 3 "" H 3800 5300 50  0001 C CNN
	1    3800 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 5150 3800 5150
Wire Wire Line
	3800 5300 3800 5150
Connection ~ 3800 5150
Wire Wire Line
	3800 5150 3850 5150
$Comp
L Connector:Conn_01x02_Female J3
U 1 1 5DF11D96
P 3350 2050
F 0 "J3" H 3350 1850 50  0000 C CNN
F 1 "Conn_01x02_BatteryIN" V 3450 2000 50  0000 C CNN
F 2 "Connectors_SparkFun:1X02" H 3350 2050 50  0001 C CNN
F 3 "~" H 3350 2050 50  0001 C CNN
	1    3350 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	3550 1950 3550 1850
Wire Wire Line
	3900 2050 3900 2150
Wire Wire Line
	3900 2150 3750 2150
Wire Wire Line
	3750 2150 3750 2250
Connection ~ 3900 2150
NoConn ~ 3900 2250
NoConn ~ 3850 3150
$Comp
L power:GND #PWR05
U 1 1 5DF22AEE
P 3550 2200
F 0 "#PWR05" H 3550 1950 50  0001 C CNN
F 1 "GND" H 3555 2027 50  0000 C CNN
F 2 "" H 3550 2200 50  0001 C CNN
F 3 "" H 3550 2200 50  0001 C CNN
	1    3550 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2050 3550 2200
$Comp
L power:+9V #PWR04
U 1 1 5DF247D9
P 3550 1850
F 0 "#PWR04" H 3550 1700 50  0001 C CNN
F 1 "+9V" H 3565 2023 50  0000 C CNN
F 2 "" H 3550 1850 50  0001 C CNN
F 3 "" H 3550 1850 50  0001 C CNN
	1    3550 1850
	1    0    0    -1  
$EndComp
Connection ~ 3550 1950
Text Label 3650 3150 0    50   ~ 0
VIN
Text Label 3750 2250 0    50   ~ 0
VIN
NoConn ~ 4800 1950
NoConn ~ 4800 2050
NoConn ~ 4800 2150
NoConn ~ 4800 2250
$Comp
L power:+5V #PWR07
U 1 1 5DF283A1
P 3950 3100
F 0 "#PWR07" H 3950 2950 50  0001 C CNN
F 1 "+5V" H 3965 3273 50  0000 C CNN
F 2 "" H 3950 3100 50  0001 C CNN
F 3 "" H 3950 3100 50  0001 C CNN
	1    3950 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3150 3950 3100
$Comp
L power:GND #PWR010
U 1 1 5DF40573
P 6300 4750
F 0 "#PWR010" H 6300 4500 50  0001 C CNN
F 1 "GND" H 6305 4577 50  0000 C CNN
F 2 "" H 6300 4750 50  0001 C CNN
F 3 "" H 6300 4750 50  0001 C CNN
	1    6300 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4350 5400 4750
Wire Wire Line
	5400 4750 5950 4750
Wire Wire Line
	5950 4350 5950 4750
Connection ~ 5950 4750
Wire Wire Line
	5950 4750 6300 4750
Wire Wire Line
	6300 4750 6500 4750
Wire Wire Line
	6500 4750 6500 4350
Connection ~ 6300 4750
Wire Wire Line
	7050 4350 7050 4750
Wire Wire Line
	7050 4750 6500 4750
Connection ~ 6500 4750
Wire Wire Line
	7600 4350 7600 4750
Wire Wire Line
	7600 4750 7050 4750
Connection ~ 7050 4750
Wire Wire Line
	8550 4800 8650 4800
Wire Wire Line
	8550 5000 8650 5000
$Comp
L power:GND #PWR011
U 1 1 5DF49AAF
P 9200 5000
F 0 "#PWR011" H 9200 4750 50  0001 C CNN
F 1 "GND" H 9205 4827 50  0000 C CNN
F 2 "" H 9200 5000 50  0001 C CNN
F 3 "" H 9200 5000 50  0001 C CNN
	1    9200 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 4800 8950 5000
Wire Wire Line
	8950 5000 9200 5000
Connection ~ 8950 5000
Wire Wire Line
	6250 5400 6150 5400
Wire Wire Line
	6150 5500 6150 5400
Connection ~ 6150 5400
Wire Wire Line
	6150 5400 6100 5400
$Comp
L power:GND #PWR09
U 1 1 5DF58A23
P 6150 5900
F 0 "#PWR09" H 6150 5650 50  0001 C CNN
F 1 "GND" H 6155 5727 50  0000 C CNN
F 2 "" H 6150 5900 50  0001 C CNN
F 3 "" H 6150 5900 50  0001 C CNN
	1    6150 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 5800 6150 5900
Wire Wire Line
	6700 5400 6600 5400
Wire Wire Line
	6600 5400 6600 5700
Wire Wire Line
	6600 5700 6700 5700
Connection ~ 6600 5400
Wire Wire Line
	6600 5400 6550 5400
NoConn ~ 6700 5500
NoConn ~ 6700 5600
Wire Wire Line
	6700 5800 6150 5800
Connection ~ 6150 5800
NoConn ~ 4250 3950
NoConn ~ 4250 3650
NoConn ~ 4250 3550
Text Label 5000 4350 2    50   ~ 0
D5
Text Label 5550 4350 2    50   ~ 0
D7
Text Label 6100 4350 2    50   ~ 0
D11
Text Label 6650 4350 2    50   ~ 0
D8
Text Label 7200 4350 2    50   ~ 0
D10
Text Label 3250 4050 2    50   ~ 0
D5
Text Label 3250 4250 2    50   ~ 0
D7
Text Label 3250 4650 2    50   ~ 0
D11
Text Label 3250 4350 2    50   ~ 0
D8
Text Label 3250 4550 2    50   ~ 0
D10
Text Label 8250 5000 2    50   ~ 0
D4
Text Label 8250 4800 2    50   ~ 0
D2
Text Label 3250 3950 2    50   ~ 0
D4
Text Label 3250 3750 2    50   ~ 0
D2
NoConn ~ 3250 3550
Text Label 3250 3850 2    50   ~ 0
D3
Text Label 5550 5400 2    50   ~ 0
D3
Wire Wire Line
	3550 1950 3900 1950
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5DFEBE28
P 3650 3150
F 0 "#FLG0104" H 3650 3225 50  0001 C CNN
F 1 "PWR_FLAG" H 3650 3323 50  0000 C CNN
F 2 "" H 3650 3150 50  0001 C CNN
F 3 "~" H 3650 3150 50  0001 C CNN
	1    3650 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_PHOTO R5
U 1 1 5DFF852F
P 8050 3100
F 0 "R5" V 7725 3100 50  0000 C CNN
F 1 "R_PHOTO" V 7816 3100 50  0000 C CNN
F 2 "Opto-Devices:Resistor_LDR_5x4.1_RM3" V 8100 2850 50  0001 L CNN
F 3 "~" H 8050 3050 50  0001 C CNN
	1    8050 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 5400 5800 5400
NoConn ~ 3250 4450
$Comp
L Device:R R6
U 1 1 5E157EEB
P 8350 4150
F 0 "R6" V 8250 4100 50  0000 C CNN
F 1 "220E" V 8350 4150 50  0000 C CNN
F 2 "SeleccionDeComponentes:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8280 4150 50  0001 C CNN
F 3 "~" H 8350 4150 50  0001 C CNN
	1    8350 4150
	0    1    1    0   
$EndComp
$Comp
L Device:LED D3
U 1 1 5E157EF1
P 8750 4150
F 0 "D3" H 8850 4100 50  0000 C CNN
F 1 "LED YELLOW" H 8750 4000 50  0000 C CNN
F 2 "SeleccionDeComponentes:LED_D5.0mm" H 8750 4150 50  0001 C CNN
F 3 "~" H 8750 4150 50  0001 C CNN
	1    8750 4150
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D6
U 1 1 5E157EF7
P 8750 4350
F 0 "D6" H 8850 4400 50  0000 C CNN
F 1 "LED RED" H 8750 4500 50  0000 C CNN
F 2 "SeleccionDeComponentes:LED_D5.0mm" H 8750 4350 50  0001 C CNN
F 3 "~" H 8750 4350 50  0001 C CNN
	1    8750 4350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 5E157EFD
P 8350 4350
F 0 "R9" V 8450 4300 50  0000 C CNN
F 1 "220E" V 8350 4350 50  0000 C CNN
F 2 "SeleccionDeComponentes:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8280 4350 50  0001 C CNN
F 3 "~" H 8350 4350 50  0001 C CNN
	1    8350 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 4150 8600 4150
Wire Wire Line
	8500 4350 8600 4350
$Comp
L power:GND #PWR0104
U 1 1 5E157F05
P 9150 4350
F 0 "#PWR0104" H 9150 4100 50  0001 C CNN
F 1 "GND" H 9155 4177 50  0000 C CNN
F 2 "" H 9150 4350 50  0001 C CNN
F 3 "" H 9150 4350 50  0001 C CNN
	1    9150 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 4150 8900 4350
Wire Wire Line
	8900 4350 9150 4350
Connection ~ 8900 4350
Text Label 8200 4150 2    50   ~ 0
D12
Text Label 3250 4150 2    50   ~ 0
D6
NoConn ~ 4250 4850
Text Label 3250 3650 2    50   ~ 0
TX
Text Label 6700 2050 0    50   ~ 0
TX
Wire Wire Line
	6600 2150 6600 2050
$Comp
L power:+5V #PWR03
U 1 1 5DFAF638
P 6600 2150
F 0 "#PWR03" H 6600 2000 50  0001 C CNN
F 1 "+5V" H 6615 2323 50  0000 C CNN
F 2 "" H 6600 2150 50  0001 C CNN
F 3 "" H 6600 2150 50  0001 C CNN
	1    6600 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	6500 2050 6500 2150
$Comp
L power:GND #PWR02
U 1 1 5DFAD9A9
P 6500 2150
F 0 "#PWR02" H 6500 1900 50  0001 C CNN
F 1 "GND" H 6505 1977 50  0000 C CNN
F 2 "" H 6500 2150 50  0001 C CNN
F 3 "" H 6500 2150 50  0001 C CNN
	1    6500 2150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5DFA6EB1
P 6600 1850
F 0 "J2" V 6450 1600 50  0000 L CNN
F 1 "Conn_01x03_MIDI OUT" V 6550 1550 50  0000 L CNN
F 2 "Connectors_SparkFun:1X03_LOCK" H 6600 1850 50  0001 C CNN
F 3 "~" H 6600 1850 50  0001 C CNN
	1    6600 1850
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5DFE4087
P 5850 2050
F 0 "#PWR0103" H 5850 1900 50  0001 C CNN
F 1 "+5V" H 5865 2223 50  0000 C CNN
F 2 "" H 5850 2050 50  0001 C CNN
F 3 "" H 5850 2050 50  0001 C CNN
	1    5850 2050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5DFE3D4B
P 5600 2050
F 0 "#PWR0102" H 5600 1800 50  0001 C CNN
F 1 "GND" H 5605 1877 50  0000 C CNN
F 2 "" H 5600 2050 50  0001 C CNN
F 3 "" H 5600 2050 50  0001 C CNN
	1    5600 2050
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5DFE3B77
P 5850 2050
F 0 "#FLG0103" H 5850 2125 50  0001 C CNN
F 1 "PWR_FLAG" H 5850 2223 50  0000 C CNN
F 2 "" H 5850 2050 50  0001 C CNN
F 3 "~" H 5850 2050 50  0001 C CNN
	1    5850 2050
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5DFE385D
P 5600 2050
F 0 "#FLG0102" H 5600 2125 50  0001 C CNN
F 1 "PWR_FLAG" H 5600 2223 50  0000 C CNN
F 2 "" H 5600 2050 50  0001 C CNN
F 3 "~" H 5600 2050 50  0001 C CNN
	1    5600 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR0101
U 1 1 5DFE30EC
P 5400 2050
F 0 "#PWR0101" H 5400 1900 50  0001 C CNN
F 1 "+9V" H 5415 2223 50  0000 C CNN
F 2 "" H 5400 2050 50  0001 C CNN
F 3 "" H 5400 2050 50  0001 C CNN
	1    5400 2050
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DFE2CB5
P 5400 2050
F 0 "#FLG0101" H 5400 2125 50  0001 C CNN
F 1 "PWR_FLAG" H 5400 2223 50  0000 C CNN
F 2 "" H 5400 2050 50  0001 C CNN
F 3 "~" H 5400 2050 50  0001 C CNN
	1    5400 2050
	1    0    0    -1  
$EndComp
NoConn ~ 4250 4750
Text Label 8200 4350 2    50   ~ 0
D6
Wire Wire Line
	7350 2550 7500 2550
Wire Wire Line
	7500 2550 7500 2600
Wire Wire Line
	5050 3450 5050 3550
Wire Wire Line
	5050 3550 5200 3550
NoConn ~ 3250 4850
Text Label 3250 4750 2    50   ~ 0
D12
$EndSCHEMATC
