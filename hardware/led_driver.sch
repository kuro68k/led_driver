EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:keio
LIBS:Primayer
LIBS:kuro
LIBS:led_driver-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
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
L AS1116-BSST U5
U 1 1 57FF44E6
P 14250 3450
F 0 "U5" H 13750 4400 60  0000 L CNN
F 1 "AS1116-BSST" H 14150 4400 60  0000 L CNN
F 2 "Housings_SSOP:SSOP-24_3.9x8.7mm_Pitch0.635mm" H 14250 2550 60  0001 C CNN
F 3 "" H 14250 3450 60  0000 C CNN
	1    14250 3450
	1    0    0    -1  
$EndComp
$Comp
L AS1116-BSST U6
U 1 1 57FF452F
P 14250 5650
F 0 "U6" H 13750 6600 60  0000 L CNN
F 1 "AS1116-BSST" H 14150 6600 60  0000 L CNN
F 2 "Housings_SSOP:SSOP-24_3.9x8.7mm_Pitch0.635mm" H 14250 4750 60  0001 C CNN
F 3 "" H 14250 5650 60  0000 C CNN
	1    14250 5650
	1    0    0    -1  
$EndComp
$Comp
L ATXMEGA32E5-A U4
U 1 1 57FF5A64
P 10350 3950
F 0 "U4" H 9200 5000 50  0000 L BNN
F 1 "ATXMEGA32E5-A" H 11000 2850 50  0000 L BNN
F 2 "Housings_QFP:TQFP-32_7x7mm_Pitch0.8mm" H 10350 3950 50  0000 C CIN
F 3 "" H 10350 3950 50  0000 C CNN
	1    10350 3950
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L1
U 1 1 57FF5BD5
P 4150 2700
F 0 "L1" V 4100 2700 50  0000 C CNN
F 1 "10uH" V 4250 2700 50  0000 C CNN
F 2 "Inductors_NEOSID:Neosid_Inductor_SM-NE56_SMD2220" H 4150 2700 50  0001 C CNN
F 3 "" H 4150 2700 50  0000 C CNN
	1    4150 2700
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 57FF5C26
P 4550 2850
F 0 "R2" H 4600 2900 50  0000 L CNN
F 1 "59k" H 4600 2800 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4480 2850 50  0001 C CNN
F 3 "" H 4550 2850 50  0000 C CNN
	1    4550 2850
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 57FF5C77
P 2050 2650
F 0 "C1" H 2075 2750 50  0000 L CNN
F 1 "10u" H 2075 2550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2088 2500 50  0001 C CNN
F 3 "" H 2050 2650 50  0000 C CNN
	1    2050 2650
	1    0    0    -1  
$EndComp
$Comp
L CP C10
U 1 1 57FF5CB8
P 12850 2700
F 0 "C10" H 12875 2800 50  0000 L CNN
F 1 "10u" H 12875 2600 50  0000 L CNN
F 2 "SMD_Packages:SMD-1206_Pol" H 12888 2550 50  0001 C CNN
F 3 "" H 12850 2700 50  0000 C CNN
	1    12850 2700
	1    0    0    -1  
$EndComp
$Comp
L USB_A P1
U 1 1 57FF5D2F
P 1000 2600
F 0 "P1" H 1200 2400 50  0000 C CNN
F 1 "USB_A" H 950 2800 50  0000 C CNN
F 2 "Primayer:Molex_47346-0001_Micro_USB_SMT" V 950 2500 50  0001 C CNN
F 3 "" V 950 2500 50  0000 C CNN
	1    1000 2600
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR01
U 1 1 57FF7550
P 900 3050
F 0 "#PWR01" H 900 2800 50  0001 C CNN
F 1 "GND" H 900 2900 50  0000 C CNN
F 2 "" H 900 3050 50  0000 C CNN
F 3 "" H 900 3050 50  0000 C CNN
	1    900  3050
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 57FF787D
P 3750 2450
F 0 "D1" H 3750 2550 50  0000 C CNN
F 1 "D" H 3750 2350 50  0000 C CNN
F 2 "Diodes_SMD:SOD-323_HandSoldering" H 3750 2450 50  0001 C CNN
F 3 "" H 3750 2450 50  0000 C CNN
	1    3750 2450
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 57FF795E
P 3400 2550
F 0 "C2" H 3425 2650 50  0000 L CNN
F 1 "10n" H 3425 2450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3438 2400 50  0001 C CNN
F 3 "" H 3400 2550 50  0000 C CNN
	1    3400 2550
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 57FF7CD7
P 4550 3250
F 0 "R3" H 4600 3300 50  0000 L CNN
F 1 "15k" H 4600 3200 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4480 3250 50  0001 C CNN
F 3 "" H 4550 3250 50  0000 C CNN
	1    4550 3250
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 57FF7D15
P 4900 2900
F 0 "C3" H 4925 3000 50  0000 L CNN
F 1 "22u" H 4925 2800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4938 2750 50  0001 C CNN
F 3 "" H 4900 2900 50  0000 C CNN
	1    4900 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 57FFA375
P 4550 3450
F 0 "#PWR02" H 4550 3200 50  0001 C CNN
F 1 "GND" H 4550 3300 50  0000 C CNN
F 2 "" H 4550 3450 50  0000 C CNN
F 3 "" H 4550 3450 50  0000 C CNN
	1    4550 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 57FFA51A
