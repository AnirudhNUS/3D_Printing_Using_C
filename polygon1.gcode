T0
M82 ;absolute extrusion mode

G92 E0
M109 S200
G280 S1
G0 Z20.001
G1 F1500 E-6.5

M107
M204 S625
M205 X10 Y10
G1 F600 Z2.2
M204 S500
M205 X5 Y5
G1 F600 Z0.2
G1 F1500 E0

;-------- End of Top Filler -------------

G1 F1200 X10 Y10 E0 

G1 X35.7735 Y50 E0
G1 X27.1133 Y55 E0.13161
G1 X27.1132 Y45 E0.26322
G1 X35.7735 Y50 E0.39483
;-------- Beginning of Bottom Filler --------

M140 S0
M204 S3000
M205 X20 Y20
M107

M82 ;absolute extrusion mode
M104 S0
M104 T1 S0
;End of Gcode
