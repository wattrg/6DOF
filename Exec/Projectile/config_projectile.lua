-- configuration file for projectile motion

-- ======================= simulation parameters ===================================
dt = 1e-2                             -- seconds
solver = 1                            -- 1: euler, 2: predictor-corrector, 3: RK4
start_time = 0.0                      -- sim start time
stop_time = 5                        -- maximum stop time
file_rate = 10                       -- frequency of plotting data
print_rate = 0                        -- frequency of writing data to screen


-- ======================== Projectile Properties ==================================
mass = 0.13                           -- kg, projectile mass
Ixx = 1.9e-3                          -- kg m^2 moment of inertia
Iyy = 4.88e-6                         -- kg m^2 moment of inertia
Izz = 1.9e-3                          -- kg m^2 moment of inertia
Ixy = 5.14e-21                        -- kg m^2 moment of inertia
Ixz = 5.14e-21                        -- kg m^2 moment of inertia
Iyz = 5.14e-21                        -- kg m^2 moment of inertia
sweep = 1.8                           -- radians sweep angle
cone = 0                              -- radians coning angle
pitch = 0                             -- radians pitching angle
x_ac = 7.23e-2                        -- m aerodynamic centre of projectile
nFoils = 10
cord = 4.88e-2                        -- average cord length for each 2D airfoil
arm_length = 0.3

-- =========================== Initial Conditions ====================================
vel_init   = Vector3 (25.0, 0.0 , 0.0) -- m/s initial velocity
pos_init   = Vector3 (0.0 , 0.0 , 2.0) -- m   initial position
omega_init = Vector3 (0.0 , 0.0 , 0.0) -- rad/s initial spin rate
euler_init = Vector3 (0.0 , -0.3, 0.0) -- rad initial euler angles

-- ============================== Debug/Verification ==================================
do_aero = false
do_grav = 1
do_DOF6_check = false