P 5200 3150
F 0 "#PWR03" H 5200 2900 50  0001 C CNN
F 1 "GND" H 5200 3000 50  0000 C CNN
F 2 "" H 5200 3150 50  0000 C CNN
F 3 "" H 5200 3150 50  0000 C CNN
	1    5200 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 57FFA70E
P 4000 2300
F 0 "#PWR04" H 4000 2050 50  0001 C CNN
F 1 "GND" H 4000 2150 50  0000 C CNN
F 2 "" H 4000 2300 50  0000 C CNN
F 3 "" H 4000 2300 50  0000 C CNN
	1    4000 2300
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 57FFACED
P 5200 2900
F 0 "C4" H 5225 3000 50  0000 L CNN
F 1 "??" H 5225 2800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5238 2750 50  0001 C CNN
F 3 "" H 5200 2900 50  0000 C CNN
	1    5200 2900
	1    0    0    -1  
$EndComp
Text Label 1400 2500 0    50   ~ 0
USB_DM
Text Label 1400 2600 0    50   ~ 0
USB_DP
$Comp
L R R1
U 1 1 57FFE89D
P 2850 1850
F 0 "R1" V 2930 1850 50  0000 C CNN
F 1 "0R" V 2850 1850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2780 1850 50  0001 C CNN
F 3 "" H 2850 1850 50  0000 C CNN
	1    2850 1850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR05
U 1 1 58000E94
P 10350 5200
F 0 "#PWR05" H 10350 4950 50  0001 C CNN
F 1 "GND" H 10350 5050 50  0000 C CNN
F 2 "" H 10350 5200 50  0000 C CNN
F 3 "" H 10350 5200 50  0000 C CNN
	1    10350 5200
	1    0    0    -1  
$EndComp
$Comp
L TPS782XX U3
U 1 1 580018D4
P 6000 2800
F 0 "U3" H 6000 3150 60  0000 C CNN
F 1 "TPS782XX" H 6000 3050 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 6000 2550 60  0001 C CNN
F 3 "" H 6000 2800 60  0000 C CNN
	1    6000 2800
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NC_Small JP1
U 1 1 58001C62
P 6550 2900
F 0 "JP1" H 6550 2980 50  0000 C CNN
F 1 "Jumper_NC_Small" H 6560 2840 50  0001 C CNN
F 2 "Resistors_SMD:R_0603" H 6550 2900 50  0001 C CNN
F 3 "" H 6550 2900 50  0000 C CNN
	1    6550 2900
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 58002EA2
P 6900 2900
F 0 "C7" H 6925 3000 50  0000 L CNN
F 1 "2u2" H 6925 2800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6938 2750 50  0001 C CNN
F 3 "" H 6900 2900 50  0000 C CNN
	1    6900 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 58003894
P 10300 2700
F 0 "#PWR06" H 10300 2450 50  0001 C CNN
F 1 "GND" H 10300 2550 50  0000 C CNN
F 2 "" H 10300 2700 50  0000 C CNN
F 3 "" H 10300 2700 50  0000 C CNN
	1    10300 2700
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 58003977
P 10300 2500
F 0 "C8" H 10325 2600 50  0000 L CNN
F 1 "100n" H 10325 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10338 2350 50  0001 C CNN
F 3 "" H 10300 2500 50  0000 C CNN
	1    10300 2500
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 58003B16
P 10800 2500
F 0 "C9" H 10825 2600 50  0000 L CNN
F 1 "100n" H 10825 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10838 2350 50  0001 C CNN
F 3 "" H 10800 2500 50  0000 C CNN
	1    10800 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 58003B86
P 10800 2700
F 0 "#PWR07" H 10800 2450 50  0001 C CNN
F 1 "GND" H 10800 2550 50  0000 C CNN
F 2 "" H 10800 2700 50  0000 C CNN
F 3 "" H 10800 2700 50  0000 C CNN
	1    10800 2700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR08
U 1 1 58004092
P 6900 2600
F 0 "#PWR08" H 6900 2450 50  0001 C CNN
F 1 "+3.3V" H 6900 2740 50  0000 C CNN
F 2 "" H 6900 2600 50  0000 C CNN
F 3 "" H 6900 2600 50  0000 C CNN
	1    6900 2600
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG09
U 1 1 5800412A
P 1350 950
F 0 "#FLG09" H 1350 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 1350 1130 50  0000 C CNN
F 2 "" H 1350 950 50  0000 C CNN
F 3 "" H 1350 950 50  0000 C CNN
	1    1350 950 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 580049BF
P 5200 2600
F 0 "#PWR010" H 5200 2450 50  0001 C CNN
F 1 "+5V" H 5200 2740 50  0000 C CNN
F 2 "" H 5200 2600 50  0000 C CNN
F 3 "" H 5200 2600 50  0000 C CNN
	1    5200 2600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 58006896
P 10100 2200
F 0 "#PWR011" H 10100 2050 50  0001 C CNN
F 1 "+3.3V" H 10100 2340 50  0000 C CNN
F 2 "" H 10100 2200 50  0000 C CNN
F 3 "" H 10100 2200 50  0000 C CNN
	1    10100 2200
	1    0    0    -1  
$EndComp
$Comp
L AP3211 U1
U 1 1 58008377
P 2850 2700
F 0 "U1" H 2550 3150 60  0000 L BNN
F 1 "AP3211" H 2850 3150 60  0000 L BNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 2850 2700 60  0001 C CNN
F 3 "" H 2850 2700 60  0000 C CNN
	1    2850 2700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR012
