-- configuration file for comparing six degree of freedom model to MATLAB

-- ======================= simulation parameters ===================================
dt = 1e-4                             -- seconds
solver = 2                            -- 1: euler, 2: predictor-corrector, 3: RK4
start_time = 0.0                      -- sim start time
stop_time = 10                        -- maximum stop time
file_rate = 10                         -- frequency of plotting data
print_rate = 0                        -- frequency of writing data to screen


-- ======================== Projectile Properties ==================================
mass = 5                              -- kg, projectile mass
Ixx = 5                               -- kg m^2 moment of inertia
Iyy = 5                               -- kg m^2 moment of inertia
Izz = 5                               -- kg m^2 moment of inertia
Ixy = 1                               -- kg m^2 moment of inertia
Ixz = 0.1                             -- kg m^2 moment of inertia
Iyz = 1                               -- kg m^2 moment of inertia
sweep = 1.8                           -- radians sweep angle
cone = 0                              -- radians coning angle
pitch = 0                             -- radians pitching angle
x_ac = 7.23e-2                        -- m aerodynamic centre of projectile
nFoils = 10
cord = 4.88e-2                        -- average cord length for each 2D airfoil
arm_length = 0.3

-- =========================== Initial Conditions ====================================
vel_init   = Vector3 (0.0, 0.0 , 0.0)    -- m/s initial velocity
pos_init   = Vector3 (0.0 , 0.0 , 200.0) -- m   initial position
omega_init = Vector3 (1.0 , 0.0 , 0.0)   -- rad/s initial spin rate
euler_init = Vector3 (0.0 , 0.0, 0.0)    -- rad initial euler angles

-- ============================== Debug/Verification ==================================
do_aero = false
do_grav = 2            -- 0: no gravity, 1: gravity const in inert frame, 2: gravity const in body frame
do_DOF6_check = true   -- true: sets moments to (1, 0, 0) to match simulink. do_aero must be false.