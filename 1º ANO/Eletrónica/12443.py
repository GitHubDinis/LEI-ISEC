import numpy as np
from matplotlib import pyplot as plt
from math import pi

f3 = 100 #10ms
f5 = 50 #20ms

P = 1/f5
PA = P/2000
t = np.arange(0,10*P,PA)

v3 = 1*np.sin(2*pi*f3*t+pi)
v5 = 0.5*np.sin(2*pi*f5*t+0.5*pi)

vout = -v3+v5

plt.plot(t,v3,'g',t,v5,'k',t,vout,'r')
plt.axis([0,10*P,-2,2])
plt.grid()
plt.show()