U 1 1 58009C0E
P 12850 2450
F 0 "#PWR012" H 12850 2300 50  0001 C CNN
F 1 "+5V" H 12850 2590 50  0000 C CNN
F 2 "" H 12850 2450 50  0000 C CNN
F 3 "" H 12850 2450 50  0000 C CNN
	1    12850 2450
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 5800A31B
P 13150 2700
F 0 "C12" H 13175 2800 50  0000 L CNN
F 1 "100n" H 13175 2600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 13188 2550 50  0001 C CNN
F 3 "" H 13150 2700 50  0000 C CNN
	1    13150 2700
	1    0    0    -1  
$EndComp
Text Label 13500 3050 0    50   ~ 0
LD
Text Label 13500 3150 0    50   ~ 0
SCL
Text Label 13500 3250 0    50   ~ 0
SDI
Text Label 13500 3350 0    50   ~ 0
SDO1
$Comp
L GND #PWR013
U 1 1 5800AED3
P 12850 2950
F 0 "#PWR013" H 12850 2700 50  0001 C CNN
F 1 "GND" H 12850 2800 50  0000 C CNN
F 2 "" H 12850 2950 50  0000 C CNN
F 3 "" H 12850 2950 50  0000 C CNN
	1    12850 2950
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 5800BBA7
P 13300 3750
F 0 "R6" H 13350 3800 50  0000 L CNN
F 1 "15k" H 13350 3700 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 13230 3750 50  0001 C CNN
F 3 "" H 13300 3750 50  0000 C CNN
	1    13300 3750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR014
U 1 1 5800C0C7
P 13300 3550
F 0 "#PWR014" H 13300 3400 50  0001 C CNN
F 1 "+5V" H 13300 3690 50  0000 C CNN
F 2 "" H 13300 3550 50  0000 C CNN
F 3 "" H 13300 3550 50  0000 C CNN
	1    13300 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 J4
U 1 1 5800CEF7
P 15100 3000
F 0 "J4" H 15100 3450 50  0000 C CNN
F 1 "CONN_01X08" V 15200 3000 50  0000 C CNN
F 2 "Primayer:B8B-ZR-SM4-TF" H 15100 3000 50  0001 C CNN
F 3 "" H 15100 3000 50  0000 C CNN
	1    15100 3000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 J5
U 1 1 5800D412
P 15600 3900
F 0 "J5" H 15600 4350 50  0000 C CNN
F 1 "CONN_01X08" V 15700 3900 50  0000 C CNN
F 2 "Primayer:B8B-ZR-SM4-TF" H 15600 3900 50  0001 C CNN
F 3 "" H 15600 3900 50  0000 C CNN
	1    15600 3900
	1    0    0    -1  
$EndComp
$Comp
L CP C11
U 1 1 5800E918
P 12850 4900
F 0 "C11" H 12875 5000 50  0000 L CNN
F 1 "10u" H 12875 4800 50  0000 L CNN
F 2 "SMD_Packages:SMD-1206_Pol" H 12888 4750 50  0001 C CNN
F 3 "" H 12850 4900 50  0000 C CNN
	1    12850 4900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR015
U 1 1 5800E91E
P 12850 4650
F 0 "#PWR015" H 12850 4500 50  0001 C CNN
F 1 "+5V" H 12850 4790 50  0000 C CNN
F 2 "" H 12850 4650 50  0000 C CNN
F 3 "" H 12850 4650 50  0000 C CNN
	1    12850 4650
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 5800E924
P 13150 4900
F 0 "C13" H 13175 5000 50  0000 L CNN
F 1 "100n" H 13175 4800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 13188 4750 50  0001 C CNN
F 3 "" H 13150 4900 50  0000 C CNN
	1    13150 4900
	1    0    0    -1  
$EndComp
Text Label 13500 5250 0    50   ~ 0
LD
Text Label 13500 5350 0    50   ~ 0
SCL
Text Label 13500 5450 0    50   ~ 0
SDO1
Text Label 13500 5550 0    50   ~ 0
SDO2
$Comp
L GND #PWR016
U 1 1 5800E93E
P 12850 5150
F 0 "#PWR016" H 12850 4900 50  0001 C CNN
F 1 "GND" H 12850 5000 50  0000 C CNN
F 2 "" H 12850 5150 50  0000 C CNN
F 3 "" H 12850 5150 50  0000 C CNN
	1    12850 5150
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 5800E946
P 13300 5950
F 0 "R7" H 13350 6000 50  0000 L CNN
F 1 "15k" H 13350 5900 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 13230 5950 50  0001 C CNN
F 3 "" H 13300 5950 50  0000 C CNN
	1    13300 5950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR017
U 1 1 5800E94C
P 13300 5750
F 0 "#PWR017" H 13300 5600 50  0001 C CNN
F 1 "+5V" H 13300 5890 50  0000 C CNN
F 2 "" H 13300 5750 50  0000 C CNN
F 3 "" H 13300 5750 50  0000 C CNN
	1    13300 5750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 J6
U 1 1 5800EF4F
P 15100 5200
F 0 "J6" H 15100 5650 50  0000 C CNN
F 1 "CONN_01X08" V 15200 5200 50  0000 C CNN
F 2 "Primayer:B8B-ZR-SM4-TF" H 15100 5200 50  0001 C CNN
F 3 "" H 15100 5200 50  0000 C CNN
	1    15100 5200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 J7
