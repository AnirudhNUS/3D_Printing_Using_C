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

G1 X58.5065 Y50 E0
G1 X52.6287 Y58.0902 E0.13161
G1 X43.1181 Y55 E0.26322
G1 X43.1181 Y45 E0.39483
G1 X52.6286 Y41.9098 E0.52644
G1 X58.5065 Y50 E0.65805


G1 X55 Y50 E0.65805
G1 X54.9901 Y50.314 E0.662184
G1 X54.9606 Y50.6267 E0.666318
G1 X54.9114 Y50.9369 E0.670452
G1 X54.8429 Y51.2434 E0.674586
G1 X54.7553 Y51.5451 E0.67872
G1 X54.6489 Y51.8406 E0.682854
G1 X54.5241 Y52.1289 E0.686988
G1 X54.3815 Y52.4088 E0.691122
G1 X54.2216 Y52.6791 E0.695256
G1 X54.0451 Y52.9389 E0.69939
G1 X53.8526 Y53.1871 E0.703524
G1 X53.6448 Y53.4227 E0.707658
G1 X53.4227 Y53.6448 E0.711792
G1 X53.1871 Y53.8526 E0.715926
G1 X52.9389 Y54.0451 E0.720059
G1 X52.6791 Y54.2216 E0.724193
G1 X52.4088 Y54.3815 E0.728327
G1 X52.1289 Y54.5241 E0.732461
G1 X51.8406 Y54.6489 E0.736595
G1 X51.5451 Y54.7553 E0.740729
G1 X51.2435 Y54.8429 E0.744863
G1 X50.9369 Y54.9114 E0.748997
G1 X50.6267 Y54.9606 E0.753131
G1 X50.314 Y54.9901 E0.757265
G1 X50 Y55 E0.761399
G1 X49.6861 Y54.9901 E0.765533
G1 X49.3733 Y54.9606 E0.769667
G1 X49.0631 Y54.9114 E0.773801
G1 X48.7566 Y54.8429 E0.777935
G1 X48.4549 Y54.7553 E0.782069
G1 X48.1594 Y54.6489 E0.786203
G1 X47.8711 Y54.5241 E0.790337
G1 X47.5912 Y54.3815 E0.794471
G1 X47.3209 Y54.2216 E0.798605
G1 X47.0611 Y54.0451 E0.802739
G1 X46.8129 Y53.8526 E0.806873
G1 X46.5773 Y53.6448 E0.811007
G1 X46.3552 Y53.4227 E0.815141
G1 X46.1474 Y53.1871 E0.819275
G1 X45.9549 Y52.9389 E0.823409
G1 X45.7784 Y52.6791 E0.827543
G1 X45.6185 Y52.4088 E0.831677
G1 X45.4759 Y52.1289 E0.835811
G1 X45.3511 Y51.8406 E0.839945
G1 X45.2447 Y51.5451 E0.844078
G1 X45.1571 Y51.2435 E0.848212
G1 X45.0886 Y50.9369 E0.852346
G1 X45.0394 Y50.6267 E0.85648
G1 X45.0099 Y50.314 E0.860614
G1 X45 Y50 E0.864748
G1 X45.0099 Y49.6861 E0.868882
G1 X45.0394 Y49.3733 E0.873016
G1 X45.0886 Y49.0631 E0.87715
G1 X45.1571 Y48.7566 E0.881284
G1 X45.2447 Y48.4549 E0.885418
G1 X45.3511 Y48.1594 E0.889552
G1 X45.4759 Y47.8711 E0.893686
G1 X45.6185 Y47.5912 E0.89782
G1 X45.7784 Y47.3209 E0.901954
G1 X45.9549 Y47.0611 E0.906088
G1 X46.1474 Y46.8129 E0.910222
G1 X46.3551 Y46.5773 E0.914356
G1 X46.5773 Y46.3552 E0.91849
G1 X46.8129 Y46.1474 E0.922624
G1 X47.0611 Y45.9549 E0.926758
G1 X47.3209 Y45.7784 E0.930892
G1 X47.5912 Y45.6185 E0.935026
G1 X47.8711 Y45.4759 E0.93916
G1 X48.1594 Y45.3511 E0.943294
G1 X48.4549 Y45.2447 E0.947428
G1 X48.7565 Y45.1571 E0.951562
G1 X49.0631 Y45.0886 E0.955696
G1 X49.3733 Y45.0394 E0.95983
G1 X49.686 Y45.0099 E0.963964
G1 X50 Y45 E0.968097
G1 X50.3139 Y45.0099 E0.972231
G1 X50.6266 Y45.0394 E0.976365
G1 X50.9369 Y45.0886 E0.980499
G1 X51.2434 Y45.1571 E0.984633
G1 X51.5451 Y45.2447 E0.988767
G1 X51.8406 Y45.3511 E0.992901
G1 X52.1289 Y45.4759 E0.997035
G1 X52.4087 Y45.6185 E1.00117
G1 X52.6791 Y45.7783 E1.0053
G1 X52.9389 Y45.9549 E1.00944
G1 X53.1871 Y46.1474 E1.01357
G1 X53.4227 Y46.3551 E1.01771
G1 X53.6448 Y46.5772 E1.02184
G1 X53.8526 Y46.8129 E1.02597
G1 X54.0451 Y47.0611 E1.03011
G1 X54.2216 Y47.3208 E1.03424
G1 X54.3815 Y47.5912 E1.03837
G1 X54.5241 Y47.8711 E1.04251
G1 X54.6489 Y48.1594 E1.04664
G1 X54.7553 Y48.4549 E1.05078
G1 X54.8429 Y48.7565 E1.05491
G1 X54.9114 Y49.0631 E1.05904
G1 X54.9606 Y49.3733 E1.06318
G1 X54.9901 Y49.686 E1.06731
G1 X55 Y50 E1.07145



;-------- Beginning of Bottom Filler --------

M140 S0
M204 S3000
M205 X20 Y20
M107

M82 ;absolute extrusion mode
M104 S0
M104 T1 S0
;End of Gcode
