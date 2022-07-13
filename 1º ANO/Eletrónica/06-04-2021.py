import numpy as np

V2 = -10
V3 = 0
R1 = 1.123
R2 = 1.280
R3 = 1.425
R4 = 1.026
I1 = 8.38

# MalhaA: V1 + R1*I1 + R2*(I1-I2) = 0
# MalhaB: V2 + R3*(I2-I3) + V3 - R2*(I2-I1) = 0
# MalhaC: R4*I3 + V3 - R3*(I3-I2) = 0

# V1            I2          I3

# V1            I2*(-R2)    0           =   -R1*I1 +R2*I1
# 0             I2*(R3-R2)  I3*(-R3)    =   -V2 -V3 -R2*I1
# 0             I2*(-R3)    I3*(R4-R3)  =   -V3


A=np.array([[1,-R2,0],[0,R3-R2,-R3],[0,-R3,R4-R3]])
B=np.array([(-R1*I1)+R2*I1,(-V2-V3)-R2*I1,V3])

solucao=np.linalg.solve(A,B)

print('Valor de V1: ', round(solucao[0],3))
print('Valor de I2: ', round(solucao[1],3))
print('Valor de I3: ', round(solucao[2],3))