U 1 1 5800EF5D
P 15600 6100
F 0 "J7" H 15600 6550 50  0000 C CNN
F 1 "CONN_01X08" V 15700 6100 50  0000 C CNN
F 2 "Primayer:B8B-ZR-SM4-TF" H 15600 6100 50  0001 C CNN
F 3 "" H 15600 6100 50  0000 C CNN
	1    15600 6100
	1    0    0    -1  
$EndComp
Text Label 14650 7100 0    50   ~ 0
LD
Text Label 14650 7200 0    50   ~ 0
SCL
Text Label 14650 7300 0    50   ~ 0
SDO2
$Comp
L +5V #PWR018
U 1 1 5801044C
P 14700 7500
F 0 "#PWR018" H 14700 7350 50  0001 C CNN
F 1 "+5V" H 14700 7640 50  0000 C CNN
F 2 "" H 14700 7500 50  0000 C CNN
F 3 "" H 14700 7500 50  0000 C CNN
	1    14700 7500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 580104B1
P 14700 6850
F 0 "#PWR019" H 14700 6600 50  0001 C CNN
F 1 "GND" H 14700 6700 50  0000 C CNN
F 2 "" H 14700 6850 50  0000 C CNN
F 3 "" H 14700 6850 50  0000 C CNN
	1    14700 6850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 58015763
P 9150 2250
F 0 "#PWR020" H 9150 2000 50  0001 C CNN
F 1 "GND" H 9150 2100 50  0000 C CNN
F 2 "" H 9150 2250 50  0000 C CNN
F 3 "" H 9150 2250 50  0000 C CNN
	1    9150 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2600 2350 2600
Wire Wire Line
	2350 2600 2350 2400
Wire Wire Line
	1300 2400 2450 2400
Wire Wire Line
	2050 1850 2050 2500
Connection ~ 2350 2400
Wire Wire Line
	900  3000 2450 3000
Connection ~ 2050 3000
Wire Wire Line
	3250 2400 3400 2400
Wire Wire Line
	3250 2700 3850 2700
Wire Wire Line
	3750 2700 3750 2600
Connection ~ 3400 2700
Connection ~ 3750 2700
Wire Wire Line
	4450 2700 5600 2700
Connection ~ 4550 2700
Wire Wire Line
	4900 1850 4900 2750
Wire Wire Line
	4900 3100 4900 3050
Wire Wire Line
	3750 2300 3750 2250
Wire Wire Line
	3750 2250 4000 2250
Wire Wire Line
	4000 2250 4000 2300
Wire Wire Line
	5200 2600 5200 2750
Connection ~ 4900 2700
Wire Wire Line
	4900 3100 6900 3100
Wire Wire Line
	5200 3050 5200 3150
Connection ~ 5200 3100
Wire Wire Line
	4550 3400 4550 3450
Wire Wire Line
	4550 3000 4550 3100
Wire Wire Line
	3250 3000 4450 3000
Wire Wire Line
	4450 3000 4450 3050
Wire Wire Line
	4450 3050 4550 3050
Connection ~ 4550 3050
Wire Wire Line
	1300 2500 1700 2500
Wire Wire Line
	1300 2600 1700 2600
Connection ~ 2050 2400
Wire Wire Line
	1400 3000 1400 2700
Wire Wire Line
	1400 2700 1300 2700
Wire Wire Line
	900  2900 900  3050
Connection ~ 1400 3000
Connection ~ 900  3000
Wire Wire Line
	2050 2800 2050 3000
Wire Wire Line
	2700 1850 2050 1850
Wire Wire Line
	3000 1850 4900 1850
Wire Wire Line
	10300 5100 10300 5150
Wire Wire Line
	10300 5150 10400 5150
Wire Wire Line
	10400 5150 10400 5100
Wire Wire Line
	10350 5150 10350 5200
Connection ~ 10350 5150
Wire Wire Line
	5600 2800 5500 2800
Wire Wire Line
	5500 2800 5500 2700
Connection ~ 5200 2700
Connection ~ 5500 2700
Wire Wire Line
	6400 2900 6450 2900
Wire Wire Line
	6650 2900 6700 2900
Wire Wire Line
	6700 2900 6700 3100
Wire Wire Line
	6900 3100 6900 3050
Connection ~ 6700 3100
Wire Wire Line
	5600 2900 5500 2900
Wire Wire Line
	5500 2900 5500 3100
Connection ~ 5500 3100
Wire Wire Line
	10100 2200 10100 2800
Wire Wire Line
	10100 2300 10800 2300
Wire Wire Line
	10300 2300 10300 2350
Wire Wire Line
	10300 2650 10300 2700
Wire Wire Line
	10800 2700 10800 2650
Wire Wire Line
	10800 2300 10800 2350
Wire Wire Line
	10600 2300 10600 2800
Connection ~ 10600 2300
Connection ~ 10300 2300
Connection ~ 6900 2700
Wire Wire Line
	6900 2600 6900 2750
Wire Wire Line
	6400 2700 6900 2700
Connection ~ 10100 2300
Wire Wire Line
	13700 3150 13500 3150
Wire Wire Line
	13700 3250 13500 3250
Wire Wire Line
	13700 3350 13500 3350
Wire Wire Line
	13700 3050 13500 3050
Wire Wire Line
	13700 2650 13650 2650
Wire Wire Line
	13650 2650 13650 2500
Wire Wire Line
	13650 2500 12850 2500
Wire Wire Line
	12850 2450 12850 2550
