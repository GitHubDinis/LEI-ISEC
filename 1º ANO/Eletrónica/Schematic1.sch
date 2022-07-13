*version 9.1 2173007555
u 52
V? 3
R? 5
@libraries
@analysis
@targets
@attributes
@translators
a 0 u 13 0 0 0 hln 100 PCBOARDS=PCB
a 0 u 13 0 0 0 hln 100 PSPICE=PSPICE
a 0 u 13 0 0 0 hln 100 XILINX=XILINX
@setup
unconnectedPins 0
connectViaLabel 0
connectViaLocalLabels 0
NoStim4ExtIFPortsWarnings 1
AutoGenStim4ExtIFPorts 1
@index
pageloc 1 0 2243 
@status
n 0 121:03:06:12:11:27;1617707487 e 
s 2832 121:03:06:12:11:32;1617707492 e 
*page 1 0 970 720 iA
@ports
@parts
part 2 VSRC 130 110 h
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 ap 9 0 20 10 hcn 100 REFDES=V1
part 4 r 170 100 h
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
a 0 ap 9 0 15 0 hln 100 REFDES=R1
a 0 u 13 0 15 25 hln 100 VALUE=1.123k
part 5 r 230 180 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R2
a 0 ap 9 0 15 0 hln 100 REFDES=R2
a 0 u 13 0 15 25 hln 100 VALUE=1.280k
part 6 r 300 130 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R3
a 0 ap 9 0 15 0 hln 100 REFDES=R3
a 0 u 13 0 15 25 hln 100 VALUE=1.425k
part 7 r 390 170 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R4
a 0 ap 9 0 15 0 hln 100 REFDES=R4
a 0 u 13 0 15 25 hln 100 VALUE=1.026
part 3 VSRC 300 170 h
a 0 a 0:13 0 0 0 hln 100 PKGREF=V2
a 1 ap 9 0 20 10 hcn 100 REFDES=V2
a 1 u 0 0 0 0 hcn 100 DC=-10
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
@conn
w 9
s 130 100 130 110 8
s 170 100 130 100 12
w 39
s 300 130 300 170 38
w 25
s 210 100 230 100 28
s 230 100 230 140 30
s 230 100 260 100 32
s 260 100 260 90 34
s 260 90 300 90 36
s 300 90 390 90 44
s 390 90 390 130 46
w 15
s 130 220 130 150 18
s 230 220 130 220 20
s 230 180 230 220 22
s 300 210 300 220 40
s 230 220 300 220 42
s 390 170 390 220 48
s 390 220 300 220 50
@junction
j 170 100
+ p 4 1
+ w 9
j 230 180
+ p 5 1
+ w 15
j 210 100
+ p 4 2
+ w 25
j 230 140
+ p 5 2
+ w 25
j 230 100
+ w 25
+ w 25
j 300 90
+ p 6 2
+ w 25
j 300 130
+ p 6 1
+ w 39
j 230 220
+ w 15
+ w 15
j 390 130
+ p 7 2
+ w 25
j 390 170
+ p 7 1
+ w 15
j 300 220
+ w 15
+ w 15
j 300 170
+ p 3 +
+ w 39
j 300 210
+ p 3 -
+ w 15
j 130 110
+ p 2 +
+ w 9
j 130 150
+ p 2 -
+ w 15
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
