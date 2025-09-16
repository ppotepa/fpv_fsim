#pragma once
#include <cmath>
#include <algorithm>
#include <stdint.h>

/**
 * @file MathUtils.h
 * @brief Comprehensive math utilities for 3D graphics, physics, and procedural generation
 *
 * Contains constants, utility functions, vector/quaternion operations, orbital mechanics,
 * random number generation, and specialized functions for the voxel busy indicator scene.
 */

namespace Math
{

    // ============================================================================
    // 1) Constants and basic utilities
    // ============================================================================

    constexpr float DegToRad = 0.017453292519943295f;
    constexpr float RadToDeg = 57.29577951308232f;
    constexpr float PI = 3.14159265358979323846f;
    constexpr float TAU = 6.28318530717958647692f; // 2*PI

    inline float saturate(float x) { return (std::min)(1.f, (std::max)(0.f, x)); }
    inline float clamp(float x, float a, float b) { return (std::min)(b, (std::max)(a, x)); }
    inline float lerp(float a, float b, float t) { return a + (b - a) * t; }
    inline float invLerp(float a, float b, float x) { return (x - a) / (b - a); }
    inline float remap(float i0, float i1, float o0, float o1, float x)
    {
        return lerp(o0, o1, saturate(invLerp(i0, i1, x)));
    }

    inline float smoothstep(float a, float b, float x)
    {
        float t = saturate(invLerp(a, b, x));
        return t * t * (3.f - 2.f * t);
    }

    inline float smootherstep(float a, float b, float x)
    {
        float t = saturate(invLerp(a, b, x));
        return t * t * t * (t * (6.f * t - 15.f) + 10.f);
    }

    // ============================================================================
    // 2) Random & hashing (deterministic per seed)
    // ============================================================================

    /**
     * @brief PCG-like quick hash function for deterministic random generation
     * @param x Input value to hash
     * @return Hashed 32-bit unsigned integer
     */
    inline uint32_t hash_u32(uint32_t x)
    {
        x ^= x >> 16;
        x *= 0x7feb352dU;
        x ^= x >> 15;
        x *= 0x846ca68bU;
        x ^= x >> 16;
        return x;
    }

    /**
     * @brief Generate random float in [0,1) range using hash-based PRNG
     * @param state Reference to PRNG state (modified)
     * @return Random float in [0,1) range
     */
    inline float rand01(uint32_t &state)
    {
        state = hash_u32(state);
        return (state >> 8) * (1.f / 16777216.f); // 24-bit mantissa
    }

    /**
     * @brief Sample from exponential distribution for Poisson inter-arrival times
     * @param u Uniform random value in [0,1)
     * @param lambda Rate parameter (events per unit time)
     * @return Time until next event
     */
    inline float sample_exponential(float u, float lambda)
    {
        return -std::log((std::max)(u, 1e-7f)) / lambda;
    }

    // ============================================================================
    // 3) Vector operations
    // ============================================================================

    /**
     * @brief 2D vector structure with basic operations
     */
    struct float2
    {
        float x, y;

        float2() : x(0), y(0) {}
        float2(float x_, float y_) : x(x_), y(y_) {}

        float2 operator+(const float2 &other) const { return {x + other.x, y + other.y}; }
        float2 operator-(const float2 &other) const { return {x - other.x, y - other.y}; }
        float2 operator*(float s) const { return {x * s, y * s}; }
        float2 &operator+=(const float2 &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }
    };

    /**
     * @brief 3D vector structure with basic operations
     */
    struct float3
    {
        float x, y, z;

        float3() : x(0), y(0), z(0) {}
        float3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

        float3 operator+(const float3 &other) const { return {x + other.x, y + other.y, z + other.z}; }
        float3 operator-(const float3 &other) const { return {x - other.x, y - other.y, z - other.z}; }
        float3 operator*(float s) const { return {x * s, y * s, z * s}; }
        float3 &operator+=(const float3 &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
    };

    /**
     * @brief 4D vector structure with basic operations (useful for quaternions and colors)
     */
    struct float4
    {
        float x, y, z, w;

        float4() : x(0), y(0), z(0), w(0) {}
        float4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}