Wire Wire Line
	13150 2550 13150 2500
Connection ~ 13150 2500
Wire Wire Line
	13700 2750 13650 2750
Wire Wire Line
	13650 2750 13650 2900
Wire Wire Line
	13650 2900 12850 2900
Wire Wire Line
	12850 2850 12850 2950
Wire Wire Line
	13150 2850 13150 2900
Connection ~ 13150 2900
Connection ~ 12850 2900
Connection ~ 12850 2500
Wire Wire Line
	13300 3550 13300 3600
Wire Wire Line
	13700 3950 13300 3950
Wire Wire Line
	13300 3950 13300 3900
Wire Wire Line
	14800 2650 14900 2650
Wire Wire Line
	14900 2750 14800 2750
Wire Wire Line
	14800 2850 14900 2850
Wire Wire Line
	14900 2950 14800 2950
Wire Wire Line
	14800 3050 14900 3050
Wire Wire Line
	14900 3150 14800 3150
Wire Wire Line
	14800 3250 14900 3250
Wire Wire Line
	14900 3350 14800 3350
Wire Wire Line
	13700 5350 13500 5350
Wire Wire Line
	13700 5450 13500 5450
Wire Wire Line
	13700 5550 13500 5550
Wire Wire Line
	13700 5250 13500 5250
Wire Wire Line
	13700 4850 13650 4850
Wire Wire Line
	13650 4850 13650 4700
Wire Wire Line
	13650 4700 12850 4700
Wire Wire Line
	12850 4650 12850 4750
Wire Wire Line
	13150 4750 13150 4700
Connection ~ 13150 4700
Wire Wire Line
	13700 4950 13650 4950
Wire Wire Line
	13650 4950 13650 5100
Wire Wire Line
	13650 5100 12850 5100
Wire Wire Line
	12850 5050 12850 5150
Wire Wire Line
	13150 5050 13150 5100
Connection ~ 13150 5100
Connection ~ 12850 5100
Connection ~ 12850 4700
Wire Wire Line
	13300 5750 13300 5800
Wire Wire Line
	13700 6150 13300 6150
Wire Wire Line
	13300 6150 13300 6100
Wire Wire Line
	14800 4850 14900 4850
Wire Wire Line
	14900 4950 14800 4950
Wire Wire Line
	14800 5050 14900 5050
Wire Wire Line
	14900 5150 14800 5150
Wire Wire Line
	14800 5250 14900 5250
Wire Wire Line
	14900 5350 14800 5350
Wire Wire Line
	14800 5450 14900 5450
Wire Wire Line
	14900 5550 14800 5550
Wire Wire Line
	14850 7200 14650 7200
Wire Wire Line
	14850 7300 14650 7300
Wire Wire Line
	14850 7100 14650 7100
$Comp
L +3.3V #PWR021
U 1 1 580155E4
P 9150 1850
F 0 "#PWR021" H 9150 1700 50  0001 C CNN
F 1 "+3.3V" H 9150 1990 50  0000 C CNN
F 2 "" H 9150 1850 50  0000 C CNN
F 3 "" H 9150 1850 50  0000 C CNN
	1    9150 1850
	1    0    0    -1  
$EndComp
$Comp
L AVR-PDI-6A J8
U 1 1 58015B79
P 8700 2050
F 0 "J8" H 8620 2290 50  0000 C CNN
F 1 "AVR-PDI-6A" H 8490 1805 50  0000 L BNN
F 2 "Primayer:3x2_1.27mm_SMD_header" V 8255 2085 50  0001 C CNN
F 3 "" H 8700 2050 50  0000 C CNN
	1    8700 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1950 9150 1950
Wire Wire Line
	9150 1950 9150 1850
Wire Wire Line
	9000 2150 9150 2150
Wire Wire Line
	9150 2150 9150 2250
Wire Wire Line
	7950 1950 8400 1950
Text Label 7950 1950 0    50   ~ 0
PDI_D
Wire Wire Line
	8400 2150 7950 2150
Text Label 7950 2150 0    50   ~ 0
PDI_C
Wire Wire Line
	9000 3150 8750 3150
Text Label 8750 3250 0    50   ~ 0
PDI_D
Text Label 8750 3150 0    50   ~ 0
PDI_C
Wire Wire Line
	9000 3250 8750 3250
Text Label 11850 4750 2    50   ~ 0
SDI
Wire Wire Line
	11850 4750 11650 4750
Wire Wire Line
	11650 4550 11850 4550
Wire Wire Line
	11650 4450 11850 4450
Text Label 11850 4550 2    50   ~ 0
SCL
Text Label 11850 4450 2    50   ~ 0
LD
Wire Wire Line
	11650 4350 12250 4350
Wire Wire Line
	11650 4250 12250 4250
$Comp
L CONN_01X05 J2
U 1 1 5801BACF
P 15050 7200
F 0 "J2" H 15050 7500 50  0000 C CNN
F 1 "CONN_01X05" V 15150 7200 50  0000 C CNN
F 2 "Primayer:B5B-ZR-SM4-TF" H 15050 7200 50  0001 C CNN
F 3 "" H 15050 7200 50  0000 C CNN
	1    15050 7200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X05 J3
U 1 1 5801BC86
P 15050 8150
F 0 "J3" H 15050 8450 50  0000 C CNN
F 1 "CONN_01X05" V 15150 8150 50  0000 C CNN
F 2 "Primayer:B5B-ZR-SM4-TF" H 15050 8150 50  0001 C CNN
F 3 "" H 15050 8150 50  0000 C CNN
	1    15050 8150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR022
