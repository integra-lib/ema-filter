#pragma once

namespace hwlib::algorithms
{

/// Exponential moving average filter: output = alpha * input + (1 - alpha) * prev_output.
/// First call to Update() initialises without lag (output == input).
/// Call Reset() to force re-initialisation on the next Update().
class EmaFilter
{
public:
    explicit EmaFilter(float alpha) noexcept
        : m_alpha{alpha}
    {}

    EmaFilter(const EmaFilter&)            = default;
    EmaFilter& operator=(const EmaFilter&) = default;
    EmaFilter(EmaFilter&&)                 = default;
    EmaFilter& operator=(EmaFilter&&)      = default;
    ~EmaFilter()                           = default;

    [[nodiscard]] float Update(float value) noexcept
    {
        if (!m_initialized)
        {
            m_value       = value;
            m_initialized = true;
        }
        else
        {
            m_value = m_alpha * value + (1.0F - m_alpha) * m_value;
        }
        return m_value;
    }

    void Reset() noexcept
    {
        m_initialized = false;
    }

private:
    float m_alpha;
    float m_value{0.0F};
    bool m_initialized{false};
};

} // namespace hwlib::algorithms
