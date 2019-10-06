figure();
hold on;
grid on;
plot(out.V_inert.time, out.V_inert.Data(:,1))
plot(out.V_inert.time, out.V_inert.Data(:,2))
plot(out.V_inert.time, out.V_inert.Data(:,3))
xlabel('time [s]')
ylabel('velocity [m/s]')
legend('v_x','v_y','v_z')
saveas(gcf, '../Final_Report/img/m_v_inert.png')

figure();
hold on;
grid on;
plot(out.V_inert.time, out.euler.Data(:,1))
plot(out.V_inert.time, out.euler.Data(:,2))
plot(out.V_inert.time, out.euler.Data(:,3))
legend('psi','theta','phi')
xlabel('time [s]')
ylabel('Angle [rad]')
saveas(gcf, '../Final_Report/img/m_euler.png')


figure();
hold on;
grid on;
plot(out.V_inert.time, out.v_b.Data(:,1))
plot(out.V_inert.time, out.v_b.Data(:,2))
plot(out.V_inert.time, out.v_b.Data(:,3))
legend('v_x','v_y','v_z')
xlabel('time [s]')
ylabel('velocity [m/s]')
saveas(gcf, '../Final_Report/img/m_v_b.png')

figure();
hold on;
grid on;
plot(out.V_inert.time, out.omega.Data(:,1))
plot(out.V_inert.time, out.omega.Data(:,2))
plot(out.V_inert.time, out.omega.Data(:,3))
legend('p', 'q', 'r')
xlabel('time [s]')
ylabel('angular velocity [rad/s]')
saveas(gcf, '../Final_Report/img/m_omega.png')