U 1 1 5801BD06
P 14800 7900
F 0 "#PWR022" H 14800 7750 50  0001 C CNN
F 1 "+5V" H 14800 8040 50  0000 C CNN
F 2 "" H 14800 7900 50  0000 C CNN
F 3 "" H 14800 7900 50  0000 C CNN
	1    14800 7900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5801BE38
P 14800 8400
F 0 "#PWR023" H 14800 8150 50  0001 C CNN
F 1 "GND" H 14800 8250 50  0000 C CNN
F 2 "" H 14800 8400 50  0000 C CNN
F 3 "" H 14800 8400 50  0000 C CNN
	1    14800 8400
	1    0    0    -1  
$EndComp
Wire Wire Line
	14400 8050 14850 8050
Wire Wire Line
	14400 8150 14850 8150
Wire Wire Line
	14400 8250 14850 8250
Wire Wire Line
	11650 3350 12250 3350
Wire Wire Line
	11650 4150 11700 4150
Wire Wire Line
	11700 4150 11700 4350
Connection ~ 11700 4350
Wire Wire Line
	11650 4050 11750 4050
Wire Wire Line
	11750 4050 11750 4250
Connection ~ 11750 4250
Text Label 12250 4250 2    50   ~ 0
EXP_RX_SDA
Text Label 12250 4350 2    50   ~ 0
EXP_TX_SCL
Text Label 12250 3350 2    50   ~ 0
EXP_ANA
$Comp
L RDA5807M U2
U 1 1 5801FBD9
P 5950 5100
F 0 "U2" H 5600 5450 50  0000 L BNN
F 1 "RDA5807M" H 5950 5450 50  0000 L BNN
F 2 "Housings_SSOP:MSOP-10_3x3mm_Pitch0.5mm" H 5950 5100 50  0001 C CNN
F 3 "" H 5950 5100 50  0000 C CNN
	1    5950 5100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR024
U 1 1 58021288
P 6800 4700
F 0 "#PWR024" H 6800 4550 50  0001 C CNN
F 1 "+3.3V" H 6800 4840 50  0000 C CNN
F 2 "" H 6800 4700 50  0000 C CNN
F 3 "" H 6800 4700 50  0000 C CNN
	1    6800 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 58021461
P 6500 5550
F 0 "#PWR025" H 6500 5300 50  0001 C CNN
F 1 "GND" H 6500 5400 50  0000 C CNN
F 2 "" H 6500 5550 50  0000 C CNN
F 3 "" H 6500 5550 50  0000 C CNN
	1    6500 5550
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 58021C8B
P 6800 4950
F 0 "C6" H 6825 5050 50  0000 L CNN
F 1 "22n" H 6825 4850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6838 4800 50  0001 C CNN
F 3 "" H 6800 4950 50  0000 C CNN
	1    6800 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 580223B7
P 6800 5150
F 0 "#PWR026" H 6800 4900 50  0001 C CNN
F 1 "GND" H 6800 5000 50  0000 C CNN
F 2 "" H 6800 5150 50  0000 C CNN
F 3 "" H 6800 5150 50  0000 C CNN
	1    6800 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 4900 6550 4900
Wire Wire Line
	6550 4900 6550 4750
Wire Wire Line
	6550 4750 6800 4750
Wire Wire Line
	6800 4700 6800 4800
Connection ~ 6800 4750
Wire Wire Line
	6800 5100 6800 5150
Wire Wire Line
	6450 5500 6500 5500
Wire Wire Line
	6500 5500 6500 5550
$Comp
L GND #PWR027
U 1 1 58022A35
P 5400 5550
F 0 "#PWR027" H 5400 5300 50  0001 C CNN
F 1 "GND" H 5400 5400 50  0000 C CNN
F 2 "" H 5400 5550 50  0000 C CNN
F 3 "" H 5400 5550 50  0000 C CNN
	1    5400 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5500 5400 5500
Wire Wire Line
	5400 5400 5400 5550
Wire Wire Line
	5450 5400 5400 5400
Connection ~ 5400 5500
$Comp
L CONN_01X01 J1
U 1 1 58022E67
P 4950 4000
F 0 "J1" H 4950 3900 50  0000 C CNN
F 1 "CONN_01X01" V 5050 4000 50  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 4950 4000 50  0001 C CNN
F 3 "" H 4950 4000 50  0000 C CNN
	1    4950 4000
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 5100 5450 5100
Wire Wire Line
	4000 5200 5450 5200
$Comp
L R R5
U 1 1 580288CC
P 4800 4900
F 0 "R5" H 4850 4950 50  0000 L CNN
F 1 "2k2" H 4850 4850 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4730 4900 50  0001 C CNN
F 3 "" H 4800 4900 50  0000 C CNN
	1    4800 4900
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 58028AF2
P 4550 4900
F 0 "R4" H 4600 4950 50  0000 L CNN
F 1 "2k2" H 4600 4850 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4480 4900 50  0001 C CNN
F 3 "" H 4550 4900 50  0000 C CNN
	1    4550 4900
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR028
U 1 1 58029285
P 4550 4650
F 0 "#PWR028" H 4550 4500 50  0001 C CNN
F 1 "+3.3V" H 4550 4790 50  0000 C CNN
F 2 "" H 4550 4650 50  0000 C CNN
F 3 "" H 4550 4650 50  0000 C CNN
	1    4550 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 4650 4550 4750
