M109 S240 ; set temperature to 240 and vait to arrive at 240 
G21 ; set system to metter (10 mean 10mm)
G91 ; set to incremental ( x10 mean move 10mm on axe x)
M83 ; Set extruder to asolute ( E10 mean 10mm wire on extruder)
G28 ; Go home all axes (X,Y,Z)

;Go to coordonate 10,10 without wire
G1 X10 Y10 

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2

;Make a square 30x30mm with 1mm/cm wire
G1 X30 Y0  E3
G1 X0 Y30  E3
G1 X-30 Y0 E3
G1 X0 Y-30 E3
Z0.2


G28 ; Go home all axes (X,Y,Z)
M84 ; disable all steppers