        float4 operator+(const float4 &other) const { return {x + other.x, y + other.y, z + other.z, w + other.w}; }
        float4 operator-(const float4 &other) const { return {x - other.x, y - other.y, z - other.z, w - other.w}; }
        float4 operator*(float s) const { return {x * s, y * s, z * s, w * s}; }
        float4 &operator+=(const float4 &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }
    };

    inline float2 add(const float2 &a, const float2 &b) { return {a.x + b.x, a.y + b.y}; }
    inline float2 sub(const float2 &a, const float2 &b) { return {a.x - b.x, a.y - b.y}; }
    inline float2 mul(const float2 &a, float s) { return {a.x * s, a.y * s}; }
    inline float dot(const float2 &a, const float2 &b) { return a.x * b.x + a.y * b.y; }
    inline float length(const float2 &v) { return std::sqrt(v.x * v.x + v.y * v.y); }
    inline float2 normalize(const float2 &v)
    {
        float len = length(v);
        return len > 1e-6f ? mul(v, 1.0f / len) : float2{0, 0};
    }

    inline float4 add(const float4 &a, const float4 &b) { return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }
    inline float4 sub(const float4 &a, const float4 &b) { return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }
    inline float4 mul(const float4 &a, float s) { return {a.x * s, a.y * s, a.z * s, a.w * s}; }
    inline float dot(const float4 &a, const float4 &b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
    inline float length(const float4 &v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
    inline float4 normalize(const float4 &v)
    {
        float len = length(v);
        return len > 1e-6f ? mul(v, 1.0f / len) : float4{0, 0, 0, 0};
    }

    inline float3 add(const float3 &a, const float3 &b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
    inline float3 sub(const float3 &a, const float3 &b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
    inline float3 mul(const float3 &a, float s) { return {a.x * s, a.y * s, a.z * s}; }
    inline float dot(const float3 &a, const float3 &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
    inline float3 cross(const float3 &a, const float3 &b)
    {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }
    inline float len(const float3 &v) { return std::sqrt(dot(v, v)); }
    inline float lengthSq(const float3 &v) { return dot(v, v); }
    inline float3 norm(const float3 &v)
    {
        float L = len(v);
        return (L > 0) ? mul(v, 1.f / L) : float3{0, 0, 0};
    }
    inline float3 normalize(const float3 &v)
    {
        return norm(v);
    }

    // ============================================================================
    // 4) Quaternion operations
    // ============================================================================

    /**
     * @brief Quaternion structure for 3D rotations
     */
    struct quat
    {
        float w, x, y, z;

        quat() : w(1), x(0), y(0), z(0) {}
        quat(float w_, float x_, float y_, float z_) : w(w_), x(x_), y(y_), z(z_) {}

        static quat identity() { return quat(1, 0, 0, 0); }
    };

    /**
     * @brief Create quaternion from axis-angle representation
     * @param axis Rotation axis (will be normalized)
     * @param angleRad Rotation angle in radians
     * @return Quaternion representing the rotation
     */
    inline quat q_from_axis_angle(const float3 &axis, float angleRad)
    {
        float3 u = norm(axis);
        float s = std::sin(angleRad * 0.5f);
        return {std::cos(angleRad * 0.5f), u.x * s, u.y * s, u.z * s};
    }

    /**
     * @brief Rotate vector by quaternion
     * @param q Rotation quaternion
     * @param v Vector to rotate
     * @return Rotated vector
     */
    inline float3 q_rotate(const quat &q, const float3 &v)
    {
        // v' = q * (0,v) * q^-1
        float3 u = {q.x, q.y, q.z};
        float s = q.w;
        float3 t = mul(cross(u, v), 2.f);
        return add(add(v, mul(t, s)), cross(u, t));
    }

    /**
     * @brief Multiply two quaternions
     * @param a First quaternion
     * @param b Second quaternion
     * @return Product quaternion a * b
     */
    inline quat q_mul(const quat &a, const quat &b)
    {
        return {
            a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
            a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
            a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
            a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w};
    }

    /**
     * @brief Create look-at rotation quaternion
     * @param forward Forward direction (will be normalized)
     * @param up Up direction (will be normalized)
     * @return Quaternion representing the orientation
     */
    inline quat q_look_rotation(const float3 &forward, const float3 &up)
    {
        float3 f = norm(forward);
        float3 r = norm(cross(up, f));
        float3 u = cross(f, r);

        // Convert 3x3 rotation matrix to quaternion
        float m00 = r.x, m01 = u.x, m02 = f.x;
        float m11 = u.y, m22 = f.z;
        float trace = m00 + m11 + m22;

        quat q;
        if (trace > 0.f)
        {
            float s = std::sqrt(trace + 1.f) * 2.f; // s = 4 * qw
            q.w = 0.25f * s;
            q.x = (u.z - f.y) / s;
            q.y = (f.x - r.z) / s;
            q.z = (r.y - u.x) / s;
        }
        else
        {
            // Handle other cases - simplified for now
            q.w = 0.5f;
            q.x = 0.5f;
            q.y = 0.0f;
            q.z = 0.0f;
        }
        return q;
    }

    // ============================================================================
    // 5) Matrix operations (4x4 for camera transforms)
    // ============================================================================

    /**
     * @brief 4x4 transformation matrix
     */
    struct float4x4
    {
        float m[4][4];

        float4x4()
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    m[i][j] = (i == j) ? 1.0f : 0.0f;
                }
            }
        }
    };

    /**
     * @brief Create look-at view matrix (right-handed, +Y up, -Z forward)
     * @param eye Camera position
     * @param target Look-at target
     * @param up Up direction
     * @return View transformation matrix
     */
    inline float4x4 lookAt(const float3 &eye, const float3 &target, const float3 &up)
    {
        float3 f = norm(sub(target, eye)); // forward
        float3 r = norm(cross(f, up));     // right
        float3 u = cross(r, f);            // corrected up

        float4x4 M{};
        M.m[0][0] = r.x;
        M.m[0][1] = u.x;
        M.m[0][2] = -f.x;
        M.m[0][3] = 0;
        M.m[1][0] = r.y;
        M.m[1][1] = u.y;
        M.m[1][2] = -f.y;
        M.m[1][3] = 0;
        M.m[2][0] = r.z;
        M.m[2][1] = u.z;
        M.m[2][2] = -f.z;
        M.m[2][3] = 0;
        M.m[3][0] = -dot(r, eye);
        M.m[3][1] = -dot(u, eye);
        M.m[3][2] = dot(f, eye);
        M.m[3][3] = 1;
        return M;
    }

    // ============================================================================
    // 6) Orbital mechanics utilities
    // ============================================================================

    /**
     * @brief Parameters for elliptical orbit calculation
     */
    struct OrbitParams
    {
        float semiMajorAxis; // a: semi-major axis
        float eccentricity;  // e: eccentricity [0,1)
        float inclination;   // i: inclination angle (radians)
        float angularRate;   // ω: angular rate (rad/s)
        float phaseOffset;   // φ₀: initial phase offset

        OrbitParams() : semiMajorAxis(1.0f), eccentricity(0.0f), inclination(0.0f),
                        angularRate(1.0f), phaseOffset(0.0f) {}
    };

    /**
     * @brief Calculate position on elliptical orbit
     * @param params Orbital parameters
     * @param time Current time
     * @return 3D position on orbit
     */
    inline float3 calculateOrbitPosition(const OrbitParams &params, float time)
    {
        float a = params.semiMajorAxis;
        float e = params.eccentricity;
        float b = a * (1.f - e); // semi-minor axis (simplified)
        float omega = params.angularRate;
        float i = params.inclination;
        float phi = omega * time + params.phaseOffset;

        // Ellipse in XZ plane
        float xP = a * std::cos(phi);
        float zP = b * std::sin(phi);

        // Rotate about X by inclination
        float x = xP;
        float y = -std::sin(i) * zP;
        float z = std::cos(i) * zP;

        return {x, y, z};
    }

    /**
     * @brief Calculate velocity on elliptical orbit
     * @param params Orbital parameters
     * @param time Current time
     * @return 3D velocity vector
     */
    inline float3 calculateOrbitVelocity(const OrbitParams &params, float time)
    {
        float a = params.semiMajorAxis;
        float e = params.eccentricity;
        float b = a * (1.f - e);
        float omega = params.angularRate;
        float i = params.inclination;
        float phi = omega * time + params.phaseOffset;

        // Velocity in XZ plane
        float vxP = -a * omega * std::sin(phi);
        float vzP = b * omega * std::cos(phi);

        // Rotate about X by inclination
        float vx = vxP;
        float vy = -std::sin(i) * vzP;
        float vz = std::cos(i) * vzP;

        return {vx, vy, vz};
    }

    /**
     * @brief Calculate banking angle for coordinated turn
     * @param velocity Current velocity vector
     * @param position Current position vector (for turn radius calculation)
     * @param maxBank Maximum banking angle (radians)
     * @return Banking angle in radians
     */
    inline float calculateBankingAngle(const float3 &velocity, const float3 &position, float maxBank = 15.f * DegToRad)
    {
        float3 Vh = {velocity.x, 0.f, velocity.z}; // horizontal velocity
        float3 Ph = {position.x, 0.f, position.z}; // horizontal position

        float speedH = len(Vh);
        if (speedH < 1e-4f)
            return 0.f;

        // Yaw rate calculation
        float yawRate = (velocity.x * position.z - velocity.z * position.x) / (Ph.x * Ph.x + Ph.z * Ph.z);

        // Coordinated turn banking
        float speed = len(velocity);
        float g = 9.81f;
        float bank = std::atan2(speed * yawRate, g);

        return clamp(bank, -maxBank, maxBank);
    }

    // ============================================================================
    // 7) Procedural generation utilities
    // ============================================================================

    /**
     * @brief Generate procedural texture noise value
     * @param x X coordinate
     * @param y Y coordinate
     * @param seed Random seed
     * @param amplitude Noise amplitude
     * @return Noise value
     */
    inline float proceduralNoise(int x, int y, uint32_t seed, float amplitude)
    {
        uint32_t state = hash_u32(seed + x * 73856093u + y * 19349663u);
        return (rand01(state) - 0.5f) * amplitude;
    }

    /**
     * @brief Check if pixel should be speckled based on density
     * @param x X coordinate
     * @param y Y coordinate
     * @param seed Random seed
     * @param density Speckle density [0,1]
     * @return True if pixel should be speckled
     */
    inline bool shouldSpeckle(int x, int y, uint32_t seed, float density)
    {
        uint32_t state = hash_u32(seed + x * 73856093u + y * 19349663u);
        return rand01(state) < density;
    }

    // ============================================================================
    // 8) Cel-shading utilities
    // ============================================================================

    /**
     * @brief Calculate cel-shaded lighting with band quantization
     * @param normal Surface normal (world space)
     * @param lightDir Light direction (from surface to light, normalized)
     * @param bands Number of shading bands
     * @return Shading factor [0,1]
     */
    inline float calculateCelShading(const float3 &normal, const float3 &lightDir, int bands = 4)
    {
        float NdotL = saturate(dot(normal, lightDir));

        // Band quantization
        float qIdx = std::floor(NdotL * bands);
        float qVal = (qIdx + 0.5f) / bands; // mid-band value

        return qVal;
    }

    /**
     * @brief Calculate rim lighting effect
     * @param normal Surface normal (world space)
     * @param viewDir View direction (from surface to camera, normalized)
     * @param power Rim falloff power
     * @return Rim lighting factor [0,1]
     */
    inline float calculateRimLighting(const float3 &normal, const float3 &viewDir, float power = 2.f)
    {
        return std::pow(1.f - saturate(dot(normal, viewDir)), power);
    }

    // ============================================================================
    // 9) Lifecycle and fade utilities
    // ============================================================================

    /**
     * @brief Calculate piecewise fade curve
     * @param t Current time
     * @param t0 Start time (0 alpha)
     * @param t1 Fade in complete time (1 alpha)
     * @param t2 Fade out start time (1 alpha)
     * @param t3 End time (0 alpha)
     * @return Alpha value [0,1]
     */
    inline float alpha_piecewise(float t, float t0, float t1, float t2, float t3)
    {
        if (t <= t0)
            return 0.f;
        if (t < t1)
            return smoothstep(t0, t1, t);
        if (t <= t2)
            return 1.f;
        if (t < t3)
            return 1.f - smoothstep(t2, t3, t);
        return 0.f;
    }

    /**
     * @brief Calculate exponential fade for contrails
     * @param elapsedTime Time since spawn
     * @param lifetime Total lifetime
     * @return Alpha value [0,1]
     */
    inline float alpha_contrail(float elapsedTime, float lifetime)
    {
        float s = saturate(1.f - elapsedTime / lifetime);
        return s * s; // quadratic falloff
    }

} // namespace Math