Wire Wire Line
	4550 4700 4800 4700
Wire Wire Line
	4800 4700 4800 4750
Connection ~ 4550 4700
Text Label 8700 3750 0    50   ~ 0
R_CLK
Wire Wire Line
	8700 3750 9000 3750
Wire Wire Line
	4800 5100 4800 5050
Wire Wire Line
	4550 5200 4550 5050
Connection ~ 4800 5100
Text Label 4000 5100 0    50   ~ 0
EXP_TX_SCL
Text Label 4000 5200 0    50   ~ 0
EXP_RX_SDA
Connection ~ 4550 5200
$Comp
L C C5
U 1 1 5802D9D4
P 5450 4200
F 0 "C5" H 5475 4300 50  0000 L CNN
F 1 "22n" H 5475 4100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5488 4050 50  0001 C CNN
F 3 "" H 5450 4200 50  0000 C CNN
	1    5450 4200
	1    0    0    -1  
$EndComp
$Comp
L L_Small L2
U 1 1 5802DC38
P 5700 4200
F 0 "L2" H 5730 4240 50  0000 L CNN
F 1 "100nH" H 5730 4160 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 5700 4200 50  0001 C CNN
F 3 "" H 5700 4200 50  0000 C CNN
	1    5700 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 5802E8DE
P 5700 4450
F 0 "#PWR029" H 5700 4200 50  0001 C CNN
F 1 "GND" H 5700 4300 50  0000 C CNN
F 2 "" H 5700 4450 50  0000 C CNN
F 3 "" H 5700 4450 50  0000 C CNN
	1    5700 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 4350 5450 4400
Wire Wire Line
	5450 4400 5700 4400
Connection ~ 5700 4400
Wire Wire Line
	5450 4000 5450 4050
Wire Wire Line
	5150 4000 5700 4000
Wire Wire Line
	5700 4000 5700 4100
Wire Wire Line
	5450 4900 5250 4900
Wire Wire Line
	5250 4900 5250 4000
Connection ~ 5450 4000
Connection ~ 5250 4000
Wire Wire Line
	6450 5400 6700 5400
Text Label 6700 5400 2    50   ~ 0
R_CLK
Wire Wire Line
	9000 4250 8700 4250
Wire Wire Line
	8700 4350 9000 4350
Text Label 8700 4250 0    50   ~ 0
USB_DM
Text Label 8700 4350 0    50   ~ 0
USB_DP
Text Label 14400 8050 0    50   ~ 0
EXP_ANA
Text Label 14400 8150 0    50   ~ 0
EXP_RX_SDA
Text Label 14400 8250 0    50   ~ 0
EXP_TX_SCL
NoConn ~ 9000 4450
NoConn ~ 9000 4550
NoConn ~ 9000 4650
NoConn ~ 9000 4750
NoConn ~ 11650 3150
NoConn ~ 11650 3250
NoConn ~ 11650 3450
NoConn ~ 11650 3550
NoConn ~ 11650 3650
NoConn ~ 11650 3750
NoConn ~ 11650 3850
NoConn ~ 13700 3650
NoConn ~ 13700 5850
NoConn ~ 9000 2050
NoConn ~ 8400 2050
NoConn ~ 6450 5100
NoConn ~ 6450 5200
$Comp
L +3.3V #PWR030
U 1 1 5803F2B3
P 1000 950
F 0 "#PWR030" H 1000 800 50  0001 C CNN
F 1 "+3.3V" H 1000 1090 50  0000 C CNN
F 2 "" H 1000 950 50  0000 C CNN
F 3 "" H 1000 950 50  0000 C CNN
	1    1000 950 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR031
U 1 1 5803F666
P 1700 950
F 0 "#PWR031" H 1700 800 50  0001 C CNN
F 1 "+5V" H 1700 1090 50  0000 C CNN
F 2 "" H 1700 950 50  0000 C CNN
F 3 "" H 1700 950 50  0000 C CNN
	1    1700 950 
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG032
U 1 1 5803F6E6
P 2050 950
F 0 "#FLG032" H 2050 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 2050 1130 50  0000 C CNN
F 2 "" H 2050 950 50  0000 C CNN
F 3 "" H 2050 950 50  0000 C CNN
	1    2050 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 950  1700 1000
Wire Wire Line
	1700 1000 2050 1000
Wire Wire Line
	2050 1000 2050 950 
Wire Wire Line
	1350 950  1350 1000
Wire Wire Line
	1350 1000 1000 1000
Wire Wire Line
	1000 1000 1000 950 
$Comp
L PWR_FLAG #FLG033
U 1 1 58043063
P 1400 2350
F 0 "#FLG033" H 1400 2445 50  0001 C CNN
F 1 "PWR_FLAG" H 1400 2530 50  0000 C CNN
F 2 "" H 1400 2350 50  0000 C CNN
F 3 "" H 1400 2350 50  0000 C CNN
	1    1400 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2350 1400 2400
Connection ~ 1400 2400
Wire Wire Line
	5700 4300 5700 4450
$Comp
L GND #PWR034
U 1 1 58047E55
P 2500 1000
F 0 "#PWR034" H 2500 750 50  0001 C CNN
F 1 "GND" H 2500 850 50  0000 C CNN
F 2 "" H 2500 1000 50  0000 C CNN
F 3 "" H 2500 1000 50  0000 C CNN
	1    2500 1000
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG035
U 1 1 580480F7
P 2500 950
F 0 "#FLG035" H 2500 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 2500 1130 50  0000 C CNN
F 2 "" H 2500 950 50  0000 C CNN
F 3 "" H 2500 950 50  0000 C CNN
	1    2500 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1000 2500 950 
