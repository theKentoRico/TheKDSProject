#include <optional>
#include <stdexcept>
#include <vector>

#ifndef _KDS_COMPONENT_HPP_
#define _KDS_COMPONENT_HPP_

template <typename SrcType /*The type of mSrc.at(0)*/, typename TotalType = std::vector<SrcType>> class KdsComponent
{
public:
    inline KdsComponent(TotalType src) : mSrc(std::move(src))
    {
    }

protected:
    std::optional<SrcType> Peek(int ahead = 0)
    {
        try
        {
            return mSrc.at(mIndex + ahead);
        }
        catch (std::out_of_range)
        {
            return {};
        }
    }
    SrcType Consume()
    {
        return mSrc.at(mIndex++);
    }

    TotalType mSrc;
    size_t mIndex = 0;

private:
};

#endif