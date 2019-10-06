import numpy as np 
from matplotlib import pyplot as plt 
import math

def CoeffL(aoa):
    aoa = aoa * 180 / 3.14159265
    while (aoa < -180):
        aoa += 360
    
    while (aoa > 180):
        aoa -= 360
    
    if (aoa <= 10 and aoa >= -10):
        return 0.1*aoa
    
    elif (aoa > 10 and aoa < 60):
        return 1.0

    elif (aoa < -10 and aoa > -60):
        return -1.0
    
    elif (aoa > 60 and aoa < 120):
        return 1-0.0333333*(aoa-60)
    
    elif (aoa < -60 and aoa > -120):
        return 1-0.033333*(aoa+120)
    
    elif (aoa > 120 and aoa < 170):
        return -1
    
    elif (aoa < -120 and aoa > -170):
        return 1
    
    elif (aoa > 170 and aoa < 180):
        return -1+0.1*(aoa-170)
    
    elif (aoa < -170 and aoa > -180):
        return 0.1*(aoa+180)

def CoeffD (aoa):
    aoa = aoa * 180 / 3.14159265
    while (aoa < -180):
        aoa += 360
    
    while (aoa > 180):
        aoa -= 360
    
    aoa = abs(aoa)
    if (aoa < 10 ):
        return 0.1
    
    elif (aoa > 10 and aoa < 90):
        return 0.017*(aoa-10)+0.1;
    
    elif (aoa > 90 and aoa < 170):
        return 1.46-0.017*(aoa-90)
    
    elif (aoa > 170 and aoa < 180):
        return 0.1

def CoeffM (aoa):
    aoa = aoa * 180 / 3.14159265
    while (aoa < -180):
        aoa += 360
    
    while (aoa > 180):
        aoa -= 360
    
    if (aoa <= 90 and aoa >= -90):
        return -0.00444*aoa
    
    if (aoa >= 90 and aoa <= 150):
        return -0.4
    
    if (aoa <= 90 and aoa >=-150):
        return 0.4
    
    if (aoa <= 180 and aoa >= 150):
        return 0.013333*(aoa-150)-0.4
    
    if (aoa <= -150 and aoa >= -180):
        return 0.013333*(aoa+150)+0.4



aoas = np.linspace(-math.pi, math.pi, 10000)
Cls = [CoeffL(i) for i in aoas]
Cds = [CoeffD(i) for i in aoas]
Cms = [CoeffM(i) for i in aoas]


plt.plot(aoas*180/math.pi, Cls, label = r"$C_l$")
plt.plot(aoas*180/math.pi, Cds, label = r"$C_d$")
plt.plot(aoas*180/math.pi, Cms, label = r"$C_m$")
plt.grid()
plt.legend()
plt.xlabel(r"$\alpha$ $[^\circ]$")
plt.savefig("../Final_Report/img/Coeffs.pdf")
plt.show()