$Comp
L KT3225T U7
U 1 1 5804C1DC
P 8000 3950
F 0 "U7" H 7750 4200 50  0000 L BNN
F 1 "KT3225T" H 8000 4200 50  0000 L BNN
F 2 "Primayer:KT3225T" H 8000 3950 50  0001 C CNN
F 3 "" H 8000 3950 50  0000 C CNN
	1    8000 3950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR036
U 1 1 5804C49D
P 7250 3800
F 0 "#PWR036" H 7250 3650 50  0001 C CNN
F 1 "+3.3V" H 7250 3940 50  0000 C CNN
F 2 "" H 7250 3800 50  0000 C CNN
F 3 "" H 7250 3800 50  0000 C CNN
	1    7250 3800
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 5804C610
P 7250 4050
F 0 "C14" H 7275 4150 50  0000 L CNN
F 1 "100n" H 7275 3950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7288 3900 50  0001 C CNN
F 3 "" H 7250 4050 50  0000 C CNN
	1    7250 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3850 7600 3850
Wire Wire Line
	7250 3800 7250 3900
Connection ~ 7250 3850
Wire Wire Line
	7600 3950 7500 3950
Wire Wire Line
	7500 3950 7500 3850
Connection ~ 7500 3850
Wire Wire Line
	7250 4200 7250 4300
Wire Wire Line
	7250 4250 7500 4250
Wire Wire Line
	7500 4250 7500 4050
Wire Wire Line
	7500 4050 7600 4050
$Comp
L GND #PWR037
U 1 1 5804CD29
P 7250 4300
F 0 "#PWR037" H 7250 4050 50  0001 C CNN
F 1 "GND" H 7250 4150 50  0000 C CNN
F 2 "" H 7250 4300 50  0000 C CNN
F 3 "" H 7250 4300 50  0000 C CNN
	1    7250 4300
	1    0    0    -1  
$EndComp
Connection ~ 7250 4250
Wire Wire Line
	8400 3850 9000 3850
Wire Wire Line
	14800 6050 15400 5750
Wire Wire Line
	14800 6450 15400 5850
Wire Wire Line
	14800 6150 15400 5950
Wire Wire Line
	14800 5950 15400 6050
Wire Wire Line
	14800 6350 15400 6150
Wire Wire Line
	14800 5850 15400 6250
Wire Wire Line
	14800 6250 15400 6350
Wire Wire Line
	14800 5750 15400 6450
Wire Wire Line
	14800 3550 15400 4250
Wire Wire Line
	14800 4050 15400 4150
Wire Wire Line
	14800 3650 15400 4050
Wire Wire Line
	14800 4150 15400 3950
Wire Wire Line
	14800 3750 15400 3850
Wire Wire Line
	14800 3950 15400 3750
Wire Wire Line
	14800 4250 15400 3650
Wire Wire Line
	14800 3850 15400 3550
$Comp
L TEST_1P W1
U 1 1 5804AF5F
P 3150 1000
F 0 "W1" H 3150 1270 50  0000 C CNN
F 1 "MOUNT" H 3150 1200 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2.5mm_Pad" H 3350 1000 50  0001 C CNN
F 3 "" H 3350 1000 50  0000 C CNN
	1    3150 1000
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P W2
U 1 1 5804BA56
P 3500 1000
F 0 "W2" H 3500 1270 50  0000 C CNN
F 1 "MOUNT" H 3500 1200 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2.5mm_Pad" H 3700 1000 50  0001 C CNN
F 3 "" H 3700 1000 50  0000 C CNN
	1    3500 1000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 5804BB4F
P 3150 1050
F 0 "#PWR038" H 3150 800 50  0001 C CNN
F 1 "GND" H 3150 900 50  0000 C CNN
F 2 "" H 3150 1050 50  0000 C CNN
F 3 "" H 3150 1050 50  0000 C CNN
	1    3150 1050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 5804BBDB
P 3500 1050
F 0 "#PWR039" H 3500 800 50  0001 C CNN
F 1 "GND" H 3500 900 50  0000 C CNN
F 2 "" H 3500 1050 50  0000 C CNN
F 3 "" H 3500 1050 50  0000 C CNN
	1    3500 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1050 3500 1000
Wire Wire Line
	3150 1050 3150 1000
Wire Wire Line
	14850 7950 14800 7950
Wire Wire Line
	14800 7950 14800 7900
Wire Wire Line
	14850 8350 14800 8350
Wire Wire Line
	14800 8350 14800 8400
Wire Wire Line
	14850 7000 14800 7000
Wire Wire Line
	14800 7000 14800 6800
Wire Wire Line
	14800 6800 14700 6800
Wire Wire Line
	14700 6800 14700 6850
Wire Wire Line
	14850 7400 14800 7400
Wire Wire Line
	14800 7400 14800 7550
Wire Wire Line
	14800 7550 14700 7550
Wire Wire Line
	14700 7550 14700 7500
Wire Wire Line
	11650 4650 11850 4650
Text Label 11850 4650 2    50   ~ 0
SDO2
NoConn ~ 9000 4050
NoConn ~ 9000 4150
$EndSCHEMATC
