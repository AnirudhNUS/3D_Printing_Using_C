;M109 S240 ;set head and wait to arrive at 240 grade celsius 

G21 ; set system to metter (10 mean 10mm)
G91 ; set to incremental ( any x10 mean move 10mm on axe x)
M83 ; Set extruder to incremental ( any E10 mean 10mm wire on extruder)
G28 ; Go home all axes (X,Y,Z)
;Go to coordonate 10,10 without wire
G1 X10 Y10 
;Make a square 30x30mm with 1mm/cm wire ( E3 because is 3cm to make)
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2  ; rise with 0.2mm