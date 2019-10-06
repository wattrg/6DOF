from matplotlib import pyplot as plt 
import pandas as pd 
import numpy as np 
import sys



raw_data = pd.read_csv("./trajectory.csv", delimiter=',')

state_data = []
state_data.append(raw_data)

for data in state_data:
    state = data.values.astype(float)

time = state[:, 0]
u = state[:, 1]
v = state[:, 2]
w = state[:, 3]
e1 = state[:, 4]
e2 = state[:, 5]
e3 = state[:, 6]
p = state[:, 7]
q = state[:, 8]
r = state[:, 9]
xv = state[:, 10]
yv = state[:, 11]
zv = state[:, 12]
x = state[:, 13]
y = state[:, 14]
z = state[:, 15]

plt.figure()
plt.plot(time, u, label=r'$u$')
plt.plot(time, v, label=r'$v$')
plt.plot(time, w, label=r'$w$')
plt.grid()
plt.legend()
plt.xlabel('time [s]')
plt.ylabel('velocity [m/s]')
plt.savefig("../../../Final_Report/img/"+sys.argv[1]+"/v_b.pdf")

plt.figure()
plt.plot(time, e1, label=r'$\psi$')
plt.plot(time, e2, label=r'$\theta$')
plt.plot(time, e3, label=r'$\phi$')
plt.legend()
plt.grid()
plt.xlabel('time [s]')
plt.ylabel('euler angle [rad]')
plt.savefig("../../../Final_Report/img/"+sys.argv[1]+"/euler.pdf")


plt.figure()
plt.plot(time, p, label=r'$p$')
plt.plot(time, q, label=r'$q$')
plt.plot(time, r, label=r'$r$')
plt.legend()
plt.grid()
plt.xlabel('time [s]')
plt.ylabel('angular velocity [rad/s]')
plt.savefig("../../../Final_Report/img/"+sys.argv[1]+"/omega.pdf")

plt.figure()
plt.plot(time, xv, label=r'$v_x$')
plt.plot(time, yv, label=r'$v_y$')
plt.plot(time, zv, label=r'$v_z$')
plt.legend()
plt.grid()
plt.xlabel('time [s]')
plt.ylabel('velocity [m/s]')
plt.savefig("../../../Final_Report/img/"+sys.argv[1]+"/v_inert.pdf")

plt.figure()
plt.plot(time, x, label=r'$x$')
plt.plot(time, y, label=r'$y$')
plt.plot(time, z, label=r'$z$')
plt.legend()
plt.grid()
plt.xlabel('time [s]')
plt.ylabel('pos [m]')
plt.savefig("../../../Final_Report/img/"+sys.argv[1]+"/pos.pdf")

plt.figure()
plt.plot(x, y)
plt.xlabel(r'$x$')
plt.ylabel(r'$y$')
plt.axis('equal')
plt.grid()
plt.xlabel('x [m]')
plt.ylabel('y [m]')
plt.savefig("../../../Final_Report/img/"+sys.argv[1]+"/overhead.pdf")


plt.draw()
plt.pause(1)
input("<Hit Enter to Close Figures>")
plt.close()


